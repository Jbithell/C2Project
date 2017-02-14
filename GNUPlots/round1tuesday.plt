set terminal png size 1000,707
set output 'output.png'
set title "C2 Project - Data for Tuesday 24 January (Saturday Timetable)"
set ylabel "Position (relative)"
set xlabel "Time"

set xdata time
set timefmt '%H:%M:%S'

#plot "../data/round1tuesday.dat" using 1:2 title 'X'
plot     "../data/round1tuesday.dat" using 1:3 title 'Y'
#     "../data/round1tuesday.dat" using 1:4 title 'Z'
