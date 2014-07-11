/**
* @brief Main de prueba de dialogo
* @file main.c
* @author Albert Soler
* @version 0.01
* @date 14-04-2014
*
*/

#include "DialogueXMLreader.h"

int main(int argc, char* argv[]) {

	FILE *xml = NULL;
	char nombre_ficheroXML[MAX]="DialogueReader/ex_Dialogo_v1.xml";
	DialogueRules *dr=NULL;

    /*Abrimos el fichero de lectura  y comprobamos que 
    esté bien abierto*/
    printf("\n>>Test de lectura de ex_Dialogo_v1:");
    printf("\nAbriendo fichero...");
    xml = fopen(nombre_ficheroXML, "r");
    if (xml == NULL) {
        printf("\n Error abriendo los ficheros de entrada \n");
        return (EXIT_FAILURE);
    }

    /*Creamos el dialogo*/
    printf("\nGenerando TAD dialogo...");
    dr=create_dialog();

    /*Cargamos el dialogo*/
    printf("\nCargando reglas de dialogo desde el xml...");
    if(dialogue_load(nombre_ficheroXML,dr)==ERROR){
    	printf("\n Error en dialogue_load");
    	return (EXIT_FAILURE);
    }
    printf("\nCompletado sin errores.");
    
    /*Destruimos el mundo*/
    printf("\nLiberando recursos...");   
    destroy_dialog(dr);
    
    /*Cerramos el fichero*/
    printf("\nCerrando fichero xml...");
    fclose(xml);

    printf("\nTest finalizado.\n");
    return (EXIT_SUCCESS);
}

