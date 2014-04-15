#   Proyecto de Programacion
# 	Escuela Politecnica Superior - UAM
# 	Fecha: enero 2014
#   Asignatura: Proyecto de programacion
#	Equipo: 02

#=============================================================
# Entorno de desarrollo y opciones
#=============================================================
# Compilador
CC= gcc -ansi -pedantic 
CFLAGS= -g -Wall
CXML2=`xml2-config --cflags`
LXML2=`xml2-config --libs`
# Directorio en el que se encuentra el proyecto
DIR=Prototipo_v1.0
#=============================================================
# Archivos que componen el proyecto
#=============================================================
## Nombre de los ejecutables separados por espacio
EJECUTABLES=wrprinter-en test_inventory test_link test_object test_player test_set  test_space test_world
EJECUTABLES_TEST=test_inventory test_link test_object test_player test_set  test_space test_world
OBJETOS_TEST=test_inventory.o test_link.o test_object.o test_player.o test_set.o  test_space.o test_world.o
OBJETOS=WorldXMLPrinter-en.o WorldXMLReader.o set.o object.o inventory.o space.o link.o player.o world.o
#=============================================================
# Construccion de los ejecutables
#=============================================================
all: $(EJECUTABLES) autores

all_tests: $(EJECUTABLES_TEST) autores

#ejecutables del world_reader:
wrprinter-en: WorldXMLPrinter-en.o WorldXMLReader.o
	${CC} ${CFLAGS} -o  $@ $^ ${LXML2}

#ejecutables de los tests:
test_set: test_set.o Set.o
	@echo Generando test_set ...
	$(CC) $(CFLAGS) -o test_set test_set.o Set.o

test_object: test_object.o Object.o Set.o
	@echo Generando test_set ...
	$(CC) $(CFLAGS) -o test_object test_object.o Object.o Set.o

test_inventory: test_inventory.o Inventory.o Set.o
	@echo Generando test_inventory ...
	$(CC) $(CFLAGS) -o test_inventory test_inventory.o Inventory.o Set.o

test_space: test_space.o Space.o Set.o
	@echo Generando test_space ...
	$(CC) $(CFLAGS) -o test_space test_set.o Space.o Set.o

test_link: test_link.o Link.o
	@echo Generando test_link
	$(CC) $(CFLAGS) -o test_link test_link.o Link.o

test_player: test_player.o Player.o Inventory.o Set.o
	@echo Generando test_player
	$(CC) $(CFLAGS) -o test_player test_player.o Player.o Inventory.o Set.o

test_world: test_world.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o
	@echo generando test_world
	$(CC) $(CFLAGS) -o test_world test_world.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o

#=============================================================
# Generacion .o
#=============================================================

#Todos los objetos de pruebas:
objetos_test: $(OBJETOS_TEST) 

#Todos los objetos de los modulos + world reader:
objetos: $(OBJETOS) 

#Objetos del world reader
WorldXMLPrinter-en.o: WorldXMLPrinter-en.c Consts.h  Link.h  Object.h  Player.h  Space.h  World.h
	${CC} ${CFLAGS} ${CXML2} -c  $<

WorldXMLReader.o: WorldXMLReader.c WorldXMLReader.h
	${CC} ${CFLAGS} ${CXML2} -c  $< ${LXML2}

Set.o: ./Set/Set.c
	@echo Compilando Set.c ...
	$(CC) $(CFLAGS) -c ./Set/Set.c

Object.o: ./Object/Object.c 
	@echo Compilando object.c ...
	$(CC) $(CFLAGS) -c ./Object/Object.c

Inventory.o: ./Inventory/Inventory.c
	@echo Compilando Inventory.c ...
	$(CC) $(CFLAGS) -c ./Inventory/Inventory.c

Space.o: ./Space/Space.c
	@echo Compilando Space.c ...
	$(CC) $(CFLAGS) -c ./Space/Space.c

Link.o: ./Link/Link.c
	@echo Compilando Link.c ...
	$(CC) $(CFLAGS) -c ./Link/Link.c

Player.o: ./Player/Player.c
	@echo Compilando Player.c ...
	$(CC) $(CFLAGS) -c ./Player/Player.c

World.o: ./World/World.c
	@echo Compilando World.c ...
	$(CC) $(CFLAGS) -c ./World/World.c

test_set.o: ./Set/test_set.c
	@echo Compilando test_set.c ...
	$(CC) $(CFLAGS) -c ./Set/test_set.c

test_object.o: ./Object/test_object.c
	@echo Compilando test_object.c ...
	$(CC) $(CFLAGS) -c ./Object/test_object.c

test_inventory.o: ./Inventory/test_inventory.c
	@echo Compilando test_inventory.c ...
	$(CC) $(CFLAGS) -c ./Inventory/test_inventory.c

test_space.o: ./Space/test_space.c
	@echo Compilando test_space.c ...
	$(CC) $(CFLAGS) -c ./Space/test_space.c

test_link.o: ./Link/test_link.c
	@echo Compilando test_link.c ...
	$(CC) $(CFLAGS) -c ./Link/test_link.c

test_player.o: ./Player/test_player.c
	@echo Compilando test_player.c ...
	$(CC) $(CFLAGS) -c ./Player/test_player.c

test_world.o: ./World/test_world.c
	@echo Compilando test_world.c ...
	$(CC) $(CFLAGS) -c ./World/test_world.c

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
# Extras
#=============================================================

party_hard:
	vlc DBMD.mp3

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
	@echo \	
	@echo Uso: make [Objetivo]

	@echo "make \t\t\t     Make all"
	@echo "make all_tests \t\t     Crea todos los ejecutables de pruebas"
	@echo "make objetos \t\t     Crea todos los objetos de los modulos"
	@echo "make objetos_test \t     Crea todos los objetos de los modulos de pruebas"

	@echo "make test_set \t\t     Crea el ejecutable test_set"
	@echo "make test_object \t     Crea el ejecutable test_object"
	@echo "make test_inventory \t     Crea el ejecutable test_inventory"
	@echo "make test_player \t     Crea el ejecutable test_player"
	@echo "make test_space \t     Crea el ejecutable test_space"
	@echo "make test_link \t\t     Crea el ejecutable test_link"
	@echo "make test_space \t     Crea el ejecutable test_space"
	@echo "make test_world \t     Crea el ejecutable test_world"

	@echo "make dist \t\t     Genera el archivo de distribucion .tgz"
	@echo "make limpia \t\t     Limpia los ficheros temporales"
	@echo \
