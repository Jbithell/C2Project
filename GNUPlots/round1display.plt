set terminal png size 2000,1414
set output 'output.png'
set title "C2 Project - Round 1 Data"
set ylabel "Position (relative)"
set xlabel "Time (hours)"
plot "../data/round1.dat" using 1:2 title 'X', \
     "../data/round1.dat" using 1:3 title 'Y', \
     "../data/round1.dat" using 1:4 title 'Z'
