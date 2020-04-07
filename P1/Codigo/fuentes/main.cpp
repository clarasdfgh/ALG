#include "AlgoritmosBusqueda.h"
#include "Constantes.h"
#include "TestBusqueda.h"
#include "Menu.h"
int main()
{
	int opc;
	do{
		cout << sangria << sangria << "Practica 3. Jorge Gangoso Kloeck";
		cout << linea << linea << sangria << "--- *U* MENU PRINCIPAL *U* ---";
		cout << linea << linea << sangria << "1.- MENU ORDENACION";
		cout << linea << linea << sangria << "2.- MENU BUSQUEDA";
		cout << linea << linea << sangria << "3.- MENU OTROS";
		cout << linea << linea << sangria << "0.- SALIR";
		cout << linea << linea << sangria << "^^^^^^^^^^^^^^^^^^^^^^^^^^";
		cout << linea << linea << sangria << "Elige opcion: ";
		cin >> opc;
		switch (opc)
		{
		case 1:
			system("cls");
			menu(1);
			break;
		case 2:
			system("cls");
			menu(2);
			break;
		case 3:
			system("cls");
			menu(3);
			break;
		default:
			break;
		}

	} while (opc != 0);



	cout << linea;
	system("pause");
}