/**
 * @brief Main del juego
 * @file main.c
 * @author Albert Soler
 * @version 0.01
 * @date 18-04-2014
 *
 */
#include "DialogueXMLreader.h"
#include "WorldXMLReader.h"
#include "Action.h"
#include "Reglas_dialogo.h"
#include "UtilCadena.h"

/*=== Definiciones ==========================================================*/

int main(int argc, char* argv[]) {

    FILE *dr_xml = NULL;
    char nombre_fichero_dr_XML[MAX] = "";
    FILE *game_xml = NULL;
    char nombre_fichero_game_XML[MAX] = "";

    Id id_topic = NO_ID;

    DialogueRules *dr = NULL;
    World *world = NULL;
    Action *action = NULL;

    int cont_oxi = 0; /*Contador de oxigeno personal*/
    int cont_lint = 0; /*Contador para la linterna*/
    int fin = -1; /*Condicion de victoria*/
    char *ptr = NULL; /*Strtok*/
    Id id = -1;
    char cadena[MAX] = {'\0'};
    int tam = 0;
    int i = 0;

    /*cadenas eliza*/
    char seps[] = {"/,.:;?*!|?¿[]{}+-_$^)(/&%·ºª#@=`^><€¶ŧ←↓→øþ~łĸŋđðßæ«»¢“”µ"};
    char respuesta [MAX] = {'\0'};
    char respuesta_elim_cars [MAX] = {'\0'};
    char respuesta_lim_esp [MAX] = {'\0'};
    char respuesta_a_mayus [MAX] = {'\0'};
    char respuesta_ori [MAX] = {'\0'};
    char dst[MAX] = {'\0'};
    char respuesta_a_ast[MAX] = {'\0'};
    char *preturn = NULL;

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
        printf("\n Error abriendo los ficheros de entrada 2 \n");
        return (EXIT_FAILURE);
    }

    /*Creamos un mundo*/
    world = create_world();
    /*Cargamos el mundo*/
    if (world_load(nombre_fichero_game_XML, world) == ERROR) {
        printf("\n Error en world_load");
        return (EXIT_FAILURE);
    }
    /*Creamos el dialogo*/
    dr = create_dialog();
    if (dialogue_load(nombre_fichero_dr_XML, dr) == ERROR) {
        printf("\n Error en dialogue_load");
        return (EXIT_FAILURE);
    }

    /*Inicializamos el seed para la funcion rand() de elecciona_plan_sal()*/
    srand(time(NULL));
    /*Lamada a T_INICIO */
    id_topic = 3000;
    printf("\n%s", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, id_topic, "0")));

    /*Llamar a T_PREGUNTA aleatoria*/
    /*printf("\n %s: ", select_random_output_template(T_PREGUNTA));*/
    /*printf("\n\n");*/
    printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
    do {


        /*Lamada a T_INICIO */
        id_topic = 3000;
        printf("\n\n%s", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, id_topic, "1")));
        printf("\n ==> ");
        fgets(respuesta, MAX, stdin); /*Almacenamos la respuesta del user*/
        respuesta[strlen(respuesta) - 1] = '\0';
        /*Mirar que frase no este vacia*/
        if (strlen(respuesta) == 0) {
            /*Lamada a T_VACIA */
            id_topic = 6000;
            printf("\n\n\n\n");
            printf("\n %s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, id_topic, "0")));
            continue;
        }
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
        if (strncmp(respuesta, "SALIR", 5) == 0) {
            fin = 2; /*Finaliza el juego, pero no porque halla ganado o perdido*/
            break;
        }

        /*Comparar la cadena con la palabra para pedir ayuda*/
        if (strncmp(respuesta, "AYUDA", 5) == 0) {
            id_topic = 4000;
            printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, id_topic, "AYUDA")));
            continue;
        }
        /*Comparar la cadena con la palabra para ver inventario completo*/
        if (strncmp(respuesta, "TODO INVENTARIO", 15) == 0) {
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("\n El inventario al completo es: ");
            /*continue;*/
            if (print_inventory_full(world) == ERROR) {
                printf("\n Error en print_inventory_full");
                return ERROR;
            }
            continue;
        }
        /*Comparar la cadena con la palabra para ver inventario*/
        if (strncmp(respuesta, "INVENTARIO", 10) == 0) {
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("\n Ahora mismo llevas en tu inventario: ");
            /*continue;*/
            if (print_inventory(world) == ERROR) {
                printf("\n Error en print_inventory");
                return ERROR;
            }
            continue;
        }


        preturn = elimina_verbo_accion(respuesta);
        /*Utilizamos la funcion strtok para separar la cadena por los espacios*/
        ptr = NULL;
        ptr = strtok(respuesta, " "); /*Primer token*/
        ptr = strtok(NULL, " ");
        id = -1;
        /*comparamos la cadena con las acciones*/
        if (strcmp(respuesta, "IR") == 0)
            id = 0;
        if (strcmp(respuesta, "COGER") == 0)
            id = 1;
        if (strcmp(respuesta, "DEJAR") == 0)
            id = 2;
        if (strcmp(respuesta, "INSPECCIONAR") == 0)
            id = 3;
        if (strcmp(respuesta, "ENCENDER") == 0)
            id = 4;
        if (strcmp(respuesta, "APAGAR") == 0)
            id = 5;
        if (strcmp(respuesta, "HABLAR") == 0)
            id = 6;
        if (strcmp(respuesta, "ABRIR") == 0)
            id = 7;

        if (id == -1) {
            /*Lamada a T_TONTA */
            id_topic = 5000;
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, id_topic, "0")));

            continue;
        }
        /*Mirar si el inventario esta lleno cuando hace pick*/
        if (id == 1 && (is_player_inv_full(world_get_player(world)) == TRUE)) {
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("\n El inventario esta lleno, no puedes coger más objetos");
            continue;
        }

        /*Inicilizamos la accion*/
        /*if (set_action(action, preturn, id) == ERROR) {
            printf("\n Error en set_action");
            return (EXIT_FAILURE);
        }*/
        /*Creamos una nueva accion*/
        if ((action = new_action(preturn, id)) == NULL) {
            printf("\n Error en new_action");
            return (EXIT_FAILURE);
        }
        /*LLamar a action*/
        if (action_execute(world, action) == ERROR) {
            if (id == 0) {
                printf("\n\n\n\n");
                printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
                printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta), respuesta)), preturn, MAX));
            } else { /*Remplaza asteriscos*/
                i = 0;
                tam = size_rule_pattern(dr, search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta_a_mayus) + 10, respuesta_a_mayus), 0);
                while (tam < strlen(respuesta_ori)) {
                    respuesta_a_ast[i] = respuesta_ori[tam];
                    tam++;
                    i++;
                }
                /*respuesta_a_ast[i-1]='\0';*/
                printf("\n\n\n\n");
                printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
                printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta_a_mayus) + 10, respuesta_a_mayus)), respuesta_a_ast, MAX));
                /*Limpiarcadena entera*/
                memset(respuesta_a_ast, 0, MAX);

            }
        } else {
            /*Contadores*/
            if ((id > 0 && id < 4) || id == 7)
                cont_oxi++;
            if (id == 4 && (strncmp(preturn, "LINTERNA", strlen("LINTERNA")) == 0))
                cont_lint++;
            if (id == 0) {
                printf("\n\n\n\n");
                printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
                printf("\n%s.", select_random_output_template(dr, search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta_a_mayus), respuesta_a_mayus)));
            } else { /*Remplaza asteriscos*/

                i = 0;
                tam = size_rule_pattern(dr, search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta_a_mayus) + 10, respuesta_a_mayus), 0);
                while (tam < strlen(respuesta_ori)) {
                    respuesta_a_ast[i] = respuesta_ori[tam];
                    tam++;
                    i++;
                }
                /*respuesta_a_ast[i-1]='\0';*/
                printf("\n\n\n\n");
                printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
                printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta_a_mayus), respuesta_a_mayus)), respuesta_a_ast, MAX));
                /*Limpiarcadena entera*/
                memset(respuesta_a_ast, 0, MAX);
            }
        }
        destroy_action(action);
        /*if (id == 0)
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));*/


        /*Mirar oxigeno*/
        if (cont_oxi == 20)
            fin = 1;
        /*Mirar linterna*/
        if (cont_lint == 20) {
            if (consume_obj(world, 28) == ERROR) {
                printf("\n ERROR en consume_obj");
                return (EXIT_FAILURE);
            }
            cont_lint = 3;
            printf("\n Se le han acabado las pilas a la linterna\n ");

        }
        if (game_finish(world) == TRUE)
            fin = 0;
        free(preturn);
    } while (fin == -1);

    /*Fin=0 te has pasado el juego, fin=1 mueres, fin=2 has abandonado*/
    /*Falta meter fin como 4 argumento*/
    id_topic = 3500;
    printf("\n\n\n\n");
    sprintf(cadena, "%d", fin);
    printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
    printf("\n\n");
    printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, id_topic, cadena)));


    /*Destruimos el dialogo*/
    destroy_dialog(dr);
    /*Destruimos el mundo*/
    destroy_world(world);
    /*Cerramos los ficheros*/



    fclose(dr_xml);
    fclose(game_xml);

    return (EXIT_SUCCESS);
}
