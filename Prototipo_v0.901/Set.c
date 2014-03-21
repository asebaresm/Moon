
#include "Set.h"


#ifndef _SET
#define _SET

struct _Set{
    Id v[MAX_SET]; /* elemento del conjunto*/
    int card;      /* numero de elementos del conjunto*/
};

/**
 *@name: Set *new_set();
 *@brief: Create a new set of IDs, it returns NULL if not possible.  
 */
Set * new_set(){
	Set * set;
	
	set = (Set*) malloc (U * sizeof(Set));
	set-> card = 0;
	
	return set;;
}

/**
 *@name: void destroy_set(Set *ccj);
 *@brief: Free the allocated resources for the set of IDs, if they were any.

 *@param: ccj allows to set to NULL the pointer to the set after. 
 */
void destroy_set(Set *ccj){
     
	if(ccj!=NULL){
        ccj->card = 0;
         
        free(ccj);
	}
}


/**
 *@name: 
 *@brief: Adds a new ID to the set if it is not already in it.

 *@param: cj is a pointer to a valid set.
 *@param: id is the new ID to add to the set (in case it is not already in it).

 *@return: Returns error if the ID was already in the set.
 */
STATUS add(Set *cj, Id id){

	if(cj==NULL || id == NO_ID)
		return ERROR;

	if(contains(cj, id) == TRUE)
		return ERROR;
     
	cj->v[cj->card] = id;
	cj->card++;
     
	return TRUE;
}

/**
 *@name:
 *@brief: Given an ID and a Set, it indicates whether the ID is an element of the set.

 *@param: cj is a pointer to a valid set.
 *@param: id is the ID to check.

 *@return: TRUE todo es correcto, cualquier otro caso FALSE.
 */
BOOL contains(Set *cj, Id id){

	int i = 0;

	if(cj == NULL)
		return FALSE;
	
	for(i = 0; i < cj->card; i++){
		if(cj->v[i]==id)
			return TRUE;
	}

	return FALSE;
}

/**
 *@name:
 *@brief: Given an ID and a Set it removes the ID from the set.

 *@param: cj is a pointer to a valid set.
 *@param: id is the ID to remove from the set.

 *@return: It returns error if the ID is not an element of the set.
 */
STATUS remove(Set *cj, Id id){

	int i = 0;
	if(cj == NULL)
		return ERROR;
	
	if(contains(cj, id) == TRUE)
		return ERROR;
			for(;i < cj->card; i++) 
				cj->v[i] = cj->v[i + 1];
			break;

		}
	}
	cj->card --;
	return TRUE;
}

/**
 *@name: Size get_size(Set *cj);  
 *@brief: It returns the current size of the set.

 *@param: cj is a pointer to a valid set. 
 */
Size get_size(Set *cj){
      
	if(cj==NULL){
		return NO_TAM;
	}

	return cj->card;
}

/**
 *@name: Id get_i_id(Set *cj, int indice);
 *@brief: It returns the i-th ID of the set.

 *@param: cj is a pointer to a valid set.
 *@param: index(indice) defines the i-th position.

 *@return: Id.
 */
Id get_i_id(Set *cj, int indice){
	/*puntero NULL || id del objeto menor o igual que 0*/				
	if(cj==NULL || cj->v[indice]<=0){
		return NO_ID;
	}

	return cj->v[indice];
}

/**
 *@name: BOOL is_empty(Set *cj); 
 *@brief: Checks wheter the set is empty or not.

 *@param: cj is a pointer to a valid set.
 
 *@return: TRUE todo es correcto, cualquier otro caso FALSE.
 */
BOOL is_empty(Set *cj){

	if(cj==NULL || cj->card != 0)
		return FALSE;
      
	if (cj->card == 0)
		return TRUE;
}

#endif /* _SET */
