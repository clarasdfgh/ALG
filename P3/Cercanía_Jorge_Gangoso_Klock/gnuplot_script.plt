set title "TSP óptimo"
set key top left vertical inside
set grid
set xlabel "coordenada_x"
set ylabel "coordenada_y"
plot "ulysses22.opt.tour" using 2:3 with lines
set terminal pdf
set output "ulysses22_optimo.pdf"
replot
pause 5 "Pulsa enter para continuar..."