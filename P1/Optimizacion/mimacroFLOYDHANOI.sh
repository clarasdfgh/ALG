#!/bin/bash

echo "" > floyd0.dat
echo "" > floyd1.dat
echo "" > floyd2.dat
echo "" > floyd3.dat
let i=100
while [ $i -le 2500 ];do
  echo $i
  ./floydSIN $i >> floyd0.dat
  ./floydO1	 $i >> floyd1.dat
  ./floydO2	 $i >> floyd2.dat
  ./floydO3	 $i >> floyd3.dat
  let i=$i+100
done

echo "" > hanoi0.dat
echo "" > hanoi1.dat
echo "" > hanoi2.dat
echo "" > hanoi3.dat
let i=0
while [ $i -le 36 ];do
  echo $i
	 ./hanoiSIN  $i >> hanoi0.dat
   ./hanoiO1	 $i >> hanoi1.dat
   ./hanoiO2	 $i >> hanoi2.dat
   ./hanoiO3	 $i >> hanoi3.dat
  let i=$i+1
done
