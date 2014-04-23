/**
 *@file Player.h
 *@brief contiene los prototipos de las funciones de Player
 *@author Alfonso
 *@date 24-03-2014
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Types.h"
#include "Inventory.h"

typedef struct _Player Player;

/**
 * @name Player *create_player();
 * @brief crea un nuevo jugador
 * @return devuelve el jugador creado o NULL en caso de error
 */
Player *create_player();

/**
 * @name void destroy_player(Player *player);
 * @brief destruye un jugador
 * @param player
 */
void destroy_player(Player *player);

/**
 * @name Id player_get_location(Player *player);
 * @brief da la localizacion de un jugador
 * @param player
 * @return el id de la localizacion del jugador o NO_ID en caso de error
 */
Id player_get_location(Player *player);

/**
 * @name char *player_get_name(Player *player);
 * @brief devuelve el nombre del player
 * @param player
 * @return nombre del jugador
 */
char *player_get_name(Player *player);

/**
 * @name STATUS player_remove_obj(Player *player, Id object_id);
 * @brief dado un id de un objeto, borrara este objeto del inventario del jugador
 * @param player
 * @param object_id
 * @return OK si el objeto se ha podido elimniar de forma correcta o ERROR en caso de error
 */
STATUS player_remove_obj(Player *player, Id object_id);


/**
 * @name BOOL player_search_obj(Player *player, Id object_id);
 * @brief busca un objeto, dado su id, en el inventario de un juegador
 * @param player
 * @param object_id
 * @return TRUE si el objeto se ha encontrado o FALSE en caso contrario
 */
BOOL player_search_obj(Player *player, Id object_id);

/**
 * @name BOOL is_player_inv_full(Player *player);
 * @brief comprueba si el inventario esta lleno
 * @param player
 * @return TRUE si el inventario esta lleno o FALSE en caso contrario
 */
BOOL is_player_inv_full(Player *player);

/**
 * @name STATUS player_set_max_objects(Player *player, unsigned int max_objects);
 * @brief determina el tamaño maximo de objetos que puede tener uun jugador en su inventario
 * @param player
 * @param max_objects
 * @return OK si ha ido todo bien, ERROR si ha habido algun error
 */
STATUS player_set_max_objects(Player *player, unsigned int max_objects);

/**
 * @name STATUS player_set_location(Player *player, Id space_id);
 * @brief establece la localicizacion de un jugador
 * @param player
 * @param space_id
 * @return OK si ha ido todo bien, ERROR si ha habido algun error
 */
STATUS player_set_location(Player *player, Id space_id);

/**
 * @name STATUS player_set_name (Player *player, char *name);
 * @brief establece el nombre de un jugador
 * @param player
 * @param name
 * @return OK si ha ido todo bien, ERROR si ha habido algun error
 */
STATUS player_set_name(Player *player, char *name);

/**
 * @name STATUS player_add_obj(Player *player, Id object_id);
 * @brief añade un objeto, a partir de su id, al inventario del jugador
 * @param player
 * @param object_id
 * @return OK si ha ido todo bien, ERROR si ha habido algun error
 */
STATUS player_add_obj(Player *player, Id object_id);

/**
 * @name Size player_inv_size(Player *player);
 * @brief calcula el tamaño del inventario del jugador
 * @param player
 * @return el tamaño del inventario del jugador o en caso de error NO_TAM
 */
Size player_inv_size(Player *player);

/**
 * @name Inventory * get_player_inv(Player *player); 
 * @brief devuelve la direccion del inventario del player
 * @param player
 * @return el inventario del jugador o NULL en caso de error
 */
Inventory * get_player_inv(Player *player);

/**
 * @name Id get_id_from_player_inv_set_index(Player *player, int indice);
 * @brief Devuelve la id de un objeto que lleva un player en funcion de un indice
 * @param player
 * @param indice
 * @return la id del objeto o NULL en caso de error
 */
Id get_id_from_player_inv_set_index(Player *player, int indice);

#endif
