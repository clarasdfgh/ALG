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

void cargarDatos(string &fichero, map<double,pair<double,double>> &matriz){
	ifstream file;
	string s;
	pair<double,double> xy;
	int n, indice, i = 0;

	file.open(fichero.c_str());
	if(file.is_open()){
		file >> s;
		file >> n;
		while(i<n){
			file >> indice >> xy.first >> xy.second;
			matriz[indice] = xy;
			i++;
		}
		file.close();
	}
	else{
		cout << "ERROR EN CARGA DE DATOS" << endl;
	}
}

typedef struct {
	vector<int> ruta;
	int indice;
	float mejor_camino = 0;
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

class comparadorPri{
	public:
		bool operator()(Nodo &n1, Nodo &n2){
			return n1.coste + n1.mejor_camino < n2.coste + n2.mejor_camino;
		}
};

vector<double> calculaMinimos(vector<vector<double>> &D){
	vector<double> min;

	for(int i = 0; i < D.size(); i++){
		float minimo = 99999999.0;
		for(int j = i+1; j < D[i].size(); j++){
			float evalua = D[i][j];
			if(evalua < minimo && evalua > 0){
				minimo = evalua;
			}
			min.push_back(minimo);
		}
	}
	return min;
}

void vecinoCercano(const vector<vector<double>> &D, int inicio, vector<int> &solucion, double &total){
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
double calcularCotaLocal(Nodo actual, priority_queue<Nodo,vector<Nodo>,comparadorPri> abiertos)
{
    double solucion=0;
    solucion += actual.coste;
    while(!abiertos.empty())
    {
        solucion += abiertos.top().mejor_camino;
        abiertos.pop();
    }

}
double calcularCotaGlobal(vector<vector<double>> D){
	vector<int> sol;
	double total;
	vecinoCercano(D,1,sol,total); 
	//cout << " TOTAL = " << total << endl;
	return total;
}

Nodo BB(vector<vector<double>> &D){
	priority_queue<Nodo,vector<Nodo>,comparadorPri> vivos;
	double dim = D.size();
	double cotaLocal;

	Nodo mejor;
	mejor.ruta.resize(D.size());
	mejor.indice = 1;
	for(int i = 0; i < D.size(); i++)
		mejor.ruta[i] = i;

	vector<double> dist_min = calculaMinimos(D);
	for(int i = 0; i < mejor.ruta.size(); i++){
		mejor.mejor_camino += dist_min[i];
		//cout << mejor.mejor_camino << " \t " << dist_min[i] << endl;
	}
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
		cotaLocal = calcularCotaLocal(actual, vivos);
		//cout << "COTA LOCAL = " << cotaLocal << endl;

		//Si es fin de ruta
		if(actual.indice == dim){
			float costeTotal = actual.coste + D[actual.ruta[dim-1]][actual.ruta[0]];

			//Comprueba si es mejor que el encontrado hasta ahora
			if(costeTotal < mejor.coste){
				mejor.ruta = actual.ruta;
				mejor.ruta.push_back(actual.ruta[0]);
				mejor.coste = costeTotal;
			}
		}
		// ver si la cota Local (actual.coste+actual.mejor_camino) es mejor que la cota Global (mejor.coste)
		else if(cotaLocal < mejor.coste){
			for(int i = actual.indice; i < dim; ++i){
                Nodo hijo(actual);
                swap(hijo.ruta[i], hijo.ruta[hijo.indice]);

                hijo.coste += D[hijo.ruta[hijo.indice-1]][hijo.ruta[hijo.indice]];
                hijo.mejor_camino -= dist_min[hijo.indice-1];
                hijo.indice++;

                vivos.push(hijo);
                cont++;
                if(cont > max)
                    max = cont;
                /*if(vivos.size() > maximo)
                	maximo = vivos.size();*/
	        }
		}
		else{
			//No se explora, se poda
			info.podas++;
		}

	}
	info.maxTamCola=max;
	//cout << "VIVOS = " << maximo << endl;
	return mejor;
}

int main(int argc, char *argv[]){
	map<double,pair<double,double>> matriz;
	vector<vector<double>> D;
	Nodo N;
    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> transcurrido;

	string s;
	if(argc == 1){
		cout << "Falta el documento con los datos\n";
		exit(1);
	}

	s = argv[1];
	cargarDatos(s,matriz);

	D.resize(matriz.size(),vector<double>(matriz.size(),-1));
	calcularDistancia(matriz,D);

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
    for(int i = 0; i < N.ruta.size(); i++){
        cout << N.ruta[i]+1 << " " << matriz[N.ruta[i]+1].first << " " << matriz[N.ruta[i]+1].second << endl;
        if(salidaDatos.is_open())
        	salidaDatos << N.ruta[i]+1 << " " << matriz[N.ruta[i]+1].first << " " << matriz[N.ruta[i]+1].second << endl;
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
