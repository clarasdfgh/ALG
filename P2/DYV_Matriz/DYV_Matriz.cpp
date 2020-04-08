/*******************************************************************************
ALGORÍTMICA 19-20 -- PRÁCTICA 2: Divide y vencerás

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
void Trasponer(int **M, int tamanio);
void DivideMatriz(int **M, int f_ini, int f_fin, int c_ini, int c_fin);
void CambiaPosicion(int **M, int f_iniA, int c_iniA, int f_iniB, int c_iniB, int tam);
void PintaMatriz(int **M, int tamanio);
/******************************************************************************/
void Trasponer(int **M, int tamanio){
    DivideMatriz(M, 0, tamanio, 0, tamanio);
}

/******************************************************************************/
void DivideMatriz(int **M, int f_ini, int f_fin, int c_ini, int c_fin){
  if(f_fin-f_ini == 1){                 //Caso final: la matriz ha alcanzado el caso más fácil
    int aux = M[f_ini][c_ini+1];
    M[f_ini][c_ini+1] = M[f_ini+1][c_ini];
    M[f_ini+1][c_ini] = aux;
  } else{
    int f_mid = (f_ini+f_fin)/2;
    int c_mid = (c_ini+c_fin)/2;

    DivideMatriz(M, f_ini, f_mid, c_ini, c_mid);        //Submatriz esq. superior izda.
    DivideMatriz(M, f_mid+1, f_fin, c_ini, c_mid);      //Submatriz esq. superior dcha.
    DivideMatriz(M, f_ini, f_mid, c_mid+1, c_fin);      //Submatriz esq. inferior izda.
    DivideMatriz(M, f_mid+1, f_fin, c_mid+1, c_fin);    //Submatriz esq. inferior dcha.

    CambiaPosicion(M, f_mid+1, c_ini, f_ini, c_mid+1, f_fin-f_mid);   //Intercambiar submatrices que no pertenecen a la diag. principal
  }
}

/******************************************************************************/
void CambiaPosicion(int **M, int f_iniA, int c_iniA, int f_iniB, int c_iniB, int tam){
  for (int i = 0; i <= tam-1; i++){
    for (int j = 0; j <= tam-1; j++) {
      int iA = f_iniA + i;
      int jA = c_iniA + j;
      int iB = f_iniB + i;
      int jB = c_iniB + j;

      int aux = M[iA][jA];
      M[iA][jA] = M[iB][jB];
      M[iB][jB] = aux;
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

    for (int i = 0; i <= tam; i++){                  //Rellenamos la matriz con numeros secuenciales (es más facil ver la traspuesta)
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
    Trasponer(M, tam);
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
