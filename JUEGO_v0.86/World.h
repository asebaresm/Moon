/**
 *@brief TAD que representa un mundo
 *@file world.h
 *@author Albert Soler, Alfonso Sebares y Pablo yus
 *@version 0.01
 *@date 13-03-2014
 */




#ifndef _WORLD
#define _WORLD

#include "Types.h"
#include "Player.h"
#include "Link.h"
#include "Space.h"
#include "Object.h"

/**
 *@brief Estructura de mundo
 */


typedef struct _World World;


/**
 *@name: World *create_world();
 *@brief: function to create the world.
 *@return: the world you have create.
 */
World *create_world();

/**
 *@name: void destroy_world(World *w);
 *@brief: function to destroy the world.
 *@param: the world that you want destroy.
 *@return: NULL si hay algun errror.
 */
void destroy_world(World *w);

/**
 *@name: Space *world_add_space(World *w, Id id); 
 *@brief: añade un espacio a menudo.
 *@param: mundo al que añadir el espacio.
 *@param: id del espacio que se quiere añadir.
 *@return: el espacio que se ha añadido, o NULL en caso de error.
 */
Space *world_add_space(World *w, Id id);

/**
 *@name: Object *world_add_obj(World *w, Id id);
 *@brief: añade un objeto a mundo.
 *@param: mundo al que añadir el objeto.
 *@param: id del objeto que se quiere añadir.
 *@return: el objeto que se ha añadido, o NULL en caso de error.
 */
Object *world_add_obj(World *w, Id id);

/**
 *@name: Link *world_add_link(World *w, Id id);
 *@brief: añade un link al mundo.
 *@param: mundo al que añadir el link.
 *@param: id del link que se quiere añadir.
 *@return: el link que se ha añadido, o NULL en caso de error.
 */
Link *world_add_link(World *w, Id id);

/**
 *@name: Player *world_set_player(World *w);
 *@brief: inicializa un jugador en mundo.
 *@param: mundo al que añadir el jugador.
 *@return: el jugador que se ha añadido, o NULL en caso de error.
 */
Player *world_set_player(World *w);

/**
 *@name: Space *world_get_space(World *w, Id id);
 *@brief: obtienes un espacio a partir de su id y del mundo en el que se encuentra. 
 *@param: mundo donde esta el esapcio.
 *@param: id del espacio
 *@return: el espacio que se queria obtener, o NULL en caso de error. 
 */
Space *world_get_space(World *w, Id id);

/**
 *@name: Link *world_get_link(World *w, Id id);
 *@brief: obtienes un link a partir de su id y del mundo en el que se encuentra. 
 *@param: mundo donde esta el link.
 *@param: id del link
 *@return: el link que se queria obtener, o NULL en caso de error. 
 */
Link *world_get_link(World *w, Id id);
/**
 * @name Object *world_get_obj_by_name(World *w, char * name);
 * @brief coge un objeto del mundo a partir de su nombre
 * @param w
 * @param name
 * @retur el objeto correspondiente o NULL en caso de error
 */
Object *world_get_obj_by_name(World *w, char * name);

/**
 * @name Object *world_get_obj_by_descInspec(World *w, char * descInspec);
 * @brief coge un objeto del mundo a partir de su descripcion de inspeccion
 * @param w
 * @param descInspec
 * @retur el objeto correspondiente o NULL en caso de error
 */
Object *world_get_obj_by_descInspec(World *w, char * descInspec);

/**
 * @name Object *world_get_obj(World *w, Id id);
 * @brief obtien un objeto del mundo a partir de su id
 * @param w
 * @param id
 * @return el objeto correspondiente o NULL en caso de error
 */
Object *world_get_obj(World *w, Id id);


/**
 * @name Space *world_get_space_north(World *w, Id space);
 * @brief toma un espacio que esta al norte a partir de un mundo y el id del espacio
 * @param w
 * @param space
 * @return el espacio o NULL en caso de error
 */
Space *world_get_space_north(World *w, Id space);

/* Given a space ID returns the space located south. Returns NULL if there is none or if the link between them is closed. */
/**
 * @name Space *world_get_space_south(World *w, Id space);
 * @brief toma un espacio que esta al sur a partir de un mundo y el id del espacio
 * @param w
 * @param space
 * @return el espacio o NULL en caso de error
 */
Space *world_get_space_south(World *w, Id space);

/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
/**
 * @name Space *world_get_space_east(World *w, Id space);
 * @brief toma un espacio que esta al este a partir de un mundo y el id del espacio
 * @param w
 * @param space
 * @return el espacio o NULL en caso de error
 */
Space *world_get_space_east(World *w, Id space);

/* Given a space ID returns the space located west. Returns NULL if there is none or if the link between them is closed. */
/**
 * @name Space *world_get_space_west(World *w, Id space);
 * @brief toma un espacio que esta al oeste a partir de un mundo y el id del espacio
 * @param w
 * @param space
 * @return el espacio o NULL en caso de error
 */
Space *world_get_space_west(World *w, Id space);

/* Given a space ID returns the space located up. Returns NULL if there is none or if the link between them is closed. */
/**
 * @name Space *world_get_space_up(World *w, Id space) ;
 * @brief toma un espacio que esta a arriba a partir de un mundo y el id del espacio
 * @param w
 * @param space
 * @return el espacio o NULL en caso de error
 */
Space *world_get_space_up(World *w, Id space);

/* Given a space ID returns the space located down. Returns NULL if there is none or if the link between them is closed. */
/**
 * @name Space *world_get_space_down(World *w, Id space);
 * @brief toma un espacio que esta debajo a partir de un mundo y el id del espacio
 * @param w
 * @param space
 * @return el espacio o NULL en caso de error
 */
Space *world_get_space_down(World *w, Id space);

/**
 * @name Object *world_get_obj_from_space(World *w, char *name, Id space);
 * @brief coge un objeto de un espacio que se encuentra en un mundo
 * @param w
 * @param name
 * @param space
 * @return el objeto o NULL en caso de error 
 */
Object *world_get_obj_from_space(World *w, char *name, Id space);

/**
 * @name STATUS world_get_space_description(World *w, Id space, char * desc, Size max_len);
 * @brief da la descripcion de un espacio contenido en un mundo
 * @param w
 * @param space
 * @param desc
 * @param max_len
 * @return OK en caso de que haya ido todo bien o ERROR en caso de error
 */
STATUS world_get_space_description(World *w, Id space, char * desc, Size max_len);


/**
 * @name STATUS world_move_player(World *w, DIRECTION dir);
 * @brief mover un jugador que se encuentra en el mundo
 * @param w
 * @param dir
 * @return OK si se ha movido el jugador correctamente o ERROR en caso contrario
 */
STATUS world_move_player(World *w, DIRECTION dir);

/**
 * @name STATUS world_inspect_space(World *w, Space *space, char *desc, int max_len);
 * @brief comprueba la descripcion de un  espacio
 * @param w
 * @param space
 * @param desc
 * @param max_len
 * @return OK en caso de que se haya podido inspeccionar o ERROR en cualquier otro caso
 */
STATUS world_inspect_space(World *w, Space *space, char *desc, int max_len);


/**
 * @name STATUS world_inspect_obj(World * m, Object *obj, char *desc, int max_len);
 * @brief ese encarga de inspeccionar un objeto
 * @param m
 * @param obj
 * @param desc
 * @param max_len
 * @return OK si se ha podido inspeccionar o ERROR en caso contrario
 */
STATUS world_inspect_obj(World * m, Object *obj, char *desc, int max_len);

/**
 * @name STATUS world_pick_up_obj(World *w, Object *obj);
 * @brief coge un objeto perteneciente a un mundo
 * @param w
 * @param obj
 * @return OK si se ha podido coger o ERROR en caso contrario
 */
STATUS world_pick_up_obj(World *w, Object *obj);

/**
 * @name STATUS world_drop_obj(World *w, Object *obj);
 * @brief dejar un objeto que esta en un mundo
 * @param w
 * @param obj
 * @return OK si se ha podido dejar o ERROR en caso contrario
 */
STATUS world_drop_obj(World *w, Object *obj);

/**
 * @name STATUS world_turn_light_on_obj(World *w, Object *obj);
 * @brief ilumina un objeto que hay en un mundo
 * @param w
 * @param obj
 * @return OK si ha ido todo bien o ERROR en cualquier otro caso
 */
STATUS world_turn_light_on_obj(World *w, Object *obj);

/**
 * @name STATUS world_turn_light_off_obj(World *w, Object *obj);
 * @brief apaga un objeto que hay en un mundo
 * @param w
 * @param obj
 * @return OK si ha ido todo bien o ERROR en cualquier otro caso
 */
STATUS world_turn_light_off_obj(World *w, Object *obj);


/**
 * @name STATUS world_illuminate_space(World * m, Space *space);
 * @brief ilumina un espacio de un mundo
 * @param m
 * @param space
 * @return OK si ha ido todo bien o ERROR en cualquier otro caso
 */
STATUS world_illuminate_space(World * m, Space *space);

/**
 * @name BOOL is_space_lighten_by_object(World *m, Space *space);
 * @brief busca si algun objeto encendido del mundo m esta en el espacio space
 * @param m
 * @param space
 * @return TRUE si esta el objeto en el espacio o FALSE en caso contrario
 */
BOOL is_space_lighten_by_object(World *m, Space *space);

/**
 * @name BOOL is_object_inventory_lighted(World *m, Inventory *inv);
 * @brief busca si algun objeto encendido del mundo m esta en el inventario inv 
 * @param m
 * @param inv
 * @return TRUE si esta el obejto que se buscaba o FALSE en caso contrario
 */
BOOL is_object_inventory_lighted(World *m, Inventory *inv);

/**
 * @name BOOL is_object_inventory(World *m, Inventory *inv);
 * @brief comprueba si un objeto esta en el inventario
 * @param m
 * @param inv
 * @return TRUE si esta, FALSE si no esta
 */
BOOL is_object_inventory(World *m, Inventory *inv);

/**
 * @name Id where_is_player(World *w);
 * @brief da la id de la localizacion del player 
 * @param w
 * @return la id del jueador o NO_ID en caso de error
 */
Id where_is_player(World *w);

/**
 * @name STATUS set_player_location(World *w, Id id);
 * @brief establece la posicion del player
 * @param w
 * @param id
 * @return ERROR / OK
 */
STATUS set_player_location(World *w, Id id);

/**
 * @name BOOL obj_is_lightable(Object *obj);
 * @brief comprueba si un objeto se puede encender
 * @param obj
 * @return TRUE o FALSE
 */
BOOL obj_is_lightable(Object *obj);

/**
 * @name BOOL obj_is_lighted(Object *obj);
 * @brief comprueba si un objeto esta encendido
 * @param obj
 * @return TRUE o FALSE
 */
BOOL obj_is_lighted(Object *obj);

/**
 * @name BOOL obj_is_hidden(Object *obj);
 * @brief comprueba si un objeto esta escondido
 * @param obj
 * @return TRUE o FALSE
 */
BOOL obj_is_hidden(Object *obj);

/**
 * @name BOOL obj_is_movable(Object *obj);
 * @brief comprueba si un objeto se puede mover
 * @param obj
 * @return TRUE o FALSE
 */
BOOL obj_is_movable(Object *obj);

/**
 * @name BOOL  game_finish(World *w);
 * @brief comprueba si se cumplen las condiciones de fin del juego
 * @param w
 * @return TRUE o FALSE
 */
BOOL game_finish(World *w);

/**
 * @name STATUS consume_obj(World *w,Id object_id);
 * @brief Consume un objeto
 * @param w
 * @param object_id
 * @return ERROR / OK
 */
STATUS consume_obj(World *w,Id object_id);

/**
 * @name STATUS reveal_space_objects(World *w, Space *s);
 * @brief revela los objetos de un espacio
 * @param w
 * @param s
 * @return ERROR / OK
 */
STATUS reveal_space_objects(World *w, Space *s);

/**
 * @name Player *world_get_player(World *w);
 * @brief devuelve el puntero de un jugador en mundo
 * @param w
 * @return Player puntero a player o null en caso de error
 */
Player *world_get_player(World *w);

/**
 * @name STATUS you_shall_turn_linterna_off(World *w);
 * @brief en el caso de llevar la linterna y ser encendible (no consumida), la apaga
 * @param w
 * @return ERROR/OK
 */
STATUS you_shall_turn_linterna_off(World *w);

STATUS print_inventory_full (World *w);
STATUS print_inventory (World *w);
STATUS world_open_door(World *w, Id link_id);

STATUS print_objs_space(World *w, Space *s );

STATUS consume_obj_oxi(World *w, char *c);
#endif /*_WORLD*/
