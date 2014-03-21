/** 
 * Player.h
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Types.h"
#include "Inventory.h"

typedef struct _Player Player;

/* Functions to create and destroy a player */
Player *create_player();

void destroy_player(Player *player);

/* Functions to acces to the properties of a player */
Id player_get_location(Player *player);
/* (...) */

/* Given an object ID removes that object from the inventory of the 
player */
STATUS player_remove_obj(Player *player, Id object_id);

/* Searches for an object in the inventory of the player. */
BOOL player_search_obj(Player *player, Id object_id);

STATUS player_set_max_objects(Player *player, unsigned int max_objects);

STATUS player_set_location(Player *player, Id space_id);

/* Function to add an object to the player’s inventory */
STATUS player_add_obj(Player *player, Id object_id);

/*Devuelve el tamanyo del inventario del player*/
Size player_inv_size(Player *player);

/*Devuelve la direccion del inventario del player*/
Inventory * get_player_inv(Player *player);

#endif

