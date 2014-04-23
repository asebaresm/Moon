                /**
 *@file Inventory.c
 *@brief contiene las implementaciones de las funciones de Inventory
 *@author Alfonso
 *@date 24-03-2014
 */

#include <stdio.h>
#include <stdlib.h>

#include "Inventory.h"

/**  *  @brief TAD inventario*/
struct _Inventory {
    unsigned int max_objects;
    Set * objects;
};

/*   funcion que crea un inventario */
Inventory *create_inventory() {
    Inventory *new_inv;
    Set *new_set_obj;

    new_inv = (Inventory*) malloc(sizeof (Inventory));
    new_set_obj = new_set();
    new_inv->objects = new_set_obj;
    new_inv->max_objects = MAX_DEFAULT;
    return new_inv;
}

/*  funcion que destruye un inventario */
void destroy_inventory(Inventory *inv) {
    destroy_set(inv->objects);
    free(inv);
}

/*  brief Sets the maximum number of objects in the inventory */
STATUS inventory_set_max_objects(Inventory * inv, unsigned int max_objects) {
    if (!inv)
        return ERROR;
    inv->max_objects = max_objects;
    return OK;
}

/*  Function to include an object in the inventory */
STATUS inventory_add_obj(Inventory *inv, Id id) {
    if (!inv)
        return ERROR;
    if (get_inventory_max(inv) == get_inventory_set_size(inv))
        return ERROR;
    if (add(inv->objects, id) == ERROR)
        return ERROR;
    return OK;
}

/*  Given an ID searches the inventory for the corresponding object. */
BOOL inventory_search_obj(Inventory *inv, Id id) {
    if (!inv)
        return FALSE;
    return contains(inv->objects, id);
}

/*  Given an object ID and an inventory, the corresponding object is 
        removed from the inventory */
STATUS inventory_remove_obj(Inventory *inv, Id id) {
    if (!inv)
        return ERROR;
    if (remove_id(inv->objects, id) == ERROR)
        return ERROR;
    return OK;
}

/*  Devuelve el numero de elmentos del set del inventario*/
Size get_inventory_set_size(Inventory *inv) {
    if (!inv)
        return NO_TAM;
    if (get_size(inv->objects) == NO_TAM)
        return NO_TAM;
    return get_size(inv->objects);
}

/*   devuelve el tam max de un iventario*/
Size get_inventory_max(Inventory *inv) {
    if (!inv)
        return NO_TAM;
    return inv->max_objects;
}

/* Devuelve la id de un objeto del inventario */
Id get_id_from_inv_obj(Inventory *inv, Id id) {
    int i;

    if (!inv)
        return NO_ID;
    for (i = 0; i < get_size(inv->objects); i++) {
        if (get_i_id(inv->objects, i) == NO_ID)
            return NO_ID;
        if (id == get_i_id(inv->objects, i))
            return id;
    }
    /*si no lo encuentra*/
    return NO_ID;
}

/* devuelve una ID de un objeto dle inventario a partir de un indice*/
Id get_id_from_inv_index(Inventory *inv, int indice) {
    if (!inv || indice < 0)
        return NO_ID;
    if (get_i_id(inv->objects, indice) == NO_ID)
        return NO_ID;
    return get_i_id(inv->objects, indice);
}

