/**
 *@file Inventory.h
 *@brief contiene los protoipos de las funciones de Inventory
 *@author Alfonso
 *@date 24-03-2014
 *@version 0.1
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "../Set/Set.h"

#define MAX_DEFAULT 50 /*!< maximo de por defecto de inventario*/

 /**
 *@brief estrucutra inverntory
 */

typedef struct _Inventory Inventory;

/**
 * @name Inventory *create_inventory();
 * @brief crea un nuevo inventario
 * @return el inventario creado y en caso de error devolvera NULL
 */
Inventory *create_inventory();

/**
 * @name void destroy_inventory(Inventory *inv);
 * @brief destruye inventario
 * @param inv
 */
void destroy_inventory(Inventory *inv);

/**
 * @name STATUS inventory_set_max_objects(Inventory * inv, unsigned int max_objects);
 * @brief determina el maximo de objetos que puede tener un inventario
 * @param inv
 * @param max_objects
 * @return OK si se ha establecido el maximo de forma correcta o ERROR en caso contrario.
 */

STATUS inventory_set_max_objects(Inventory * inv, unsigned int max_objects);

/**
 * @name STATUS inventory_add_obj(Inventory *inv, Id id);
 * @brief añade un objeto a un inventario
 * @param inv
 * @param id
 * @return OK si ha ido todo bien o ERROR en cualquier otro caso
 */
STATUS inventory_add_obj(Inventory *inv, Id id);

/**
 * @name BOOL inventory_search_obj(Inventory *inv, Id id); 
 * @brief busca objeto en inventario a partir de su id
 * @param inv
 * @param id
 * @return Devuelve TRUE si el objeto se encuentra en el inventario, FALSE en caso contrario
 */
BOOL inventory_search_obj(Inventory *inv, Id id);

/**
 * @name STATUS inventory_remove_obj(Inventory *inv, Id id);
 * @brief elimina un objeto de un inventario
 * @param inv
 * @param id
 * @return OK si se eliminado correctamente o ERROR si no ha sido asi
 */
STATUS inventory_remove_obj(Inventory *inv, Id id);

/**
 * @name Size get_inventory_set_size(Inventory *inv);
 * @brief funcion que establece el tamaño de un inventario
 * @param inv
 * @return devuelve el tamño delñ inventario o NO_TAM en caso de error
 */
Size get_inventory_set_size(Inventory *inv);

/**
 * @name Size get_inventory_max(Inventory *inv);
 * @brief funcion que devuelve el tamaño de un inventario
 * @param inv
 * @return devuelve el tamaño maximo inventario o NO_TAM en caso de error
 */
Size get_inventory_max(Inventory *inv);

/**
 * @name Id get_id_from_inv_obj(Inventory *inv, Id id);
 * @brief Devuelve la id de un objeto del inventario en funcion del indice del array del set
 * @param inv
 * @param id
 * @return la id del objeto que se encuentra en el inventario o NO_ID en caso de error
 */
Id get_id_from_inv_obj(Inventory *inv, Id id);

/**
 * @name Id get_id_from_inv_index(Inventory *inv, int indice);
 * @brief devuelve una ID de un objeto del inventario a partir de un indice
 * @param inv
 * @param indice
 * @return la id del objeto o NO_ID en caso contrario
 */
Id get_id_from_inv_index(Inventory *inv, int indice);

#endif
