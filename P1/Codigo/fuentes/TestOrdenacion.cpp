/* 
 * La clase TestOrdenacion contiene los metodos para:
 * 1. Comprobar que los m�todos de ordenacion de la clase Ordenacion funcionan adecuadamente.
 * 2. Calcular la eficiencia para el caso medio de un m�todo de ordenaci�n,
 *    guardando los datos y permitiendo imprimir la gr�fica correspondiente 
 * 3. Comparar el coste temporal de dos de los m�todos de ordenaci�n 
 *    burbuja, inserci�n, y selecci�n, guardando los datos y permitiendo imprimir la gr�fica correspondiente.
 */
#include "AlgoritmosOrdenacion.h"
#include "TestOrdenacion.h"
#include "ConjuntoInt.h"
#include "Graficas.h"
#include "Mtime.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Constantes.h"
using namespace std;

///* Constantes simb�licas para indicar el metodo de ordenacion*/
//enum algoritmos { BURBUJA, INSERCION, SELECCION};
///* Constantes para indicar el Orden del metodo de ordenacion*/
//enum ordenes { CUADRADO, NlogN};
///* Constantes para indicar el Numero de repeticiones para el caso medio de cada m�todo de b�squeda */
//static const int NUMREPETICIONES=10;
///* Constantes para indicar la variacion de las tallas del vector */
//enum valoresTallas { tallaIni = 100,tallaFin = 1000,incTalla = 100}; 

/*1!!! -A�adir el push back para que se sume a la cantidad de algoritmos en uso*/
TestOrdenacion::TestOrdenacion()
{
	nombreAlgoritmo.push_back("Burbuja");
	nombreAlgoritmo.push_back("Insercion");
	nombreAlgoritmo.push_back("Seleccion");
	nombreAlgoritmo.push_back("Mergesort");
	nombreAlgoritmo.push_back("QuickSort");
	nombreAlgoritmo.push_back("HeapSort");
} 
TestOrdenacion::~TestOrdenacion(){}

/*
 * Ordena un array de enteros seg�n el m�todo indicado
 * param v: el array de enteros a ordenar
 * param size: tama�o del array de enteros a ordenar
 * param metodo: Metodo de ordenacion a utilizar
 * return Tiempo empleado en la ordenaci�n (en milisegundos)
 */

/*2!!!!- A�adir la llamada al algoritmo nuevo*/
double TestOrdenacion::ordenarArrayDeInt(int v[],int size,int metodo) 
{
	AlgoritmosOrdenacion estrategia;
	Mtime t;
	LARGE_INTEGER t_inicial, t_final;
	QueryPerformanceCounter(&t_inicial);
	// Invoca al m�todo de ordenaci�n elegido
	switch (metodo){
		case BURBUJA:
			estrategia.ordenaBurbuja(v, size);
			break;
		case INSERCION: estrategia.ordenaInsercion(v, size);
			break;
		case SELECCION: estrategia.ordenaSeleccion(v, size);
			break;
		case MERGESORT: estrategia.ordenaMerge(v, size);
			break;
		case QUICKSORT:
			estrategia.ordenaQuicksort(v, size);
			break;
		case HEAPSORT:
			estrategia.ordenaQuicksort(v, size);
			break;
	}
	QueryPerformanceCounter(&t_final);
	return t.performancecounter_diff(&t_final, &t_inicial) * 1000;   
}

/*
 * Comprueba los metodos de ordenacion
 */
void TestOrdenacion::comprobarMetodosOrdenacion()
{
	int talla;
	cout<<endl<<endl<<"Introduce la talla: ";
	cin>>talla; 
	system("cls"); 
	for (int metodo = 0; metodo < nombreAlgoritmo.size(); metodo++){
		ConjuntoInt *v= new ConjuntoInt(talla); 
		v->GeneraVector(talla);
		cout <<endl<<endl<< "Vector inicial para el metodo "<<nombreAlgoritmo[metodo]<< ":"<<endl<<endl;
		v->escribe();
		double secs=ordenarArrayDeInt(v->getDatos(),talla,metodo);
    		cout<<endl<<endl<<"Array ordenado con metodo "<<nombreAlgoritmo[metodo]<< ":"<<endl<<endl;
        	v->escribe();
		cout<<endl;
		v->vaciar(); 
		system("pause");
		system("cls");
    	} /* fin del for */
	system("cls");
}
    
/*
 * Calcula el caso medio de un metodo de ordenacion,
 * Permite las opciones de crear el fichero de datos y la gr�fica correspondiente.
 * param metodo: metodo de ordenacion a estudiar.
 */

/*3!!!!!- Crear el casoMedio personalizado*/
void TestOrdenacion::casoMedio(int metodo)
{
	switch (metodo)
	{
	case 0:
	{
			  cout << "METODO BURBUJA" << endl;
			  ofstream casomedio_bur;
			  casomedio_bur.open("burbuja.dat");
			  cout << "TALLA" << "\t" << "TIEMPO";
			  for (int talla = 1; talla < TALLAMAX; talla++)
			  {
				  double tempo = 0;
				  for (int repeticiones = 0; repeticiones < NUMREPETICIONES; repeticiones++)
				  {
					  ConjuntoInt *v = new ConjuntoInt(talla*100);
					  v->GeneraVector(talla*100);
					  double secs = ordenarArrayDeInt(v->getDatos(), talla * 100, metodo);
					  v->vaciar();
					  tempo = tempo + secs;
				  }
				  tempo = tempo / NUMREPETICIONES;
				  cout << endl << talla*100 << "\t" << tempo;
				  casomedio_bur << talla*100 << "\t" << tempo << "\n";
			  }
			  casomedio_bur.close();
			  cout << endl;
			  break;
	}
	case 1:
	{
			  cout << "METODO INSERCION" << endl;
			  ofstream casomedio_ins;
			  casomedio_ins.open("insercion.dat");
			  cout << "TALLA" << "\t" << "TIEMPO";
			  for (int talla = 1; talla < TALLAMAX; talla++)
			  {
				  double tempo = 0;
				  for (int repeticiones = 0; repeticiones < NUMREPETICIONES; repeticiones++)
				  {
					  ConjuntoInt *v = new ConjuntoInt(talla * 100);
					  v->GeneraVector(talla * 100);
					  double secs = ordenarArrayDeInt(v->getDatos(), talla * 100, metodo);
					  v->vaciar();
					  tempo = tempo + secs;
				  }
				  tempo = tempo / NUMREPETICIONES;
				  cout << endl << talla * 100 << "\t" << tempo;
				  casomedio_ins << talla * 100 << "\t" << tempo << "\n";
			  }
			  casomedio_ins.close();
			  cout << endl;
			  break;
	}
	case 2:
	{
			  cout << "METODO SELECCION" << endl;
			  ofstream casomedio_sel;
			  casomedio_sel.open("seleccion.dat");
			  cout << "TALLA" << "\t" << "TIEMPO";
			  for (int talla = 1; talla < TALLAMAX; talla++)
			  {
				  double tempo = 0;
				  for (int repeticiones = 0; repeticiones < NUMREPETICIONES; repeticiones++)
				  {
					  ConjuntoInt *v = new ConjuntoInt(talla * 100);
					  v->GeneraVector(talla * 100);
					  double secs = ordenarArrayDeInt(v->getDatos(), talla * 100, metodo);
					  v->vaciar();
					  tempo = tempo + secs;
				  }
				  tempo = tempo / NUMREPETICIONES;
				  cout << endl << talla * 100 << "\t" << tempo;
				  casomedio_sel << talla * 100 << "\t" << tempo << "\n";
			  }
			  casomedio_sel.close();
			  cout << endl;
			  break;
	}
	case 3:
	{
			  cout << "METODO MERGESORT" << endl;
			  ofstream casomedio_merge;
			  casomedio_merge.open("mergesort.dat");
			  cout << "TALLA" << "\t" << "TIEMPO";
			  for (int talla = 1; talla < TALLAMAX; talla++)
			  {
				  double tempo = 0;
				  for (int repeticiones = 0; repeticiones < NUMREPETICIONES; repeticiones++)
				  {
					  ConjuntoInt *v = new ConjuntoInt(talla * 100);
					  v->GeneraVector(talla * 100);
					  double secs = ordenarArrayDeInt(v->getDatos(), talla * 100, metodo);
					  v->vaciar();
					  tempo = tempo + secs;
				  }
				  tempo = tempo / NUMREPETICIONES;
				  cout << endl << talla * 100 << "\t" << tempo;
				  casomedio_merge << talla * 100 << "\t" << tempo << "\n";
			  }
			  casomedio_merge.close();
			  cout << endl;
			  break;
	}
	case 4:
	{
		cout << "METODO QUICKSORT" << endl;
		ofstream casomedio_quick;
		casomedio_quick.open("quicksort.dat");
		cout << "TALLA" << "\t" << "TIEMPO";
		/*devolver a 1 < tallamax*/
		for (int talla = 1; talla < TALLAMAX; talla++)
		{
			double tempo = 0;
			for (int repeticiones = 0; repeticiones < NUMREPETICIONES; repeticiones++)
			{
				ConjuntoInt *v = new ConjuntoInt(talla*100);
				v->GeneraVector(talla * 100);
				double secs = ordenarArrayDeInt(v->getDatos(), talla * 100, metodo);
				v->vaciar();
				tempo = tempo + secs;
			}
			tempo = tempo / NUMREPETICIONES;
			cout << endl << talla * 100 << "\t" << tempo;
			casomedio_quick << talla * 100 << "\t" << tempo << "\n";
		}
		casomedio_quick.close();
		cout << endl;
		break;
	}
	case 5:
	{
		cout << "METODO HEAPSORT" << endl;
		ofstream casomedio_heap;
		casomedio_heap.open("heapsort.dat");
		cout << "TALLA" << "\t" << "TIEMPO";
		for (int talla = 1; talla < TALLAMAX; talla++)
		{
			double tempo = 0;
			for (int repeticiones = 0; repeticiones < NUMREPETICIONES; repeticiones++)
			{
				ConjuntoInt *v = new ConjuntoInt(talla * 100);
				v->GeneraVector(talla * 100);
				double secs = ordenarArrayDeInt(v->getDatos(), talla * 100, metodo);
				v->vaciar();
				tempo = tempo + secs;
			}
			tempo = tempo / NUMREPETICIONES;
			cout << endl << talla * 100 << "\t" << tempo;
			casomedio_heap << talla * 100 << "\t" << tempo << "\n";
		}
		casomedio_heap.close();
		cout << endl;
		break;
	}
	}
}
/*
 * Compara dos metodos de ordenacion. 
 * Genera el fichero de datos y permite las opcion de crear la gr�fica correspondiente.
 * param metodo1: Primer metodo de ordenacion a comparar
 * param metodo2: Segundo metodo de ordenacion a comparar
 */
void TestOrdenacion::comparar(int metodo1, int metodo2) {
	 //** ESCRIBIR PARA COMPLETAR LA PRACTICA **//	

	/*NOTA: Este metodo podria hacerse un poco mas visual poniendo ambos uno al lado de otro, pero esto necesitaria
	volver a codificar un metodo identico al casoMedio con la unica diferencia de que se muestren de dos en dos.
	Por esta razon he escogido esta opcion que a pesar de ser algo menos visual es mucho mas eficiente*/
	casoMedio(metodo1);
	casoMedio(metodo2);
	cout << linea;
}	
