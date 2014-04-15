/**
* @brief Main de prueba de dialogo
* @file main.c
* @author Albert Soler
* @version 0.01
* @date 14-04-2014
*
*/

#include "DialogueXMLreader.h"
#include "Reglas_dialogo.h"


/*=== Definiciones ==========================================================*/
#define MAX 100 /*Numero máximo de caracteres*/

int main(int argc, char* argv[]) {

	FILE *xml = NULL;
	char nombre_ficheroXML[MAX]="";
	DialogueRules *dr=NULL;


	/*Comprobamos que el numero de parametros de entrada es 2: archivo,
    nombre fichero xml*/
    if (argc != 2) {
        fprintf(stderr, "Error en los parametros de entrada:\n\n");
        return (EXIT_FAILURE);
    }

    /*Copia el argumento de entrada a cadena entrada*/
    strcpy(nombre_ficheroXML, argv[1]);
    
    /*Abrimos el fichero de lectura  y comprobamos que 
    esté bien abierto*/
    xml = fopen(nombre_ficheroXML, "r");
    if (xml == NULL) {
        printf("\n Error abriendo los ficheros de entrada \n");
        return (EXIT_FAILURE);
    }

    /*Creamos el dialogo*/
    dr=create_dialog();

    /*Cargamos el dialogo*/
    if(dialogue_load(nombre_ficheroXML,dr)==ERROR){
    	printf("\n Error en dialogue_load");
    	return (EXIT_FAILURE);
    }

    /*Destruimos el mundo*/   
    destroy_dialog(dr);
    
    /*Cerramos el fichero*/
    fclose(xml);

    return (EXIT_SUCCESS);
}

