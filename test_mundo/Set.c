#include "Set.h"

struct _Set {
    Id v[MAX_SET]; /* elemento del conjunto*/
    int card; /* numero de elementos del conjunto*/
};

/**
 *@name: Set *new_set();
 *@brief: Create a new set of IDs, it returns NULL if not possible.  
 */
Set * new_set() {
    int i;
    Set * set;

    set = (Set*) malloc(U * sizeof (Set));
    set-> card = 0;
    /*se inicializa a 0 todos los elementos por la implementacion elegida*/
    for(i=0;i<MAX_SET;i++)
        set->v[i]=0;
    
    return set;
}

/**
 *@name: void destroy_set(Set *ccj);
 *@brief: Free the allocated resources for the set of IDs, if they were any.

 *@param: ccj allows to set to NULL the pointer to the set after. 
 */
void destroy_set(Set *ccj) {

    if (ccj != NULL) {
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
STATUS add(Set *cj, Id id) {
    
    int i;
    
    if (cj == NULL || id == NO_ID)
        return ERROR;

    if (contains(cj, id) == TRUE)
        return ERROR;

    for(i=0;i<MAX_SET;i++){
        if(cj->v[i]==0){
            cj->v[i]=id;
            cj->card++;
            return OK;
        }
    }
    return ERROR;
}

/**
 *@name:
 *@brief: Given an ID and a Set, it indicates whether the ID is an element of the set.

 *@param: cj is a pointer to a valid set.
 *@param: id is the ID to check.

 *@return: TRUE todo es correcto, cualquier otro caso FALSE.
 */
BOOL contains(Set *cj, Id id) {

    int i;

    if (cj == NULL)
        return FALSE;

    for (i = 0; i < cj->card; i++) {
        if (cj->v[i] == id)
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
STATUS remove_id(Set *cj, Id id){
    int i, j;

    /*encontrar id en el array*/
    for (i = 0; i < cj->card; i++) {
        if (cj->v[i] == id) {
            /*caso 1: la id es la ultima del array*/
            if (i == cj->card - 1) {
                /*ponerlo a NO_ID*/
                cj->v[i] = EMPTY_ID;
                cj->card--;
                return OK;
            }
            /*caso 2: mover todo una posicion*/
            else {
                /*busca el 0 en el array (id sin inicializar)*/
                for (j = 0; cj->v[i]!=EMPTY_ID; j++, i++)
                    cj->v[i] = cj->v[i + 1];
                cj->card--;
                return OK;
            }
        }
    }
    /*id no encontrada*/
    return ERROR;
}

/**
 *@name: Size get_size(Set *cj);  
 *@brief: It returns the current size of the set.

 *@param: cj is a pointer to a valid set. 
 */
Size get_size(Set *cj) {

    if (cj == NULL) {
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
Id get_i_id(Set *cj, int indice) {
    /*puntero NULL || id del objeto menor o igual que 0*/
    if (cj == NULL || cj->v[indice] < 0 || indice> MAX_SET) {
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
BOOL is_empty(Set *cj) {

    if (cj == NULL || cj->card != 0)
        return FALSE;

    if (cj->card == 0)
        return TRUE;
    return FALSE;
}

