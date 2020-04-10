set title "Comparacion K frente N"
set key top left vertical inside
set grid
set xlabel "variable cambiante(n[lila] y k[verde])"
set ylabel "Tiempo(sec)"
plot "mezcla_k50_n100_2000.dat" using 1:2 with lp, "mezcla_n50_k100_2000.dat" using 1:2 with lp
#CUBO(x) = a*x*x*x + b*x*x + c*x + d
#fit CUBO(x) "floyd.dat" using 1:2 via a,b,c,d
#plot "floyd.dat" using 1:2 title "floyd" , CUBO(x)
set terminal pdf
set output "Comparacion.pdf"
replot
pause 5 "Pulsa enter para continuar..."