set terminal png size 4000,1414
set output '../graphs/round1computed.png'
set title "C2 Project - Round 1 Data Computed Output"
set ylabel "Magnitude SUM"
set xlabel "Time (hours)"
plot "../data/round1computed.dat" using 1:($2 >200 ? $2 : 1/0) title ''
