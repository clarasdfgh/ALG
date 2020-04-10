#!/bin/bash
for ((nvectores=1000;nvectores<=25000;nvectores=nvectores+1000))
do
  echo -e "\n  - Para $nvectores vectores:"
   ./mezcla 50 $nvectores >> mezcla.dat
done