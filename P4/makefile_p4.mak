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
# makefile_p4.mak
#
# makefile para la practica 4
#
#############################################################################


#................................................
all:  preambulo \
      TSP_PD  \
      final

#................................................
preambulo:
	@echo
	@echo ------------------------------------------------------------
	@echo Practica 4	
	@echo
	@echo ALGORITMICA
	@echo
	@echo GERMÁN CASTILLA LÓPEZ
	@echo JORGE GANGOSO KLÖCK
	@echo PEDRO JAVIER MORALES LEYVA
	@echo CLARA Mª ROMERO LARA
	@echo Universidad de Granada
	@echo ------------------------------------------------------------
	@echo

#................................................
final: 
	@echo

#................................................
# EJECUTABLES

TSP_PD : TSP_PD.o
	@echo 
	@echo Creando ejecutable: TSP_PD
	@echo 
	g++ -o TSP_PD TSP_PD.o 


#................................................
# OBJETOS 

TSP_PD.o : TSP_PD.cpp

	@echo 
	@echo Creando objeto: TSP_PD.o
	@echo 
	g++ -c -o TSP_PD.o TSP_PD.cpp -std=c++11

#................................................
# LIMPEZA

clean: clean-objs

clean-objs:

	@echo Borrando objetos de la practica

	-rm TSP_PD.o

	@echo ...Borrados objetos de la practica 4
	@echo 

mr.proper:  clean-objs

