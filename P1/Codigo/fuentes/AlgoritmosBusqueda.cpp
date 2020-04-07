
/*
 * Clase AlgoritmosBusqueda que implementa los Algoritmos de Búsqueda para buscar un elemento en un vector de enteros.
 * Define las implementaciones de los siguientes métodos de búsqueda
 * de búsqueda en vectores:
 *	- Secuencial
 *	- Binaria o dicotómica
 *  - Ternaria
 */

#include "AlgoritmosBusqueda.h"


/*
 * Implementación de los métodos de la clase AlgoritmosBusqueda
 */
AlgoritmosBusqueda::AlgoritmosBusqueda() { }
AlgoritmosBusqueda:: ~AlgoritmosBusqueda() { }

/*
	 * Función busquedaSecuencialIt, implementa el método de búsqueda secuencial Iterativo
	 * param v: el array de enteros donde buscar
	 * param size: tamaño del array
	 * param key: clave o elemento a buscar
	 * return posición de la clave en el array
	 */
int AlgoritmosBusqueda::busquedaSecuencialIt(int v[], int size,int key)
{
	int i = 0;
	while (v[i] != key && i <= size)
	{
		i++;
	}
	if (v[i] == key)
	{
		return i;
	}
	else return -1;
}
/*modificacion*/
int AlgoritmosBusqueda::BusquedaSecuencialRc(int v[], int size, int key)
{
	if (size != 0)
	{
		if (v[size - 1] == key)
		{
			return (size - 1);
		}
		else
		{
			return BusquedaSecuencialRc(v, size - 1, key);
		}
	}
	else return -1;
}



/*
	 * Función busquedaBinariaRc, implementa el método de búsqueda binaria Recursivo
	 * param v: el array de enteros donde buscar
	 * param size: tamaño del array
	 * param key: clave o elemento a buscar
	 * return posición de la clave en el array
	 */
   
int AlgoritmosBusqueda::busquedaBinariaRc(int v[], int size,int key)
{
	return BinariaRc(v, 0, size - 1, key);
}

int AlgoritmosBusqueda::BinariaRc(int v[], int left, int right, int key)
{
	if (right >= left)
	{
		int M = (left + right) / 2;
		if (v[M] == key)
			return M;
		else if (v[M] < key)
			return BinariaRc(v, M + 1, right, key);
		else
			return BinariaRc(v, left, M - 1, key);
	}
	return -1;
}
	
/*
	 * Función busquedaTernariaRc, implementa el método de búsqueda ternaria recursiva
	 * param v: el array de enteros donde buscar
	 * param size: tamaño del array
	 * param key: clave o elemento a buscar
	 * return posición de la clave en el array
	 */
	 
int AlgoritmosBusqueda::busquedaTernariaRc(int v[], int size,int key)
{
	//** ESCRIBIR PARA COMPLETAR LA PRACTICA **//
	return TernariaRc(v, 0, size - 1, key);
}

int AlgoritmosBusqueda::TernariaRc(int v[], int left, int right, int key)
{
	//** ESCRIBIR PARA COMPLETAR LA PRACTICA **//
	if (right >= left)
	{
		int tercio = (right - left + 1) / 3;
		if (v[left + tercio] == key)
			return (left+tercio);
		else if (v[right - tercio] == key)
			return (right-tercio);

		else if (key < v[left + tercio])
			return TernariaRc(v, left, left+tercio-1, key);

		else if (key < v[right - tercio])
			return TernariaRc(v, left+tercio+1, right-tercio-1, key);
		else
			return TernariaRc(v, right - tercio +1, right, key);
	}
	return -1;
}

int AlgoritmosBusqueda::busquedaBinariaIt(int v[], int size, int key)
{
	return BinariaIt(v, 0, size - 1, key);
}

int AlgoritmosBusqueda::BinariaIt(int A[], int primero, int ultimo, int key)
{
	while (primero <= ultimo)
	{
		int mitad = (primero + ultimo) / 2;
		if (key == A[mitad])
		{
			return mitad;
		}
		else if (key < A[mitad])
		{
			ultimo = mitad - 1;
		}
		else
		{
			primero = mitad + 1;
		}
	}
	return -1;
}