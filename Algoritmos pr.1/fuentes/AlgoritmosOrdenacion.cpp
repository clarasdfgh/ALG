/*
 * Clase AlgoritmosOrdenacion que implementa los Algoritmos de Ordenación para ordenar un vector de enteros en orden descendente.
 * Define las implementaciones de los siguientes métodos de Ordenación en vectores: 
 *	- Burbuja
 *	- Inserción
 *	- Selección.
 */

#include <iostream>
#include "AlgoritmosOrdenacion.h"

#include <climits>
#include <cassert>

AlgoritmosOrdenacion :: AlgoritmosOrdenacion() {}
AlgoritmosOrdenacion :: ~AlgoritmosOrdenacion(){}


/*
 * Función ordenaBurbuja, implementa el método de ordenación Burbuja
 * param v: el array de enteros a ordenar
 * param size: tamaño del array de enteros a ordenar
 */

int posicion(int v[], int primero,int ultimo, int clave)
{
	do
	{
		int mitad = (primero + ultimo + 1) / 2;
		if (clave > v[mitad])
		{
			primero = mitad + 1;
		}
		else
		{
			ultimo = mitad - 1;
		}
	} while (primero <= ultimo);
	int mitad = (primero + ultimo + 1) / 2;
	return mitad;
}

void AlgoritmosOrdenacion :: ordenaBurbuja(int v[], int size)
{
//** ESCRIBIR PARA COMPLETAR LA PRACTICA **//
	int aux = 0;
	for (int i = 0; i < size-1; i++)
	{
		for (int j = size-1; j > i; j--)
		{
			if (v[j] < v[j - 1])
			{
				aux = v[j];
				v[j] = v[j - 1];
				v[j-1] = aux;
			}
		} 
	}
}


/*
 * Función ordenaInsercion, implementa el método de ordenación por Inserción
 * param v: el array de enteros a ordenar
 * param size: tamaño del array de enteros a ordenar
 */

void AlgoritmosOrdenacion :: ordenaInsercion(int v[], int size)
{
	int x;
	int j;
	for (int i = 1; i < size; i++)
	{
		x = v[i];
		j = i - 1;
		while (j>=0 && x < v[j])
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = x;
	}
}


/*
 * Función ordenaSeleccion, implementa el método de ordenación por Selección
 * param v: el array de enteros a ordenar
 * param size: tamaño del array de enteros a ordenar
 */
void AlgoritmosOrdenacion :: ordenaSeleccion(int v[], int size)
{
	int posminimo;
	int aux;
	for (int i = 0; i < size - 1; i++)
	{
		posminimo = i;
		for (int j = (i + 1); j < size; j++)
		{
			if (v[j] < v[posminimo])
			{
				posminimo = j;
			}
			aux = v[posminimo];
		}
		v[posminimo] = v[i];
		v[i] = aux;
	}


}

void InsercionBinaria(int v[], int primero, int ultimo)
{
	for (int i = 0; i < ultimo; i++)
	{
		int x = v[i];
		AlgoritmosBusqueda a;
		int k = a.BinariaIt(v, primero, i, x);
		for (int j = i - 1; j>k; j--)
		{
			v[j + 1] = v[j];
		}
		v[k] = x;
	}
}

void AlgoritmosOrdenacion::ordenaInsercionBinaria(int v[], int size)
{
	InsercionBinaria(v, 1, size - 1);
}

//QUICKSOOOORT
static void quicksort_lims(int T[], int inicial, int final);
inline static
void insercion(int T[], int num_elem);
static void insercion_lims(int T[], int inicial, int final);
static void dividir_qs(int T[], int inicial, int final, int & pp);
inline static void insercion(int T[], int num_elem)
{
	insercion_lims(T, 0, num_elem);
}
static void insercion_lims(int T[], int inicial, int final)
{
	int i, j;
	int aux;
	for (i = inicial + 1; i < final; i++) {
		j = i;
		while ((T[j] < T[j - 1]) && (j > 0)) {
			aux = T[j];
			T[j] = T[j - 1];
			T[j - 1] = aux;
			j--;
		};
	};
}

const int UMBRAL_QS = 50;
inline void quicksort(int T[], int num_elem)
{
	quicksort_lims(T, 0, num_elem);
}
static void quicksort_lims(int T[], int inicial, int final)
{
	int k;
	if (final - inicial < UMBRAL_QS) {
		insercion_lims(T, inicial, final);
	}
	else {
		dividir_qs(T, inicial, final, k);
		quicksort_lims(T, inicial, k);
		quicksort_lims(T, k + 1, final);
	};
}
static void dividir_qs(int T[], int inicial, int final, int & pp)
{
	int pivote, aux;
	int k, l;

	pivote = T[inicial];
	k = inicial;
	l = final;
	do {
		k++;
	} while ((T[k] <= pivote) && (k < final - 1));
	do {
		l--;
	} while (T[l] > pivote);
	while (k < l) {
		aux = T[k];
		T[k] = T[l];
		T[l] = aux;
		do k++; while (T[k] <= pivote);
		do l--; while (T[l] > pivote);
	};
	aux = T[inicial];
	T[inicial] = T[l];
	T[l] = aux;
	pp = l;
};

void AlgoritmosOrdenacion::ordenaQuicksort(int v[], int size)
{
	quicksort(v, size);
}

//MERGESOOOOORT
static void mergesort_lims(int T[], int inicial, int final);

inline static
void insercion(int T[], int num_elem);
static void insercion_lims(int T[], int inicial, int final);
static void fusion(int T[], int inicial, int final, int U[], int V[]);
const int UMBRAL_MS = 100;

void mergesort(int T[], int num_elem)
{
	mergesort_lims(T, 0, num_elem);
}
static void mergesort_lims(int T[], int inicial, int final)
{
	if (final - inicial < UMBRAL_MS)
	{
		insercion_lims(T, inicial, final);
	}
	else {
		int k = (final - inicial) / 2;

		int * U = new int[k - inicial + 1];
		assert(U);
		int l, l2;
		for (l = 0, l2 = inicial; l < k; l++, l2++)
			U[l] = T[l2];
		U[l] = INT_MAX;

		int * V = new int[final - k + 1];
		assert(V);
		for (l = 0, l2 = k; l < final - k; l++, l2++)
			V[l] = T[l2];
		V[l] = INT_MAX;

		mergesort_lims(U, 0, k);
		mergesort_lims(V, 0, final - k);
		fusion(T, inicial, final, U, V);
		delete[] U;
		delete[] V;
	};
}
static void fusion(int T[], int inicial, int final, int U[], int V[])
{
	int j = 0;
	int k = 0;
	for (int i = inicial; i < final; i++)
	{
		if (U[j] < V[k]) {
			T[i] = U[j];
			j++;
		}
		else {
			T[i] = V[k];
			k++;
		};
	};
}

void AlgoritmosOrdenacion::ordenaMerge(int T[], int n)
{
	mergesort(T, n);
}
//HEAPSOOOOOORT
static void reajustar(int T[], int num_elem, int k);
static void heapsort(int T[], int num_elem)
{
	int i;
	for (i = num_elem / 2; i >= 0; i--)
		reajustar(T, num_elem, i);
	for (i = num_elem - 1; i >= 1; i--)
	{
		int aux = T[0];
		T[0] = T[i];
		T[i] = aux;
		reajustar(T, i, 0);
	}
}
static void reajustar(int T[], int num_elem, int k)
{
	int j;
	int v;
	v = T[k];
	bool esAPO = false;
	while ((k < num_elem / 2) && !esAPO)
	{
		j = k + k + 1;
		if ((j < (num_elem - 1)) && (T[j] < T[j + 1]))
			j++;
		if (v >= T[j])
			esAPO = true;
		T[k] = T[j];
		k = j;
	}
	T[k] = v;
}
void AlgoritmosOrdenacion::ordenaHeap(int T[], int n)
{
	heapsort(T, n);
}
