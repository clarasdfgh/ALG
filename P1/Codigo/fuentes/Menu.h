#include "TestOrdenacion.h"
#include "TestOtros.h"
#define linea "\n"
#define sangria "\t\t"
typedef char cadena[20];

int menu(int opc)
{
	cadena estado;
	int eleccion;
	if (opc == 1) strcpy_s(estado, "ORDENACION");
	else if (opc == 2) strcpy_s(estado, "BUSQUEDA");
	else if (opc == 3)
	{
		strcpy_s(estado, "OTROS");
		eleccion = 2;
		cin.ignore();

	};
	
	do {
		//** ESCRIBIR PARA COMPLETAR LA PRACTICA **//
		cout << "\n\t" << sangria << "  MENU " << estado << endl;
		cout << "\n\t" << "---ANALISIS EXPERIMENTAL DE ALGORITMOS DE " << estado << "---";
		cout << linea << sangria << "1.- PROBAR LOS METODOS DE " << estado;
		cout << linea << sangria << "2.- OBTENER EL CASO MEDIO DE UN METODO DE " << estado;
		cout << linea << sangria << "3.- COMPARAR DOS METODOS";
		cout << linea << sangria << "0.- VOLVER AL MENU PRINCIPAL";
		cout << linea << sangria << "---------";
		cout << linea << sangria << "Elegir opcion: ";
		cin >> eleccion;

		if (opc == 1)
		{
			TestOrdenacion T1;
			switch (eleccion)
			{
			case 1:
				T1.comprobarMetodosOrdenacion();
				break;
			case 2:
				int seleccion;
				system("cls");
				/*Añadir nuevos algoritmos al menu*/
				cout << linea << sangria << sangria << "*** Metodo a estudiar para el caso medio ***";
				cout << linea << sangria << "0.- BURBUJA";
				cout << linea << sangria << "1.- INSERCION";
				cout << linea << sangria << "2.- SELECCION";
				cout << linea << sangria << "3.- MERGESORT";
				cout << linea << sangria << "4.- QUICKSORT";
				cout << linea << sangria << "5.- HEAPSORT";
				cout << linea << sangria << "-------------------";
				cout << linea << sangria << "Elija la opcion: ";
				cin >> seleccion;
				system("cls");
				T1.casoMedio(seleccion);
				Graficas g;
				switch (seleccion)
				{
					/*Su correspondiente llamada a la grafica y su script de grafica*/
					/*Arreglar los ordenes de complejidad*/
				case 0:
					g.generarGraficaMEDIO("burbuja", 3);
					break;
				case 1:
					g.generarGraficaMEDIO("insercion", 3);
					break;
				case 2:
					g.generarGraficaMEDIO("seleccion", 3);
					break;
				case 3:
					g.generarGraficaMEDIO("mergesort", 2);
					break;
				case 4:
					g.generarGraficaMEDIO("quicksort", 2);
					break;
				case 5:
					g.generarGraficaMEDIO("heapsort", 2);
					break;
				default:
					break;
				}
				system("pause");
				system("cls");
				break;
			case 3:
				int opc1, opc2;
				system("cls");
				/*Añadir nuevos algoritmos para comparar*/
				cout << linea << sangria << sangria << "*** Metodos a comparar ***";
				cout << linea << sangria << "0.- BURBUJA";
				cout << linea << sangria << "1.- INSERCION";
				cout << linea << sangria << "2.- SELECCION";
				cout << linea << sangria << "3.- MERGESORT";
				cout << linea << sangria << "4.- QUICKSORT";
				cout << linea << sangria << "5.- HEAPSORT";
				cout << linea << sangria << "-------------------";
				cout << linea << "Introduzca el primer metodo: ";
				cin >> opc1;
				cout << linea << "Introduzca el segundo metodo: ";
				cin >> opc2;
				system("cls");
				T1.comparar(opc1, opc2);
				/*Y nuevas combinaciones*/
				/*Asi como nuevos scripts de graficas CMP*/
				if (opc1 != opc2) {
					if (opc1 > opc2)
					{
						int temp = opc1;
						opc1 = opc2;
						opc2 = temp;
					}
					switch (opc1)
					{
					case 0:
						switch (opc2)
						{
						case 1:
							g.generarGraficaCMP("burbuja", "insercion");
							break;
						case 2:	
							g.generarGraficaCMP("burbuja", "seleccion");
							break;
						case 3:
							g.generarGraficaCMP("burbuja", "mergesort");
							break;
						case 4:
							g.generarGraficaCMP("burbuja", "quicksort");
							break;
						case 5:
							g.generarGraficaCMP("burbuja", "heapsort");
							break;
						default:
							cout << "Error, numero no disponible" << endl;
						}
						break;
					case 1:
						switch (opc2)
						{
						case 2:
							g.generarGraficaCMP("insercion", "seleccion");
							break;
						case 3:
							g.generarGraficaCMP("insercion", "mergesort");
							break;
						case 4:
							g.generarGraficaCMP("insercion", "quicksort");
							break;
						case 5:
							g.generarGraficaCMP("insercion", "heapsort");
							break;
						default:
							cout << "Error, numero no disponible" << endl;
						}
						break;
					case 2:
						switch (opc2)
						{
						case 3:
							g.generarGraficaCMP("seleccion", "mergesort");
							break;
						case 4:
							g.generarGraficaCMP("seleccion", "quicksort");
							break;
						case 5:
							g.generarGraficaCMP("seleccion", "heapsort");
							break;
						default:
							cout << "Error, numero no disponible" << endl;
						}
						break;
					case 3:
						switch (opc2)
						{
						case 4:
							g.generarGraficaCMP("mergesort", "quicksort");
							break;
						case 5:
							g.generarGraficaCMP("mergesort", "heapsort");
							break;
						default:
							cout << "Error, numero no disponible" << endl;
						}
						break;
					case 4:
						switch (opc2)
						{
						case 5:
							g.generarGraficaCMP("quicksort", "heapsort");
							break;
						default:
							cout << "Error, numero no disponible" << endl;
						}
						break;
					default:
						cout << "Error, numero no disponible" << endl;
					}
				}
				else
					cout << "No se puede comparar dos metodos iguales";
				system("pause");
				system("cls");
				break;
			case 0:
				break;
			default:
				cout << linea << sangria << "Eleccion incorrecta, el programa se detendra." << linea;
				eleccion = 0;
			}
		}
		else if (opc == 2)
		{
			TestBusqueda T2;
			switch (eleccion)
			{
			case 1:
				T2.comprobarMetodosBusqueda();
				break;
			case 2:
				int seleccion;
				system("cls");
				cout << linea << sangria << sangria << "*** Metodo a estudiar para el caso medio ***";
				cout << linea << sangria << "0.- SECUENCIAL";
				/*modificacion*/
				cout << linea << sangria << "1.- SECUENCIAL RC.";

				cout << linea << sangria << "2.- BINARIA";
				/*modificacion*/
				cout << linea << sangria << "3.- BINARIA IT.";

				cout << linea << sangria << "4.- TERNARIA";
				cout << linea << sangria << "-------------------";
				cout << linea << sangria << "Elija la opcion: ";
				cin >> seleccion;
				system("cls");
				T2.casoMedio(seleccion);
				Graficas g;
				switch (seleccion)
				{
				case 0:
					g.generarGraficaMEDIO("secuencial", 3);
					break;
				case 1:
					g.generarGraficaMEDIO("secuencialrc", 1);
					break;
				case 2:
					g.generarGraficaMEDIO("binaria", 0);
					break;
				case 3:
					g.generarGraficaMEDIO("binariait", 3);
					break;
				case 4:
					g.generarGraficaMEDIO("ternaria", 0);
					break;
				default:
					break;
				}
				system("pause");
				system("cls");
				break;

			case 3:
				int opc1, opc2;
				system("cls");
				cout << linea << sangria << sangria << "*** Metodos a comparar ***";
				cout << linea << sangria << "0.- SECUENCIAL";
				cout << linea << sangria << "1.- SECUENCIALrc ";
				cout << linea << sangria << "2.- BINARIArc";
				cout << linea << sangria << "3.- BINARIAit";
				cout << linea << sangria << "4.- TERNARIArc";
				cout << linea << sangria << "-------------------";
				cout << linea << "Introduzca el primer metodo: ";
				cin >> opc1;
				cout << linea << "Introduzca el segundo metodo: ";
				cin >> opc2;
				system("cls");
				T2.comparar(opc1, opc2);
				string nombre1, nombre2;
				switch (opc1)
				{
				case 0:
					nombre1 = "secuencial";
					break;
				case 1:
					nombre1 = "secuencialrc";
					break;
				case 2:
					nombre1 = "binaria";
					break;
				case 3:
					nombre1 = "binariait";
					break;
				case 4:
					nombre1 = "ternaria";
				}
				switch (opc2)
				{
				case 0:
					nombre2 = "secuencial";
					break;
				case 1:
					nombre2 = "secuencialrc";
					break;
				case 2:
					nombre2 = "binaria";
					break;
				case 3:
					nombre2 = "binariait";
					break;
				case 4:
					nombre2 = "ternaria";
					break;
				}
				g.generarGraficaCMP(nombre1, nombre2);
				system("pause");
				system("cls");
				break;
			}

		}
		else
		{
			TestOtros T1;
			switch (eleccion)
			{
			case 2:
			{
				int seleccion;
				system("cls");
				/*Añadir nuevos algoritmos al menu*/
				cout << linea << sangria << sangria << "*** Metodo a estudiar para el caso medio ***";
				cout << linea << sangria << "0.- FLOYD";
				cout << linea << sangria << "1.- FIBONACCI";
				cout << linea << sangria << "-------------------";
				cout << linea << sangria << "Elija la opcion: ";
				cin >> seleccion;
				system("cls");
				T1.casoMedio(seleccion);
				Graficas g;
				switch (seleccion)
				{
					/*Su correspondiente llamada a la grafica y su script de grafica*/
					/*Arreglar los ordenes de complejidad*/
				case 0:
					g.generarGraficaMEDIO("floyd", 4);
					break;
				case 1:
					g.generarGraficaMEDIO("fibonacci", 5);
					break;
				default:
					break;
				}
				system("pause");
				system("cls");
				break;
			}

			default:
			{
				cout << "Opcion no disponible con estos algoritmos, seleccione de nuevo." << linea;
				system("cls");
			}
			}
		}

		
	} while (eleccion != 0);
	system("pause");
	system("cls");
	return 0;
}