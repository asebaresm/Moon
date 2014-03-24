#ifndef _WORLD
#define _WORLD

#include "Types.h"
#include "Player.h"
#include "Link.h"
#include "Space.h"
#include "Object.h"


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
 *@brief: añade un espacio a menudo
 
 *@param: mundo al que añadir el espacio
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

/* Returns a reference to the corresponding element given an ID. Returns NULL if there is an error or if the element is not found. */
Object *world_get_obj_by_name(World *w, char * name);

Object *world_get_obj(World *w, Id id);

/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
 Space *world_get_space_north(World *w, Id space);
/* Given the name of an object checks if it is located in a given space. Returns the object or NULL if it does not exist. */
 Object *world_get_obj_from_space(World *w, char *name, Id space);
/* Shows the description of the space and its visible objects. Hidden objects are not shown. The client must reserve enough memory for desc. */ 
 STATUS world_get_space_description(World *w, Id space, char * desc, Size max_len);

 /* Changes the location of the player. The current place must be connected to the destination. */ 
 STATUS world_move_player(World *w, DIRECTION dir);
 /* Inspect spaces. Example: 
 -> if there is light 
 -> inspect the room 
The description is returned in the parameter desc which must be allocated by the client */ 
STATUS world_inspect_space(World *w, Space *space, char *desc, int max_len);


/* Inspect Objects. Example: 
 -> if there is light 
 -> inspect object from the inventory or in the current room (if 
hidden, the object is no longer hidden). The description is returned 
in the parameter desc which must be allocated by the client. ***************__allocated by the client__*****/ 
STATUS world_inspect_obj(World * m, Object *obj, char *desc, int max_len);

/*REVISAR: si X objeto que tiene que hacer Y, no puede hacerlo?***********************/
/* Pick up an object 
 -> the object must not be hidden in the current space 
 -> the object must be movable 
 -> The inventory of the player has to have enough free space for the 
object */ 
STATUS world_pick_up_obj(World *w, Object *obj);
/* Drop an object 
 -> the object must be in the inventory */ 
STATUS world_drop_obj(World *w, Object *obj);

/* Light object 
 -> object in the current room or the inventory 
 -> The object must be lightable 
*/ 
STATUS world_turn_light_on_obj(World *w, Object *obj);

/* Unlight object 
 -> object in the current room or the inventory 
 -> The object must be lightable */ 
STATUS world_turn_light_off_obj(World *w, Object *obj);


/* Illuminates a space if the following conditions are met: 
 -> object is in the space and it is lighten 
 -> object is in the inventory and it is lighten */ 
STATUS world_illuminate_space(World * m, Space *space);

/*__________FUNCIONES AUX_________*/

/*AUX_world_1*/
/*busca si algun objeto encendido del mundo m esta en el espacio space*/
BOOL is_space_lighten_by_object(World *m, Space *space);

/*AUX_world_2*/
/*busca si algun objeto encendido del mundo m esta en el inventario inv*/
BOOL is_object_inventory_lighted(World *m, Inventory *inv);

/*AUX_world_3*/
BOOL is_object_inventory(World *m, Inventory *inv);

/*AUX_world_4*/
Id where_is_player(World *w);

STATUS set_player_location(World *w, Id id);

/*AUX_object_1*/
BOOL obj_is_lightable(Object *obj);
/*AUX_object_2*/
BOOL obj_is_lighted(Object *obj);

/*AUX_object_3*/
BOOL obj_is_hidden(Object *obj);

/*AUX_object_4*/
BOOL obj_is_movable(Object *obj);

/*AUX*/
Space *world_add_space(World *w, Id id);

#endif /*_WORLD*/
