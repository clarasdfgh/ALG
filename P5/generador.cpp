/*******************************************************************************
ALGORÍTMICA 19-20 -- PRÁCTICA 5: Backtracking

Ejercicio individual: Laberinto

  Archivo auxiliar para la generación de laberintos 7x7
  para resolver con Backtracking.

*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "generador.h"

using namespace std;

/******************************************************************************/
void pintaMatriz(int laberinto[][n]){
  cout << endl;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cout << laberinto[i][j];
    }
    cout << endl ;
  }
  cout << endl;
}

/******************************************************************************/
void ponParedHorizontal(int laberinto[][n], int pos, int a, int b){             //Dibujar pared horizontal en la fila pos, entre las posiciones de la fila pos a y b
  for(int i=a; i<b; i++){
    laberinto[pos][i] = 1;
  }

  //pintaMatriz(laberinto);
}

/******************************************************************************/
void ponParedVertical(int laberinto[][n], int pos, int a, int b){               //Dibujar pared vertical en la columna pos, entre las posiciones de la columna pos a y b
  for(int i=a; i<b; i++){
    laberinto[i][pos] = 1;
  }

  //pintaMatriz(laberinto);
}

/******************************************************************************/
void abrePuertaEnHorizontal(int laberinto[][n], int pos, int a, int b){         //Abrir una puerta en la fila pos entre las posiciones de la fila pos a y b
  int puerta;                                                                   //Las puertas en paredes horizontales se ponen en alturas pares
  int despl = a + (a%2);

  puerta = (rand() % (b-a-1));

  if(puerta % 2 != 0){
    puerta++;
  }

  if(puerta + despl >= b){
    puerta -= 2;
  }

  laberinto[pos][puerta + despl] = 3;
  //pintaMatriz(laberinto);
}

/******************************************************************************/
void abrePuertaEnVertical(int laberinto[][n], int pos, int a, int b){           //Abrir una puerta en la columna pos entre las posiciones de la columna pos a y b
  int puerta;                                                                   //Las puertas en paredes horizontales se ponen en anchuras impares
  int despl = a + (a%2);

  puerta = (rand() % (b-a-1));

  if(puerta % 2 == 0){
    puerta++;
  }

  if(puerta + despl >= b){
    puerta -= 2;
  }

  laberinto[puerta + despl][pos] = 3;
  //pintaMatriz(laberinto);
}

/******************************************************************************/
int escogeOrientacion(int ancho, int alto){                                     //Escoger una orientacion para la siguiente pared. Favorece donde hay más espacio
  if(ancho < alto){                                                             //1 -> vertical, 2-> horizontal
    return 2;
  } if (alto < ancho){
    return 1;
  } else
    return (rand() % 2) + 1;
}

/******************************************************************************/
void generaLaberintoRecursivo(int laberinto[][n], int posX_izda, int posX_dcha, int posY_arr, int posY_abj){
  int ancho = posX_dcha - posX_izda;
  int alto  = posY_abj  - posY_arr;

  if(ancho < 2 || alto < 2 || posX_izda < 0 || posX_dcha > n
                           || posY_arr  < 0  || posY_abj > n){
    laberinto[0][0] = 3;
    laberinto[n-1][n-1] = 3;

  } else{
    int orientacion = (escogeOrientacion(ancho, alto));

    /* VERTICAL ***************************************************************/
    if(orientacion == 1) {
      int posicion_pared = -1;
      int i = ancho / 2 + posX_izda;

      for(; posicion_pared == -1; i++){                                         //Las paredes verticales se ponen en anchuras impares en las que no haya puertas
        if(i%2 != 0){
          if(laberinto[i+posY_arr][posY_arr] != 3 && laberinto[i+posY_arr][posY_abj] != 3){
            posicion_pared = i;
          }
        } if(i == posX_dcha){
          i = 0;
        }
      }

      int despl = posX_izda + (posX_izda%2);

      if(posicion_pared + despl > posX_izda){
        posicion_pared -= 2;
      }

      posicion_pared += despl;

      ponParedVertical(laberinto, posicion_pared, posY_arr, posY_abj);
      abrePuertaEnVertical(laberinto, posicion_pared, posY_arr, posY_abj);

      generaLaberintoRecursivo(laberinto, posX_izda, posicion_pared, posY_arr, posY_abj);
      generaLaberintoRecursivo(laberinto, posicion_pared+1, posX_dcha, posY_arr, posY_abj);
    }

    /* HORIZONTAL *************************************************************/
    if(orientacion == 2){

      int posicion_pared = -1;
      int i = alto / 2 + posY_arr;

      for(; posicion_pared == -1; i++){                                         //Las paredes horizontales se ponen en alturas pares en las que no haya puertas
        if(i % 2 == 0){
          if(laberinto[posX_izda][i+posX_izda-1] != 3 && laberinto[posX_dcha][i+posX_izda] != 3){
            posicion_pared = i;
          }
        } if(i == posY_abj){
          i = 0;
        }
      }

      int despl = posY_arr + (posY_arr%2);

      if(posicion_pared + despl > posY_abj){
        posicion_pared -= 2;
      }

      posicion_pared += despl;

      ponParedHorizontal(laberinto, posicion_pared, posX_izda, posX_dcha);
      abrePuertaEnHorizontal(laberinto, posicion_pared, posX_izda, posX_dcha);

      generaLaberintoRecursivo(laberinto, posX_izda, posX_dcha, posY_arr, posicion_pared);
      generaLaberintoRecursivo(laberinto, posX_izda, posX_dcha, posicion_pared+1, posY_abj);
    }
  }
}

/******************************************************************************/
void abrePuertas(int laberinto[][n]){                                           //Convierte las puertas (3) en pasillos (0)
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(laberinto[i][j] == 3){
        laberinto[i][j] = 0;
      }
    }
  }
}

/******************************************************************************/
/******************************************************************************/
/*int main(){
  int laberinto[n][n];
  srand(time(NULL));

  //Inicializamos el laberinto vacío
  for (int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      laberinto[i][j] = 0;
    }
  }

  generaLaberintoRecursivo(laberinto, 0, n, 0, n);
  abrePuertas(laberinto);

  pintaMatriz(laberinto);

  return 0;
}*/
