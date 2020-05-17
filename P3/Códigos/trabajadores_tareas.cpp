/*******************************************************************************
ALGORÍTMICA 19-20 -- PRÁCTICA 3: Algoritmos voraces

Ejercicio individual 3.3: Trabajadores y tareas

  Dada una matriz cuadrada de tamaño n, en la que las filas son trabajadores,
  las tareas columnas y Cij el coste de asignar una tarea a un trabajador,
  diseñar un algoritmo voraz para la óptima asignación de tareas.

*******************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

/*******************************************************************************/
struct posicion {
  int trabajador;
  int tarea;
  int valor;
};

/******************************************************************************/
void PintaMatriz(int **M, int tamanio);
void AsignacionGreedy(int **M, int tamanio, int *V);
posicion EncuentraMasBarato(int **M, int tamanio, bool **usados);
void SalidaAsignacion(int *V);
int CalculaCoste(int **M, int tamanio, int *V);




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
posicion EncuentraMasBarato(int **M, int tamanio, bool **usados){
  posicion min;
    min.valor = 101;


  for (int i = 0; i <= tamanio; i++){
    for(int j = 0; j <= tamanio; j++){
      int actual = M[i][j];

      if(actual <= min.valor && !usados[i][j]){     //La matriz "usados" existe para que un número se pueda dar multiples veces dentro de la matriz
          min.valor = actual;
          min.trabajador = i;
          min.tarea = j;
      }
    }
  }

  usados[min.trabajador][min.tarea] = true;

  return min;
}

/******************************************************************************/
void AsignacionGreedy(int **M, int tamanio, int *V){
  bool ocupados[tamanio];         //factibilidad
  int tareas_asignadas = 0;
  posicion seleccionado;
  bool **M_aux = new bool*[tamanio+10];

  for (int i = 0; i <= tamanio; i++){
    ocupados[i] = false;         //Inicialmente todos los trabajadores están disponibles
    M_aux[i] = new bool[tamanio+10];
    for (int j = 0; j <= tamanio; j++){
      M_aux[i][j] = false;
    }
  }

  while (tareas_asignadas <= tamanio){
    seleccionado = EncuentraMasBarato(M, tamanio, M_aux);

    if (!ocupados[seleccionado.trabajador] && V[seleccionado.tarea] == -1){     //Factibilidad
      ocupados[seleccionado.trabajador] = true;
      V[seleccionado.tarea] = seleccionado.trabajador;

      tareas_asignadas++;
    }
  }
}

/******************************************************************************/
void SalidaAsignacion(int *V, int tamanio){
  cout << endl;

  for(int i = 0; i <= tamanio; i++){
    cout << "Tarea " << i+1 << " asignada a trabajador " << V[i]+1 ;
    cout << endl;
  }
}

/******************************************************************************/
int CalculaCoste(int **M, int tamanio, int *V){
  int coste = 0;

  for(int i = 0; i <= tamanio; i++){
    coste += M[V[i]][i];
  }

  return coste;
}

/******************************************************************************/
/******************************************************************************/

int main(int argc, char** argv){
  clock_t t_antes;
  clock_t t_despues;

  if(argc != 2 && argc != 3){
    cerr << "Formato:    " << argv[0] << " <num_elem>" << endl;
    cerr << "Modo debug: " << argv[0] << " <num_elem> D " << endl;
    return -1;
  }

  int n = atoi(argv[1]) - 1;

  int **M;
  M = (int **)malloc(n*sizeof(int*)+10);

  int asignacion[n];                      //Vector solución

  srand(time(NULL));		                  //Semilla basada en el tiempo de ejecución

  for (int i = 0; i <= n; i++){           //Generamos la matriz dinámica e inicializamos el vector solución
      M[i] = (int*)malloc(n*sizeof(int)+10);
      asignacion[i] = -1;

      for (int j = 0; j <= n; j++){
          if (argc==3 && (*argv[2] == 'D' && n <= 4)){           //Modo debug
            cout << endl;
            cout << "M["<< i << "][" << j << "] = ";
            cin >> M[i][j];
          } else{
            M[i][j] = rand() % 90 + 10;     //Numeros aleatorios del 10 al 100
      }
    }
  }


  t_antes = clock();                      //Mediciones de tiempo
    AsignacionGreedy(M, n, asignacion);
  t_despues = clock();

  if(n <= 4){
      PintaMatriz(M, n);
      SalidaAsignacion(asignacion, n);
    }

  cout << endl;
  cout << n+1 << "  " << fixed << (double)(t_despues - t_antes)/CLOCKS_PER_SEC  << "  " << CalculaCoste(M, n, asignacion)  << endl;

  for( int i = 0; i <= n; i++){
    delete[] M[i];                        //Liberamos memoria
  }

  delete[] M;

  return 0;
}
