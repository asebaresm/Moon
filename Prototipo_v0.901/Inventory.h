/*
* Inventory.h
*/
#ifndef INVENTORY_H
#define INVENTORY_H

#include "Types.h"
#include "Set.h"

#define MAX_DEFAULT 50

typedef struct _Inventory Inventory;

/* Functions to create and destroy an inventory */
Inventory *create_inventory();

void destroy_inventory(Inventory *inv);

/* Sets the maximum number of objects in the inventory */
STATUS inventory_set_max_objects(Inventory * inv, unsigned int max_objects);

/* Function to include an object in the inventory */
STATUS inventory_add_obj(Inventory *inv, Id id);

/* Given an ID searches the inventory for the corresponding object. */
BOOL inventory_search_obj(Inventory *inv, Id id);

/* Given an object ID and an inventory, the corresponding object is 
removed from the inventory */
STATUS inventory_remove_obj(Inventory *inv, Id id);

/*Devuelve el numero de elmentos del set del inventario*/
 Size get_inventory_set_size(Inventory *inv);

 /*Devuelve la id de un objeto del inventario*/
 Id get_id_from_inv_obj(Inventory *inv, Id id);

 /*devuelve una ID de un objeto dle inventario a partir de un indice*/
Id get_id_from_inv_index(Inventory *inv, int indice);

#endif
