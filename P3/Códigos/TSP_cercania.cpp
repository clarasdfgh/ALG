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
            D[i][j] = sqrt(pow((ciudades[j].x) - (ciudades[i].x),2)+pow((ciudades[j].y) - (ciudades[i].y),2));
        }
    }
}
//Selecciona las ciudades para la solución
void vecinoCercano(const vector<vector<int>> &D, int inicio, vector<int> &solucion, int &total){
    bool visitado[D.size()] = {false};
    int destino = -1;
    int actual = inicio-1;
    int distMinima = 999999999;

    for(int j = 0; j < D.size(); j++)
    {
        visitado[actual] = true;
        for(int i = 0; i < D.size(); i++){
            //cout << "DISTANCIA de: " << actual << " a : " << i << " ==== " << D[actual][i] << endl;
            if(D[actual][i] < distMinima && !visitado[i] && i != actual){
                distMinima = D[actual][i];
                destino = i;
                //cout << "DISTANCIA MINIMA ACTUAL : " << distMinima << " VISITADO = " << visitado[i] << " DESTINO: " << destino << endl;
            }
        }
        //Se le suma 1 a actual para coincidir con los datos introducidos que van de 1..N mientras que el bucle va de 0..N-1
        solucion.push_back(actual+1);
        if(j == D.size()-1){
            distMinima = D[actual][inicio-1];
            destino = inicio-1;
            solucion.push_back(inicio);
        }
        total+=distMinima;
        actual = destino;
        //Reseteamos la distancia mínima
        distMinima = 999999999;
    }
}
//Igual pero devuelve el vector de ciudades en lugar de la numeración de éstas
void vecinoCercanoUbicacion(const vector<vector<int>> &D, vector<ciudad> &ciudades, int inicio, vector<ciudad> &solucion){
    bool visitado[D.size()] = {false};
    int destino = -1;
    int actual = inicio-1;
    double distMinima = 999999999;

    for(int j = 0; j < D.size(); j++)
    {
        visitado[actual] = true;
        for(int i = 0; i < D.size(); i++){
            //cout << "DISTANCIA de: " << actual << " a : " << i << " ==== " << D[actual][i] << endl;
            if(D[actual][i] < distMinima && !visitado[i] && i != actual){
                distMinima = D[actual][i];
                destino = i;
                //cout << "DISTANCIA MINIMA ACTUAL : " << distMinima << " VISITADO = " << visitado[i] << " DESTINO: " << destino << endl;
            }
        }
        //Se le suma 1 a actual para coincidir con los datos introducidos que van de 1..N mientras que el bucle va de 0..N-1
        solucion.push_back(ciudades[actual]);
        if(j == D.size()-1){
            distMinima = D[actual][inicio-1];
            destino = inicio-1;
            solucion.push_back(ciudades[inicio-1]);
        }
        //El otro actualiza el total y este no ¬¬
        actual = destino;
        //Reseteamos la distancia mínima
        distMinima = 999999999;
    }
}




int main(int argc, char* argv[]){

    string nombre_fichero = argv[1];
    string nombre_recorrido = "";
    vector<ciudad> ciudades = recogerDatos(nombre_fichero, nombre_recorrido);
    vector<ciudad> solucionC;   //Solución en forma de vector de ciudades
    vector<int> solucion;       //Solución en forma de numeración de ciudades
    vector<vector<int>> D;      //Matriz para las Distancias desde la ciudad [i] a la ciudad [i][j]

    int total = 0;           //Distancia total recorrida

    distancia(ciudades, D);

    //La estructura if-else es para mostrar la información por consola de diferentes formas
    // 1 - ./cercano <nombre_fichero>
    // 2 - ./cercano <nombre_fichero> <ciudad_inicial(int)>
    // 3 - ./cercano <nombre_fichero> <ciudad_inicial(int)> <anything> [para redireccionar la salida a .tsp, devuelve vector de ciudad]
    // 4 - ./cercano <nombre_fichero> <ciudad_inicial(int)> <anything> <anything> [devuelve el tiempo de ejecucion]

    cout<< nombre_recorrido << endl;
    //1
    if(argc == 2){
        vecinoCercano(D, 1, solucion,total);
        for(int i = 0; i < solucion.size(); i++)
            cout << solucion[i] << endl;

        cout << endl << "Distancia total: " << total << endl;
    }
    //2
    else if(argc == 3){
        int n = atoi(argv[2]);
        vecinoCercano(D, n, solucion,total);
        for(int i = 0; i < solucion.size(); i++)
            cout << solucion[i] << endl;

        cout << endl << "Distancia total: " << total << endl;
    }
    //3
    else if(argc == 4){
        int n = atoi(argv[2]);
        vecinoCercanoUbicacion(D, ciudades, n, solucionC);
        for(int i = 0; i < solucionC.size(); i++)
            cout << solucionC[i].n << "\t" << solucionC[i].x << "\t" << solucionC[i].y << endl;
    }
    //4
    else if(argc == 5){
        int n = atoi(argv[2]);
        high_resolution_clock::time_point tantes, tdespues;
        duration<double> transcurrido;
        tantes = high_resolution_clock::now();
        vecinoCercanoUbicacion(D, ciudades, n, solucionC);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues-tantes);
            cout << transcurrido.count() << endl;
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