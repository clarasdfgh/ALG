/*******************************************************************************
ALGORÍTMICA 19-20 -- PRÁCTICA 2: Fuerza bruta
Ejercicio común: Traspuesta de una matriz
  Dada una matriz cuadrada de tamaño n = 2k , diseñar el algoritmo que devuelva
  la traspuesta de dicha matriz.
  Se debe tener en cuenta que n es el número de elementos de la matriz.
*******************************************************************************/
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

/******************************************************************************/
void TrasponerFB(int **M, int tamanio);
void PintaMatriz(int **M, int tamanio);
/******************************************************************************/
void TrasponerFB(int **M, int tamanio){

	int aux;

	for (int i = 0; i <= tamanio; i++){
		for (int j = i; j <= tamanio; j++) {
			aux = M[i][j];
			M[i][j] = M[j][i];
			M[j][i] = aux;
		}
	}
}

/******************************************************************************/
void PintaMatriz(int **M, int tamanio){
  cout << endl;

  for(int i = 0; i <= tamanio; i++){
    for(int j = 0; j <= tamanio; j++){
      cout << "\t" << M[i][j];
    }
    cout << endl;
  }
}

/******************************************************************************/
/******************************************************************************/

int main(){
  clock_t t_antes;
  clock_t t_despues;

  for(int k = 2; k <= 30; k = k+2){
    int n = pow(2, k);
    int tam = sqrt(n)-1;
    int **M = new int*[tam];

    int relleno = 1;
//Rellenamos la matriz con numeros secuenciales (es más facil ver la traspuesta)
    for (int i= 0; i <= tam; i++) {                  
        M[i] = new int[tam];

      for (int j = 0; j <= tam; j++){
        M[i][j] = relleno;

        relleno++;
      }
    }

/*  
    cout << "Matriz generada: " << endl;            //Para comprobaciones
    PintaMatriz(M, tam);
*/

    t_antes = clock();                              //Mediciones de tiempo
    TrasponerFB(M, tam);
    t_despues = clock();

/*  
    cout << "Matriz traspuesta: " << endl;          //Para comprobaciones
    PintaMatriz(M, tam);
*/  

    cout << endl << endl;
    cout << k << "  " << fixed << (double)(t_despues - t_antes)/CLOCKS_PER_SEC << endl << endl;


  }

  return 0;
}
