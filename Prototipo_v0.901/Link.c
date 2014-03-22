/**
 *@brief TAD que representa una union entre dos espacios
 *@file union.c
 *@author Albert Soler
 *@version 0.01
 *@date 13-03-2014
 */

/*Tipo opaco de datos*/

#include "Link.h"

typedef struct _Link {
    Id id;
    Id space1;
    Id space2;
    BOOL openable; /* TRUE, if it is a door. FALSE otherwise */
    BOOL close; /* TRUE, if it is closed. FALSE otherwise */
};

/* Functions to create and destroy links */
Link *create_link(Id id) {
    Link *new_link;

    if (id==-1)
        return NULL;
    new_link = (Link*) malloc(sizeof (Link));
    if (!new_link)
        return NULL;
    new_link->id=id;
    return new_link;
}

void destroy_link(Link *link) {
    free(link);
}

/* Functions to create a link between two spaces */

STATUS link_join_spaces(Link *link, Id space1_id, Id space2_id) {

    if (!link || space1_id==-1 || space2_id ==-1)
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
    if ((link->space1 == space) || (link->space2 == space))
        return space;
    return NO_ID;

}

BOOL link_is_openable(Link *link, BOOL openable) {
    if (!link)
        return FALSE;
    if(link->openable == openable)
        return TRUE;
    return FALSE;

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
    if(!link)
        return ERROR;

    printf("\n ID %ld", link->id);
    printf("\n space1 %ld", link->space1);
    printf("\n space2 %ld", link->space2);
    printf("\n openable %d", link->openable);
    printf("\n close %d", link->close);
    return OK;
}

BOOL link_ask_linked(Link *link, Id space1_id, Id space2_id) {
    if (!link)
        return FALSE;
    if ((link->space1 == space1_id) && (link->space2 == space2_id) && (link->openable == TRUE) && (link->close == FALSE))
        return TRUE;
    return FALSE;
}

