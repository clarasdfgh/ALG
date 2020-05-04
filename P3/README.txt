INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN

TSP POR CERCANÍA
g++ TSP_cercania.cpp -o cercania
./cercania <nombreFichero> (optional <ciudad_inicial> <salida_vector_ciudades> <salida_tiempo>)

TSP POR INSERCIÓN
g++ TSP_insercion.cpp -o insercion
./insercion <nombreFichero>

TSP POR MÉTODO PROPIO
g++ codigoMetodoPropioRe.cpp -o metodoPropio
./metodoPropio <nombreFichero>

TRABAJADORES Y TAREAS
g++ trabajadores_tareas.cpp -o greedy
./greedy <n>
./greedy <n> D 
