set title "Tiempo medio de fibonacci"
set key top left vertical inside
set grid
set xlabel "Talla(n)"
set ylabel "Tiempo(sec)"
plot "fibonacci.dat" using 1:2 
EXPO(x) = a*(1.618**x)
fit EXPO(x) "fibonacci.dat" using 1:2 via a
plot "fibonacci.dat" using 1:2 title "fibonacci" , EXPO(x)
set terminal pdf
set output "fibonacci.pdf"
replot
pause 5 "Pulsa enter para continuar..."
