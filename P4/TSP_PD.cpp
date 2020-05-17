#include <vector>
#include <fstream>
#include <cstring>
#include <map>
#include <sstream>
#include <iterator>
#include <iostream>
#include <cmath>
#include <climits>
#include <ctime>

    //Compilacion: g++ -o TSP TSP_PD.cpp
    //Ejecucion: ./TSP <nombre_fichero>

using namespace std;


map<string, int> memoizacion;
/*
 * EL MAPA GUARDA UNA CLAVE Y EL VALOR ASOCIADO
 * LA CLAVE SE GENERA COMO UN STRING ALMACENANDO:
 * NODO ACTUAL
 * NODOS SIN VISITAR
 * EL VALOR ASOCIADO ES EL COSTE ALMACENADO EN EL INT
 */

struct ciudad{
    int n; //Numero de la ciudad
    double x; //Coordenada x
    double y; //Coordenada y
};

//Leer datos del fichero
vector<ciudad> recogerDatos(string nombre_fichero, string &nombre_recorrido)
{
    int n;
    double x;
    double y;
    vector<ciudad> ciudades;
    ciudad ciudad_aux;
    ifstream f(nombre_fichero);

    getline(f, nombre_recorrido);

    string aux = "";
    getline(f, aux);
    while(aux != "NODE_COORD_SECTION"){
        getline(f, aux);
    }

    string aux2;
    f>>aux2;
    while(aux2 != "EOF"){
        ciudad_aux.n = ciudades.size()+1;
        f >> ciudad_aux.x;
        f >> ciudad_aux.y;
        ciudades.push_back(ciudad_aux);
        //cout << "CIUDAD " << ciudad_aux.n << " X: " << ciudad_aux.x << " Y: " << ciudad_aux.y << endl;
        f>>aux2;
    }

    f.close();
    return ciudades;
}
//Cálculo de la distancia entre las ciudades
void distancia(const vector<ciudad> &ciudades, vector<vector<int>> &D){
    D.resize(ciudades.size());
    //Bucle externo que intera sobre la ciudad en la que se calcula la distancia
    //Para calcular la distancia de esa ciudad con el resto de ellas
    for(int i = 0; i < D.size(); i++){
        D[i].resize(ciudades.size());
        //Bucle interno que itera sobre las ciudades almacenadas para calcular la distancia respecto a la del bucle externo
        for(int j = 0; j < D[i].size(); j++){
            //Fórmula del calculo de la distancia entre 2 puntos de dos dimensiones (x,y), se almacena en una matriz bidimensional
            D[i][j] = round(sqrt(pow((ciudades[j].x) - (ciudades[i].x),2)+pow((ciudades[j].y) - (ciudades[i].y),2)));
        }
    }
}

//Genera el arbol rellenando el map
int subTSP(int actual, vector<int> sin_visitar, vector<vector<int>> D)
{
    int mejor, mejor_aux;
    string clave;
    stringstream lista_clave;
    vector<int> aux;    //Necesitamos un vector auxiliar para que al realizar la recursividad no se alteren unas ramas a otras
    map<string, int>::iterator iterador;

    mejor = INT_MAX;
    mejor_aux = INT_MAX;

    // Si quedan ciudades por visitar
    if (!sin_visitar.empty()) {

        copy(sin_visitar.begin(), sin_visitar.end(), ostream_iterator<int>(lista_clave, " "));
        clave = to_string(actual) + ' ' + lista_clave.str();

        // Comprobamos si ya hemos almacenado el valor en memoizacion
        iterador = memoizacion.find(clave);
        if (iterador != memoizacion.end()) {
            mejor = iterador -> second;
        }
            // No ha sido almacenado en memoizacion aun
        else {
            for (int i = 0; i < (int) sin_visitar.size(); i++) {
                aux = sin_visitar;
                aux.erase(aux.begin()+i);

                mejor_aux = D[actual][sin_visitar[i]] + subTSP(sin_visitar[i], aux, D);

                if (mejor_aux < mejor) {
                    mejor = mejor_aux;
                }
            }

            // Guardamos el estado en memoizacion
            memoizacion[clave] = mejor;
        }
    }
    else    //Si ya se han visitado todas, solo queda volver a la ciudad inicial (se podria sustituir 0 por inicial en el caso de que la funcion calcule el camino empezando en inicial
    {
        mejor = D[actual][0];
    }
    return mejor;
}
//Devuelve el camino una vez generado el arbol entero
vector<int> TSP(int actual, vector<int> sin_visitar, vector<vector<int>> D)
{
    int mejor, mejor_aux, index_mejor;
    vector<int> solucion, restante, aux;

    restante = sin_visitar;
    solucion.push_back(actual);

    while (solucion.size() <= sin_visitar.size()) {

        mejor = INT_MAX;
        index_mejor = -1;

        for (int i = 0; i < (int) restante.size(); i++) {

            aux = restante;
            aux.erase(aux.begin()+i);

            mejor_aux = D[solucion.back()][restante[i]] + subTSP(restante[i], aux, D);

            if (mejor_aux < mejor) {
                mejor = mejor_aux;
                index_mejor = i;
            }
        }

        solucion.push_back(restante[index_mejor]);
        restante.erase(restante.begin()+index_mejor);
    }

    return solucion;
}

ciudad getCiudad(int indice, vector<ciudad> ciudades){
  ciudad res;
  bool encontrado = false;

  for(int i=0; i<ciudades.size() && !encontrado; i++){
    if(indice+1 == ciudades[i].n){
      res = ciudades[i];
      encontrado = true;
    }
  }

  return res;
}


int main(int argc, char* argv[]){

    string nombre_fichero = argv[1];
    string nombre_recorrido = "";

    vector<ciudad> ciudades = recogerDatos(nombre_fichero, nombre_recorrido);   //Ciudades leidas del fichero
    vector<int> indices;    //Indices de todas las ciudades que se pasan a la funcion
    vector<int> camino;     //Vector donde se guardará la solucion
    int total;              //Coste de la solución
    vector<vector<int>> D;      //Matriz para las Distancias desde la ciudad [i] a la ciudad [i][j]

    //Inicializar los indices sobre los que se busca el camino, quitando la ciudad inicial
        for(int i=0; i<ciudades.size(); i++)
        {
            indices.push_back(ciudades[i].n-1);
        }
        indices.erase(indices.begin());

    //Calcular las distancias entre todas las ciudades guardandolas en D
        distancia(ciudades, D);

    //MOSTRAR EL NOMBRE DEL RECORRIDO
    cout<< nombre_recorrido << endl;

    //MOSTRAR LAS DISTANCIAS ENTRE TODOS
        /* COMENTADO ABAJO*/
      
    //Cantidad de parámetros ./programa <nombre_fichero>
    if(argc == 2)
    {
            //Llamada a subTSP
        total = subTSP(0, indices, D);
        cout << "Distancia total: " << total << endl;
            //Llamada a TSP
        camino = TSP(0, indices, D);
        cout << "Camino final: ";
        for (int i = 0; i < camino.size(); i++)
        {
            //cout << camino[i]+1 << " " << getCiudad(camino[i], ciudades).x << " " << getCiudad(camino[i], ciudades).y << " " << endl;
            cout << camino[i]+1 << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Cantidad de Parámetros incorrecta: ./TSP <nombre_fichero>" << endl;
    }
    return 0;
}

//Couts para comprobar funcionamientos:
//Comprobar las distancias:
/*
    for(int i=0; i<D.size(); i++)
    {
        for (int j=0; j<D[i].size(); j++)
        {
            cout << "Distancia de "<< i <<" a " << j << ": " << D[i][j] << endl;
        }
    }
*/
