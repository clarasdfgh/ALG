#include <vector>
#include <fstream>
#include <cstring>
#include <iostream>

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
    //cout << "CIUDAD " << ciudad_aux.n << " X: " << ciudad_aux.x << " Y: " << ciudad_aux.y << endl;
    f>>aux2;
  }

  f.close();
  return ciudades;
}

int main(int argc, char* argv[]){

  string nombre_fichero = argv[1];
  string nombre_recorrido = "";


  vector<ciudad> res = recogerDatos(nombre_fichero, nombre_recorrido);

  cout<<nombre_recorrido;
}
