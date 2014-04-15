/**
 *@brief TAD que representa un mundo
 *@file world.c
 *@author Albert Soler, Alfonso Sebares y Pablo yus
 *@version 0.01
 *@date 13-03-2014
 */


#include "World.h"

/** * @brief TAD World */
struct _World {
    Space * spaces[MAX_SPACES + 1];
    Object * objects[MAX_OBJ + 1];
    Link * links[MAX_LINKS + 1];
    Player *player;
    int n_spaces; /*Numero de espacios de un mundo*/
    int n_objects; /*Numero de espacios de un mundo*/
    int n_links; /*Numero de uniones de un mundo*/
};

/*function to create the world.*/
World *create_world() {

    World * w;

    w = (World*) malloc(sizeof (World));

    w->n_links = 0;
    w->n_spaces = 0;
    w->n_objects = 0;

    return w;
}

/* function to destroy the world.*/
void destroy_world(World *w) {
    int i;

    if (w == NULL)
        return;
    for (i = 0; i < w->n_spaces; w->n_spaces--) {
        destroy_space(w->spaces[w->n_spaces - 1]);
    }
    for (i = 0; i < w->n_objects; w->n_objects--) {
        obj_destroy(w->objects[w->n_objects - 1]);
    }
    for (i = 0; i < w->n_links; w->n_links--) {
        destroy_link(w->links[w->n_links - 1]);
    }

    destroy_player(w->player);

    free(w);
}

/*añade un espacio a mundo */
Space *world_add_space(World *w, Id id) {
    if (w == NULL || id < 0)
        return NULL;

    w->spaces[w->n_spaces] = create_space(id);

    if ((w->spaces[w->n_spaces]) == NULL)
        return NULL;

    w->n_spaces++;
    return w->spaces[w->n_spaces - 1];
}

/*añade un objeto a mundo.*/
Object *world_add_obj(World *w, Id id) {
    int i;
    Id espacio;
    if (w == NULL || id < 0)
        return NULL;

    w->objects[w->n_objects] = obj_create(id);
    
    for(i=0;i<MAX_SPACES;i++){
        if(space_get_object(w->spaces[i],id)==TRUE){
            espacio=space_get_id(w->spaces[i]);
            break;
        } 
    }
    if(obj_set_location(w->objects[w->n_objects],espacio)==ERROR)
            return NULL;

    if ((w->objects[w->n_objects]) == NULL)
        return NULL;

    w->n_objects++;
    return w->objects[w->n_objects - 1];
}

/*añade un link al mundo. */
Link *world_add_link(World *w, Id id) {
    if (w == NULL || id < 0 || w->n_links > MAX_LINKS)
        return NULL;

    w->links[w->n_links] = create_link(id);

    if ((w->links[w->n_links]) == NULL)
        return NULL;

    w->n_links++;
    return w->links[w->n_links - 1];
}

/* inicializa un jugador en mundo.*/
Player *world_set_player(World *w) {
    if (w == NULL)
        return NULL;
    w->player = create_player();

    if (w->player == NULL)
        return NULL;
    return w->player;
}

/*obtienes un espacio a partir de su id y del mundo en el que se encuentra.*/
Space *world_get_space(World *w, Id id) {
    int idAux = 0;
    if (w == NULL || id < 0)
        return NULL;

    for (idAux = 0; idAux < MAX_SPACES; idAux++) {
        if (space_get_id(w->spaces[idAux]) == id)
            return w->spaces[idAux];
    }/*Añadir funcion Id space_get_id(Space *s);, a space.h/.c*/
    return NULL;

}

/*obtienes un link a partir de su id y del mundo en el que se encuentra*/
Link *world_get_link(World *w, Id id) {
    int idAux = 0;
    if (w == NULL || id < 0)
        return NULL;

    for (idAux = 0; idAux < MAX_LINKS; idAux++) {
        if (link_get_id(w->links[idAux]) == id)
            return w->links[idAux];
    }
    return NULL;

}

/*Return a referenece to the corresponding element given a NAME. Returns NULL if there is an error or if the element is not found. */
Object *world_get_obj_by_name(World *w, char * name) {
    int i = 0;
    if (!w || !name)
        return NULL;

    for (i = 0; i < MAX_OBJ; i++) {
        if (obj_get_name(w->objects[i]) != NULL) {
            if (strncmp(obj_get_name(w->objects[i]), name,strlen(obj_get_name(w->objects[i]))) == 0)
                return w->objects[i];
        }

    }
    return NULL;
}

Object *world_get_obj_by_descInspec(World *w, char * descInspec) {
    int i = 0;
    if (!w || !descInspec)
        return NULL;

    for (i = 0; i < MAX_OBJ; i++) {
        if (strcmp(obj_get_descInspect(w->objects[i]), descInspec) == 0)
            return w->objects[i];
    }
    return NULL;
}

/* Returns a reference to the corresponding element given an ID. Returns NULL if there is an error or if the element is not found. */
Object *world_get_obj(World *w, Id id) {
    int i = 0;
    if (!w || id == -1)
        return NULL;

    for (i = 0; i < MAX_OBJ + 1; i++) {
        if (get_object_id(w->objects[i]) == id)
            return w->objects[i];
    }
    return NULL;
}

/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
Space *world_get_space_north(World *w, Id space) {
    int i, j, z;
    Id norte; /*Link norte*/
    Id spaceN; /*ID espacio en el norte*/
    if (!w || space == NO_ID)
        return NULL;
    for (i = 0; i < MAX_SPACES; i++) {
        if (space_get_id(w->spaces[i]) == space) {
            /*Almacenar id Link al espacio al norte*/
            norte = space_get_north(w->spaces[i]);
            /*Buscar Link del espacio*/
            for (z = 0; i < MAX_LINKS; ++z) {
                if (link_get_id(w->links[z]) == norte) {
                    if (link_ask_linked(w->links[z]) == TRUE) {
                        spaceN = link_get_space(w->links[z], space);
                        if (spaceN != NO_ID) {
                            for (j = 0; i < MAX_SPACES; j++) {
                                if (space_get_id(w->spaces[j]) == spaceN)
                                    return w->spaces[j];
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

/* Given a space ID returns the space located south. Returns NULL if there is none or if the link between them is closed. */
Space *world_get_space_south(World *w, Id space) {
    int i, j, z;
    Id norte; /*Link norte*/
    Id spaceN; /*ID espacio en el norte*/
    if (!w || space == NO_ID)
        return NULL;
    for (i = 0; i < MAX_SPACES; i++) {
        if (space_get_id(w->spaces[i]) == space) {
            /*Almacenar id Link al espacio al norte*/
            norte = space_get_south(w->spaces[i]);
            /*Buscar Link del espacio*/
            for (z = 0; i < MAX_LINKS; ++z) {
                if (link_get_id(w->links[z]) == norte) {
                    if (link_ask_linked(w->links[z]) == TRUE) {
                        spaceN = link_get_space(w->links[z], space);
                        if (spaceN != NO_ID) {
                            for (j = 0; i < MAX_SPACES; j++) {
                                if (space_get_id(w->spaces[j]) == spaceN)
                                    return w->spaces[j];
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

/* Given a space ID returns the space located east. Returns NULL if there is none or if the link between them is closed. */
Space *world_get_space_east(World *w, Id space) {
    int i, j, z;
    Id norte; /*Link norte*/
    Id spaceN; /*ID espacio en el norte*/
    if (!w || space == NO_ID)
        return NULL;
    for (i = 0; i < MAX_SPACES; i++) {
        if (space_get_id(w->spaces[i]) == space) {
            /*Almacenar id Link al espacio al norte*/
            norte = space_get_east(w->spaces[i]);
            /*Buscar Link del espacio*/
            for (z = 0; i < MAX_LINKS; ++z) {
                if (link_get_id(w->links[z]) == norte) {
                    if (link_ask_linked(w->links[z]) == TRUE) {
                        spaceN = link_get_space(w->links[z], space);
                        if (spaceN != NO_ID) {
                            for (j = 0; i < MAX_SPACES; j++) {
                                if (space_get_id(w->spaces[j]) == spaceN)
                                    return w->spaces[j];
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
Space *world_get_space_west(World *w, Id space) {
    int i, j, z;
    Id norte; /*Link norte*/
    Id spaceN; /*ID espacio en el norte*/
    if (!w || space == NO_ID)
        return NULL;
    for (i = 0; i < MAX_SPACES; i++) {
        if (space_get_id(w->spaces[i]) == space) {
            /*Almacenar id Link al espacio al norte*/
            norte = space_get_west(w->spaces[i]);
            /*Buscar Link del espacio*/
            for (z = 0; i < MAX_LINKS; ++z) {
                if (link_get_id(w->links[z]) == norte) {
                    if (link_ask_linked(w->links[z]) == TRUE) {
                        spaceN = link_get_space(w->links[z], space);
                        if (spaceN != NO_ID) {
                            for (j = 0; i < MAX_SPACES; j++) {
                                if (space_get_id(w->spaces[j]) == spaceN)
                                    return w->spaces[j];
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
Space *world_get_space_up(World *w, Id space) {
    int i, j, z;
    Id norte; /*Link norte*/
    Id spaceN; /*ID espacio en el norte*/
    if (!w || space == NO_ID)
        return NULL;
    for (i = 0; i < MAX_SPACES; i++) {
        if (space_get_id(w->spaces[i]) == space) {
            /*Almacenar id Link al espacio al norte*/
            norte = space_get_up(w->spaces[i]);
            /*Buscar Link del espacio*/
            for (z = 0; i < MAX_LINKS; ++z) {
                if (link_get_id(w->links[z]) == norte) {
                    if (link_ask_linked(w->links[z]) == TRUE) {
                        spaceN = link_get_space(w->links[z], space);
                        if (spaceN != NO_ID) {
                            for (j = 0; i < MAX_SPACES; j++) {
                                if (space_get_id(w->spaces[j]) == spaceN)
                                    return w->spaces[j];
                            }
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
Space *world_get_space_down(World *w, Id space) {
    int i, j, z;
    Id norte; /*Link norte*/
    Id spaceN; /*ID espacio en el norte*/
    if (!w || space == NO_ID)
        return NULL;
    for (i = 0; i < MAX_SPACES; i++) {
        if (space_get_id(w->spaces[i]) == space) {
            /*Almacenar id Link al espacio al norte*/
            norte = space_get_down(w->spaces[i]);
            /*Buscar Link del espacio*/
            for (z = 0; i < MAX_LINKS; ++z) {
                if (link_get_id(w->links[z]) == norte) {
                    if (link_ask_linked(w->links[z]) == TRUE) {
                        spaceN = link_get_space(w->links[z], space);
                        if (spaceN != NO_ID) {
                            for (j = 0; i < MAX_SPACES; j++) {
                                if (space_get_id(w->spaces[j]) == spaceN)
                                    return w->spaces[j];
                            }
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
            for (j = 0; j < MAX_OBJ; ++j) {
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
    if (!w || !desc || strlen(desc) > max_len || space == -1)
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

    if (!w)
        return ERROR;
    switch (dir) {
        case N:
            return player_set_location(w->player, link_get_space(world_get_link(w, space_get_north(world_get_space(w, player_get_location(w->player)))), player_get_location(w->player)));

            break;
        case S:
            return player_set_location(w->player, link_get_space(world_get_link(w, space_get_south(world_get_space(w, player_get_location(w->player)))), player_get_location(w->player)));

            break;
        case E:
            return player_set_location(w->player, link_get_space(world_get_link(w, space_get_east(world_get_space(w, player_get_location(w->player)))), player_get_location(w->player)));

            break;
        case W:
            return player_set_location(w->player, link_get_space(world_get_link(w, space_get_west(world_get_space(w, player_get_location(w->player)))), player_get_location(w->player)));

            break;
        case UP:
            return player_set_location(w->player, link_get_space(world_get_link(w, space_get_up(world_get_space(w, player_get_location(w->player)))), player_get_location(w->player)));

            break;
        case DOWN:
            return player_set_location(w->player, link_get_space(world_get_link(w, space_get_down(world_get_space(w, player_get_location(w->player)))), player_get_location(w->player)));

            break;
        default:
            return ERROR;
    }

    return ERROR;

}
/*fin*/

/* Inspect spaces*/
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
                printf(" %s (printf en world_inspect_space)", desc);
                return OK;
            }/*si no esta ilumninado: devuelve la descripcion base*/
            else {
                strcpy(desc, desc_space(w->spaces[i]));
                printf(" %s (printf en world_inspect_space)", desc);
                return OK;
            }
        }
    }
    /*no ha encontrado al player*/
    return ERROR;
}

/* Inspect Objects */
STATUS world_inspect_obj(World * m, Object *obj, char *desc, int max_len) {
    int i;

    if (!m || !obj)
        return ERROR;
    /*bucle para localizar el espacio del player*/
    for (i = 0; i < MAX_SPACES + 1; i++) {
        /*comprobacion de coincidencia*/
        /*Comprobar que no devuelvan -1*/
        if (where_is_player(m) != NO_ID)
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
                        /*Comprobar que no devuelvan -1*/
                        if (get_id_from_player_inv_set_index(m->player, i) != NO_ID)
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
                        /*Comprobar que no devuelvan -1*/
                        if (get_id_from_space_set_index(m->spaces[i], i) != NO_ID)
                            if (get_id_from_space_set_index(m->spaces[i], i) == get_object_id(obj)) {
                                /*devuelve por *desc la descripcion sin mas al no haber luz*/
                                /*obj->hidden se mantiene TRUE*/
                                strcpy(desc, obj_get_description(obj));
                                return OK;
                            }
                    }
                    /*si no encuentra el objeto en el espacio, lo busca en el inv*/
                    for (i = 0; i < player_inv_size(m->player); i++) {
                        /*si coinciden las IDs, lo ha encontrado*/
                        /*Comprobar que no devuelvan -1*/
                        if (get_id_from_player_inv_set_index(m->player, i) != NO_ID)
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

/* Pick up an object */
STATUS world_pick_up_obj(World *w, Object *obj) {
    int i;
    /*punteros null, oculto o no movible*/
    if (!w || !obj || obj_is_hidden(obj) == TRUE || obj_is_movable(obj) == FALSE)
        return ERROR;
    /*caso que no quepan mas objetos/objeto ya en el inventario*/
    if (is_player_inv_full(w->player) == TRUE || player_search_obj(w->player, get_object_id(obj)) == TRUE)
        return ERROR;
    /*entonces añadimos la id al set del inventario*/
    /*if (player_add_obj(w->player, get_object_id(obj)) == ERROR)
        return ERROR;*/
    for (i = 0; i < MAX_SPACES; i++) {
        /*buscar el espacio donde esta el player con el objeto*/
        /*Comprobar que no devuelvan -1*/
        if (space_get_id(w->spaces[i]) != NO_ID) {
            /*si encuentra que el player esta en ese espacio*/
            if (space_get_id(w->spaces[i]) == player_get_location(w->player)) {
                /*si ese espacio contiene el objeto a añadir*/
                if (space_get_object(w->spaces[i], get_object_id(obj)) == TRUE) {
                    /*entonces añadimos la id al set del inventario*/
                    if (player_add_obj(w->player, get_object_id(obj)) == ERROR)
                        return ERROR;
                    /*y lo eliminamos del set del espacio*/
                    if (space_remove_obj(w->spaces[i], get_object_id(obj)) == ERROR)
                        return ERROR;
                    /*actualizar posicion del objeto*/
                    if (obj_set_location(obj, PLAYER_BAG) == ERROR)
                        return ERROR;
                    /*insercion y extraccion correctas*/
                    return OK;
                }
            }
        }
    }/*fin del for de busqueda*/
    return ERROR;
}

/* Drop an object*/
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
            /*Comprobar que no devuelvan -1*/
            if (space_get_id(w->spaces[i]) != NO_ID)
                /*si encuentra el espacio donde esta el player:*/
                if (space_get_id(w->spaces[i]) == player_get_location(w->player)) {
                    /*lo añadimos al set*/
                    if (space_add_obj(w->spaces[i], get_object_id(obj)) == ERROR)
                        return ERROR;
                    /*actualizar posicion del objeto*/
                    if (obj_set_location(obj, space_get_id(w->spaces[i])) == ERROR)
                        return ERROR;
                    /*si todo OK*/
                    return OK;
                }
        }/*fin del for de busqueda de espacios*/
    }/*sale directamente si no encuentra el objeto en el inventario del player*/
    return ERROR;
}

/* Light object */
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
            /*Comprobar que no devuelvan -1*/
            if (get_object_id(obj) != NO_ID)
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
            /*Comprobar que no devuelvan -1*/
            if (get_object_id(obj) != NO_ID)
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

/* Unlight object */
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
            /*Comprobar que no devuelvan -1*/
            if (get_object_id(obj) != NO_ID)
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
            /*Comprobar que no devuelvan -1*/
            if (get_object_id(obj) != NO_ID)
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

/* Illuminates a space if the following conditions are met*/
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

/*establece la localizacion del player*/
STATUS set_player_location(World *w, Id id) {
    if (!w)
        return NO_ID;
    if (player_set_location(w->player, id) == ERROR)
        return ERROR;
    return OK;
}

/*busca donde esta el player*/
Id where_is_player(World *w) {
    if (!w)
        return NO_ID;
    return player_get_location(w->player);
}

