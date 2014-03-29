/**
 *@brief contiene las implementaciones de las funciones de S
 *@file Set.h
 *@author Alfonso
 *@version 0.01
 *@date 24-03-2014
 */



#ifndef _SET
#define _SET

#include "Types.h"

#define MAX_SET 100 /*!< maximo de ids del set*/
#define EMPTY_ID 0  /*!< macro para ID vacia*/

/** @brief Estrucutura Set*/
typedef struct _Set Set;

/**
 *@name: Set *new_set();
 *@brief: Create a new set of IDs.

 *@return: El set que ha sido creado, o NULL en caso de error.  
 */
Set *new_set();

/**
 *@name: void destroy_set(Set *ccj);
 *@brief: Free the allocated resources for the set of IDs, if they were any.

 *@param: ccj allows to set to NULL the pointer to the set after.
 */
void destroy_set(Set *ccj);


/**
 *@name: STATUS add(Set *cj, Id id);
 *@brief: Adds a new ID to the set if it is not already in it.

 *@param: cj is a pointer to a valid set.
 *@param: id is the new ID to add to the set (in case it is not already in it).

 *@return: Returns error if the ID was already in the set.
 */
STATUS add(Set *cj, Id id);

/**
 *@name:
 *@brief: Given an ID and a Set, it indicates whether the ID is an element of the set.

 *@param: cj is a pointer to a valid set.
 *@param: id is the ID to check.

 *@return: TRUE todo es correcto, cualquier otro caso FALSE.
 */
BOOL contains(Set *cj, Id id);

/**
 *@name: STATUS remove(Set *cj, Id id);
 *@brief: Given an ID and a Set it removes the ID from the set.

 *@param: cj is a pointer to a valid set.
 *@param: id is the ID to remove from the set.

 *@return: It returns error if the ID is not an element of the set.
 */
STATUS remove_id(Set *cj, Id id);

/**
 *@name: Size get_size(Set *cj);  
 *@brief: It returns the current size of the set.

 *@param: cj is a pointer to a valid set. 

 *@return: el tamño del conjunto o NULL en caso de error.
 */
Size get_size(Set *cj);

/**
 *@name: Id get_i_id(Set *cj, int indice);
 *@brief: It returns the i-th ID of the set.

 *@param: cj is a pointer to a valid set.
 *@param: index(indice) defines the i-th position.

 *@return: Id del conjunto.
 */
Id get_i_id(Set *cj, int indice);

/**
 *@name: BOOL is_empty(Set *cj); 
 *@brief: Checks wheter the set is empty or not.

 *@param: cj is a pointer to a valid set.
 
 *@return: TRUE todo es correcto, cualquier otro caso FALSE.
 */
BOOL is_empty(Set *cj);

#endif /* _SET */
