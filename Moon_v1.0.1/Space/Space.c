/**
 *@brief TAD que representa un espacio en el mundo
 *@file space.c
 *@author Albert Soler
 *@version 0.01
 *@date 13-03-2014
 */


#include "Space.h"

/** * @brief TAD Space */
struct _Space {
    Id id;
    char description[WORD_SIZE + 1];
    char descInspect[WORD_SIZE + 1];
    char descGraphical[WORD_SIZE + 1];
    Id north;
    Id south;
    Id east;
    Id west;
    Id up;
    Id down;
    BOOL light;
    Set *space_objects;
};

/* Functions to create and destroy a particular space */

/*
 *brief Funcion que crea un espacio
 *param id 
 *return devuelve un puntero al espacio formado.
 */
Space *create_space(Id id) {
    Space *new_space;
    if (id == NO_ID)
        return NULL;

    new_space = (Space*) malloc(sizeof (Space));
    if (!new_space)
        return NULL;

    new_space->north = NO_ID;
    new_space->south = NO_ID;
    new_space->east = NO_ID;
    new_space->west = NO_ID;
    new_space->up = NO_ID;
    new_space->down = NO_ID;

    new_space->id = id;
    new_space->space_objects = new_set();
    return new_space;

}

/*
 *brief Funcion que destruye un espacio
 *param space espacio a destruir
 */
void destroy_space(Space *space) {
    destroy_set(space->space_objects);
    free(space);
    space = NULL;
}

/* Functions that modify space properties values */
STATUS space_set_description(Space *space, char *description) {
    if (!space || !description)
        return ERROR;
    /*Asignamos al espacio el valor de description*/
    strcpy(space->description, description);
    return OK;


}

STATUS space_set_description_inspect(Space *space, char *description) {
    if (!space || !description)
        return ERROR;
    /*Asignamos al espacio el valor de description*/
    strcpy(space->descInspect, description);
    return OK;
}

STATUS space_set_description_graphical(Space *space, char *descriptionGraph) {
    if (!space || !descriptionGraph)
        return ERROR;
    /*Asignamos al espacio el valor de description*/
    strcpy(space->descGraphical, descriptionGraph);
    return OK;
}

STATUS space_set_light(Space *space, BOOL light) {
    if (!space || (light != 0 && light != 1))
        return ERROR;
    /*Asignamos el valor de luz al espacio*/
    space->light = light;
    return OK;

}

/* Functions to add elements to a space */
STATUS space_add_link_north(Space *space, Id link_id) {
    if (!space || link_id == NO_ID)
        return ERROR;
    space->north = link_id;
    return OK;
}

STATUS space_add_link_west(Space *space, Id link_id) {
    if (!space || link_id == NO_ID)
        return ERROR;
    space->west = link_id;
    return OK;
}

STATUS space_add_link_south(Space *space, Id link_id) {
    if (!space || link_id == NO_ID)
        return ERROR;
    space->south = link_id;
    return OK;
}

STATUS space_add_link_east(Space *space, Id link_id) {
    if (!space || link_id == NO_ID)
        return ERROR;
    space->east = link_id;
    return OK;
}

STATUS space_add_link_up(Space *space, Id link_id) {
    if (!space || link_id == NO_ID)
        return ERROR;
    space->up = link_id;
    return OK;
}

STATUS space_add_link_down(Space *space, Id link_id) {
    if (!space || link_id == NO_ID)
        return ERROR;
    space->down = link_id;
    return OK;
}

STATUS space_add_obj(Space *space, Id object_id) {
    if (!space || object_id == NO_ID)
        return ERROR;
    return add(space->space_objects, object_id);
}

STATUS space_remove_obj(Space *space, Id object_id) {
    if (!space || object_id == NO_ID)
        return ERROR;
    return remove_id(space->space_objects, object_id);
}

/* Functions to access the properties of a space */
const char * desc_space(Space *space) {
    if (!space)
        return NULL;
    return space->description;

}

/*Devuelve la descripcion de inspeccion del espacio*/
const char * desc_space_inspect(Space *space) {
    if (!space)
        return NULL;
    return space->descInspect;

}

/* Given a space returns the link to the north. Returns NO_ID if there is no such link */
Id space_get_north(Space *space) {
    if (!space)
        return NO_ID;
    if (space->north == NO_ID)
        return NO_ID;
    return space->north;

}

/* Given a space returns the link to the south. Returns NO_ID if there is no such link */
Id space_get_south(Space *space) {
    if (!space)
        return NO_ID;
    if (space->south == NO_ID)
        return NO_ID;
    return space->south;

}

/* Given a space returns the link to east. Returns NO_ID if there is no such link */
Id space_get_east(Space *space) {
    if (!space)
        return NO_ID;
    if (space->east == NO_ID)
        return NO_ID;
    return space->east;

}

/* Given a space returns the link to the west. Returns NO_ID if there is no such link */
Id space_get_west(Space *space) {
    if (!space)
        return NO_ID;
    if (space->west == NO_ID)
        return NO_ID;
    return space->west;

}

/* Given a space returns the link to the up. Returns NO_ID if there is no such link */
Id space_get_up(Space *space) {
    if (!space)
        return NO_ID;
    if (space->up == NO_ID)
        return NO_ID;
    return space->up;

}

/* Given a space returns the link to the down. Returns NO_ID if there is no such link */
Id space_get_down(Space *space) {
    if (!space)
        return NO_ID;
    if (space->down == NO_ID)
        return NO_ID;
    return space->down;

}

/* Prints a space. This function is included for debugging purposes */
BOOL space_print(Space *space) {
    if (!space)
        return FALSE;
    printf("\n ID %ld", space->id);
    printf("\n description %s", space->description);
    printf("\n descInspect %s", space->descInspect);
    printf("\n north %ld", space->north);
    printf("\n south %ld", space->south);
    printf("\n east %ld", space->east);
    printf("\n west %ld", space->west);
    printf("\n up %ld", space->up);
    printf("\n down %ld", space->down);
    printf("\n light %d", space->light);

    return TRUE;

}

/*Devuelve el numero de objetos que hay en un espacio*/
Size get_space_set_size(Space *space) {
    if (!space || get_size(space->space_objects) == NO_TAM)
        return NO_TAM;
    return get_size(space->space_objects);
}

/*Devuelve la id de un objeto del set para ese espacio en funcion de un indice*/
Id get_id_from_space_set_index(Space *space, int indice) {
    if (!space || indice < 0)
        return NO_ID;
    return get_i_id(space->space_objects, indice);
}

/*Comprueba si el set de objetos para un espacio esta vacio*/
BOOL is_space_set_empty(Space *space) {
    if (!space)
        return FALSE;
    return is_empty(space->space_objects);
}

/*Comprueba si el espacio esta iluminado*/
BOOL is_space_lighted(Space *space) {
    if (!space)
        return FALSE;
    return space->light;
}

/*
 *name: Id space_get_id(Space *s);
 *author: Pablo Yus.
 *brief: devuleve el id de un espacio.
 
 *param: Space * space: espacio del que se quiere conocer su id.
 
 *return: el id del espacio o NO_ID si hay algun errror.
 */
Id space_get_id(Space *space) {
    if (space == NULL)
        return NO_ID;

    return space->id;
}

/*Returns the objetc of the objetcs id*/
BOOL space_get_object(Space *space, Id id) {
    if (!space || id == NO_ID)
        return FALSE;
    return contains(space->space_objects, id);
}

/*Returnea un puntero a un set de objetos de un espacio*/
Set *space_get_set(Space *space) {
    if (!space)
        return NULL;
    return space->space_objects;
}

/*Devuelve la descripcion grafica del espacio*/
 char * desc_space_graphical(Space *space) {
    if (!space)
        return NULL;
    return space->descGraphical;

}

