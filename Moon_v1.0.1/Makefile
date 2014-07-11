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
DIR= Moon_v1.0.1
#=============================================================
# Archivos que componen el proyecto
#=============================================================
## Nombre de los ejecutables separados por espacio
EJECUTABLES= Moon test_inventory test_link test_object test_player test_set  test_space test_world test_action test_map test_reglas test_lector_reglas test_lector_mundo test_util_cadena
#=============================================================
# Construccion de los ejecutables
#=============================================================
all: $(EJECUTABLES) autores

#juego:
Moon: main.o WorldXMLReader.o DialogueXMLreader.o Action.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o Maps.o UtilCadena.o Reglas_dialogo.o 
	${CC} ${CFLAGS} ${CXML2} -o  $@ $^ ${LXML2}

#ejecutables de los tests:
test_map: test_map.o Maps.o
	@echo Generando test_map
	$(CC) $(CFLAGS) -o test_map test_map.o Maps.o

test_util_cadena: test_util_cadena.o UtilCadena.o
	@echo Generando test_util_cadena
	$(CC) $(CFLAGS) -o test_util_cadena test_util_cadena.o UtilCadena.o 

test_reglas: test_reglas.o Reglas_dialogo.o Set.o
	@echo Generando test_reglas
	$(CC) $(CFLAGS) -o test_reglas test_reglas.o Reglas_dialogo.o Set.o

test_lector_reglas: test_lector_reglas.o DialogueXMLreader.o Reglas_dialogo.o Set.o
	@echo Generando test_lector_reglas
	${CC} ${CFLAGS} ${CXML2} -o  $@ $^ ${LXML2}

test_lector_mundo: test_lector_mundo.o WorldXMLReader.o Action.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o
	@echo Generando test_lector_mundo
	${CC} ${CFLAGS} ${CXML2} -o  $@ $^ ${LXML2}

test_set: test_set.o Set.o
	@echo Generando test_set ...
	$(CC) $(CFLAGS) -o test_set test_set.o Set.o

test_object: test_object.o Object.o Set.o
	@echo Generando test_object ...
	$(CC) $(CFLAGS) -o test_object test_object.o Object.o Set.o

test_inventory: test_inventory.o Inventory.o Set.o
	@echo Generando test_inventory ...
	$(CC) $(CFLAGS) -o test_inventory test_inventory.o Inventory.o Set.o

test_space: test_space.o Space.o Set.o
	@echo Generando test_space ...
	$(CC) $(CFLAGS) -o test_space test_space.o Space.o Set.o

test_link: test_link.o Link.o
	@echo Generando test_link
	$(CC) $(CFLAGS) -o test_link test_link.o Link.o

test_player: test_player.o Player.o Inventory.o Set.o
	@echo Generando test_player
	$(CC) $(CFLAGS) -o test_player test_player.o Player.o Inventory.o Set.o

test_world: test_world.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o
	@echo generando test_world
	$(CC) $(CFLAGS) -o test_world test_world.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o

test_action: test_action.o Action.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o
	@echo generando test_action
	$(CC) $(CFLAGS) -o test_action test_action.o Action.o World.o Space.o Player.o Link.o Object.o Inventory.o Set.o
#=============================================================
# Generacion .o
#=============================================================

#Objetos
main.o: main.c
	@echo Compilando main.c ...
	$(CC) $(CFLAGS) ${CXML2} -c main.c $< ${LXML2}

WorldXMLReader.o: ./WorldReader/WorldXMLReader.c 
	$(CC) $(CFLAGS) ${CXML2} -c  $< ${LXML2}

Maps.o: ./Map/Maps.c
	@echo Compilando Maps.c
	$(CC) $(CFLAGS) -c ./Map/Maps.c

Reglas_dialogo.o: ./Dialogue/Reglas_dialogo.c
	@echo Compilando Reglas_dialogo.c
	$(CC) $(CFLAGS) -c ./Dialogue/Reglas_dialogo.c

UtilCadena.o: ./Dialogue/UtilCadena.c
	@echo Compilando UtilCadena.c
	$(CC) $(CFLAGS) -c ./Dialogue/UtilCadena.c

DialogueXMLreader.o: ./DialogueReader/DialogueXMLreader.c
	@echo Compilando DialogueXMLreader.c
	$(CC) $(CFLAGS) ${CXML2} -c  $< ${LXML2}

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

Action.o: ./Action/Action.c
	@echo Compilando Action.c ...
	$(CC) $(CFLAGS) -c ./Action/Action.c

test_map.o: ./Map/test_map.c
	@echo Compilando test_map.c ...
	$(CC) $(CFLAGS) -c ./Map/test_map.c

test_util_cadena.o: ./Dialogue/test_util_cadena.c
	@echo Compilando test_util_cadena.c ...
	$(CC) $(CFLAGS) -c ./Dialogue/test_util_cadena.c

test_reglas.o: ./Dialogue/test_reglas.c
	@echo Compilando test_reglas.c ...
	$(CC) $(CFLAGS) -c ./Dialogue/test_reglas.c

test_lector_reglas.o: ./DialogueReader/test_lector_reglas.c
	@echo Compilando test_lector_reglas.c ...
	$(CC) $(CFLAGS) ${CXML2} -c ./DialogueReader/test_lector_reglas.c $< ${LXML2}

test_lector_mundo.o: ./WorldReader/test_lector_mundo.c
	@echo Compilando test_lector_mundo.c ...
	$(CC) $(CFLAGS) ${CXML2} -c ./WorldReader/test_lector_mundo.c $< ${LXML2}

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

test_action.o: ./Action/test_action.c
	@echo Compilando test_action.c ...
	$(CC) $(CFLAGS) -c ./Action/test_action.c
#=============================================================
# Crea un archivo tgz para distribuir el codigo
#=============================================================
## Crea un archivo .tgz eliminando previamente el codigo objeto

dist: limpia
	cd .. ; tar cvzf $(DIR).zip $(DIR)

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
	@echo \	
	@echo Uso: make [Objetivo]

	@echo "make \t\t\t\t     Crea todos los ejecutables del proyecto"

	@echo "make test_<nombre del modulo> \t     Crea el test ejecutable del modulo especifico"

	@echo "make dist \t\t\t     Genera el archivo de distribucion .tgz"
	@echo "make limpia \t\t\t     Limpia los ficheros temporales"
