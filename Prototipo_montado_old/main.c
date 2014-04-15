
/**
* @brief Main del prototipo
* @file main.c
* @author Albert Soler
* @version 0.01
* @date 26-03-2014
*
*/


#include "WorldReader/WorldXMLReader.h"

/*=== Definiciones ==========================================================*/
#define MAX 100 /*Numero máximo de caracteres*/

int main(int argc, char* argv[]) {

	FILE *f = NULL
	FILE *xml = NULL;
	char nombre_fichero[MAX];
	char entrada[MAX];
	char entradaXML[MAX];
	World *world=NULL;
	char *ptr; /*Strtok*/
	Action *action;


	/*Comprobamos que el numero de parametros de entrada es 2: archivo,
    nombre fichero entrada, fichero de entrada*/
    if (argc != 3) {
        fprintf(stderr, "Error en los parametros de entrada:\n\n");
        exit(EXIT_FAILURE);
    }

    /*Copia el argumento de entrada a cadena entrada*/
    strcpy(nombre_fichero, argv[1]);
    strcpy(nombre_ficheroXML, argv[2]);


    /*Abrimos el fichero de lectura  y comprobamos que 
     esté bien abierto*/
    f = fopen(nombre_fichero, "r");
    if (f == NULL) {
        printf("\n Error abriendo los ficheros de entrada \n");
        return (EXIT_FAILURE);
    }
        /*Abrimos el fichero de lectura  y comprobamos que 
     esté bien abierto*/
    xml = fopen(nombre_ficheroXML, "r");
    if (xml == NULL) {
        printf("\n Error abriendo los ficheros de entrada \n");
        return (EXIT_FAILURE);
    }

     world=create_world();

    if(STATUS world_load(xml,world)==ERROR){
    	printf("\n Error en world_load");
    	return (EXIT_FAILURE);
    }

    while(!feof(f)){

    	fgets(entrada,MAX,f);
    	ptr=sttok(entrada," "); /*Primer token*/

    	if(strcmp(ptr,"GO")==0)
    		strcpy(ptr,"A_GO");
    	if(strcmp(ptr,"GRAB")==0)
    		strcpy(ptr,"A_PICK_UP");
    	if(strcmp(ptr,"EXAMINE")==0)
    		strcpy(ptr,"A_INSPECT");
    	/*Faltan los otros casos*/

    	if(action_ini(action,ptr,entrada)==ERROR){
    		printf("\n Error en action_ini");
    		return (EXIT_FAILURE)
    	}
    	/*LLamar a action*/
    	if(action_execute(world,action)==ERROR){
    		printf("\n ERROR");
    	}
    	printf("\n OK");

    }

    destroy_world(world);

	return (EXIT_SUCCESS)
}