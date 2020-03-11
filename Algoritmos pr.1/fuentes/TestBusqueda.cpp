/* 
 * La clase TestBusqueda contiene los metodos para:
 * 1. Comprobar que los métodos de búsqueda de la clase AlgoritmosBusqueda funcionan adecuadamente.
 * 2. Calcular la eficiencia para el caso medio de un método de búsqueda,
 *    permitiendo guardar los datos e imprimir la gráfica correspondiente con ajuste al Orden de complejidad.
 * 3. Comparar el coste temporal de dos métodos de búsqueda
 *    permitiendo guardar los datos e imprimir la gráfica correspondiente.
 */
#include "TestBusqueda.h"
#include "Constantes.h"
#include "AlgoritmosBusqueda.h"
#include "AlgoritmosOrdenacion.h"
#include "ConjuntoInt.h"
#include "Graficas.h"
#include "Mtime.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

TestBusqueda::TestBusqueda()
{
	nombreAlgoritmo.push_back("SecuencialI");
	nombreAlgoritmo.push_back("BinariaR");
	nombreAlgoritmo.push_back("TernariaR");
} 
TestBusqueda::~TestBusqueda()
{
}

/*
 * Busca en un array de enteros según el método indicado
 * param v: el array de enteros a ordenar
 * param size: tamaño del array de enteros a ordenar
 * param metodo: Metodo de búsqueda a utilizar
 * return Tiempo empleado en la busqueda (en milisegundos)
 */
double TestBusqueda::buscaEnArrayDeInt(int key,int v[],int size,int metodo,int &posicion) 
{
    AlgoritmosBusqueda strategia;
		Mtime t;
		LARGE_INTEGER t_inicial, t_final;
		QueryPerformanceCounter(&t_inicial);
// Invoca al método de búsqueda elegido
    switch (metodo)
		{
        case SECUENCIALIt: posicion = strategia.busquedaSecuencialIt(v, size, key);
            break;
		case SECUENCIALRc: posicion = strategia.BusquedaSecuencialRc(v, size, key);
			break;
		case BINARIARc: posicion = strategia.busquedaBinariaRc(v, size, key); 
            break;
		case BINARIAIt: posicion = strategia.busquedaBinariaIt(v, size, key);
			break;
		case TERNARIARc: posicion=strategia.busquedaTernariaRc(v, size, key); 
            break;
		}
		QueryPerformanceCounter(&t_final);
    return t.performancecounter_diff(&t_final, &t_inicial) * 1000000;   
}

/*
 * Comprueba los metodos de búsqueda
 */
void TestBusqueda::comprobarMetodosBusqueda(){
	int talla;
	cout<<endl<<endl<<"Introduce la talla: ";
	cin>>talla; 
	system("cls");
	ConjuntoInt *v= new ConjuntoInt(talla); 
	AlgoritmosOrdenacion AlOrdena;
	for (int metodo = 0; metodo < nombreAlgoritmo.size(); metodo++){
		v->GeneraVector(talla);
		/* Ordenar array*/
		AlOrdena.ordenaInsercion(v->getDatos(),talla);
		cout <<endl<<endl<< "vector para el metodo "<<nombreAlgoritmo[metodo]<< ":"<<endl<<endl;
		v->escribe();
		int key;
		cout<<endl<<endl<<"Introduce la clave a buscar: ";
		cin>>key; 
		int posicion;
		buscaEnArrayDeInt(key,v->getDatos(),talla,metodo,posicion);
		cout<<endl<<endl<<"posicion de "<<key<<" buscado con el metodo "<<nombreAlgoritmo[metodo]<< " : "<<posicion<<endl<<endl;
		v->vaciar(); 
		system("pause");
		system("cls");
	}
	system("cls");
}
    
/*
 * Compara dos metodos de búsqueda. 
 * Permite las opciones de crear el fichero de datos y la gráfica correspondiente.
 * param metodo1: Primer metodo de búsqueda a comparar
 * param metodo2: Segundo metodo de búsqueda a comparar
 */
void TestBusqueda::comparar(int metodo1, int metodo2) 
{
   //** ESCRIBIR PARA COMPLETAR LA PRACTICA **//
	system("cls");
	casoMedio(metodo1);
	cout << endl;
	casoMedio(metodo2);
}
/*
 * Calcula el caso medio de un metodo de búsqueda,
 * Permite las opciones de crear el fichero de datos y la gráfica correspondiente.
 * param metodo: metodo de búsqueda a estudiar.
 */
void TestBusqueda::casoMedio(int metodo)
{
	ofstream fichero;
	switch (metodo)
	{		
	case SECUENCIALIt:
		fichero.open("secuencial.dat");
		break;
	case SECUENCIALRc:
		fichero.open("secuencialrc.dat");
		break;
	case BINARIARc:
		fichero.open("binaria.dat");
		break;
	case BINARIAIt:
		fichero.open("binariait.dat");
		break;
	case TERNARIARc:
		fichero.open("ternaria.dat");
		break;
	default:
		cout << "Error";
		break;
	}
	cout << endl;
	cout << "TAMANO" << "\t" << "TIEMPO";
	for (int i = tallaIni; i <= tallaFin; i += incTalla)
	{
		ConjuntoInt *v = new ConjuntoInt(i);
		AlgoritmosOrdenacion ordenar;
		int clave;
		/*Aqui el vector ya esta ordenado, falta buscar un elemento 100 veces y hacer la media de los tiempos*/
		double milisegundos = 0;
		for (int j = 0; j < NUMREPETICIONES; j++)
		{

			v->GeneraVector(i);
			ordenar.ordenaInsercion(v->getDatos(), i);
			clave = v->generaKey();
			int posicion;
			int* datos = v->getDatos();
			
			milisegundos = milisegundos + buscaEnArrayDeInt(clave, datos, i, metodo, posicion);
		}
		milisegundos = milisegundos / NUMREPETICIONES;
		cout << endl;
		cout << i << "\t" << milisegundos;
		fichero << i << "\t" << milisegundos << endl;
		
		delete v;
	}
	cout << endl;
}	
