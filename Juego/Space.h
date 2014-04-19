/**
 *@brief TAD que representa un espacio en el mundo
 *@file space.h
 *@author Albert Soler
 *@version 0.01
 *@date 13-03-2014
 */

#ifndef SPACE_H
#define	SPACE_H


#include "Set.h"

/** @brief Estrucura de espacio */
typedef struct _Space Space;

/**
 * @name Space *create_space(Id id);
 * @brief Funcion que crea un espacio
 * @param id 
 * @return devuelve un puntero al espacio formado.
 */
Space *create_space(Id id);

/**
 * @name void destroy_space(Space *space);
 * @brief Funcion que destruye un espacio
 * @param space espacio a destruir
 */
void destroy_space(Space *space);

/**
 * @name STATUS space_set_description(Space *space, char *description);
 * @brief establece una descripcion a un espacio
 * @param space
 * @param description
 * @return OK si todo ha salido correctamente o ERROR en caso de error
 */
STATUS space_set_description(Space *space, char *description);

/**
 * @name STATUS space_set_description_inspect(Space *space, char *description);
 * @brief establece la descripcion ,al inspeccionar un espacio, de este mismo
 * @param space
 * @param description
 * @return OK si se ha establecido bien o ERROR en caso de error
 */
STATUS space_set_description_inspect(Space *space, char *description);

/**
 * @name STATUS space_set_description_graphical(Space *space, char *descriptionGraph);
 * @brief establece la descripcion grafica (mapa) de un espacio
 * @param space
 * @param descriptionGraph
 * @return OK si se ha establecido bien o ERROR en caso de error
 */
STATUS space_set_description_graphical(Space *space, char *descriptionGraph);
/**
 * @name STATUS space_set_light(Space *space, BOOL light);
 * @brief establece si un espacio esta iluminado
 * @param space
 * @param light
 * @return OK si todo ha ido bien o ERROR en caso de error
 */
STATUS space_set_light(Space *space, BOOL light);

/**
 * @name STATUS space_add_link_north(Space *space, Id link_id);
 * @brief añade un union(link) al lado norte de un espacio
 * @param space
 * @param link_id
 * @return OK si todo ha ido bien o ERROR en caso de error
 */
STATUS space_add_link_north(Space *space, Id link_id);

/**
 * @name STATUS space_add_link_west(Space *space, Id link_id);
 * @brief añade un union(link) al lado oeste de un espacio
 * @param space
 * @param link_id
 * @return OK si todo ha ido bien o ERROR en caso de error
 */
STATUS space_add_link_west(Space *space, Id link_id);

/**
 * @name STATUS space_add_link_south(Space *space, Id link_id);
 * @brief añade un union(link) al lado sur de un espacio
 * @param space
 * @param link_id
 * @return OK si todo ha ido bien o ERROR en caso de error
 */
STATUS space_add_link_south(Space *space, Id link_id);

/**
 * @name STATUS space_add_link_east(Space *space, Id link_id);
 * @brief añade un union(link) al lado este de un espacio
 * @param space
 * @param link_id
 * @return OK si todo ha ido bien o ERROR en caso de error
 */
STATUS space_add_link_east(Space *space, Id link_id);

/**
 * @name STATUS space_add_link_up(Space *space, Id link_id); 
 * @brief añade un union(link) al lado arriba de un espacio
 * @param space
 * @param link_id
 * @return OK si todo ha ido bien o ERROR en caso de error
 */
STATUS space_add_link_up(Space *space, Id link_id);

/**
 * @name STATUS space_add_link_down(Space *space, Id link_id);
 * @brief añade un union(link) al lado abajo de un espacio
 * @param space
 * @param link_id
 * @return OK si todo ha ido bien o ERROR en caso de error
 */
STATUS space_add_link_down(Space *space, Id link_id);

/**
 * @name STATUS space_add_obj(Space *space, Id object_id);
 * @brief añade un objeto, a partir de su id, al espacio 
 * @param space
 * @param object_id
 * @return 
 */
STATUS space_add_obj(Space *space, Id object_id);

/**
 * @name STATUS space_remove_obj (Space *space, Id object_id);
 * @brief elimina un objeto del espacio
 * @param space
 * @param object_id
 * @return ERROR / OK
 */
STATUS space_remove_obj(Space *space, Id object_id);

/**
 * @name const char * desc_space(Space *space);
 * @brief da la descripcion de un espacio
 * @param space
 * @return devuelve la descripcion de dicho espacio o NULL en caso de error
 */
const char * desc_space(Space *space);

/**
 * @name const char * desc_space_inspect(Space *space);
 * @brief da la descripcion de un espacio cuando se inspecciona
 * @param space
 * @return devuelve la descripcion de dicho espacio o NULL en caso de error
 */
const char * desc_space_inspect(Space *space);

/**
 * @name Id space_get_north(Space *space);
 * @brief da la id del espacio que se encuentra por el lado norte del espacio
 * @param space
 * @return la id del espacio o NO_ID en caso de error
 */
Id space_get_north(Space *space);


/**
 * @name Id space_get_south(Space *space);
 * @brief da la id del espacio que se encuentra por el lado sur del espacio
 * @param space
 * @return la id del espacio o NO_ID en caso de error
 */
Id space_get_south(Space *space);

/**
 * @name Id space_get_east(Space *space);
 * @brief da la id del espacio que se encuentra por el lado este del espacio
 * @param space
 * @return la id del espacio o NO_ID en caso de error
 */
Id space_get_east(Space *space);

/**
 * @name Id space_get_west(Space *space);
 * @brief da la id del espacio que se encuentra por el lado oeste del espacio
 * @param space
 * @return la id del espacio o NO_ID en caso de error
 */
Id space_get_west(Space *space);

/**
 * @name Id space_get_up(Space *space);
 * @brief da la id del espacio que se encuentra por el lado de arriba del espacio
 * @param space
 * @return la id del espacio o NO_ID en caso de error
 */
Id space_get_up(Space *space);

/**
 * @name Id space_get_down(Space *space);
 * @brief da la id del espacio que se encuentra por el lado de abajo del espacio
 * @param space
 * @return la id del espacio o NO_ID en caso de error
 */
Id space_get_down(Space *space);
/**
 * @name BOOL space_print(Space *space);
 * @brief imprime por pantalla el espacio con cada uno de sus campos
 * @param space
 * @return TRUE si la impresion por pantalla ha sido correcta o FALSE en caso contrario
 */
BOOL space_print(Space *space);

/**
 * @name Id get_id_from_space_set_index(Space *space, int indice);
 * @brief devuelve la id de un objeto del set para ese espacio en funcion de un indice
 * @param space
 * @param indice
 * @return la id del objeto o en caos de error NO_ID
 */
Id get_id_from_space_set_index(Space *space, int indice);

/**
 * @name Size get_space_set_size(Space *space);
 * @brief devuelve el numero de objetos que hay en un espacio
 * @param space
 * @return el numero de objetos que hay en el espacio o NO_TAM en caso de error
 */
Size get_space_set_size(Space *space);

/*Comprueba si el set de objetos para un espacio esta vacio*/
/**
 * @name BOOL is_space_set_empty(Space *space);
 * @brief comprueba si el set 
 * @param space
 * @return el numero de objetos que hay en el espacio o NO_TAM en caso de error
 */
BOOL is_space_set_empty(Space *space);


/**
 *@name: BOOL is_space_lighted(Space *space);
 *@brief: comprueba si un estapcio esta iluminado
 *@param: space
 *@return: TRUE si esta encendido (iluminado) o FALSE si no lo esta
 */
BOOL is_space_lighted(Space *space);

/**
 *@name: Id space_get_id(Space *s);
 *@author: Pablo Yus.
 *@brief: devuleve el id de un espacio.
 *@param: Space * s: espacio del que se quiere conocer su id.
 *@return: el id del espacio o NULL si hay algun errror.
 */
Id space_get_id(Space *space);

/**
 *@name: BOOL space_get_object(Space *space, Id id);
 *@brief: comprueba si existe el objeto con esa id en el espacio
 *@param: space
 *@param: id
 *@return: TRUE si se ha encontrado el objeto o FALSE en caso contrario
 */
BOOL space_get_object(Space *space, Id id);


#endif	/* SPACE_H */
