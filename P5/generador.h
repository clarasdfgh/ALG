#ifndef GENLAB
#define GENLAB

/******************************************************************************/
#define n 7

/******************************************************************************/
void pintaMatriz(int laberinto[][n]);
void ponParedHorizontal(int laberinto[][n], int pos, int a, int b);
void ponParedVertical(int laberinto[][n], int pos, int a, int b);
void abrePuertaEnHorizontal(int laberinto[][n], int pos, int a, int b);
void abrePuertaEnVertical(int laberinto[][n], int pos, int a, int b);
int escogeOrientacion(int ancho, int alto);
void generaLaberintoRecursivo(int laberinto[][n], int posX_izda, int posX_dcha, int posY_arr, int posY_abj);
void abrePuertas(int laberinto[][n]);

#endif
