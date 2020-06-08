#############################################################################
#
# ALGORTIMICA
#
# CURSO 2019-2020
#
# GERMÁN CASTILLA LÓPEZ
#
# JORGE GANGOSO KLÖCK
#
# PEDRO JAVIER MORALES LEYVA
#
# CLARA Mª ROMERO LARA
#
# makefile_p5.mak
#
# makefile para la practica 5
#
#############################################################################


#................................................
all:  preambulo \
      Laberinto \
      TSP_back \
      TSP_byb \
      final

#................................................
preambulo:
	@echo
	@echo ------------------------------------------------------------
	@echo Practica 5	
	@echo
	@echo ALGORITMICA
	@echo
	@echo GERMÁN CASTILLA LÓPEZ
	@echo JORGE GANGOSO KLÖCK
	@echo PEDRO JAVIER MORALES LEYVA
	@echo CLARA Mª ROMERO LARA
	@echo
	@echo Universidad de Granada
	@echo ------------------------------------------------------------
	@echo

#................................................
final: 
	@echo

#................................................
# EJECUTABLES


Laberinto : Laberinto.o generador.o
	@echo 
	@echo Creando ejecutable: Laberinto
	@echo 
	g++ -o Laberinto Laberinto.o generador.o


TSP_back : TSP_back.o
	@echo 
	@echo Creando ejecutable: TSP_back
	@echo 
	g++ -o TSP_back TSP_back.o

TSP_byb : TSP_byb.o
	@echo 
	@echo Creando ejecutable: TSP_byb
	@echo 
	g++ -o TSP_byb TSP_byb.o 


#................................................
# OBJETOS 

generador.o : generador.cpp

	@echo 
	@echo Creando objeto: generador.o
	@echo 
	g++ -c -o generador.o -I./ generador.cpp -std=c++11

Laberinto.o : Laberinto.cpp

	@echo 
	@echo Creando objeto: Laberinto.o
	@echo 
	g++ -c -o Laberinto.o Laberinto.cpp -std=c++11


TSP_back.o : TSP_back.cpp

	@echo 
	@echo Creando objeto: TSP_back.o
	@echo 
	g++ -c -o TSP_back.o TSP_back.cpp -std=c++11

TSP_byb.o : TSP_byb.cpp

	@echo 
	@echo Creando objeto: TSP_byb.o
	@echo 
	g++ -c -o TSP_byb.o TSP_byb.cpp -std=c++11

#................................................
# LIMPEZA

clean: clean-objs

clean-objs:

	@echo Borrando objetos de la practica 5

	-rm *.o

	@echo ...Borrados objetos de la practica 5
	@echo 

clean-bins:

	@echo Borrando ejecutables de la practica 5

	-rm Laberinto TSP_back TSP_byb

	@echo ...Borrados objetos de la practica 5
	@echo 

mr.proper:  clean-objs clean-bins

