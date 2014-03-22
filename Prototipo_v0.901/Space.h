/**
*@brief TAD que representa un espacio en el mundo
*@file espacio.h
*@author Albert Soler
*@version 0.01
*@date 06-03-2014
*/

#include "Types.h"
#include "Set.h"

typedef struct _Space Space;

/* Functions to create and destroy a particular space */
/**
*@brief Funcion que crea un espacio
*@param id 
*@return devuelve un puntero al espacio formado.
*/
Space *create_space(Id id);

/**
*@brief Funcion que destruye un espacio
*@param space espacio a destruir
*/
void destroy_space(Space *space);

/* Functions that modify space properties values */ 
STATUS space_set_description(Space *space, char *description);

STATUS space_set_description_inspect(Space *space, char *description);

STATUS space_set_light(Space *space, BOOL light);
 
 /* Functions to add elements to a space */ 
STATUS space_add_link_north(Space *space, Id link_id);

STATUS space_add_obj (Space *space, Id object_id);

/* Functions to access the properties of a space */ 
const char * desc_space(Space *space);

/* Given a space returns the link to the north. Returns NO_ID if there is no such link */ 
Id space_get_north(Space *space);

/* Prints a space. This function is included for debugging purposes */
 BOOL space_print(Space *space);

/*Devuelve la id de un objeto del set para ese espacio en funcion de un indice*/
 Id get_id_from_space_set_index(Space *space, int indice);

 /*Devuelve el numero de objetos que hay en un espacio*/
 Size get_space_set_size(Space *space);

/*Comprueba si el set de objetos para un espacio esta vacio*/
 BOOL is_space_set_empty(Space *space);

/*Comprueba si el espacio esta iluminado*/
BOOL is_space_lighted(Space *space);

/**
 *@name: Id space_get_id(Space *s);
 *@author: Pablo Yus.
 *@brief: devuleve el id de un espacio.
 
 *@param: Space * s: espacio del que se quiere conocer su id.
 
 *@return: el id del espacio o NULL si hay algun errror.
 */
 Id space_get_id(Space *space);

/*NOTA
ambién tienes que incluir una nueva función en el módulo World para que los espacios se pueden añadir a un mundo concreto.*/

/* Space *world_add_space(World *w, Id id); */
