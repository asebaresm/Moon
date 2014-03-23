/**
 *@name: Object *obj_create(Id id);
 *@brief: functions to create the object.

 *@param: id del objeto.

 *@return: devuelve un objeto
 */

#include "Object.h"

struct _Object {
    Id id;
    Id location;
    char name[WORD_SIZE + 1];
    char description[WORD_SIZE + 1];
    char descMoved[WORD_SIZE + 1];
    char descInspect[WORD_SIZE + 1];
    BOOL movable;
    BOOL moved;
    BOOL illuminates;
    BOOL lighted;
    BOOL hidden;
    Set * openable_links;
};

Id get_object_id(Object *obj) {
    if (!obj)
        return NO_ID;
    return obj->id;
}

/**
 *@name: Object *obj_create(Id id);
 *@brief: function to create the object.

 *@param: id desde el que tomara el objeto creado.

 *@return: obj, es decir,el objeto.
 */
Object *obj_create(Id id) {

    Object * obj;
    
    obj = (Object*) malloc(sizeof (Object));
    obj->id = id;
    obj->hidden=FALSE;
    obj->movable=FALSE;
    obj->moved=FALSE;
    obj->illuminates=FALSE;
    obj->lighted=FALSE;
    obj->hidden=FALSE;
    
    obj->openable_links=new_set();
    if(obj->openable_links==NULL)
        return NULL;
    return obj;
}

/**
 *@name: void obj_destroy(Object *obj);
 *@brief: function to destroy the object.

 *@param:

 *@return:
 */
void obj_destroy(Object *obj) {
    if (obj == NULL)
        return;
    destroy_set(obj->openable_links);
    free(obj);
}

/**
 *@name: STATUS obj_set_description(Object *obj, char *description);
 *@brief:

 *@param:

 *@return:
 */
STATUS obj_set_description(Object *obj, char *description) {
    if (obj == NULL || description == NULL)
        return FALSE;

    strcpy(obj->description, description);
    return TRUE;
}

/**
 *@name: STATUS obj_set_description_moved(Object *object, char *description);
 *@brief:

 *@param:

 *@return:
 */
STATUS obj_set_description_moved(Object *object, char *description) {
    if (object == NULL || description == NULL)
        return ERROR;
    strcpy(object->descMoved, description);
    return OK;
}

/**
 *@name: obj_set_description_moved
 *@brief:

 *@param:

 *@return:
 */
STATUS obj_set_description_inspect(Object *object, char *description) {
    if (object == NULL || description == NULL)
        return ERROR;
    strcpy(object->descInspect, description);
    return OK;
}

STATUS obj_set_name(Object *object, char *name) {
    if (object == NULL || name == NULL)
        return ERROR;
    strcpy(object->name, name);
    return OK;
}
/**
 *@name:
 *@brief: function that modify the property, movable, of the object.

 *@param:

 *@return:
 */
STATUS obj_set_movable(Object *obj, BOOL movable) {
    if (obj == NULL)
        return ERROR;

    obj->movable = movable;
    return OK;
}

STATUS obj_set_lighted(Object *obj, BOOL lighted) {
    if (obj == NULL)
        return ERROR;

    obj->lighted = lighted;
    return OK;
}

STATUS obj_set_lightable (Object *obj, BOOL lightable){
    if (obj == NULL)
        return ERROR;

    obj->illuminates=lightable;
    return OK;
}

STATUS obj_set_not_hidden(Object *obj) {
    if (!obj)
        return ERROR;
    obj->hidden = FALSE;
    return OK;
}

/**
 *@name: const char * obj_get_description(Object *obj);
 *@brief: function that get the description of the object.

 *@param:

 *@return:
 */
char * obj_get_description(Object *obj) {
    if (obj == NULL)
        return NULL;

    return obj->description;
}

char * obj_get_descInspect(Object *obj) {
    if (obj == NULL)
        return NULL;

    return obj->descInspect;
}

char * obj_get_descMoved(Object *obj){
    if (obj == NULL)
        return NULL;

    return obj->descMoved;
}

char * obj_get_name(Object *obj){
    if (obj == NULL)
        return NULL;

    return obj->name;
}
/**
 *@name: BOOL obj_is_movable(Object *obj);
 *@brief:

 *@param:

 *@return:
 */
BOOL obj_is_movable(Object *obj) {
    if (obj == NULL)
        return FALSE;
    return obj->movable;
}

/**
 *@name: STATUS obj_print(Object *obj);
 *@brief: prints the object.

 *@param:

 *@return:
 */
STATUS obj_print(Object *obj) {
    if (obj == NULL)
        return ERROR;
    
    printf("\n>>>Objeto: %d\n", (int)obj->id);
    printf("Localizacion: %d\n", (int)obj->location);
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

/*AUX_object_1*/
BOOL obj_is_lightable(Object *obj) {
    if (!obj)
        return FALSE;
    if (obj->illuminates == TRUE)
        return TRUE;
    return FALSE;
}

/*AUX_object_2*/
BOOL obj_is_lighted(Object *obj) {
    if (!obj)
        return FALSE;
    return obj->lighted;
}

/*AUX_object_3*/
BOOL obj_is_hidden(Object *obj) {
    if (!obj)
        return FALSE;
    return obj->hidden;
}


/*Given an object returns the id, or NO_ID if there is an error*/
Id obj_get_id(Object *obj) {
    if (!obj)
        return -1;

    return obj->id;
}

/*Given a name return ID if the objetc exists, NO_ID in the other case*/
Id obj_is_name(Object *obj, char *name) {
    if (!obj)
        return NO_ID;
    if (strcmp(obj->name, name) == 0)
        return obj->id;
    return NO_ID;
}
