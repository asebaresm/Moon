/**
 *@file Object.c
 *@brief contiene las implementaciones de las funciones de Object
 *@author Alfonso
 *@version 0.01
 *@date 24-03-2014
 */

#include "Object.h"

/** * @brief TAD Object */
struct _Object {
    Id id;
    Id location;
    char name[WORD_SIZE + 1];
    char description[WORD_SIZE + 1];
    char descMoved[WORD_SIZE + 1];
    char descInspect[WORD_SIZE + 1];
    char descGraphical[WORD_SIZE + 1];
    BOOL movable;
    BOOL moved;
    BOOL illuminates;
    BOOL lighted;
    BOOL hidden;
    Set * openable_links;
};

/*devuelve la id de un objeto*/
Id get_object_id(Object *obj) {
    if (!obj)
        return NO_ID;
    return obj->id;
}

/*function to create the object.*/
Object *obj_create(Id id) {
    Object * obj;
    if (id == NO_ID)
        return NULL;

    obj = (Object*) malloc(sizeof (Object));
    obj->id = id;
    obj->location = NO_ID;
    obj->hidden = FALSE;
    obj->movable = FALSE;
    obj->moved = FALSE;
    obj->illuminates = FALSE;
    obj->lighted = FALSE;
    obj->hidden = FALSE;

    obj->openable_links = new_set();
    if (obj->openable_links == NULL)
        return NULL;
    return obj;
}

/*function to destroy the object.*/
void obj_destroy(Object *obj) {
    if (obj == NULL)
        return;
    destroy_set(obj->openable_links);
    free(obj);
    obj = NULL; /*AÑADIDO*/
}

/*establece la descripcion de un objeto*/
STATUS obj_set_description(Object *obj, char *description) {
    if (obj == NULL || description == NULL)
        return FALSE;

    strcpy(obj->description, description);
    return TRUE;
}

/*establece la descripcion de "movido" para un objeto*/
STATUS obj_set_description_moved(Object *object, char *description) {
    if (object == NULL || description == NULL)
        return ERROR;
    strcpy(object->descMoved, description);
    return OK;
}

/*establece la descripcion de inspecciomn*/
STATUS obj_set_description_inspect(Object *object, char *description) {
    if (object == NULL || description == NULL)
        return ERROR;
    strcpy(object->descInspect, description);
    return OK;
}

/*Establece la descripcion grafica de un objeto*/
STATUS obj_set_description_graphical(Object *object, char *descriptionGraph) {
    if (!object || !descriptionGraph)
        return ERROR;
    /*Asignamos al object el valor de description*/
    strcpy(object->descGraphical, descriptionGraph);
    return OK;
}

/*establece la localizacion del objeto*/
STATUS obj_set_location(Object *object, Id location) {
    if (!object)
        return ERROR;
    object->location = location;
    return OK;
}

/*establece el nombre de un objeto*/
STATUS obj_set_name(Object *object, char *name) {
    int i;
    if (object == NULL || name == NULL)
        return ERROR;
    /*Pasar nombre a mayusculas*/
    for (i = 0; name[i]; i++)
        name[i] = toupper(name[i]);

    strcpy(object->name, name);
    return OK;
}

/*establece si un objeto es movible*/
STATUS obj_set_movable(Object *obj, BOOL movable) {
    if (obj == NULL)
        return ERROR;

    obj->movable = movable;
    return OK;
}

/*establece si un objeto esta encendido */
STATUS obj_set_lighted(Object *obj, BOOL lighted) {
    if (obj == NULL)
        return ERROR;

    obj->lighted = lighted;
    return OK;
}

/*establece si un objeto se enciende*/
STATUS obj_set_lightable(Object *obj, BOOL lightable) {
    if (obj == NULL)
        return ERROR;

    obj->illuminates = lightable;
    return OK;
}

/*establece un objeto a no escondido*/
STATUS obj_set_not_hidden(Object *obj) {
    if (!obj)
        return ERROR;
    obj->hidden = FALSE;
    return OK;
}

/*establece un objeto a escondido*/
STATUS obj_hide(Object *obj) {
    if (!obj)
        return ERROR;
    obj->hidden = TRUE;
    return OK;
}

/*devuelve la descripcion de un objeto*/
char * obj_get_description(Object *obj) {
    if (obj == NULL)
        return NULL;

    return obj->description;
}

/*devuelve la descripcion de inspeccion de un objeto*/
char * obj_get_descInspect(Object *obj) {
    if (obj == NULL)
        return NULL;

    return obj->descInspect;
}

/*devuelve la descripcion de  "movido" de un objeto*/
char * obj_get_descMoved(Object *obj) {
    if (obj == NULL)
        return NULL;

    return obj->descMoved;
}

/*devuelve la descripcion grafica de un objeto*/
char * obj_get_descGraphical(Object *obj) {
    if (obj == NULL)
        return NULL;

    return obj->descGraphical;
}

/*devuelve el nombre de un objeto*/
char * obj_get_name(Object *obj) {
    if (obj == NULL)
        return NULL;
    return obj->name;
}

/* comprueba si un objeto s epuede mover*/
BOOL obj_is_movable(Object *obj) {
    if (obj == NULL)
        return FALSE;
    return obj->movable;
}

/*printea un objeto*/
STATUS obj_print(Object *obj) {
    if (obj == NULL)
        return ERROR;

    printf("\n>>>Objeto: %d\n", (int) obj->id);
    printf("Localizacion: %d\n", (int) obj->location);
    printf("Nombre: %s\n", obj->name);
    printf("Descripcion: %s\n", obj->description);
    printf("Descripcion movido: %s\n", obj->descMoved);
    printf("Descripcion inspeccion: %s\n", obj->descInspect);

    printf(">Booleanas:\n");
    if (obj->movable == TRUE)
        printf("Si movible\n");
    else
        printf("No movible\n");

    if (obj->moved == TRUE)
        printf("Si movido\n");
    else
        printf("No movido\n");

    if (obj->illuminates == TRUE)
        printf("Si ilumina\n");
    else
        printf("No ilumina\n");

    if (obj->lighted == TRUE)
        printf("Esta encendido\n");
    else
        printf("No esta encendido\n");

    if (obj->hidden == TRUE)
        printf("Es oculto\n");
    else
        printf("No es oculto\n");

    return OK;
}

/*comprueba si un objeto se puede encender*/
BOOL obj_is_lightable(Object *obj) {
    if (!obj)
        return FALSE;
    if (obj->illuminates == TRUE)
        return TRUE;
    return FALSE;
}

/*comprueba si un objeto esta encendido*/
BOOL obj_is_lighted(Object *obj) {
    if (!obj)
        return FALSE;
    return obj->lighted;
}

/*comprueba si un ibjeto esta oculto*/
BOOL obj_is_hidden(Object *obj) {
    if (!obj)
        return FALSE;
    return obj->hidden;
}

/*comprueba el nombre de un objeto devolviendo su ID*/
Id obj_is_name(Object *obj, char *name) {
    if (!obj || !name)
        return NO_ID;
    if (strcmp(obj->name, name) == 0)
        return obj->id;
    return NO_ID;
}

STATUS obj_open_link(Object *object, Id new_id) {
    if (!object || new_id == NO_ID)
        return ERROR;
    return add(object->openable_links, new_id);
}

STATUS obj_add_obj(Object *object, Id new_id) {
    if (!object || new_id == NO_ID)
        return ERROR;
    return add(object->openable_links, new_id);
}

/*printea un objeto*/
STATUS obj_print_name(Object *obj) {
    if (obj == NULL)
        return ERROR;
    printf(" %s\n", obj->name);
    return OK;
}

/*Devuelve la localizacion de un objeto*/
Id obj_get_location(Object *obj) {
    if(!obj)
        return NO_ID;
    return obj->location;
}

/*Pone un objeto como movido*/
STATUS obj_set_moved(Object *obj, BOOL moved){
    if(!obj)
        return ERROR;
        obj->moved=moved;
    return OK;
    
}

/* comprueba si un objeto es moved*/
BOOL obj_is_moved(Object *obj) {
    if (obj == NULL)
        return FALSE;
    return obj->moved;
}