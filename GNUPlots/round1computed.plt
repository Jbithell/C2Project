set terminal png size 6000,2000
set output 'output.png'
set title "C2 Project - Round 1 Data Computed Output"
set ylabel "Magnitude SUM"
set xlabel "Time (hours)"
plot "../data/round1computed.dat" using 1:2 title ''
