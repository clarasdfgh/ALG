/* 
 *Clase Graficas, contiene métodos crear los ficheros de comandos para dibujar 
 * la gráfica que corresponda. 
 */
#include "Graficas.h"
#include <fstream>
#include <iostream>
#include "Constantes.h"
using namespace std;


/*
 * Método generarGraficaMEDIO, genera el fichero de comandos para GNUPlot 
 * y dibuja la gráfica del caso medio de un método de
 * ordenación y su ajuste a la función correspondiente.  
 * param nombre_metodo: metodo de ordenacion.
 * param orden: Orden del metodo de ordenacion.
 */
void Graficas::generarGraficaMEDIO(string nombre_metodo,int ordenes)
{
//** ESCRIBIR PARA COMPLETAR LA PRACTICA **//
	char sel;
	cout << "Desea graficar los resultados?(s/n): ";
	cin >> sel;
	if (sel == 's')
	{
		string ordenf;
		string formula;
		string via;
		string tiempo;
		switch (ordenes)
		{
		case LOGN:
			ordenf = "Log(x)";
			formula = "a*log(x) + b";
			via = "a,b";
			tiempo = "ms";
			break;
		case N:
			ordenf = "N(x)";
			formula = "a*x";
			via = "a";
			tiempo = "ms";
			break;
		case NLOGN:
			ordenf = "NlogN(x)";
			formula = "a*x*log(x) + b*x + c";
			via = "a,b,c";
			tiempo = "ms";
			break;
		case CUADRADO:
			ordenf = "CUADRADO(x)";
			formula = "a*x*x + b*x + c";
			via = "a,b,c";
			tiempo = "ms";
			break;
		case CUBO:
			ordenf = "CUBO(x)";
			formula = "a*x*x*x + b*x*x + c*x + d";
			via = "a,b,c,d";
			tiempo = "ms";
			break;
		case EXPO:
			ordenf = "EXPO(x)";
			formula = "a*(1.618**x)";
			via = "a";
			tiempo = "sec";
			break;
		default:
			cout << "No se encontro el orden de complejidad" << endl;
			
		}
		string nom = nombre_metodo + ".dat";
		string nompdf = nombre_metodo + ".pdf";
			ofstream CmdMedio("CmdMedio.plt");
			CmdMedio << "set title \"Tiempo medio de " << nombre_metodo << "\"" << endl
				<< "set key top left vertical inside" << endl
				<< "set grid" << endl
				<< "set xlabel \"Talla(n)\"" << endl
				<< "set ylabel \"Tiempo(" << tiempo <<")\"" << endl
				<< "plot \"" << nom << "\" using 1:2 " << endl
				<< ordenf << " = " << formula << endl
				<< "fit " << ordenf << " \"" << nom << "\" using 1:2 via " << via << endl
				<< "plot \"" << nom << "\" using 1:2 title \"" << nombre_metodo << "\" , " << ordenf << endl
				<< "set terminal pdf" << endl
				<< "set output \"" << nompdf << "\"" << endl
				<< "replot" << endl
				<< "pause 5 \"Pulsa enter para continuar...\"" << endl;
			CmdMedio.close();
			system("CmdMedio.plt");
	}

}	

/*
 * Método generarGraficaCMP, genera el fichero de comandos para GNUPlot.
 * param nombre1: es el nombre del fichero de datos del primer método de ordenación 
 * param nombre2: es el nombre del fichero de datos del segundo método de ordenación 
 */
void  Graficas::generarGraficaCMP(string nombre1,string nombre2)
{
//** ESCRIBIR PARA COMPLETAR LA PRACTICA **//
	char sel;
	cout << "Desea graficar los resultados?(s/n): ";
	cin >> sel;
	if (sel == 's')
	{
		string nom1 = nombre1 + ".dat";
		string nom2 = nombre2 + ".dat";
		string nomf = nombre1 + nombre2 + ".pdf";
		ofstream CmdCmp("CmdCmp.plt");
		CmdCmp << "set title \" Comparacion tiempos " << nombre1 << " y " << nombre2 << "\"" << endl
			<< "set key top left vertical inside" << endl
			<< "set grid" << endl
			<< "set xlabel \"Talla(n)\"" << endl
			<< "set ylabel \"Tiempo(ms)\"" << endl
			<< "plot \"" << nom1 << "\" using 1:2 with lines title \"" << nombre1 << "\"" << ",\"" << nom2 << "\" using 1:2 with lines title \"" << nombre2 << "\"" << endl
			<< "set terminal pdf" << endl
			<< "set output \"" << nomf << "\"" << endl
			<< "replot" << endl
			<< "pause 5 \"Pulsa Enter para continuar\"" << endl;
		CmdCmp.close();
		system("CmdCmp.plt");
	}
}