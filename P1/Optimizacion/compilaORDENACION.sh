#!/bin/bash

g++ burbuja.cpp -o burbujaSIN
g++ -O1 burbuja.cpp -o burbujaO1
g++ -O2 burbuja.cpp -o burbujaO2
g++ -O3 burbuja.cpp -o burbujaO3

g++ insercion.cpp -o insercionSIN
g++ -O1 insercion.cpp -o insercionO1
g++ -O2 insercion.cpp -o insercionO2
g++ -O3 insercion.cpp -o insercionO3

g++ seleccion.cpp -o seleccionSIN
g++ -O1 seleccion.cpp -o seleccionO1
g++ -O2 seleccion.cpp -o seleccionO2
g++ -O3 seleccion.cpp -o seleccionO3

g++ mergesort.cpp -o mergeSIN
g++ -O1 mergesort.cpp -o mergeO1
g++ -O2 mergesort.cpp -o mergeO2
g++ -O3 mergesort.cpp -o mergeO3

g++ heapsort.cpp -o heapSIN
g++ -O1 heapsort.cpp -o heapO1
g++ -O2 heapsort.cpp -o heapO2
g++ -O3 heapsort.cpp -o heapO3

g++ quicksort.cpp -o quickSIN
g++ -O1 quicksort.cpp -o quickO1
g++ -O2 quicksort.cpp -o quickO2
g++ -O3 quicksort.cpp -o quickO3
