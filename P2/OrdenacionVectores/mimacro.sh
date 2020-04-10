#!/bin/bash
let n=50
let k=100
while [ $k -le 2000 ];do
  echo $k
  ./ordenaVectores $n $k >> salidaAumentaPrueba.dat
  let k=$k+100
done
