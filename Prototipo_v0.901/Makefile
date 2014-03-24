#   Proyecto de Programacion
# 	Escuela Politecnica Superior - UAM
# 	Fecha: enero 2014
#   Asignatura: Proyecto de programacion
#	Equipo: 02

#=============================================================
# Entorno de desarrollo y opciones
#=============================================================
# Compilador
CC=gcc -ansi -pedantic 
CFLAGS=-g -Wall
# Directorio en el que se encuentra el proyecto
DIR=ElizaBasico
#=============================================================
# Archivos que componen el proyecto
#=============================================================
## Nombre de los ejecutables separados por espacio
EJECUTABLES=cliutilcadena clireglas eliza
#=============================================================
# Construccion de los ejecutables
#=============================================================

all: $(EJECUTABLES) autores

eliza: eliza.o 	Reglas.o UtilCadena.o
	@echo Generando eliza ...
	$(CC) $(CFLAGS) -o eliza eliza.o Reglas.o UtilCadena.o

clireglas: clireglas.o Reglas.o
	@echo Generando clireglas ...
	$(CC) $(CFLAGS) -o clireglas Reglas.o clireglas.o  

cliutilcadena: cliutilcadena.o  UtilCadena.o
	@echo Generando utilcadena ...
	$(CC) $(CFLAGS) -o cliutilcadena UtilCadena.o cliutilcadena.o 

#=============================================================
# Generacion .o
#=============================================================
eliza.o: eliza.c Reglas.h UtilCadena.h
	@echo Compilando eliza.c ...
	$(CC) $(CFLAGS) -c eliza.c
reglas.o: Reglas.h Reglas.c
	@echo Compilando reglas.c ...
	$(CC) $(CFLAGS) -c Reglas.c

UtilCadena.o: UtilCadena.h UtilCadena.c
	@echo Compilando UtilCadena.c ...
	$(CC) $(CFLAGS) -c UtilCadena.c
 
clireglas.o: Reglas.h clireglas.c
	@echo Compilando clireglas.c ...
	$(CC) $(CFLAGS) -c clireglas.c	

cliutilcadena.o: UtilCadena.h UtilCadena.c cliutilcadena.c
	@echo Compilando cliutilcadena.c ...
	$(CC) $(CFLAGS) -c cliutilcadena.c	
	
#=============================================================
# Crea un archivo tgz para distribuir el codigo
#=============================================================
## Crea un archivo .tgz eliminando previamente el codigo objeto
dist: limpia
	cd .. ; tar cvzf $(DIR).tgz $(DIR)

#=============================================================
# Limpia fichero temporales
#=============================================================
limpia:
	rm -rf *\.o *\.a $(EJECUTABLES)

#=============================================================
# Mensaje que aparecen al ejecutar MAKE, y que ayuda a identificar los
# autores del trabajo. 
#=============================================================
autores:
	@ echo "----------------------------------------------------------------------"
	@ echo "Proyecto de programacion, desarrollado por el equipo 02 compuesto por:"
	@ echo "Sebares, Alfonso; Yus, Pablo y Soler, Albert.                          "
	@ echo "----------------------------------------------------------------------"

#=============================================================
# Ayuda
#=============================================================
ayuda:	
	@echo Uso: make [Objetivo]
	@echo "make \t\t     Make all"
	@echo "make clireglas \t     Crea el ejecutable clireglas"
	@echo "make cliutilcadena   Crea el ejecutable cliutilcadena"
	@echo "make eliza \t     Crea el ejecutable eliza"
	@echo "make dist \t     Genera el archivo de distribucion .tgz"
	@echo "make limpia \t     Limpia los ficheros temporales"

