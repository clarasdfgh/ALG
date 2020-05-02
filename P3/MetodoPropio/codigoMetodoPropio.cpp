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

bool estaEnCamino(int nCiudad, vector<ciudad> camino){
  bool res = false;

  for(int i=0; i<camino.size() && !res; i++){
    if(nCiudad == (camino[i].n-1))
      res = true;
  }

  return res;
}

ciudad getCiudad(int n, vector<ciudad> ciudades){
  ciudad res;
  bool encontrado = false;

  for(int i = 0; i < ciudades.size() && !encontrado; i++){
    if(i == n-1){
      res = ciudades[i];
      encontrado = true;
    }
  }

  return res;
}

vector<ciudad> ciudadesCerca(int distancia, int c, vector<vector<int>> D, vector<ciudad> camino, vector<ciudad> ciudades){
  vector<ciudad> res;
  ciudad cAux;

  for(int i=0; i < D[c].size(); i++){
    if(i != c && !estaEnCamino(i, camino) && D[c][i] <= distancia){
        cAux = getCiudad(i+1, ciudades);
        res.push_back(cAux);
      }
  }
  return res;
}

int menorDist(ciudad cActual, vector<ciudad> ciudades, vector<vector<int>> D, vector<ciudad> camino, ciudad &ciudadCercana){
  int menorDistancia = 9999999, cont=0, ciudadActual = cActual.n-1;

  for(int i=0; i < D[ciudadActual].size(); i++){
    if(D[ciudadActual][i] < menorDistancia && D[ciudadActual][i] != 0 && !estaEnCamino(i, camino)){
      menorDistancia = D[ciudadActual][i];
      ciudadCercana = ciudades[i];
    }
  }

  return menorDistancia;
}

bool renta(int distancia, vector<ciudad> ciudadesCerc, ciudad sigCiudad, ciudad actual, vector<vector<int>> D){
  bool res = false;
  int suma = D[actual.n-1][sigCiudad.n-1];

  for(int i = 0; i < ciudadesCerc.size(); i++){
    suma += D[sigCiudad.n-1][ciudadesCerc[i].n-1];
  }

  suma = (int)suma/(ciudadesCerc.size()+1);

  if(suma < distancia)
    res =  true;

  return res;
}

int main(int argc, char* argv[]){
  string nombre_fichero = argv[1];
  string nombre_recorrido = "";
  vector<ciudad> ciudades = recogerDatos(nombre_fichero, nombre_recorrido); //Ciudades en el mapa


  vector<vector<int>> D; //Distnacia entre ciudades
  vector<ciudad> camino; //Ciudades ya visitadas
  vector<ciudad> ciudadesCercanas, ciudadesCercanasAux; //Ciudades cercanas a una ciudad, la posicion en el vector ciudades, no el numero de la ciudad
  ciudad sigCiudad; //Ciudad a la que ir
  ciudad ciudadCercana; //Ciudad mas cercana a la actual
  int menorDistancia; //Distancia entre la ciudad actual y la mas cercana
  int nCercanas = 0; //Numero de ciudades cercanas a una ciudad

  distancia(ciudades, D);
  ciudad ciudadActual = ciudades[0];
  camino.push_back(ciudadActual);
  menorDistancia = menorDist(ciudadActual, ciudades, D, camino, ciudadCercana);

  while(camino.size() < ciudades.size()){
    //Recorre todas las ciudades y guarda la que tenga el mayor numero de ciudades cercanas
    for(int i = 0; i < ciudades.size(); i++){
      if(i != ciudadActual.n-1 && !estaEnCamino(i, camino)){
        ciudadesCercanasAux = ciudadesCerca(menorDistancia, i, D, camino, ciudades);
      }

      if(ciudadesCercanasAux.size() > nCercanas){
        ciudadesCercanas = ciudadesCercanasAux;
        sigCiudad = ciudades[i];
        nCercanas = ciudadesCercanas.size();
      }
    }

    //Añadimos las ciudades cercanas al camino si se ha guardado una ciudad con mas de una ciudad cercana
    if(nCercanas > 1 && renta(menorDistancia, ciudadesCercanas, sigCiudad, ciudadActual, D)){
      camino.push_back(sigCiudad);

      for(int i = 0; i < ciudadesCercanas.size(); i++){
        camino.push_back(ciudadesCercanas[i]);
      }

      ciudadActual = ciudadesCercanas[ciudadesCercanas.size()-1];

    }else{ //Si no, añadimos la ciudad mas cercana
      camino.push_back(ciudadCercana);
      ciudadActual = ciudadCercana;
    }

    //Devolvemos las variables a su estado inicial
    ciudadesCercanas.clear();
    ciudadesCercanasAux.clear();
    nCercanas = 0;
    menorDistancia = menorDist(ciudadActual, ciudades, D, camino, ciudadCercana);
 }

  //Añadimos al final la primera ciudad
  camino.push_back(ciudades[0]);

  // cout << nombre_recorrido << endl;

  for(int i = 0; i < camino.size(); i++){
    cout << camino[i].n << " " << camino[i].x << " " << camino[i].y << endl;
  }

}
