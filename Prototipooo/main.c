
/**
* @brief Main del prototipo
* @file main.c
* @author Albert Soler
* @version 0.01
* @date 26-03-2014
*
*/


#include "WorldXMLReader.h"
#include "Action.h"


/*=== Definiciones ==========================================================*/
#define MAX 100 /*Numero máximo de caracteres*/

int main(int argc, char* argv[]) {

	FILE *f = NULL;
	FILE *xml = NULL;
	char nombre_fichero[MAX]="";
	char entrada[MAX]="";
	char nombre_ficheroXML[MAX]="";
	World *world=NULL;
	char *ptr; /*Strtok*/
	Action *action;
        ActionType id;


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
    /*Creamos un mundo*/
     world=create_world();

    /*Cargamos el mundo*/    
    if( world_load(nombre_ficheroXML,world)==ERROR){
    	printf("\n Error en world_load");
    	return (EXIT_FAILURE);
    }
     /*Creamos una nueva accion*/
    if( (action=new_action("Prueba",2))==NULL){
    	printf("\n Error en new_action");
    	return (EXIT_FAILURE);
    } 
     
     /*Bucle fin de fichero*/
    while(!feof(f)){
        
        /*comprobamos los argumentos de entrada*/
    	if(fgets(entrada,MAX,f)==NULL)
            break;
        /*Utilizamos la funcion strtok para separar la cadena por los espacios*/
    	ptr=strtok(entrada," "); /*Primer token*/
        ptr=strtok(NULL," ");
        /*comparamos la cadena con las acciones*/
    	if(strcmp(entrada,"GO")==0)
            id=0;
    	if(strcmp(entrada,"GRAB")==0)
            id=1;
    	if(strcmp(entrada,"EXAMINE")==0)
            id=3;
    	if(strcmp(entrada,"LEAVE")==0)
            id=2;        
    	/*Faltan los otros casos
            0 A_GO,
        1A_PICK_UP,
        2A_DROP,
        3A_INSPECT,
        4A_TURN_LIGHT_ON,
        5A_TURN_LIGHT_OFF,
         6A_SPEAK
         */
        
        /*Inicilizamos la accion*/
    	if(set_action(action,ptr,id)==ERROR){
    		printf("\n Error en action_ini");
    		return (EXIT_FAILURE);
    	}
    	/*LLamar a action*/
    	if(action_execute(world,action)==ERROR){
    		printf("\n ERROR");
    	}
        else
    	printf("\n OK");

    }

     /*Destruimos el mundo*/   
    destroy_world(world);
    
    /*Cerramos los ficheros*/
    fclose(f);
    fclose(xml);

	return (EXIT_SUCCESS);
}
