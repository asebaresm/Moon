/**
* @brief Main del juego
* @file main.c
* @author Albert Soler
* @version 0.01
* @date 18-04-2014
*
*/

#include "WorldXMLReader.h"
#include "Action.h"
#include "DialogueXMLreader.h"
#include "Reglas_dialogo.h"
#include "UtilCadena.h"
#include <time.h>


/*=== Definiciones ==========================================================*/
#define MAX 100 /*Numero máximo de caracteres*/

int main(int argc, char* argv[]) {

	FILE *dr_xml = NULL;
	char nombre_fichero_dr_XML[MAX]="";
	FILE *game_xml = NULL;
	char nombre_fichero_game_XML[MAX]="";

	DialogueRules *dr=NULL;
	World *world=NULL;

	int cont_oxi=0; /*Contador de oxigeno personal*/
	int cont_lint=0; /*Contador para la linterna*/
	int fin=-1; /*Condicion de victoria*/
	char *ptr; /*Strtok*/

	/*cadenas eliza*/
	char seps[] = {"/,.:;?*!|?¿[]{}+-_$^)(/&%·ºª#@=`^><€¶ŧ←↓→øþ~łĸŋđðßæ«»¢“”µ"};
    char respuesta [MAX] = {'\0'};
    char respuesta_elim_cars [MAX] = {'\0'};
    char respuesta_lim_esp [MAX] = {'\0'};
    char respuesta_a_mayus [MAX] = {'\0'};
    char respuesta_a_ast[MAX] = {'\0'};
    char respuesta_ori [MAX] = {'\0'};
    char respuesta_ant [MAX] = {'\0'}; 
    char dst[MAX] = {'\0'};

    int *pind_patr = NULL;
    int ind_patr;
    pind_patr = &ind_patr;


	/*Comprobamos que el numero de parametros de entrada es 3: archivo,
    fichero juego, fichero de reglas*/
    if (argc != 3) {
        fprintf(stderr, "Error en los parametros de entrada:\n\n");
        exit(EXIT_FAILURE);
    }

    /*Copia el argumento de entrada a cadena entrada*/
    strcpy(nombre_fichero_game_XML, argv[1]);
    strcpy(nombre_fichero_dr_XML, argv[2]);


    /*Abrimos el fichero de lectura  y comprobamos que 
     esté bien abierto*/
    game_xml = fopen(nombre_fichero_game_XML, "r");
    if (game_xml == NULL) {
        printf("\n Error abriendo los ficheros de entrada \n");
        return (EXIT_FAILURE);
    }
    /*Abrimos el fichero de lectura  y comprobamos que 
     esté bien abierto*/
    dr_xml = fopen(nombre_fichero_dr_XML, "r");
    if (dr_xml == NULL) {
        printf("\n Error abriendo los ficheros de entrada \n");
        return (EXIT_FAILURE);
    }

    /*Creamos un mundo*/
    world=create_world();
    /*Creamos el dialogo*/
    dr=create_dialog();


    /*Inicializamos el seed para la funcion rand() de elecciona_plan_sal()*/
    srand(time(NULL));
    /*Lamada a T_INICIO */
    printf("%s \n", select_output_template(search_rule_and_pattern (dr,pind_patr, 0300,0)));

    /*Llamar a T_PREGUNTA aleatoria*/
    printf("\n %s: ", select_random_output_template(T_PREGUNTA));


    do{

    	 fgets(respuesta, MAX, stdin); /*Almacenamos la respuesta del user*/

        /*Mirar que frase no este vacia*/
        if (strlen(respuesta) == 1) {
            printf("\n %s: ", selecciona_plan_sal(busca_regla_y_patron(&patron, T_VACIA, respuesta)));
            continue;
        }
        /*Comprobar que no se repita frase*/
        if (strcmp(respuesta, respuesta_ant) == 0) {
            printf("\n %s: ", selecciona_plan_sal(busca_regla_y_patron(&patron, T_REPETIDO, respuesta)));
            continue;
        }
        strcpy(respuesta_ant, respuesta); /*Copia la respuesta a respuesta anteror para comprar*/

        /*Elimnar caracteres*/
        if (elimina_cars(respuesta_elim_cars, respuesta, seps, MAX) == NULL) {
            printf("\n Error en elimina_cars");
            return -1;
        }
        /*limpia espacios*/
        if (limpia_espacios(respuesta_lim_esp, respuesta_elim_cars, MAX) == NULL) {
            printf("\n Error en limpia_espacios");
            return -1;
        }
        strcpy(respuesta_ori, respuesta_lim_esp); /* Almacenamos la cadena para sustituyte astericos*/
        /*Pasar a mayus*/
        if (a_mayusculas(respuesta_a_mayus, respuesta_lim_esp, MAX) == NULL) {
            printf("\n Error en a_mayusculas");
            return -1;
        }
        /*Copiar la cadena dst en respuesta*/
        strcpy(respuesta, respuesta_a_mayus);

        /*Comparar la cadena con la palabra para salir*/
        if(strcmp(respuesta,"SALIR")==0){
        	fin = 2; /*Finaliza el juego, pero no porque halla ganado o perdido*/
        	break;
        }

        /*Comparar la cadena con la palabra para pedir ayuda*/
        if(strcmp(respuesta,"AYUDA")==0){
        	printf("%s \n", select_output_template(search_rule_and_pattern (dr,pind_patr, 0400,0)));
        	continue;
        }


         
        /*Utilizamos la funcion strtok para separar la cadena por los espacios*/
    	ptr=strtok(respuesta," "); /*Primer token*/
        ptr=strtok(NULL," ");
        /*comparamos la cadena con las acciones*/
    	if(strcmp(respuesta,"IR")==0)
            id=0;
    	if(strcmp(respuesta,"COGER")==0)
            id=1;
        if(strcmp(respuesta,"DEJAR")==0)
            id=2;
        if(strcmp(respuesta,"INSPECCIONAR")==0)
            id=3;
    	if(strcmp(respuesta,"ENCENDER")==0)
            id=4;
        if(strcmp(respuesta,"APAGAR")==0)
            id=5;
    	if(strcmp(respuesta,"HABLAR")==0)
            id=6;


    	/*
        0 A_GO,
        1A_PICK_UP,
        2A_DROP,
        3A_INSPECT,
        4A_TURN_LIGHT_ON,
        5A_TURN_LIGHT_OFF,
        6A_SPEAK
        */
        /*Mirar si el inventario esta lleno cuando hace pick*/
        if (id==1 && (is_player_inv_full(world->player)==TRUE)){
        	printf("\n El inventario esta lleno, no puedes coger más objetos");
        	continue;
        }


        /*Inicilizamos la accion*/
    	if(set_action(action,ptr,id)==ERROR){
    		printf("\n Error en action_ini");
    		return (EXIT_FAILURE);
    	}
    	/*LLamar a action*/
    	if(action_execute(world,action)==ERROR){
    		printf("\n %s: ", select_random_output_template(search_rule_and_pattern (dr,pind_patr,get_id_from_topic(dr,respuesta)+1,respuesta)));
    	}
        else{
        	cont_oxi++;
        	cont_lint++;
        	printf("\n %s: ", select_random_output_template(search_rule_and_pattern (dr,pind_patr,get_id_from_topic(dr,respuesta),respuesta)));
        }

        /*Mirar oxigeno*/
        if(cont_oxi==20)
        	fin=1;
        /*Mirar linterna*/
        if(cont_lint==20){
        	/*FALTA METER LA ID DE LA LINTERNA*/
        	if(consume_obj(world,Id object_id)==ERROR){
        		printf("\n ERROR en consume_obj");
        		return (EXIT_FAILURE);
        	}
        	printf("\n Se le han acabado las pilas a la linterna y ha desaparecido");

        }


    }while(fin==-1)

    /*Fin=0 te has pasado el juego, fin=1 mueres, fin=2 has abandonado*/
    printf("%s \n", select_output_template(search_rule_and_pattern (dr,pind_patr, 03500,fin)));




    /*Destruimos el dialogo*/   
    destroy_dialog(dr);
    /*Destruimos el mundo*/   
    destroy_world(world);  
    /*Cerramos los ficheros*/
    fclose(dr_xml);
    fclose(game_xml);

	return (EXIT_SUCCESS);
}