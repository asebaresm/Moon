/**
 *file Action.c
 *brief contiene las implementaciones de las funciones de Action
 *author Pablo Yus
 *date 24-03-2014
 */

#include "Action.h"


struct _Action {
    ActionType id; /* type of action to do */
    char *do_act; /* direct object */
};

/*^^
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
    char * desc[WORD_SIZE];
    Size max_len;
    
    if (w == NULL || a == NULL)
        return ERROR;
    
    switch (a->id) {
        case A_GO:
            if(strcmp(a->do_act,"NORTE")=0){
                if(world_move_player(w,(DIRECTION)N)== OK)
                        return ERROR;
                return OK;
            }
            if(strcmp(a->do_act,"SUR")=0){
                if(world_move_player(w,(DIRECTION)S)== OK)
                        return ERROR;
                return OK;
            }
            if(strcmp(a->do_act,"ESTE")=0){
                if(world_move_player(w,(DIRECTION)E)== OK)
                        return ERROR;
                return OK;
            }
            if(strcmp(a->do_act,"OESTE")=0){
                if(world_move_player(w,(DIRECTION)W)== OK)
                        return ERROR;
                return OK;
            }
            if(strcmp(a->do_act,"ARRIBA")=0){
                if(world_move_player(w,(DIRECTION)UP)== OK)
                        return ERROR;
                return OK;
            }
            if(strcmp(a->do_act,"ABAJO")=0){
                if(world_move_player(w,(DIRECTION)DOWN)== OK)
                        return ERROR;
                return OK;
            }
            break;

        case A_PICK_UP:
            obj = get_object_by_name(w,a->do_act);
            return world_pick_up_obj(w, obj);
            break;

        case A_DROP:
            obj = get_object_by_name(w,a->do_act);
            return world_drop_obj(w, obj);
            break;

        case A_INSPECT:
            return action_execute_inspect(w, a, desc, max_len);
            break;

        case A_TURN_LIGHT_ON:
            obj = get_object_by_name(w,a->do_act);
            return world_turn_light_on_obj(w, obj);
            break;

        case A_TURN_LIGHT_OFF:
            obj = get_object_by_name(w,a->do_act);
            return world_turn_light_on_obj(w, obj);
            break;

        case A_SPEAK:
            return TRUE;
            break;

        default:
            printf("No ha escogido ninguna de las acciones disponibles.\n");
            return ERROR;
            break;

    }
}

/*^^
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
    Space *spa;
    Object *obj;
    
    if (w == NULL || a == NULL || inspected == NULL || max_len < 0)
        return ERROR;

    inspected = (char*) malloc(max_len * sizeof (char));

    /*Para examinar espacios*/
    if (strcmp(a->do_act, "SPACE") == 0) {

        id = world_get_player_location(w);
        spa = world_get_space(w,id);
        return world_inspect_space(w, spa, inspected, (int)max_len);
    
    /*Para examinar objetos*/
    }else{
    
        id = world_get_player_location(w);
        obj = get_object_by_name(w,inspected);
        return world_inspect_obj(w, obj, inspected, (int) max_len);
    }    
}

/*^^
 *name: topic_is_valid
 *brief: permite comprobar si el tema es valido para ese momento del juego. 
 *param: World *w: mundo actual
 *param: Topic t: tema a comprobar
 *return: devuelve TRUE si es valido el tema, o FALSE en caso contrario.

Allows to check if a given conversation topic is valid for the 
current state of the game. Returns TRUE if so and FALSE otherwise.
 */
BOOL topic_is_valid(World *w, Topic t) {
    if (w == NULL)
        return FALSE;
/*DEBE HACERRSE RESPECTO A LECTOR DIALOGO*/

}
