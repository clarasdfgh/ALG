#!/bin/bash
for ((tamano=100;tamano<=2000;tamano=tamano+100))
do
  echo -e "\n  - Para tamano vectores:"
   ./mezcla $tamano 50 >> mezcla.dat
done