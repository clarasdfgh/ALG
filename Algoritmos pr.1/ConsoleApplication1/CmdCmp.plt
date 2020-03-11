set title " Comparacion tiempos mergesort y quicksort"
set key top left vertical inside
set grid
set xlabel "Talla(n)"
set ylabel "Tiempo(ms)"
plot "mergesort.dat" using 1:2 with lines title "mergesort","quicksort.dat" using 1:2 with lines title "quicksort"
set terminal pdf
set output "mergesortquicksort.pdf"
replot
pause 5 "Pulsa Enter para continuar"
