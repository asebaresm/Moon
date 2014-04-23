/**
 *@file Player.c
 *@brief contiene las implementaciones de las funciones de Player
 *@author Alfonso
 *@date 24-03-2014
 */

#include "Player.h"
#include "Set.h"

/** * @brief TAD Player*/
struct _Player {
    char name[WORD_SIZE + 1];
    Id location;
    Inventory * inventory;
};

/* Functions to create and destroy a player */
Player *create_player() {
    Player *jugador;
    Inventory *inventario;

    jugador = (Player*) malloc(sizeof (Player));
    if (!jugador)
        return NULL;

    inventario = create_inventory();
    if (!inventario)
        return NULL;
    jugador->inventory = inventario;
    jugador->location=NO_ID;
    if(player_set_name(jugador, "MAOKAI")==ERROR)
        return NULL;
    return jugador;
}

/*destruye el player*/
void destroy_player(Player *player) {
    destroy_inventory(player->inventory);
    free(player);
}

/* Functions to acces to the properties of a player */
Id player_get_location(Player *player) {
    if (!player)
        return NO_ID;
    return player->location;
}

/*devuelve el nombre del player*/
char *player_get_name(Player *player) {
    if (!player)
        return NULL;
    return player->name;
}

/* Given an object ID removes that object from the inventory of the 
player */
STATUS player_remove_obj(Player *player, Id object_id) {
    if (!player)
        return ERROR;
    if (inventory_remove_obj(player->inventory, object_id) == ERROR)
        return ERROR;
    return OK;
}

/* Searches for an object in the inventory of the player. */
BOOL player_search_obj(Player *player, Id object_id) {
    if (!player)
        return FALSE;
    return inventory_search_obj(player->inventory, object_id);
}

/*Comprueba si el inventario del player esta lleno*/
BOOL is_player_inv_full(Player *player) {
    if (!player)
        return FALSE;
    if (get_inventory_set_size(player->inventory) == get_inventory_max(player->inventory))
        return TRUE;
    return FALSE;
}

/*establece el maximo de objetos del player*/
STATUS player_set_max_objects(Player *player, unsigned int max_objects) {
    if (!player)
        return ERROR;
    if (inventory_set_max_objects(player->inventory, max_objects) == ERROR)
        return ERROR;
    return OK;
}

/*establece la posicion del player*/
STATUS player_set_location(Player *player, Id space_id) {
    if (!player || space_id==NO_ID)
        return ERROR;
    player->location = space_id;
    return OK;
}

/*establece el nombre del player*/
STATUS player_set_name(Player *player, char *name) {
    if (!player || !name)
        return ERROR;
    strcpy(player->name, name);
    return OK;
}

/* Function to add an object to the player’s inventory */
STATUS player_add_obj(Player *player, Id object_id) {
    if (!player)
        return ERROR;
    if (inventory_add_obj(player->inventory, object_id) == ERROR)
        return ERROR;
    return OK;
}

/*Devuelve el tamanyo del inventario del player*/
Size player_inv_size(Player *player) {
    if (!player)
        return NO_TAM;
    if (get_inventory_set_size(player->inventory) == NO_TAM)
        return NO_TAM;
    return get_inventory_set_size(player->inventory);
}

/*Devuelve la direccion del inventario del player*/
Inventory * get_player_inv(Player *player) {
    if (!player)
        return NULL;
    return player->inventory;
}

/*Devuelve la id de un objeto que lleva un player en funcion de un indice*/
Id get_id_from_player_inv_set_index(Player *player, int indice) {
    if (!player || indice < 0)
        return NO_ID;
    return get_id_from_inv_index(player->inventory, indice);
}
