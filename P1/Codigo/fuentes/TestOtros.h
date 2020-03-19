#ifndef _TEST_OTROS
#define _TEST_OTROS

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "Graficas.h"
using namespace std;

#define sangria "\t\t"
#define linea "\n\n"

class TestOtros {
	vector<string> nombreAlgoritmo;
public:

	TestOtros();
	~TestOtros();
	/*
	 * Ordena un array de enteros según el método indicado
	 * param v: el array de enteros a ordenar
	 * param size: tamaño del array de enteros a ordenar
	 * param metodo: Metodo de ordenacion a utilizar
	 * return Tiempo empleado en la ordenación (en milisegundos)
	 */
	void casoMedio(int metodo);

	/*Aqui no hay que hacer nada*/
};
#endif