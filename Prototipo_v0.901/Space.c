/**
*@brief TAD que representa un espacio en el mundo
*@file espacio.c
*@author Albert Soler
*@version 0.01
*@date 13-03-2014
*/

/*Notas:
* Que hacer con Set *space_objects; 
* Que hacer con la última funcion?
*/

#include "Space.h"

/*Tipo opaco de datos*/
struct _Space{
	Id id;
	char description[WORD_SIZE+1];
	char descInspect[WORD_SIZE+1];
	Id north;
	Id south;
	Id east;
	Id west;
	Id up;
	Id down;
	BOOL light;
	Set *space_objects;
};

/* Functions to create and destroy a particular space */
/**
*@brief Funcion que crea un espacio
*@param id 
*@return devuelve un puntero al espacio formado.
*/
Space *create_space(Id id){
	if(!id)
		return NULL;

	Space *new_space;
	new_space=(space*)malloc(sizeof(space));
	if(!new_space)
		return NULL;
	return new_space;

}

/**
*@brief Funcion que destruye un espacio
*@param space espacio a destruir
*/
void destroy_space(Space *space){

	free(space);
}

/* Functions that modify space properties values */
 STATUS space_set_description(Space *space,char *description){
 	if(!space || !description)
 		return ERROR;
 	/*Asignamos al espacio el valor de description*/
 	if(strcpy(space->description,description)==0)
 		return OK;
 	else
 		return ERROR;

 }


STATUS space_set_description_inspect(Space *space,char *description){
	 if(!space || !description)
 		return ERROR;
 	/*Asignamos al espacio el valor de description*/
 	/*Asignamos al espacio el valor de description*/
 	if(strcpy(space->descInspect,description)==0)
 		return OK;
 	else
 		return ERROR;
}


STATUS space_set_light(Space *space, BOOL light){
	if(!space || (light!=1 || light!=0))
		return ERROR;
	/*Asignamos el valor de luz al espacio*/
	space->light=light;
	return OK;

}


 /* Functions to add elements to a space */ 
STATUS space_add_link_north(Space *space, Id link_id){
	if(!space)
		return ERROR;
	space->north=link_id;
	return OK:
}


STATUS space_add_obj (Space *space, Id object_id){
	if(!space)
		return ERROR;
	/*mmmmm*/
	space->space_objects=object_id;
	return OK;

}

/* Functions to access the properties of a space */ 
const char * desc_space(Space *space){
	if(!space)
		return NULL;
	return space->description;

}
/* Given a space returns the link to the north. Returns NO_ID if there is no such link */ 
Id space_get_north(Space *space){
	if(!space)
		return NO_ID;
	if (space->north==0)
		return NO_ID;
	return space->north;

}
/* Prints a space. This function is included for debugging purposes */
 BOOL space_print(Space *space){
 	if(!space)
 		return FALSE;
 	printf("\n ID %d",space->id);
 	printf("\n description %s",space->description);
 	printf("\n descInspect %s",space->descInspect);
 	printf("\n north %d",space->north);
 	printf("\n south %d",space->south);
 	printf("\n east %d",space->east);
 	printf("\n west %d",space->west);
 	printf("\n up %d",space->up);
 	printf("\n down %d",space->down);
 	printf("\n light %d",space->light);
 	/*mmmm*/
 	printf("\n space_objects %d",space->space_objects);

 	return TRUE;

 }

/*NOTA
también tienes que incluir una nueva función en el módulo World para que los espacios se pueden añadir a un mundo concreto.*/

 /*Devuelve el numero de objetos que hay en un espacio*/
 Size get_space_set_size(Space *space){
 	if(!space || get_size(space->space_objects)==NO_TAM)
 		return NO_TAM;
 	return get_size(space->space_objects);
 }

Space *world_add_space(World *w, Id id);

/*Devuelve la id de un objeto del set para ese espacio en funcion de un indice*/
Id get_id_from_space_set_index(Space *space, int indice){
	if(!inv || indice<0)
		return NO_ID;
	if(get_i_id(space->space_objects, indice)==NO_ID)
		return NO_ID;
	return get_i_id(space->space_objects, indice);
}

/*Comprueba si el set de objetos para un espacio esta vacio*/
 BOOL is_space_set_empty(Space *space){
 	if(!space)
 		return FALSE;
 	return is_empty(space->space_objects);
 }

/**
 *@name: Id space_get_id(Space *s);
 *@author: Pablo Yus.
 *@brief: devuleve el id de un espacio.
 
 *@param: Space * s: espacio del que se quiere conocer su id.
 
 *@return: el id del espacio o NULL si hay algun errror.
 */
 Id space_get_id(Space *space){
 	if (s == NULL)
 		return NULL

 	return space->id;
 }
