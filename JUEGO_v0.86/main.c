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
#include "Maps.h"

/*=== Definiciones ==========================================================*/
#define T_INIT_GAME 3000
#define T_END_GAME 3500
#define T_HELP_CONTROLS 4000
#define T_TONTA 5000
#define T_VACIA 6000
#define T_HABLAR 11000
#define T_HABLAR_ERROR 11010

/*PC-Eliza*/
#define T_PC_INICIO 8000
#define T_PC_AYUDA 8030
#define T_PC_DESPEDIDA 8040
#define T_PC_TONTA 8050
#define T_PC_NORMAL 8060
#define T_PC_FLAG1 8110
#define T_PC_FLAG2 8120
#define T_PC_FLAG3 8130
#define T_PC_VICTORY 8140
#define ID_SALA_MAQUINAS 10


int mini_eliza(DialogueRules *dr);
BOOL is_player_ready_for_space(World *w);
void loadBar(int x, int n, int r, int w);
STATUS bar(int actual, int total);

int main(int argc, char* argv[]) {

    FILE *dr_xml = NULL;
    char nombre_fichero_dr_XML[MAX] = "";
    FILE *game_xml = NULL;
    char nombre_fichero_game_XML[MAX] = "";
    char nombre_lista[WORD_TINY] = "";

    DialogueRules *dr = NULL;
    World *world = NULL;
    Action *action = NULL;

    int cont_oxi = 0; /*Contador de oxigeno personal*/
    int cont_lint = 0; /*Contador para la linterna*/
    int cont_gen = 0; /*Contador generador*/
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
    char new_map[WORD_SIZE] = "";
    char txt_return[WORD_SIZE] = "";

    int *pind_patr = NULL;
    int ind_patr;
    pind_patr = &ind_patr;

    /*Comprobamos que el numero de parametros de entrada es 4: archivo,
fichero juego, fichero de reglas, lista de identificadores de objetos*/
    if (argc != 4) {
        fprintf(stderr, "Error en los parametros de entrada:\n\n");
        exit(EXIT_FAILURE);
    }

    /*Copia el argumento de entrada a cadena entrada*/
    strcpy(nombre_fichero_game_XML, argv[1]);
    strcpy(nombre_fichero_dr_XML, argv[2]);
    strcpy(nombre_lista, argv[3]);

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

    printf("\n%s", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_INIT_GAME, "0")));

    /*Llamar a T_PREGUNTA aleatoria*/
    /*printf("\n %s: ", select_random_output_template(T_PREGUNTA));*/
    /*printf("\n\n");*/
    printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
    do {
        printf("\n Contadores: \n");
        printf("Oxigeno:  ");
        bar(50-cont_oxi,50);
        /*loadBar(10 - cont_oxi, 10, 1, 100);*/
        printf("Linterna: ");
        bar(8-cont_lint,8);
        /*loadBar(10 - cont_lint, 10, 1, 100);*/
        printf("Generador:");
        bar(8-cont_gen,8);
        /*loadBar(10 - cont_gen, 10, 1, 100);*/

        /*Lamada a T_INICIO */
        printf("\n\n%s", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_INIT_GAME, "1")));
        printf("\n ==> ");
        fgets(respuesta, MAX, stdin); /*Almacenamos la respuesta del user*/
        respuesta[strlen(respuesta) - 1] = '\0';
        /*Mirar que frase no este vacia*/
        if (strlen(respuesta) == 0) {
            /*Lamada a T_VACIA */
            printf("\n\n\n\n");
            printf("\n %s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_VACIA, "0")));
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
        if (strcmp(respuesta, "SALIR") == 0) {
            fin = 2; /*Finaliza el juego, pero no porque halla ganado o perdido*/
            break;
        }

        /*Comparar la cadena con la palabra para pedir ayuda*/
        if (strcmp(respuesta, "AYUDA") == 0) {
            printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_HELP_CONTROLS, "AYUDA")));
            continue;
        }
        /*Comparar la cadena con la palabra para ver inventario completo*/
        if (strcmp(respuesta, "TODO INVENTARIO") == 0) {
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("\n Los valores de tus contadores son: linterna: %d, oxigeno: %d, generador %d", cont_lint, cont_oxi, cont_gen);
            printf("\n El inventario al completo es: ");
            /*continue;*/
            if (print_inventory_full(world) == ERROR) {
                printf("\n Error en print_inventory_full");
                return ERROR;
            }
            continue;
        }
        /*Comparar la cadena con la palabra para ver inventario*/
        if (strcmp(respuesta, "INVENTARIO") == 0) {
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

        preturn = elimina_verbo_accion(txt_return, respuesta);
        /*Utilizamos la funcion strtok para separar la cadena por los espacios*/
        ptr = NULL;
        ptr = strtok(respuesta, " "); /*Primer token*/
        ptr = strtok(NULL, " ");
        /*wiii*/
        ptr++;
        ptr--;
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
        if (strcmp(respuesta, "ACTIVAR") == 0)
            id = 8;
        if (strcmp(respuesta, "USAR") == 0)
            id = 9;

        if (id == -1) {
            /*Lamada a T_TONTA */
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_TONTA, "0")));

            continue;
        }
        if (id == 6) {
            if (ID_SALA_MAQUINAS == where_is_player(world)) {
                mini_eliza(dr);
                continue;
            }
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_HABLAR_ERROR, respuesta)), preturn, MAX));
            continue;
        }

        /*Mirar si el inventario esta lleno cuando hace pick*/
        if (id == 1 && (is_player_inv_full(world_get_player(world)) == TRUE)) {
            printf("\n\n\n\n");
            printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
            printf("\n El inventario esta lleno, no puedes coger más objetos");
            continue;
        }

        /*Creamos una nueva accion*/
        if ((action = new_action(preturn, id)) == NULL) {
            printf("\n Error en new_action");
            return (EXIT_FAILURE);
        }
        /*LLamar a action*/
        if (action_execute(world, action) == ERROR) {
            /*Remplaza asteriscos*/
            if (search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta_a_mayus) + 10, respuesta_a_mayus) == NOT_FOUND)
                printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_TONTA, "0")));
            else {
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
            if (id == 4 && (strncmp(preturn, "ESPACIO", strlen("ESPACIO")) == 0))
                cont_gen++;
            if ((id >= 0 && id < 4) || id == 7)
                cont_oxi++;
            if (id == 4 && (strncmp(preturn, "LINTERNA", strlen("LINTERNA")) == 0))
                cont_lint++;
            if (id == 0) {
                printf("\n\n\n\n");

                printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
                printf("\n%s.", select_random_output_template(dr, search_rule_and_pattern(dr, pind_patr, get_id_from_topic(dr, respuesta_a_mayus), respuesta_a_mayus)));
            } else { /*Remplaza asteriscos*/
                if (id == 1) {
                    strcpy(new_map, elimina_objeto_map(preturn, desc_space_graphical(world_get_space(world, where_is_player(world))), nombre_lista));
                    if (space_set_description_graphical(world_get_space(world, where_is_player(world)), new_map) == ERROR) {
                        printf("\n ERROR en elimina_objeto_map");
                        return (EXIT_FAILURE);
                    }
                    /*Oxi bottles*/
                    if (consume_obj_oxi(world, preturn) != ERROR) {
                        printf("\n Felicidades has consumido una recarga de oxigeno");
                        cont_oxi = cont_oxi - 5;
                    }
                }
                if (id == 2) {
                    strcpy(new_map, add_objeto_map(preturn, desc_space_graphical(world_get_space(world, where_is_player(world))), nombre_lista));
                    if (space_set_description_graphical(world_get_space(world, where_is_player(world)), new_map) == ERROR) {
                        printf("\n ERROR en add_objeto_map");
                        return (EXIT_FAILURE);
                    }
                }

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
        if (cont_oxi == 50 || cont_gen == 8)
            fin = 1;
        /*Mirar linterna*/
        if (cont_lint == 8) {
            if (consume_obj(world, 28) == ERROR) {
                printf("\n ERROR en consume_obj");
                return (EXIT_FAILURE);
            }
            cont_lint = 300;
            printf("\n Se le han acabado las pilas a la linterna\n ");

        }
        if (game_finish(world) == TRUE)
            fin = 0;
        if (where_is_player(world) == 17 || where_is_player(world) == 10)
            if (is_player_ready_for_space(world) == FALSE)
                fin = 1;

    } while (fin == -1);

    /*Fin=0 te has pasado el juego, fin=1 mueres, fin=2 has abandonado*/
    printf("\n\n\n\n");
    sprintf(cadena, "%d", fin);
    printf("\n%s", desc_space_graphical(world_get_space(world, where_is_player(world))));
    printf("\n\n");
    printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_END_GAME, cadena)));


    /*Destruimos el dialogo*/
    destroy_dialog(dr);
    /*Destruimos el mundo*/
    destroy_world(world);
    /*Cerramos los ficheros*/


    fclose(dr_xml);
    fclose(game_xml);

    return (EXIT_SUCCESS);
}

int mini_eliza(DialogueRules *dr) {

    /*cadenas eliza*/
    char seps[] = {"/,.:;?*!|?¿[]{}+-_$^)(/&%·ºª#@=`^><€¶ŧ←↓→øþ~łĸŋđðßæ«»¢“”µ"};
    char respuesta [MAX] = {'\0'};
    char respuesta_elim_cars [MAX] = {'\0'};
    char respuesta_lim_esp [MAX] = {'\0'};
    char respuesta_a_mayus [MAX] = {'\0'};
    char respuesta_ori [MAX] = {'\0'};
    char dst[MAX] = {'\0'};

    BOOL flag_res1 = FALSE;
    BOOL flag_res2 = FALSE;
    BOOL flag_res3 = FALSE;

    Id rule_id;
    int *pind_patr = NULL;
    int ind_patr;
    pind_patr = &ind_patr;

    /*Lamada a T_INICIO */
    printf("\n%s", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_PC_INICIO, "0")));
    printf("\n\n%s", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_PC_INICIO, "1")));
    printf("\n\n%s", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_PC_INICIO, "2")));


    /*Llamar a T_PREGUNTA aleatoria*/
    /*printf("\n %s: ", select_random_output_template(T_PREGUNTA));*/
    /*printf("\n\n");*/
    do {
        printf("\n ==> ");
        fgets(respuesta, MAX, stdin); /*Almacenamos la respuesta del user*/
        respuesta[strlen(respuesta) - 1] = '\0';
        /*Mirar que frase no este vacia*/
        if (strlen(respuesta) == 0) {
            /*Lamada a T_VACIA */
            printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_VACIA, "0")));
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

        /*Miramos despedida*/
        if (search_rule_and_pattern(dr, pind_patr, T_PC_DESPEDIDA, respuesta) == T_PC_DESPEDIDA / 10) {
            printf("%s \n", select_output_template(dr, T_PC_DESPEDIDA / 10));
            break;
        }
        /*Miramos ayuda*/
        if (search_rule_and_pattern(dr, pind_patr, T_PC_AYUDA, respuesta) == T_PC_AYUDA / 10) {
            printf("%s \n", select_output_template(dr, T_PC_AYUDA / 10));
            continue;
        }

        /*Miramos la primera flag*/
        if (flag_res1 == FALSE) {
            if (search_rule_and_pattern(dr, pind_patr, T_PC_FLAG1, respuesta) == T_PC_FLAG1 / 10) {
                printf("%s \n", select_output_template(dr, T_PC_FLAG1 / 10));
                flag_res1 = TRUE;
                continue;
            } else if ((rule_id = search_rule_and_pattern(dr, pind_patr, T_PC_NORMAL, respuesta)) != NOT_FOUND) { /*Remplaza sterisco T_NORMAL*/
                printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, rule_id), get_pattern_from_index(dr, rule_id, pind_patr), MAX));
            } else {
                printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_PC_TONTA, "*")));
            }

        }
        if (flag_res1 == TRUE && flag_res2 == FALSE) {
            if (search_rule_and_pattern(dr, pind_patr, T_PC_FLAG2, respuesta) == T_PC_FLAG2 / 10) {
                printf("%s \n", select_output_template(dr, T_PC_FLAG2 / 10));
                flag_res2 = TRUE;
                continue;
            } else if ((rule_id = search_rule_and_pattern(dr, pind_patr, T_PC_NORMAL, respuesta)) != NOT_FOUND) { /*Remplaza sterisco T_NORMAL*/
                printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, rule_id), get_pattern_from_index(dr, rule_id, pind_patr), MAX));
            } else {
                printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_PC_TONTA, "*")));
            }
        }
        if (flag_res1 == TRUE && flag_res2 == TRUE && flag_res3 == FALSE) {
            if (search_rule_and_pattern(dr, pind_patr, T_PC_FLAG3, respuesta) == T_PC_FLAG3 / 10) {
                printf("%s \n", select_output_template(dr, T_PC_FLAG3 / 10));
                flag_res3 = TRUE;
                continue;
            } else if ((rule_id = search_rule_and_pattern(dr, pind_patr, T_PC_NORMAL, respuesta)) != NOT_FOUND) { /*Remplaza sterisco T_NORMAL*/
                printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, rule_id), get_pattern_from_index(dr, rule_id, pind_patr), MAX));
            } else {
                printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_PC_TONTA, "*")));
            }
        }
        if (flag_res1 == TRUE && flag_res2 == TRUE && flag_res3 == TRUE) {
            if (search_rule_and_pattern(dr, pind_patr, T_PC_VICTORY, respuesta) == T_PC_VICTORY / 10) {
                printf("%s \n", select_output_template(dr, T_PC_VICTORY / 10));
                break;
            } else if ((rule_id = search_rule_and_pattern(dr, pind_patr, T_PC_NORMAL, respuesta)) != NOT_FOUND) { /*Remplaza sterisco T_NORMAL*/
                printf("\n%s.", reemplaza_asterisco(dst, select_random_output_template(dr, rule_id), get_pattern_from_index(dr, rule_id, pind_patr), MAX));
            } else {
                printf("%s \n", select_output_template(dr, search_rule_and_pattern(dr, pind_patr, T_PC_TONTA, "*")));
            }
        }
    } while (1);

    return 0;

}

BOOL is_player_ready_for_space(World *w) {
    if (!w)
        return FALSE;
    if (player_search_obj(world_get_player(w), 22) == TRUE && player_search_obj(world_get_player(w), 23) == TRUE && player_search_obj(world_get_player(w), 24) == TRUE)
        return TRUE;
    return FALSE;
}

/* Process has done i out of n rounds,
 and we want a bar of width w and resolution r.*/
void loadBar(int x, int n, int r, int w) {


    /*Calculuate the ratio of complete-to-incomplete.*/
    float ratio = x / (float) n;
    int c = ratio * w;

    /*Only update r times.
    if (x % (n / r + 1) != 0) return;*/

    /* Show the percentage complete.*/
    printf("%3d%% [", (int) (ratio * 100));

    /* Show the load bar.*/
    for (x = 0; x < c; x++)
        printf("=");

    for (x = c; x < w; x++)
        printf(" ");

    /* ANSI Control codes to go back to the
     previous line and clear it.*/
    printf("]\n\033[F\033[J");
}

STATUS bar(int actual, int total) {
    int i;
    float ratio = actual / (float) total;
    
    if (actual < 0 || total < 0 || actual > total)
        return ERROR;


    /*Porcentaje */
    printf("%3d%% [", (int) (ratio * 100));
    /*Imprimir carga*/
    for (i=0; i<actual;i++)
        printf("==");
    for(i=0; i<total-actual;i++)
        printf("  ");
    printf("]\n");
    return OK;

    }