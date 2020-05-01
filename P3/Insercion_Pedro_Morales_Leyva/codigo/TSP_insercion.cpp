#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct ciudad{
  int n; //Numero de la ciudad
  double x; //Coordenada x
  double y; //Coordenada y
};

//Leer datos de un fichero
vector<ciudad> recogerDatos(string nombre_fichero, string &nombre_recorrido){
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

//Metodo para eliminar las ciudades usadas
void eliminarCiudadesUsadas(vector<ciudad> &ciudades, int indice1, int indice2, int indice3){

  int contador = 1, i = 0;

  while(i < ciudades.size() && contador <= 3){
    if(ciudades[i].n == indice1 || ciudades[i].n == indice2 || ciudades[i].n == indice3){
      ciudades.erase(ciudades.begin() + i);
      contador++;
    }
    else{
      i++;
    }
  }
}

//Método para obtener un camino parcial basado en la obtencion de
//la ciudad más al Norte, más al Este y más al Oeste
void obtenerCircuitoParcial(vector<ciudad> &ciudades, vector<ciudad> &ciudades_solucion){

  int indice_este = 0, indice_oeste = 0, indice_norte = 0;
  int minimo_x = 10000, maximo_x = 0, maximo_y = 0;

  for(int i = 0; i < ciudades.size(); i++){
    //Calcular ciudad más al oeste
    if(ciudades[i].x < minimo_x){
      minimo_x = ciudades[i].x;
      indice_oeste = i;
    }
    //Calcular ciudad más al norte
    if(ciudades[i].y > maximo_y){
      maximo_y = ciudades[i].y;
      indice_norte = i;
    }
    //Calcular ciudad más al este
    if(ciudades[i].x > maximo_x){
      maximo_x = ciudades[i].x;
      indice_este = i;
    }
  }

  //Añadir ciudades a la solución
  ciudades_solucion.push_back(ciudades[indice_oeste]);
  ciudades_solucion.push_back(ciudades[indice_norte]);
  ciudades_solucion.push_back(ciudades[indice_este]);
  ciudades_solucion.push_back(ciudades[indice_oeste]);
  //Eliminar del vector de ciudades
  eliminarCiudadesUsadas(ciudades, indice_norte+1, indice_oeste+1, indice_este+1);

}

//Método para calcular la distancia total de un vector de ciudades
double calcularDistanciaTotal(vector<ciudad> ciudades){

  double distancia = 0.0, x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;

  for(int i = 1; i < ciudades.size(); i++){
    x1 = ciudades[i-1].x;
    y1 = ciudades[i-1].y;
    x2 = ciudades[i].x;
    y2 = ciudades[i].y;

    distancia += sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
  }

  return distancia;
}

//Método para seleccionar la siguiente ciudad solución
void seleccionarCiudad(vector<ciudad> &ciudades, vector<ciudad> &ciudades_solucion){

  ciudad ciudad_actual;
  vector<ciudad> v_aux;
  double min_distancia = 9999999999;
  int indice_ciudad = 0, indice_posicion_insertar = 0;

  for(int i = 0; i < ciudades.size(); i++){
    ciudad_actual = ciudades[i];
    for(int j = 1; j < ciudades_solucion.size() - 1; j++){	
      v_aux = ciudades_solucion;
      v_aux.insert(v_aux.begin() + j, ciudad_actual);
      double d = calcularDistanciaTotal(v_aux);
      if(d < min_distancia){
        min_distancia = d;
        indice_ciudad = i;
        indice_posicion_insertar = j;
      }
      v_aux.clear();
    }
  }

  ciudades_solucion.insert(ciudades_solucion.begin() + indice_posicion_insertar, ciudades[indice_ciudad]);
  ciudades.erase(ciudades.begin() + indice_ciudad);
}

//Método para calcular el camino solución
void calcularRuta(vector<ciudad> &ciudades, vector<ciudad> &ciudades_solucion){

  obtenerCircuitoParcial(ciudades, ciudades_solucion);

  while(ciudades.size()){
    seleccionarCiudad(ciudades, ciudades_solucion);
  }
}


int main(int argc, char* argv[]){

  //Declaracion de variables
  string nombre_fichero = argv[1];
  string nombre_recorrido = "";

  vector<ciudad> ciudades, solucion_ciudades;
  ciudades = recogerDatos(nombre_fichero, nombre_recorrido);

  high_resolution_clock::time_point tantes, tdespues;
  duration<double> transcurrido;

  //Medir aqui
  tantes = high_resolution_clock::now();
  calcularRuta(ciudades, solucion_ciudades);
  tdespues = high_resolution_clock::now();

  transcurrido = duration_cast<duration<double>>(tdespues-tantes);
/*
  for(int i = 0; i < solucion_ciudades.size(); i++){
    cout << solucion_ciudades[i].n << " " << solucion_ciudades[i].x << " " <<   solucion_ciudades[i].y << endl;
  }
*/
//  cout << endl << calcularDistanciaTotal(solucion_ciudades) << endl;
  cout << endl << transcurrido.count() << endl;

  return 0;

}
