set title "Mezcla N vectores"
set key top left vertical inside
set grid
set xlabel "tamano vector(n)"
set ylabel "Tiempo(sec)"
plot "mezcla_k50_n100_2000.dat" using 1:2 with lp
#Nlogn(x) = a*50*x*log(x)+b
#fit Nlogn(x) "mezcla_n50_k100_2000.dat" using 1:2 via a, b
#plot "mezcla_n50_k100_2000.dat" using 1:2 title "Mezcla K vectores" , Nlogn(x)
set terminal pdf
set output "Mezcla_N.pdf"
replot
pause 5 "Pulsa enter para continuar..."