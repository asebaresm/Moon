/**
 *@brief TAD que representa una union entre dos espacios
 *@file link.c
 *@author Albert Soler
 *@version 0.01
 *@date 13-03-2014
 */


#include "Link.h"

/** * @brief TAD Link*/
struct _Link {
    Id id;
    Id space1;
    Id space2;
    BOOL openable; /* TRUE, if it is a door. FALSE otherwise */
    BOOL close; /* TRUE, if it is closed. FALSE otherwise */
};

/* @brief Functions to create and destroy links */
Link *create_link(Id id) {
    Link *new_link;

    if (id == -1)
        return NULL;
    new_link = (Link*) malloc(sizeof (Link));
    if (!new_link)
        return NULL;
    new_link->id = id;
    new_link->openable = FALSE;
    new_link->close= FALSE;
    return new_link;
}

/* * @brief destruye un link*/
void destroy_link(Link *link) {
    free(link);
}

/* * @brief Functions to create a link between two spaces */
STATUS link_join_spaces(Link *link, Id space1_id, Id space2_id) {

    if (!link || space1_id == -1 || space2_id == -1)
        return ERROR;
    link->space1 = space1_id;
    link->space2 = space2_id;
    link->openable = TRUE;
    return OK;


}

/* Functions to access the fields of a link */
Id link_get_space(Link *link, int space) {
    if (!link)
        return NO_ID;
    if (link->space1 == space)
        return link->space2;
    if (link->space2 == space)
        return link->space1;
    return NO_ID;

}

/* Comprueba si un link se puede abrir*/
BOOL link_is_openable(Link *link, BOOL openable) {
    if (!link)
        return FALSE;
    if (link->openable == openable)
        return TRUE;
    return FALSE;

}

/* Establace el valor boolean a openable*/
STATUS link_set_openable(Link *link, BOOL openable) {
    if (!link)
        return ERROR;
    link->openable = openable;
    return OK;
}

/* Functions to update a link */
STATUS link_open(Link *link) {
    if (!link)
        return ERROR;
    if (link->openable == FALSE)
        return ERROR;
    link->close = FALSE;
    return OK;
}

/* Cierra un link*/
STATUS link_close(Link *link) {
    if (!link)
        return ERROR;
    if (link->openable == FALSE)
        return ERROR;
    link->close = TRUE;
    return OK;


}

/* Print a link. This function is included for debugging purposes */
STATUS link_print(Link *link) {
    if (!link)
        return ERROR;

    printf("\n ID %ld", link->id);
    printf("\n space1 %ld", link->space1);
    printf("\n space2 %ld", link->space2);
    printf("\n openable %d", link->openable);
    printf("\n close %d", link->close);
    return OK;
}

/* Comprueba si un link esta unido*/
BOOL link_ask_linked(Link *link) {
    if (!link)
        return FALSE;
    if ((link->openable == TRUE) && (link->close == FALSE))
        return TRUE;
    return FALSE;
}

/*Devuelve la id de un link*/
Id link_get_id(Link *link) {
    if (!link)
        return NO_ID;
    return link->id;

}
