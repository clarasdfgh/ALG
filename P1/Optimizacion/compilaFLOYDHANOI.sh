#!/bin/bash

g++ floyd.cpp -o floydSIN
g++ -O1 floyd.cpp -o floydO1
g++ -O2 floyd.cpp -o floydO2
g++ -O3 floyd.cpp -o floydO3

g++ hanoi.cpp -o hanoiSIN
g++ -O1 hanoi.cpp -o hanoiO1
g++ -O2 hanoi.cpp -o hanoiO2
g++ -O3 hanoi.cpp -o hanoiO3
