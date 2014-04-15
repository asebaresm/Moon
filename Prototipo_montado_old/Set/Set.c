/**
 *@file Set.c
 *@brief contiene las implementaciones de las funciones de S
 *@author Alfonso
 *@date 24-03-2014
 */

#include "Set.h"

/** * @brief TAD Set*/
struct _Set {
    Id v[MAX_SET]; /* elemento del conjunto*/
    int card; /* numero de elementos del conjunto*/
};

/* Create a new set of IDs, it returns NULL if not possible. */
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

/*Free the allocated resources for the set of IDs, if they were any.*/
void destroy_set(Set *ccj) {

    if (ccj != NULL) {
        ccj->card = 0;

        free(ccj);
        ccj=NULL;
    }
}

/* Adds a new ID to the set if it is not already in it.*/
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

/*Given an ID and a Set, it indicates whether the ID is an element of the set.*/
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

/*Given an ID and a Set it removes the ID from the set.*/
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

/*It returns the current size of the set.*/
Size get_size(Set *cj) {

    if (cj == NULL) {
        return NO_TAM;
    }

    return cj->card;
}

/*It returns the i-th ID of the set.*/
Id get_i_id(Set *cj, int indice) {
    /*puntero NULL || id del objeto menor o igual que 0*/
    if (cj == NULL || cj->v[indice] < 0 || indice> MAX_SET) {
        return NO_ID;
    }

    return cj->v[indice];
}

/*Checks wheter the set is empty or not.*/
BOOL is_empty(Set *cj) {

    if (cj == NULL || cj->card != 0)
        return FALSE;

    if (cj->card == 0)
        return TRUE;
    return FALSE;
}

