#ifndef _OBJECT
#define _OBJECT

#include "Types.h"
#include "Set.h"

typedef struct _Object Object;


/**
 * @name Id get_object_id(Object *obj);
 * @brief devuelve el id de un objeto
 * @param obj
 * @return el id del objeto o NULL en caso de error
 */
Id get_object_id(Object *obj);

/**
 *@name: Object *obj_create(Id id);
 *@brief: functions to create the object.
 *@param: id
 *@return: el objeto y en caso de error devuelve NULL
 */
Object *obj_create(Id id);


/**
 *@name: void obj_destroy(Object *obj);
 *@brief: function to destroy the object.
 *@param: obj
 */
void obj_destroy(Object *obj);


/**
 * @name STATUS obj_set_description(Object *obj, char *description);
 * @brief se le da una descripcion a un objeto
 * @param obj
 * @param description
 * @return OK si ha ido todo correctamente o ERROR en caso de error
 */
STATUS obj_set_description(Object *obj, char *description);


/**
 * @name STATUS obj_set_description_moved(Object *object, char *description);
 * @brief se le da una descripcionMovil a un objeto
 * @param object
 * @param description
 * @return OK si todo ha ido correctamente o ERROR si ha habido algun problema
 */
STATUS obj_set_description_moved(Object *object, char *description);

/**
 * @name STATUS obj_set_description_inspect(Object *object, char *description);
 * @brief se le da una descripcion-Inspeccion a un objeto
 * @param object
 * @param description
 * @return OK si todo ha ido correctamente o ERROR si ha habido algun problema
 */
STATUS obj_set_description_inspect(Object *object, char *description);

/**
 * @name STATUS obj_set_name(Object *obj, char *name);
 * @brief se establece un nombre a un objeto
 * @param object
 * @param description
 * @return OK si todo ha ido correctamente o ERROR si ha habido algun problema
 */
STATUS obj_set_name(Object *obj, char *name);

/**
 * @name STATUS obj_set_movable(Object *obj, BOOL movable);
 * @brief function that modify the property, movable, of the object.
 * @param obj
 * @param movable
 * @return devuelve OK si ha ido todo bien o ERROR si ha habido algun problema.
 */
STATUS obj_set_movable(Object *obj, BOOL movable);

/**
 * @name STATUS obj_set_lighted(Object *obj, BOOL lighted);
 * @brief function that modify the property, lighted, of the object.
 * @param obj
 * @param lighted
 * @return devuelve OK si ha ido todo bien o ERROR si ha habido algun problema.
 */
STATUS obj_set_lighted(Object *obj, BOOL lighted);

/**
 * @name STATUS obj_set_lightable(Object *obj, BOOL lightable);
 * @brief function that modify the property, lightable, of the object.
 * @param obj
 * @param lightable
 * @return devuelve OK si ha ido todo bien o ERROR si ha habido algun problema.
 */
STATUS obj_set_lightable(Object *obj, BOOL lightable);

/**
 * @name STATUS obj_set_not_hidden (Object *obj);
 * @brief function that modify the property, hidden, of the object.
 * @param obj
 * @return devuelve OK si ha ido todo bien o ERROR si ha habido algun problema.
 */
STATUS obj_set_not_hidden(Object *obj);

/**
 * @name char * obj_get_description(Object *obj);
 * @brief function that get the description of the object
 * @param obj
 * @return devuelve la descripcion del objeto o NULL en caso de error
 */
char * obj_get_description(Object *obj);

/**
 * @name char * obj_get_descInspect(Object *obj);
 * @brief function that get the descriptionInspect of the object
 * @param obj
 * @return devuelve la descripcion del objeto o NULL en caso de error
 */
char * obj_get_descInspect(Object *obj);

/**
 * @name char * obj_get_descMoved(Object *obj);
 * @brief function that get the descriptionMoved of the object
 * @param obj
 * @return devuelve la descripcion del objeto o NULL en caso de error
 */
char * obj_get_descMoved(Object *obj);

/**
 * @name char * obj_get_name(Object *obj);
 * @brief function that get the name of the object
 * @param obj
 * @return devuelve el nombre del objeto o NULL en caso de error
 */
char * obj_get_name(Object *obj);

/**
 * @name BOOL obj_is_movable(Object *obj);
 * @brief comprueba si un objeto es movable o no
 * @param obj
 * @return TRUE si el objeto es movable, FALSE si no es asi
 */
BOOL obj_is_movable(Object *obj);


/**
 * @name STATUS obj_print(Object *obj);
 * @brief prints the object
 * @param obj
 * @return OK si se ha impreso por pantalla correctamente o ERROR en caso contrario
 */
STATUS obj_print(Object *obj);

/**
 * @name BOOL obj_is_lightable(Object *obj);
 * @brief comprueba si el objeto es lightable
 * @param obj
 * @return TRUE en caso de que sea lightable, FALSE en caso contrario
 */
BOOL obj_is_lightable(Object *obj);

/**
 * @name BOOL obj_is_lighted(Object *obj);
 * @brief comprueba si el objeto es lighted
 * @param obj
 * @return TRUE en caso de que sea lighted, FALSE en caso contrario
 */
BOOL obj_is_lighted(Object *obj);

/**
 * @name BOOL obj_is_hidden(Object *obj);
 * @brief comprueba si el objeto es hidden(oculto)
 * @param obj
 * @return TRUE en caso de que sea hidden(oculto), FALSE en caso contrario
 */
BOOL obj_is_hidden(Object *obj);

/**
 * @name BOOL obj_is_movable(Object *obj);
 * @brief comprueba si el objeto es se mueve
 * @param obj
 * @return TRUE en caso de que sea hidden(oculto), FALSE en caso contrario
 */
BOOL obj_is_movable(Object *obj);

/**
 * @name Id obj_is_name(Object *obj, char *name);
 * @brief Given a name return ID if the objetc exists
 * @param obj
 * @param name
 * @return ID if the objetc exists, NO_ID in the other case
 */
Id obj_is_name(Object *obj, char *name);

#endif /*_OBJECT*/
