#include "World.h"

struct _World {
    Space * spaces[MAX_SPACES + 1];
    Object * objects[MAX_OBJECTS + 1];
    Link * links[MAX_LINKS + 1];
    Player *player;
    int n_spaces; /*Numero de espacios de un mundo*/
    int n_objects; /*Numero de espacios de un mundo*/
    int n_links; /*Numero de uniones de un mundo*/
};

/**
 *@name: World *create_world();
 *@brief: function to create the world.
 
 *@return: the world you have create.
 */
World *create_world() {
   
    World * w;
    
    w = (World*) malloc(sizeof (World));
    
    w->n_links = 0;
    w->n_spaces = 0;
    w->n_objects = 0;

    return w;
}

/**
 *@name: void destroy_world(World *w);
 *@brief: function to destroy the world.
 
 *@param: the world that you want destroy.
 
 *@return: NULL si hay algun errror.
 */
void destroy_world(World *w) {
    if (w == NULL)
        return;

    free(w);
}

/**
 *@name: Space *world_add_space(World *w, Id id); 
 *@brief: añade un espacio a menudo
 
 *@param: mundo al que añadir el espacio
 *@param: id del espacio que se quiere añadir.
 
 *@return: el espacio que se ha añadido, o NULL en caso de error.
 */
Space *world_add_space(World *w, Id id) {
    if (w == NULL || id < 0)
        return NULL;

    w->spaces[w->n_spaces] = create_space(id);

    if ((w->spaces[w->n_spaces]) == NULL)
        return NULL;

    w->n_spaces++;
    return w->spaces[w->n_spaces - 1];
}

/**
 *@name: Object *world_add_obj(World *w, Id id);
 *@brief: añade un objeto a mundo.
 
 *@param: mundo al que añadir el objeto.
 *@param: id del objeto que se quiere añadir.
 
 *@return: el objeto que se ha añadido, o NULL en caso de error.
 */
Object *world_add_obj(World *w, Id id) {
    if (w == NULL || id < 0)
        return NULL;

    w->objects[w->n_objects] = obj_create(id);

    if ((w->objects[w->n_objects]) == NULL)
        return NULL;

    w->n_objects++;
    return w->objects[w->n_objects - 1];
}

/**
 *@name: Link *world_add_link(World *w, Id id);
 *@brief: añade un link al mundo.
 
 *@param: mundo al que añadir el link.
 *@param: id del link que se quiere añadir.
 
 *@return: el link que se ha añadido, o NULL en caso de error.
 */
Link *world_add_link(World *w, Id id) {
    if (w == NULL || id < 0 || w->n_links < MAX_LINKS)
        return NULL;

    w->links[w->n_links] = create_link(id);

    if ((w->links[w->n_links]) == NULL)
        return NULL;

    w->n_links++;
    return w->links[w->n_links - 1];
}

/**
 *@name: Player *world_set_player(World *w);
 *@brief: inicializa un jugador en mundo.
 
 *@param: mundo al que añadir el jugador.
 
 *@return: el jugador que se ha añadido, o NULL en caso de error.
 */
Player *world_set_player(World *w) {
    if (w == NULL)
        return NULL;
    w->player = create_player();

    if (w->player == NULL)
        return NULL;
    return w->player;
    /*Solo queda esta que no se que quiere que haga la funcion.*/

}

/**
 *@name: Space *world_get_space(World *w, Id id);
 *@brief: obtienes un espacio a partir de su id y del mundo en el que se encuentra. 
 
 *@param: mundo donde esta el esapcio.
 *@param: id del espacio
 
 *@return: el espacio que se queria obtener, o NULL en caso de error. 
 */
Space *world_get_space(World *w, Id id) {
    int idAux = 0;
    if (w == NULL || id < 0)
        return NULL;



    for (idAux = 0; idAux < MAX_SPACES; idAux++) {
        if (space_get_id(w->spaces[idAux]) == id)
            return w->spaces[idAux];
    }/*Añadir funcion Id space_get_id(Space *s);, a space.h/.c*/

    printf("Espacio no encontrado.\n");
    return NULL;

}

/*Albert*/

/*Return a referenece to the corresponding element given a NAME. Returns NULL if there is an error or if the element is not found. */
Object *world_get_obj_by_name(World *w, char * name) {
    int i = 0;
    if (!w || !name)
        return NULL;

    for (i = 0; i < MAX_OBJECTS + 1; i++) {
        if (strcmp(obj_get_name(w->objects[i]), name)==0)
            return w->objects[i];
    }
    return NULL;
}

/* Returns a reference to the corresponding element given an ID. Returns NULL if there is an error or if the element is not found. */
Object *world_get_obj(World *w, Id id) {
    int i = 0;
    if (!w || id == -1)
        return NULL;

    for (i = 0; i < MAX_OBJECTS + 1; i++) {
        if (get_object_id(w->objects[i]) == id)
            return w->objects[i];
    }
    return NULL;
}


/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
Space *world_get_space_north(World *w, Id space) {
    int i, j, k;
    Id norte;
    if (!w || space == -1)
        return NULL;
    for (i = 0; i < MAX_SPACES + 1; i++) {

        if (space_get_id(w->spaces[i]) == space) {
            /*Almacenar id espacio al norte*/
            norte = space_get_north(w->spaces[i]);
            /*Comprobar el espacio con la id*/
            for (j = 0; j < MAX_SPACES + 1; j++) {
                if (space_get_id(w->spaces[j]) == norte) {
                    /*Comprobar si el link existe entre ellos y esta abierto*/
                    for (k = 0; k < MAX_LINKS; k++) {
                        if (link_ask_linked(w->links[k], space, norte) == TRUE) {
                            return w->spaces[j];
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

/* Given the name of an object checks if it is located in a given space. Returns the object or NULL if it does not exist. */
Object *world_get_obj_from_space(World *w, char *name, Id space) {
    int i, j;
    if (!w || !name || space == NO_ID)
        return NULL;
    for (i = 0; i < MAX_SPACES; ++i) {
        if (space_get_id(w->spaces[i]) == space) {
            for (j = 0; j < MAX_OBJECTS; ++j) {
                if (space_get_object(w->spaces[i], obj_is_name(w->objects[j], name)) == TRUE)
                    return w->objects[j];
            }
        }
    }
    return NULL;
}

/* Shows the description of the space and its visible objects. Hidden objects are not shown. The client must reserve enough memory for desc. */
STATUS world_get_space_description(World *w, Id space, char * desc, Size max_len) {
    int i;
    if (!w || !desc || strlen(desc) > max_len)
        return ERROR;

    desc = (char*) malloc(max_len * sizeof (char));
    for (i = 0; i < MAX_SPACES; i++) {
        if (space_get_id(w->spaces[i]) == space) {
            strcpy(desc, desc_space(w->spaces[i]));
            return OK;
        }
    }
    return ERROR;
}

/* Changes the location of the player. The current place must be connected to the destination. */
STATUS world_move_player(World *w, DIRECTION dir) {
    int i;
    if (!w)
        return ERROR;
    switch (dir) {
        case N:
            for (i = 0; i < MAX_SPACES; ++i) {
                if (space_get_id(w->spaces[i]) == player_get_location(w->player)) {
                    player_set_location(w->player, space_get_north(w->spaces[i]));
                }
            }
            return OK;

            break;
        case S:

            break;
        case E:

            break;
        case W:

            break;
        case UP:

            break;
        case DOWN:

            break;
        default:
            return ERROR;
    }

    return ERROR;

}
/*fin*/

/* Inspect spaces. Example: 
-> if there is light 
-> inspect the room 
The description is returned in the parameter desc which must be allocated by the client */
STATUS world_inspect_space(World *w, Space *space, char *desc, int max_len) {
    int i;

    if (!w || !space)
        return ERROR;
    /*bucle para localizar el espacio del player*/
    for (i = 0; i < MAX_SPACES + 1; i++) {
        /*comprobacion de coincidencia*/
        if (where_is_player(w) == space_get_id(w->spaces[i])) {
            /*el espacio está iluminado*/
            if (is_space_lighted(w->spaces[i]) == TRUE) {
                strcpy(desc, desc_space_inspect(w->spaces[i]));
                return OK;
            }/*si no esta ilumninado: devuelve la descripcion base*/
            else {
                strcpy(desc, desc_space(w->spaces[i]));
                return OK;
            }
        }
    }
    /*no ha encontrado al player*/
    return ERROR;
}

/* Inspect Objects. Example: 
 -> if there is light 
 -> inspect object from the inventory or in the current room (if 
hidden, the object is no longer hidden). The description is returned 
in the parameter desc which must be allocated by the client. ***************__allocated by the client__*****/
STATUS world_inspect_obj(World * m, Object *obj, char *desc, int max_len) { /*int max_len?*******************/
    int i;

    if (!m || !obj)
        return ERROR;
    /*bucle para localizar el espacio del player*/
    for (i = 0; i < MAX_SPACES + 1; i++) {
        /*comprobacion de coincidencia*/
        if (where_is_player(m) == space_get_id(m->spaces[i])) {
            /*el espacio está iluminado*/
            if (is_space_lighted(m->spaces[i]) == TRUE) {
                /*entonces busca el objeto*/
                for (i = 0; i < get_space_set_size(m->spaces[i]); i++) {
                    /*si coinciden las IDs, lo ha encontrado*/
                    if (get_id_from_space_set_index(m->spaces[i], i) == get_object_id(obj)) {
                        /*devuelve por *desc la descripcion de inspección*/
                        if (obj_is_hidden(obj) == TRUE)
                            obj_set_not_hidden(obj);
                        strcpy(desc, obj_get_descInspect(obj));
                        return OK;
                    }
                }
                /*si no encuentra el objeto en el espacio, lo busca en el inv*/
                for (i = 0; i < player_inv_size(m->player); i++) {
                    /*si coinciden las IDs, lo ha encontrado*/
                    if (get_id_from_player_inv_set_index(m->player, i) == get_object_id(obj)) {
                        /*devuelve por *desc la descripcion de inspección*/
                        if (obj_is_hidden(obj) == TRUE)
                            obj_set_not_hidden(obj);
                        strcpy(desc, obj_get_descInspect(obj));
                        return OK;
                    }
                }
                /*para light=TRUE, no lo ha encontrado ni en espacio ni en inv*/
                return ERROR;
            }/*si el espacio no esta iluminado:*/
            else {
                /*entonces busca el objeto en el espacio*/
                for (i = 0; i < get_space_set_size(m->spaces[i]); i++) {
                    /*si coinciden las IDs, lo ha encontrado*/
                    if (get_id_from_space_set_index(m->spaces[i], i) == get_object_id(obj)) {
                        /*devuelve por *desc la descripcion sin mas al no haber luz*/
                        /*obj->hidden se mantiene TRUE***************************************/
                        strcpy(desc, obj_get_description(obj));
                        return OK;
                    }
                }
                /*si no encuentra el objeto en el espacio, lo busca en el inv*/
                for (i = 0; i < player_inv_size(m->player); i++) {
                    /*si coinciden las IDs, lo ha encontrado*/
                    if (get_id_from_player_inv_set_index(m->player, i) == get_object_id(obj)) {
                        /*devuelve por *desc la descripcion del objeto sin más*/
                        /*obj->hidden se mantiene TRUE*/
                        strcpy(desc, obj_get_description(obj));
                        return OK;
                    }
                }
                /*para light=FALSE, no lo ha encontrado ni en espacio ni en inv*/
                return ERROR;
            }
        }
    }/*fin del for de busqueda de espacios*/
    /*no se ha encontrado el espacio donde esta el player*/
    return ERROR;
}

/*REVISAR: si X objeto que tiene que hacer Y, no puede hacerlo?***********************/

/* Pick up an object 
 -> the object must not be hidden in the current space 
 -> the object must be movable 
 -> The inventory of the player has to have enough free space for the 
object */
STATUS world_pick_up_obj(World *w, Object *obj) {
    int i;
    /*punteros null, oculto o no movible*/
    if (!w || !obj || obj_is_hidden(obj) == TRUE || obj_is_movable(obj) == FALSE)
        return ERROR;
    /*caso que no quepan mas objetos/objeto ya en el inventario*/
    if (is_player_inv_full(w->player) == TRUE || player_search_obj(w->player, get_object_id(obj)) == TRUE)
        return ERROR;
    /*entonces añadimos la id al set del inventario*/
    if (player_add_obj(w->player, get_object_id(obj)) == ERROR)
        return ERROR;
    for (i = 0; i < MAX_SPACES; i++) {
        /*buscar el espacio donde esta el player con el objeto*/
        if (space_get_id(w->spaces[i]) == player_get_location(w->player)) {
            /*lo eliminamos del set*/
            if (space_remove_obj(w->spaces[i], get_object_id(obj)) == ERROR)
                return ERROR;
        }
    }
    return OK;
}

/* Drop an object 
 -> the object must be in the inventory */
STATUS world_drop_obj(World *w, Object *obj) {
    int i;

    if (!w || !obj)
        return ERROR;
    /*si el objeto esta en el set del player*/
    if (player_search_obj(w->player, get_object_id(obj)) == TRUE) {
        /*drop del array de ids del inv*/
        if (player_remove_obj(w->player, get_object_id(obj)) == ERROR)
            return ERROR;
        /*se añade al set del espacio donde esta*/
        for (i = 0; i < MAX_SPACES; i++) {
            /*buscar el espacio donde esta el player con el objeto*/
            if (space_get_id(w->spaces[i]) == player_get_location(w->player)){
                /*lo añadimos al set*/
                if(space_add_obj (w->spaces[i], get_object_id(obj))==ERROR)
                    return ERROR;
            }
        }
    }
    return ERROR;    
}

/* Light object 
 -> object in the current room or the inventory 
 -> The object must be lightable 
 */
STATUS world_turn_light_on_obj(World *w, Object *obj) {
    int i;
    BOOL lighted;

    if (!w || !obj)
        return ERROR;
    /*se puede encender?*/
    if (obj_is_lightable(obj) == TRUE) {
        /*¿esta el objeto en el inventario?*/
        for (i = 0; i < player_inv_size(w->player); i++) {
            /*¿ID objeto recibido misma que ID objeto de inventario?*/
            if (get_object_id(obj) == get_id_from_player_inv_set_index(w->player, i)) {
                if (obj_is_lighted(obj) == TRUE)
                    return OK;
                else {
                    lighted = TRUE;
                    obj_set_lighted(obj, lighted);
                    return OK;
                }
            }
        }
        /*¿esta el objeto en ese espacio?*/
        for (i = 0; i < get_space_set_size(w->spaces[i]); i++) {
            /*¿ID objeto recibido misma que ID objeto de inventario?*/
            if (get_object_id(obj) == get_id_from_player_inv_set_index(w->player, i)) {
                if (obj_is_lighted(obj) == TRUE)
                    return OK;
                else {
                    lighted = TRUE;
                    obj_set_lighted(obj, lighted);
                    return OK;
                }
            }
        }
    }
    if (obj_is_lightable(obj) == FALSE)
        return OK;
    return ERROR;
}

/* Unlight object 
 -> object in the current room or the inventory 
 -> The object must be lightable */
STATUS world_turn_light_off_obj(World *w, Object *obj) {
    int i;
    BOOL lighted;

    if (!w || !obj)
        return ERROR;
    /*se puede encender?*/
    if (obj_is_lightable(obj) == TRUE) {
        /*¿esta el objeto en el inventario?*/

        for (i = 0; i < player_inv_size(w->player); i++) {
            /*¿ID objeto recibido misma que ID objeto de inventario?*/
            if (get_object_id(obj) == get_id_from_player_inv_set_index(w->player, i)) {
                if (obj_is_lighted(obj) == FALSE)
                    return OK;
                else {
                    lighted = FALSE;
                    obj_set_lighted(obj, lighted);
                    return OK;
                }
            }
        }
        /*¿esta el objeto en ese espacio?*/
        for (i = 0; i < get_space_set_size(w->spaces[i]); i++) {
            /*¿ID objeto recibido misma que ID objeto de inventario?*/
            if (get_object_id(obj) == get_id_from_player_inv_set_index(w->player, i)) {
                if (obj_is_lighted(obj) == FALSE)
                    return OK;
                else {
                    lighted = FALSE;
                    obj_set_lighted(obj, lighted);
                    return OK;
                }
            }
        }
    }
    if (obj_is_lightable(obj) == FALSE)
        return OK;
    return ERROR;
}

/* Illuminates a space if the following conditions are met: 
 -> object is in the space and it is lighten 
 -> object is in the inventory and it is lighten */
STATUS world_illuminate_space(World * m, Space *space) {
    /*int i;*/
    BOOL light;

    if (!m || !space)
        return ERROR;

    /*si hay objetos en el espacio:*/
    if (is_space_set_empty(space) == FALSE) {
        /*si alguno de los objetos esta encendido:*/
        if (is_space_lighten_by_object(m, space) == TRUE) {
            light = TRUE;
            return space_set_light(space, light);
        }/*hay objetos pero ninguno encendido:*/
        else {
            light = FALSE;
            return space_set_light(space, light);
        }
    }
    /*si no hay objetos en el espacio:*/
    if (is_space_set_empty(space) == TRUE) {
        /*si tampoco lleva objetos el player:*/
        if (player_inv_size(m->player) == 0) {
            light = FALSE;
            return space_set_light(space, light);
        }
        /*si lleva objetos y alguno encendido:*/

        if (get_player_inv(m->player) == NULL)
            return ERROR;
        else if (is_object_inventory_lighted(m, get_player_inv(m->player)) == TRUE) {
            light = TRUE;
            return space_set_light(space, light);
        }/*si lleva objetos pero ninguno encendido:*/
        else {
            light = FALSE;
            return space_set_light(space, light);
        }
    }
    /*no entra ningun caso*/
    return ERROR;
}

/*__________FUNCIONES AUX_________*/

/*AUX_world_1*/

/*busca si algun objeto encendido del mundo m esta en el espacio space*/
BOOL is_space_lighten_by_object(World *m, Space *space) {
    int i;

    for (i = 0; i < get_space_set_size(space); i++) {
        /*Antiguo:
        if(m->objects[i]->lighted==TRUE && m->objects[i]->id == space->space_objects->v[i])
                return TRUE;*/

        /*objeto encendido y coincide la ID del objeto del mundo con ID del objeto del espacio recibido*/
        if (obj_is_lighted(m->objects[i]) == TRUE && (get_object_id(m->objects[i]) == get_id_from_space_set_index(space, i)))
            return TRUE;
    }
    return FALSE;
}

/*AUX_world_2*/

/*busca si algun objeto encendido del mundo m esta en el inventario inv*/
BOOL is_object_inventory_lighted(World *m, Inventory *inv) {
    int i;

    if (get_inventory_set_size(inv) == NO_TAM)
        return FALSE;
    for (i = 0; i < get_inventory_set_size(inv); i++) {
        /*antiguo: 
        if(m->objects[i]->lighted==TRUE && m->objects[i]->id == inv->objects->v[i])
                return TRUE;*/

        /*objeto encendido y coincide la ID del objeto del mundo con ID del objeto del inventario recibido*/
        if (obj_is_lighted(m->objects[i]) == TRUE && (get_object_id(m->objects[i]) == get_id_from_inv_index(inv, i)))
            return TRUE;
    }
    return FALSE;
}

STATUS set_player_location(World *w, Id id){
    if (!w)
        return NO_ID;
    if(player_set_location(w->player, id)==ERROR)
        return ERROR;
    return OK;
}

/*AUX_world_3*/
Id where_is_player(World *w) {
    if (!w)
        return NO_ID;
    return player_get_location(w->player);
}
/*REVISAR: MAX_SPACES+1*******************************************************/

