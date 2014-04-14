/**
 *@file Action.c
 *@brief contiene las implementaciones de las funciones de Action
 *@author Pablo Yus
 *@date 24-03-2014
 */

#include "Action.h"

 /** * @brief TAD Acion */
struct _Action {
    ActionType id; /* type of action to do */
    char *do_act; /* direct object */
};

/*
 *name: action_execute
 *brief: ejecuta una accione en particular en mundo (excepto A_PICK_UP)
 *param: World *w: mundo sobre el que se ejecuta la accion
 *param: Action *a: accion que se va a ejecutar
 *return: devuelve OK si todo ha ido bien o ERROR si algo ha fallado

Executes a particular action on the world (except A_PICK_UP). The 
action includes the type of action and the direct object the action is 
performed over. Returns OK if everything goes well or ERROR if there 
is an error. */
STATUS action_execute(World *w, Action *a) {

    Object * obj = NULL;
    char * desc;
    Size max_len = WORD_SIZE;

    if((desc = (char *)malloc(max_len * sizeof(char)))==NULL)
        return ERROR;
    if (w == NULL || a == NULL)
        return ERROR;
    
    switch (a->id) {
        case A_GO:
            if (strcmp(a->do_act, "NORTE") == 0) {
                if (world_move_player(w, (DIRECTION) N) != OK)
                    return ERROR;
                return OK;
            }
            if (strcmp(a->do_act, "SUR") == 0) {
                if (world_move_player(w, (DIRECTION) S) != OK)
                    return ERROR;
                return OK;
            }
            if (strcmp(a->do_act, "ESTE") == 0) {
                if (world_move_player(w, (DIRECTION) E) != OK)
                    return ERROR;
                return OK;
            }
            if (strcmp(a->do_act, "OESTE") == 0) {
                if (world_move_player(w, (DIRECTION) W) != OK)
                    return ERROR;
                return OK;
            }
            if (strcmp(a->do_act, "ARRIBA") == 0) {
                if (world_move_player(w, (DIRECTION) UP) != OK)
                    return ERROR;
                return OK;
            }
            if (strcmp(a->do_act, "ABAJO") == 0) {
                if (world_move_player(w, (DIRECTION) DOWN) != OK)
                    return ERROR;
                return OK;
            }
            break;

        case A_PICK_UP:
            obj = world_get_obj_by_name(w, a->do_act);
            return world_pick_up_obj(w, obj);
            break;

        case A_DROP:
            obj = world_get_obj_by_name(w, a->do_act);
            return world_drop_obj(w, obj);
            break;

        case A_INSPECT:
            if(action_execute_inspect(w, a, desc, max_len)==ERROR)
                return ERROR;
            free(desc);
            return OK;
            
            break;

        case A_TURN_LIGHT_ON:
            obj = world_get_obj_by_name(w, a->do_act);
            return world_turn_light_on_obj(w, obj);
            break;

        case A_TURN_LIGHT_OFF:
            obj = world_get_obj_by_name(w, a->do_act);
            return world_turn_light_off_obj(w, obj);
            break;

        case A_SPEAK:
            return OK;
            break;

        default:
            printf("No ha escogido ninguna de las acciones disponibles.\n");
            return ERROR;
            break;

    }
    return ERROR;
}

/*
 *name: action_execute_inspect
 *brief: reserva memeoria para la cadena que almacenara la descripicion del objeto inspeccionado.
 *param: World *w: mundo que contine aquello que se va a inspeccionar.
 *param: Action *a: accion a realizar
 *param: char *inspected: cadena de caracteres que guarda la descripcion de lo inspeccionado.
 *param: Size max_len: tamño maximo de la cadena inspected.
 *return: devuelve Ok si todo ha ido bien o ERROR si ha habido algun error.

Executes the inspect action. The description is returned in the 
“inspected“ parameter, which must be allocated by the client. 
Returns OK if everything goes well and ERROR otherwise. 
 */
STATUS action_execute_inspect(World *w, Action *a, char *inspected, Size max_len) {

    Id id;
    Space *spa = NULL;
    Object *obj = NULL;

    if (w == NULL || a == NULL || max_len < 0)
        return ERROR;
    
    /*Para exapminar espacios*/
    if (strcmp(a->do_act, "SPACE") == 0) {

        id = where_is_player(w);
        spa = world_get_space(w, id);
        return world_inspect_space(w, spa, inspected, (int) max_len);

        /*Para examinar objetos*/
    } else {

        id = where_is_player(w);
        obj = world_get_obj_by_name(w, a->do_act);
        return world_inspect_obj(w, obj, inspected, (int) max_len);
    }
    return ERROR;
}

/*
 *name: topic_is_valid
 *brief: permite comprobar si el tema es valido para ese momento del juego. 
 *param: World *w: mundo actual
 *param: Topic t: tema a comprobar
 *return: devuelve TRUE si es valido el tema, o FALSE en caso contrario.

Allows to check if a given conversation topic is valid for the 
current state of the game. Returns TRUE if so and FALSE otherwise.
 */
/*BOOL topic_is_valid(World *w, Topic t) {
    if (w == NULL)
        return FALSE;
    DEBE HACERRSE RESPECTO A LECTOR DIALOGO*/

/*}*/

/*----------------Auxiliares---------------*/

/*
 * name Action* new_action(const char* do_act, ActionType id);
 * brief crea una nueva accion
 * param do_act
 * param id
 * return la accion si se ha creado correctamente o NULL en caso contrario
 */
Action* new_action(const char* do_act, ActionType id) {
    Action *action;

    action = (Action*) malloc(sizeof (Action));
    action->do_act = malloc(sizeof(char) * (strlen(do_act)+1));

    if (action == NULL || do_act == NULL)
        return NULL;

    action->id = id;
    strcpy(action->do_act, do_act);

    return action;

}
/*
 * name void destroy_action(Action *a);
 * brief destruye una accion liberando memoria que habia sido reservada previamente
 * param a
 */

void destroy_action(Action *a) {
    free(a->do_act);
    free(a);
    a = NULL;
    return;
}

STATUS set_action(Action *a, const char *do_act, ActionType id){
    if (!a || !do_act)
        return ERROR;
    a->id=id;
    strcpy(a->do_act, do_act);
    return OK;
}