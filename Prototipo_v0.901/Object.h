#include "Types.h"
#include "Set.h"

#ifndef _OBJECT
#define _OBJECT

typedef struct _Object Object;


/*Devuelve la id de un objeto*/
Id get_object_id(Object *obj);

/**
 *@name: Object *obj_create(Id id);
 *@brief: functions to create the object.

 *@param: id del objeto.

 *@return: devuelve un objeto
 */

/* Functions to create and destroy the object */
Object *obj_create(Id id);


/**
 *@name: void obj_destroy(Object *obj);
 *@brief: function to destroy the object.

 *@param:

 *@return:
 */
void obj_destroy(Object *obj);


/**
 *@name: STATUS obj_set_description(Object *obj, char *description);
 *@brief:

 *@param:

 *@return:
 */
STATUS obj_set_description(Object *obj, char *description);


/**
 *@name: STATUS obj_set_description_moved(Object *object, char *description);
 *@brief:

 *@param:

 *@return:
 */
STATUS obj_set_description_moved(Object *object, char *description);


/**
 *@name:
 *@brief: function that modify the property, movable, of the object.

 *@param:

 *@return:
 */
STATUS obj_set_movable (Object *obj, BOOL movable);

STATUS obj_set_lighted (Object *obj, BOOL lighted);

STATUS obj_set_not_hidden (Object *obj, BOOL hidden);

/**
 *@name: const char * obj_get_description(Object *obj);
 *@brief: function that get the description of the object.

 *@param:

 *@return:
 */
const char * obj_get_description(Object *obj);

/*devuelve la descripciond e inspeccion del objeto*/
const char * obj_get_descInspect(Object *obj);

/**
 *@name: BOOL obj_is_movable(Object *obj);
 *@brief:

 *@param:

 *@return:
 */
BOOL obj_is_movable(Object *obj);


/**
 *@name: STATUS obj_print(Object *obj);
 *@brief: prints the object.

 *@param:

 *@return:
 */
STATUS obj_print(Object *obj);


BOOL obj_is_lightable(Object *obj);

/*AUX_object_2*/
BOOL obj_is_lighted(Object *obj);

/*AUX_object_3*/
BOOL obj_is_hidden(Object *obj);

/*AUX_object_4*/
BOOL obj_is_movable(Object *obj);

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
También tienes que incluir una nueva función en el modulo World para que los objetos 
se puedan añadir a un mundo concreto. 
Object *world_add_obj(World *w, Id id);*/

#endif /*_OBJECT*/
