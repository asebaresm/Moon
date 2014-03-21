/**
 *@name: Object *obj_create(Id id);
 *@brief: functions to create the object.

 *@param: id del objeto.

 *@return: devuelve un objeto
 */

#include "Object.c"

struct _Object
{
Id id;
Id location;
char name[WORD_SIZE+1];
char description[WORD_SIZE+1];
char descMoved[WORD_SIZE+1];
char descInspect[WORD_SIZE+1];
BOOL movable;
BOOL moved;
BOOL illuminates;
BOOL lighted;
BOOL hidden;
Set * openable_links;
} ;


Id get_object_id(Object *obj){
    if(!obj)
        return NO_ID;
    return obj->id;
}


/**
 *@name: Object *obj_create(Id id);
 *@brief: function to create the object.

 *@param: id desde el que tomara el objeto creado.

 *@return: obj, es decir,el objeto.
 */
Object *obj_create(Id id){
    
	Object * obj;
    
    obj = (Object*) malloc (sizeof(Object));
    
    obj->id = id;
    
    return obj;
}


/**
 *@name: void obj_destroy(Object *obj);
 *@brief: function to destroy the object.

 *@param:

 *@return:
 */
void obj_destroy(Object *obj){
   
	 if(obj == NULL)
        return;
    
     destruye_conjunto(obj->openable_links);
     free(obj);
}


/**
 *@name: STATUS obj_set_description(Object *obj, char *description);
 *@brief:

 *@param:

 *@return:
 */
STATUS obj_set_description(Object *obj, char *description){
    if(obj == NULL || descripcion == NULL)
        return FALSE;
    
    strcpy(obj->descripton, description);
    return TRUE;
}


/**
 *@name: STATUS obj_set_description_moved(Object *object, char *description);
 *@brief:

 *@param:

 *@return:
 */
STATUS obj_set_description_moved(Object *object, char *description){
    if(object == NULL || description == NULL)
        return ERRROR;

    object->description = description;

    return OK;
}


/**
 *@name:
 *@brief: function that modify the property, movable, of the object.

 *@param:

 *@return:
 */
STATUS obj_set_movable (Object *obj, BOOL movable){
    if(obj == NULL)
        return ERROR;

    obj->movable = movable;
    return OK;
}

STATUS obj_set_lighted (Object *obj, BOOL lighted){
    if(obj == NULL)
        return ERROR;

    obj->lighted=lighted;
    return OK;
}

/**
 *@name: const char * obj_get_description(Object *obj);
 *@brief: function that get the description of the object.

 *@param:

 *@return:
 */
const char * obj_get_description(Object *obj){
    if(obj == NULL)
        return NULL;
    
    return obj->description;
}


/**
 *@name: BOOL obj_is_movable(Object *obj);
 *@brief:

 *@param:

 *@return:
 */
BOOL obj_is_movable(Object *obj){
    BOOL st;
    
    if(obj == NULL)
        return FALSE;
    
    st = obj->movido;
    
    if(st == TRUE)
        return TRUE;
    
    return FALSE;
}


/**
 *@name: STATUS obj_print(Object *obj);
 *@brief: prints the object.

 *@param:

 *@return:
 */
STATUS obj_print(Object *obj){
    if(obj == NULL)
        return FALSE;
    
    printf("%s\n", obj->name);
    printf("%s\n", obj->description);
    printf("%s\n", obj->descMoved);
    printf("%s\n", obj->descInspect);

    if(obj->movable == TRUE)
	printf("Si movible\n");
    else
	printf("No movible\n");

    if(obj->moved == TRUE)
	printf("Si movido\n");
    else
	printf("No movido\n");

    if(obj->illuminates == TRUE)
	printf("Si Ilumina\n");
    else
	printf("No ilumina\n");

    if(obj->lighted == TRUE)
	printf("Esta encendido\n");
    else
	printf("No esta encendido\n");

    if(obj->hidden == TRUE)
	printf("Es oculto\n");
    else
	printf("No es oculto\n");
    return TRUE;
}

/*AUX_object_1*/
BOOL obj_is_lightable(Object *obj){
    if(!obj)
        return FALSE;
    if(obj->illuminates==TRUE)
        return TRUE;
    return FALSE;
}

/*AUX_object_2*/
BOOL obj_is_lighted(Object *obj){
    if(!obj)
        return FALSE;
    return obj->lighted;
}

/*AUX_object_3*/
BOOL obj_is_hidden(Object *obj){
    if(!obj)
        return FALSE;
    return obj->hidden;
}

/*AUX_object_4*/
BOOL obj_is_movable(Object *obj){
    if(!obj)
        return FALSE;
    return obj->movable;
}
