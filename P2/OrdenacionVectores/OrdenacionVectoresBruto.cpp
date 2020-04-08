#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

double uniforme()
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

vector<vector<int> > generaVector(int n, int k){
  vector<vector<int> > res;
  vector<int> vaux;

  int **T;
  T =  new int * [k];
    assert(T);

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

  for (int i=0; i<k; i++) {
   for (int j=0; j<n; j++)
     vaux.push_back(T[i][j]);
   res.push_back(vaux);
   vaux.clear();
  }

  return res;
}

vector<int> mezclaVectoresOrdenados(vector<int> v1 , vector<int> v2){
  int cont1=0, cont2=0;
  vector<int> v3;

  while (cont1<v1.size() && cont2<v2.size()){
      if (v1[cont1]<v2[cont2]){
          v3.push_back(v1[cont1]);
          cont1++;
      }else if( v1[cont1]>v2[cont2]){
          v3.push_back(v2[cont2]);
          cont2++;
      }else{
          v3.push_back(v1[cont1]);
          cont1++;
          cont2++;
      }
  }

  while (cont1<v1.size()) {
      v3.push_back(v1[cont1]);
      cont1++;
  }

  while (cont2<v2.size()) {
      v3.push_back(v2[cont2]);
      cont2++;
  }

  return v3;
}

int main(int argc, char * argv[]){

  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);


  vector<vector<int> > vInicial = generaVector(n,k);
  int n_vectores = vInicial.size();
  vector<int> vFinal = vInicial[0];
  clock_t tantes;
  clock_t tdespues;


  tantes = clock();
  for(int i = 1; i<n_vectores; i++){
    vector<int> vAux1 = vFinal;
    vector<int> vAux2 = vInicial[i];
    vFinal.clear();

    vFinal = mezclaVectoresOrdenados(vAux1, vAux2);
  }
  tdespues = clock();

    cout << n << " " << (double)(tdespues - tantes) / CLOCKS_PER_SEC << endl;

  /*for(int i=0; i<vInicial.size(); i++){
    vector<int> aux = vInicial[i];
    for(int j=0; j<aux.size(); j++)
      cout << aux[j] << " ";
    cout << endl;
  }

    cout << endl << endl;

    for(int i=0; i<vFinal.size(); i++){
      cout << vFinal[i] << " ";
    }*/
}
