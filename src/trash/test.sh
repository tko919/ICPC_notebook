S=$1.cpp
O=$1.out
T=test.in

g++ -std=c++17 $S -Wall -g -O0 -o $O && ./$O < $T