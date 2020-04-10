#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
using namespace std::chrono;
//#include <algorithm>
//#include <vector>

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tama�o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tama�o n para obtener los k vectores. Est�n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

//AQUI COMIENZAN LAS FUNCIONES NECESARIAS PARA LA RECOMBINACION, MERGE Y RECOMBINE
void recombine(int v_inicial, int v_final, int *vector, int n)
{
    //Almacenar el inicio de los dos vectores inicial y final
    int inicio_vini= v_inicial*n;
    int inicio_vfin= ((v_inicial+v_final)/2+1)*n;

    //Almacenar el tamano de cada uno
    int tamano_vini= ((v_inicial+v_final)/2-v_inicial+1)*n; //El valor medio menos el inicial por la cantidad de elementos en cada array
    int tamano_vfin= (v_final-(v_inicial+v_final)/2)*n;  //El valor final menos el medio por la cantidad de elementos en cada array

    //Almacenar temporalmente los extremos
    int temporal_vini[tamano_vini];
    int temporal_vfin[tamano_vfin];

    //Copiar los datos
    for(int i=0; i<tamano_vini; i++)
    {
        temporal_vini[i] = vector[inicio_vini+i];
    }
    for(int i=0; i<tamano_vfin; i++)
    {
        temporal_vfin[i] = vector[inicio_vfin+i];
    }

    //procedemos a iterar sobre los temporales para recombinarlos en el vector
    int index_ini = 0, index_fin = 0;
    int index_vector=inicio_vini;
    while(index_ini+index_fin < tamano_vini+tamano_vfin) //Mientras no hayamos llegado al tamaño total
    {
        //Si ya no quedan elementos del vector final o el elemento del v_ini es menor que el de v_fin, escogemos el de vini
        if(index_fin==tamano_vfin || (index_ini != tamano_vini && temporal_vini[index_ini] < temporal_vfin[index_fin]))
        {
            vector[index_vector] = temporal_vini[index_ini];
            index_ini++;
            index_vector++;
        }
        else    //Si no, cogemos el de vfin
        {
            vector[index_vector] = temporal_vfin[index_fin];
            index_fin++;
            index_vector++;
        }
    }
}
void merge(int v_inicial, int v_final, int* parcial, int **T, int n)
{

    //Si sólo tenemos que mezclar un vector estamos en el caso base
    if(v_inicial == v_final)
    {
        for(int i=0; i<n; i++)
        {
            //Almacenamos en el vector solución temporal, el sub-array ordenado
            parcial[v_inicial*n+i] = T[v_inicial][i];
        }
    }
    else {
        //En otro caso
        //Ordenar mitad izquierda: desde el primero hasta el primero mas el ultimo entre 2
        merge(v_inicial, (v_inicial + v_final) / 2, parcial, T, n);
        //Ordenar mitad derecha: desde el siguiente, hasta el último
        merge((v_inicial + v_final) / 2 + 1, v_final, parcial, T, n);
        //Mezclar sub-vectores mezclados
        recombine(v_inicial, v_final, parcial, n);
    }

}

//AQUI EMPIEZA EL MAIN

int main(int argc, char * argv[])
{

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);


int **T;
T =  new int * [k];
  assert(T);
//clock_t tantes2, tdespues2;
//tantes2= clock();
 for (int i = 0; i < k; i++)
      T[i]= new int [n];

int N=k*n;
int * aux = new int[N];
  assert(aux);

srand(time(0));
//genero todos los enteros entre 0 y k*n-1
for (int j=0; j<N; j++) aux[j]=j;

//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
    for (int i=0; i<k; i++) {
       int t=0;
       int m=0;
       while (m<n) {
        double u=uniforme();
        if ((N-t)*u >= (n-m)) t++;
        else {
            T[i][m]=aux[t];
        t++;
        m++;
        }
      }

    }

delete [] aux;
    //tdespues2 = clock();
    //cout << "Tiempo de creacion y ordenacion de subvectores: " <<  (double)(tdespues2 - tantes2) / CLOCKS_PER_SEC << " segundos" <<endl;
    //Mostrar los vectores inicializados
    /*
    for (int i=0; i<k; i++) {
     for (int j=0; j<n; j++)
       cout << T[i][j] << " ";
     cout << " " << endl;
    }
    */
    //Vector Solucion: n*k posiciones
    int *Solucion=new int [n*k];
    //Primera llamada a la recursividad
    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;

    tantes = high_resolution_clock::now();
    merge(0, k-1, Solucion, T, n);
    tdespues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    //cout << "Tiempo de ejecucion: " <<  transcurrido.count() << " segundos" <<endl;
    cout << k << "\t" << transcurrido.count() << endl;
    //cout << n << "\t" << transcurrido.count() << endl;
    //Comprobar Solución
    /*
    for(int i=0; i<n*k; i++)
        cout << Solucion[i] << " ";
    cout << endl;
     */
}
