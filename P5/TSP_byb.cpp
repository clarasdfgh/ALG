#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>
#include <chrono>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

#define DATOS

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



typedef struct {
	vector<int> ruta;
	int indice;
	float coste = 0;
} Nodo;

typedef struct{
	float numNodos = 0;
	float maxTamCola = 0;
	float podas = 0;
	double tiempo = 0;
} Info;

Info info;

double distEuclidea (double x1,double y1,double x2,double y2) {
    double aux1, aux2, distancia;
    aux1 = (x2-x1)*(x2-x1);
    aux2 = (y2-y1)*(y2-y1);
    aux2 += aux1;
    distancia = sqrt(aux2);
    return distancia;
}
/*
void calcularDistancia(map<double,pair<double,double>> matriz, vector<vector<double>> &D){
	for(int i = 0; i < D.size(); i++){
		for(int j = 0; j < D.size(); j++){
			if(i != j)
				D[i][j] = distEuclidea(matriz[i+1].first, matriz[i+1].second, matriz[j+1].first, matriz[j+1].second);
			else
				D[i][j] = 0;
			//cout << "D[" << i << "][" << j << "] = " << D[i][j] << "\t\t";
		}
		//cout << endl;
	}
	//cout << endl;
}
*/
class comparadorPri{
	public:
		bool operator()(Nodo &n1, Nodo &n2){
			return n1.coste < n2.coste;
		}
};
bool enRuta(Nodo actual, int ciudad)
{
    bool encontrado = false;
    for(int i=0; i<actual.ruta.size(); i++)
    {
        if(actual.ruta[i] == ciudad)
        {
            encontrado = true;
        }
    }
    return encontrado;
}

//Calcula el camino más corto saliente de cada ciudad a las demas sin visitar
vector<int> calculaMinimos(vector<vector<int>> &D, Nodo actual){
	vector<int> min;

	for(int i = 0; i < D.size(); i++)
	{
	    bool visitada = enRuta(actual, i);
	    if(!visitada)
        {
            int minimo = 99999999;
            for (int j = 0; j < D.size(); j++)
            {
                visitada = enRuta(actual, j);
                if(!visitada)
                {
                    if (i != j)
                    {
                        int evalua = D[i][j];
                        if (evalua < minimo && evalua > 0)
                        {
                            minimo = evalua;
                        }
                    }
                }
            }
            if(minimo != 99999999)
            min.push_back(minimo);
        }
	}
	return min;
}

void vecinoCercano(const vector<vector<int>> &D, int inicio, vector<int> &solucion, int &total){
	bool visitado[D.size()] = {false};
	int destino = -1;
	int actual = inicio-1;
	double distMinima = 999999999;

	//Bucle externo para que se realicen n-ciudades busquedas de la ciudad más cercana
	for(int j = 0; j < D.size(); j++){
		visitado[actual] = true;
		//Bucle interno que itera sobre la fila de distancias de una ciudad previamente seleccionada
		for(int i = 0; i < D.size(); i++){
			//cout << "DISTANCIA de: " << actual << " a : " << i << " ==== " << D[actual][i] << endl;
			//Si la distancia que está comprobando es menor que la almacenada para la ciudad ACTUAL y no se ha visitado aún y no es la misma ciudad
			//se almacenan los nuevos datos de la ciudad, seleccionandola como distancia minima y siguiente destino.
			if(D[actual][i] < distMinima && !visitado[i] && i != actual){
				distMinima = D[actual][i];
				destino = i;
				//cout << "DISTANCIA MINIMA ACTUAL : " << distMinima << " VISITADO = " << visitado[i] << " DESTINO: " << destino << endl;
			}
		}
		//Introduce la solución encontrada por el bucle interno al vector de soluciones (solucion)
		//se le suma 1 a actual para coincidir con los datos introducidos que van de 1..N mientras que el
		//bucle va de 0..N-1
		//solucion.push_back(actual+1);
		//Cuando ya es la última iteración del bucle externo y, por lo tanto, ya se ha pasado
		//por todas las ciudades, añadimos la inicial (de donde partimos a buscar la mas cercana) para convertir la solucion en un ciclo cerrado.
		if(j == D.size()-1){
			//distMinima = 0;
			distMinima = D[actual][inicio-1];
			//destino = inicio-1;
			//solucion.push_back(inicio);
		}
		//contador de la distancia total recorrida
		total+=distMinima;
		//Actualizamos el siguiente destino para la proxima iteración del bucle externo
		actual = destino;
		//Reseteamos la distancia mínima
		distMinima = 999999999;
	}
}
int calcularCotaLocal(Nodo actual, vector<int> dist_min)
{
    int solucion=actual.coste;
    for(int i=0; i<dist_min.size(); i++)    //Cada ciudad
    {
            solucion += dist_min[i];
    }
    //devolver la suma total
    return solucion;
}
int calcularCotaGlobal(vector<vector<int>> D){
	vector<int> sol;
	int total;
	vecinoCercano(D,1,sol,total); 
	//cout << " TOTAL = " << total << endl;
	return total;
}


Nodo BB(vector<vector<int>> &D){
	priority_queue<Nodo,vector<Nodo>,comparadorPri> vivos;
	int dim = D.size();
	int cotaLocal;

	Nodo mejor;
	mejor.ruta.push_back(1);    //añadir la ciudad 1 a la ruta
	mejor.indice = 1;

	vector<int> dist_min = calculaMinimos(D, mejor);
    /*
	for(int i = 0; i < mejor.ruta.size(); i++){
		mejor.mejor_camino += dist_min[i];
		//cout << mejor.mejor_camino << " \t " << dist_min[i] << endl;
	}
     */
	//int maximo = 0;

	vivos.push(mejor);
	int max = 1, cont = 1;
	mejor.coste = calcularCotaGlobal(D);
	//cout << "COSTE = " << mejor.coste << endl;

	while(!vivos.empty()){
		Nodo actual = vivos.top();
		vivos.pop();
		info.numNodos++;
		cont--;
		//Buscar la ciudad actual y borrarla de sin_visitar


		dist_min = calculaMinimos(D, actual);
		//cout << "INICIO" << endl;
		/*for(int i=0; i<dist_min.size(); i++)
        {
		    cout << i << ": " << dist_min[i] << endl;
        }
        */
		cotaLocal = calcularCotaLocal(actual, dist_min);
        /*
        if(actual.indice < dim-1)
        {
            cout << "Cota Local: " << cotaLocal << endl;
            cout << "Cota Global: " << mejor.coste << endl << endl;
        }
        */
		//Si es fin de ruta
		if(actual.indice == dim){
			float costeTotal = actual.coste + D[actual.ruta[dim-1]][actual.ruta[0]];    //Sumarle el coste de la ultima ciudad a la inicial

			//Comprueba si es mejor que el encontrado hasta ahora
			if(costeTotal < mejor.coste){
				mejor.ruta = actual.ruta;               //actualizar la mejor ruta definitiva
				mejor.ruta.push_back(actual.ruta[0]);   //añadir la ciudad inicial a la ruta definitiva
				mejor.coste = costeTotal;               //Actualuzar la cotaGlobal
			}
		}
		// ver si la cota Local es mejor que la cota Global (mejor.coste)
		else if(cotaLocal < mejor.coste)
		{
		    //Generar todos los hijos de ciudades que no esten ya en la ruta
			for(int i = 0; i < dim; i++)
			{
			    if(!enRuta(actual, i))
                {
                    Nodo hijo(actual);
                    hijo.ruta.push_back(i);

                    hijo.coste += D[hijo.ruta[hijo.indice - 1]][hijo.ruta[hijo.indice]];
                    hijo.indice++;

                    vivos.push(hijo);
                    cont++;
                    if (cont > max)
                        max = cont;
                    /*if(vivos.size() > maximo)
                        maximo = vivos.size();*/
                }
	        }
		}
		else
        {
			//No se explora, se poda
			info.podas++;
		}
	}
	info.maxTamCola=max;
	//cout << "VIVOS = " << maximo << endl;
	return mejor;
}

int main(int argc, char *argv[]){
	vector<vector<int>> D;
	Nodo N;
    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> transcurrido;

	string s;
	if(argc == 1){
		cout << "Falta el documento con los datos\n";
		exit(1);
	}
    string nombre_fichero = argv[1];
    string nombre_recorrido = "";

    vector<ciudad> ciudades = recogerDatos(nombre_fichero, nombre_recorrido);
    distancia(ciudades, D);

	tantes = chrono::high_resolution_clock::now();
    N = BB(D);
    tdespues = chrono::high_resolution_clock::now();
    transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues - tantes);

    info.tiempo = transcurrido.count();

    ofstream salidaDatos;
    ofstream salidaTiempo;
    ofstream salidaTiempoTodos;
    string sd = "./Salidas/";
    sd+=argv[1];
    sd+="_Salida.dat";
    string st  = "./Tiempos/";
    st+=argv[1];
    st+="_Tiempo.dat";
    string stGlobal = "./Tiempos/tiempos.dat";
    salidaDatos.open(sd);
    salidaTiempo.open(st);
    salidaTiempoTodos.open(stGlobal, std::ios_base::app | std::ios_base::out);

    cout << "Dimension: " << N.ruta.size() << endl;
    /*
    for(int i = 0; i < N.ruta.size(); i++){
        cout << N.ruta[i]+1 << " " << ciudades[N.ruta[i]+1].x << " " << ciudades[N.ruta[i]+1].y << endl;
        if(salidaDatos.is_open())
        	salidaDatos << N.ruta[i]+1 << " " << ciudades[N.ruta[i]+1].x << " " << ciudades[N.ruta[i]+1].y << endl;
    }
    */
    for(int i = 0; i < N.ruta.size(); i++){
        cout << N.ruta[i] << " " << ciudades[N.ruta[i]].x << " " << ciudades[N.ruta[i]].y << endl;
        if(salidaDatos.is_open())
            salidaDatos << N.ruta[i]+1 << " " << ciudades[N.ruta[i]+1].x << " " << ciudades[N.ruta[i]+1].y << endl;
    }
    #ifdef DATOS
        cout << endl << endl << endl << endl;
        cout << "Mejor coste: " << N.coste << endl;
        cout << "Nodos expandidos: " << info.numNodos << endl;
        cout << "Tamaño maximo de cola: " << info.maxTamCola << endl;
        cout << "Podas: " << info.podas << endl;
        cout << "Tiempo: " << info.tiempo << endl;
        if(salidaTiempo.is_open()){
        	salidaTiempo << D.size() << " " << info.tiempo << endl;
        	salidaTiempo.close();
        }
        if(salidaTiempoTodos.is_open()){
        	salidaTiempoTodos << D.size() << " " << info.tiempo << endl;
        	salidaTiempoTodos.close();
        }
    #endif

    if(salidaDatos.is_open())
   		salidaDatos.close();
}
