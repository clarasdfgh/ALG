#!/bin/bash

echo "" > burb0.dat
echo "" > burb1.dat
echo "" > burb2.dat
echo "" > burb3.dat
let i=100
while [ $i -le 2500 ];do
  echo $i
  ./burbujaSIN  $i >> burb0.dat
  ./burbujaO1	 $i >> burb1.dat
  ./burbujaO2	 $i >> burb2.dat
  ./burbujaO3	 $i >> burb3.dat
  let i=$i+100
done

echo "" > ins0.dat
echo "" > ins1.dat
echo "" > ins2.dat
echo "" > ins3.dat
let i=100
while [ $i -le 2500 ];do
  echo $i
	./insercionSIN   $i >> ins0.dat
   ./insercionO1	 $i >> ins1.dat
   ./insercionO2	 $i >> ins2.dat
   ./insercionO3	 $i >> ins3.dat
  let i=$i+100
done

echo "" > sel0.dat
echo "" > sel1.dat
echo "" > sel2.dat
echo "" > sel3.dat
let i=100
while [ $i -le 2500 ];do
  echo $i
  ./seleccionSIN   $i >> sel0.dat
  ./seleccionO1	 $i >> sel1.dat
  ./seleccionO2	 $i >> sel2.dat
  ./seleccionO3	 $i >> sel3.dat
  let i=$i+100
done

echo "" > merge0.dat
echo "" > merge1.dat
echo "" > merge2.dat
echo "" > merge3.dat
let i=100
while [ $i -le 2500 ];do
  echo $i
  ./mergeSIN   $i >> merge0.dat
  ./mergeO1	 	$i >> merge1.dat
  ./mergeO2		$i >> merge2.dat
  ./mergeO3		$i >> merge3.dat
  let i=$i+100
done

echo "" > heap0.dat
echo "" > heap1.dat
echo "" > heap2.dat
echo "" > heap3.dat
let i=100
while [ $i -le 2500 ];do
  echo $i
  ./heapSIN		$i >> heap0.dat
  ./heapO1		$i >> heap1.dat
  ./heapO2		$i >> heap2.dat
  ./heapO3		$i >> heap3.dat
  let i=$i+100
done

echo "" > quick0.dat
echo "" > quick1.dat
echo "" > quick2.dat
echo "" > quick3.dat
let i=100
while [ $i -le 2500 ];do
  echo $i
  ./quickSIN	$i >> quick0.dat
  ./quickO1		$i >> quick1.dat
  ./quickO2		$i >> quick2.dat
  ./quickO3		$i >> quick3.dat
  let i=$i+100
done
