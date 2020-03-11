/* 
 *Definiciones de las Constantes utilizadas en la pr�ctica 3. 
 */
#ifndef _CONSTANTES
#define _CONSTANTES

/* Constantes simb�licas para indicar el metodo de ordenacion*/
/*A�adir nuevos algoritmos!!!*/
enum algoritmosOrdenacion { BURBUJA, INSERCION, SELECCION, MERGESORT, QUICKSORT, HEAPSORT};
enum algoritmosOtros {FLOYD, FIBONACCI};
/* Constantes simb�licas para indicar el metodo de Busqueda*/
enum algoritmosBusquedaClave{SECUENCIALIt, SECUENCIALRc, BINARIARc, BINARIAIt, TERNARIARc};

/* Constantes para indicar el Orden de complejidad*/
/*Arreglar*/
enum ordenes {LOGN,N,NLOGN,CUADRADO,CUBO,EXPO};

/* Constantes para indicar el Numero de repeticiones para el caso medio de cada m�todo de ordenaci�n-b�squeda */
static const int NUMREPETICIONES=100;
static const int TALLAMAX = 26;

/* Constantes para indicar la variacion de las tallas del vector */
/*Crear nuevos valores para algoritmos mas complejos*/
enum valoresTallas { tallaIni = 100,tallaFin = 1000,incTalla = 100};

#endif