#include <iostream>
#include <vector>
#include <ctime>
#include "generador.h"

using namespace std;

struct posMatriz{
  int fila;
  int columna;
};

const int TAM = 7;

int pared = 1;
int transitable = 0;
int ruta = 2;
int rutaEquivocada = 3;
int matriz[TAM][TAM];

vector<posMatriz> rutaFinal;

bool buscarRuta(int fila, int columna){
  bool res;

  if(fila < 0 || fila > TAM-1 || columna < 0 || columna > TAM-1){
    res = false;
  }else{
    if(matriz[fila][columna] != transitable){
      res = false;
    }else{
      matriz[fila][columna] = ruta;
      posMatriz posActual;
      posActual.fila = fila;
      posActual.columna = columna;
      rutaFinal.push_back(posActual);

      if(fila == TAM-1 && columna == TAM-1){
        res = true;
      }else{
        res = true;
        if(!buscarRuta(fila+1, columna) && !buscarRuta(fila-1, columna) && !buscarRuta(fila, columna+1) && !buscarRuta(fila, columna-1) ){
            matriz[fila][columna] = rutaEquivocada;
            res = false;
        }
      }
    }
  }
  return res;
}


int main(){

  clock_t tAntes, tDespues;

  tAntes = clock();

  srand(time(NULL));
  generaLaberintoRecursivo(matriz, 0, n, 0, n);
  abrePuertas(matriz);
  pintaMatriz(matriz);

  bool hayRuta = buscarRuta(0,0);
  tDespues = clock();

  if(hayRuta){
    for(int i = 0; i<rutaFinal.size(); i++)
      cout << rutaFinal[i].fila << ", " << rutaFinal[i].columna << endl;
  }else{
    cout << "No hay ruta";
  }

}
