#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

struct ciudad{
  int n; //Numero de la ciudad
  double x; //Coordenada x
  double y; //Coordenada y
};

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
            D[i][j] = sqrt(pow((ciudades[j].x) - (ciudades[i].x),2)+pow((ciudades[j].y) - (ciudades[i].y),2));
        }
    }
}

bool estaEnCamino(ciudad c, vector<ciudad> camino){
  bool res = false;

  for(int i=0; i<camino.size() && !res; i++){
    if(c.n == camino[i].n)
      res = true;
  }

  return res;
}

ciudad ciudadVecina(ciudad cActual, vector<vector<int>> D, vector<ciudad> ciudades, vector<ciudad> camino){
  ciudad res;
  int dist = 9999999;

  for(int i = 0; i < D.size(); i++){
    if(D[cActual.n-1][i] < dist && D[cActual.n-1][i] > 0 && !estaEnCamino(ciudades[i], camino)){
      dist = D[cActual.n-1][i];
      res = ciudades[i];
    }
  }

  return res;
}

vector<ciudad> getCiudadesRecorrido(ciudad cActual, int dist, vector<ciudad> ciudades, vector<vector<int>> D, vector<ciudad> camino){
  vector<ciudad> res;

  res.push_back(cActual);

  for(int i = 0; i < D.size(); i++){
    if(D[cActual.n-1][i] <= dist && D[cActual.n-1][i] != 0 && !estaEnCamino(ciudades[i], camino))
      res.push_back(ciudades[i]);
  }

  return res;
}

int getRecorrido(vector<ciudad> cRec, vector<vector<int>> D, int dist){
  int res = 0;

  for(int i = 0; i < cRec.size()-1; i++){
    res += D[cRec[i].n-1][cRec[i+1].n-1];
  }

  res += dist;
  res /= cRec.size();

  return res;
}

int main(int argc, char* argv[]){
  string nombre_fichero = argv[1];
  string nombre_recorrido = "";
  vector<ciudad> ciudades = recogerDatos(nombre_fichero, nombre_recorrido); //Ciudades en el mapa

  vector<vector<int>> D; //Vector con las distancias entre ciudades
  distancia(ciudades, D);

  vector<ciudad> camino; //Ciudades que ya se han
  int distanciaMenor; //Distancia entre la ciudad actual y su vecina mas cercana
  ciudad ciudadCercana; //Ciudad mas cercana
  ciudad ciudadActual; //Ciudad en la que nos encontramos actualmente
  ciudad cAux;
  vector<ciudad> ciudadesRecorrido, ciudadesRecorridoAux; //Ciudades vecinas a una ciudad
  int recorrido = 99999999, recorridoAux; //Distancia total del recorrido entre la ciudad actual y una ciudad candidata con sus vecinos, entre el numero de ciudades del recorrido
  int distanciaTotal = 0; //Distancia total recorrida

  ciudadActual = ciudades[0];
  ciudadCercana = ciudadVecina(ciudadActual, D, ciudades, camino);
  distanciaMenor = D[ciudadActual.n-1][ciudadCercana.n-1];

  //Tiempo

  while(camino.size() < ciudades.size()){
    //Comprobamos la ciudad con un recorrido mas rentable respecto a la distancia que hay con la ciudad mas cercana
    for(int i = 0; i < ciudades.size(); i++){
      //Comprobamos solo las ciudades que no estan ya en el camino
      if(!estaEnCamino(ciudades[i], camino)){
        cAux = ciudades[i];
        ciudadesRecorridoAux = getCiudadesRecorrido(cAux, distanciaMenor, ciudades, D, camino);

        if(ciudadesRecorridoAux.size() != 0){
          recorridoAux = getRecorrido(ciudadesRecorridoAux, D, D[ciudadActual.n-1][cAux.n-1]);
        }

        if(recorridoAux < recorrido){
          recorrido = recorridoAux;
          ciudadesRecorrido = ciudadesRecorridoAux;
        }
      }
    }

    //Comprobamos si el nuevo camino resulta mas rentable que ir a la ciudad vecina y lo añadimos en el Camino
    if(recorrido < distanciaMenor){

      for(int i = 0; i < ciudadesRecorrido.size(); i++){
        camino.push_back(ciudadesRecorrido[i]);
      }

    }else{ //Si no, añadimos la ciudad mas cercana al camino
        camino.push_back(ciudadCercana);
    }

    //Y volvemos a comenzar desde la ultima ciudad agregada al camino
    ciudadActual = camino[camino.size()-1];
    ciudadCercana = ciudadVecina(ciudadActual, D, ciudades, camino);
    distanciaMenor = D[ciudadActual.n-1][ciudadCercana.n-1];
    recorrido = 99999999, recorridoAux = 9999999;
    ciudadesRecorrido.clear();
  }

  //Añadimos al camino la primera ciudad, para volver a ella
  camino.push_back(ciudades[0]);

  //Tiempo

   for(int i = 0; i < camino.size(); i++){
     cout << camino[i].n << " " << camino[i].x << " " << camino[i].y << endl;
   }

  int c1, c2;
  for(int i=0; i < camino.size()-1; i++){
    c1 = camino[i].n-1;
    c2 = camino[i+1].n-1;
    distanciaTotal += D[c1][c2];
  }

  cout << "Distancia total: " << distanciaTotal << endl;

}
