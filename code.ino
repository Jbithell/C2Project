
/* ###########################################################
 * Arduino Accelerometer Project
 * 06/02/2017
 * ----------------------------------------------------------
 * James Bithell & William Ashton
 * C2 Physics project
 *  
 * -----------------------LCD--------------------------------
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K variable resistor: ends to +5V and ground and wiper to LCD VO pin
 *  
 * ---------------------SD CARD-----------------------------  
 * SD card attached to SPI bus as follows:
 * MOSI   -   pin 11
 * MISO   -   pin 12
 * CLK    -   pin 13 - also SD operation LED
 * CS     -   pin 10
 * 
 * -------------------ACCELEROMTER---------------------------
 * SCL    -   analogue pin 5   
 * SDA    -   analogue pin 4
 * 
*/


#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <SD.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 
// initialize the LCD library with the numbers of the interface pins
// float V = 0; // Computed voltage from input pin 0 AD converter
unsigned long Time = 0; // Becomes number of seconds since power up 

String dataString = ""; 
Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  //Setup Accelerometer
  Serial.begin(9600);
  
  Serial.println("Adafruit MMA8451 test!");
  
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");


  //Setup Screen
  pinMode(10,OUTPUT); //CS pin on the SD
  Serial.begin(9600); 
  lcd.begin(16, 2); 
  lcd.print("      JBWA");  
  lcd.setCursor(0,1);
  lcd.print("     Logger");
  delay(2000); //wait two seconds
  lcd.clear(); //clear LCD
    
  if (SD.begin(10)) {    // see if the card is present initialize
      dataString = "START,"; // make a string for assembling the data to log:
      File dataFile = SD.open("data.txt", FILE_WRITE); // open the file. 
        if (dataFile) { // if the file is available, write to it:
        dataFile.println(dataString);
        dataFile.close();
        lcd.print("Micro SD Card"); //and display a message
        lcd.setCursor(0,1);   
        lcd.print("initialised");
        delay(2000); //wait two seconds
        lcd.clear(); //clear LCD
      }
  }
}

void loop() {
  mma.read();
  sensors_event_t event; 
  mma.getEvent(&event);
  
  if (millis()/100  > Time) { //Do everything below once a 1/10th of a second
    Time = millis()/100; //Time in tenths of seconds since power up  
    dataString = "" ;
    
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("Logging | ");
    lcd.print(mma.x);
    lcd.setCursor(0,1);
    lcd.print(mma.y);
    lcd.print(" | ");
    lcd.print(mma.z);
    //It's best to plot the sum of the three values as it gives you the most sensible data with some jitter
    dataString += millis();
    dataString += ",";
    dataString += mma.x;
    dataString += ",";
    dataString += mma.y;
    dataString += ",";
    dataString += mma.z;
    dataString += "\r\n";
   
    File dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.print(dataString);
      dataFile.close();
    }
  }
  
}



