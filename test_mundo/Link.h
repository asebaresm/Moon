/* 
 * File:   Link.h
 * Author: Albert
 *
 * Created on 22 de marzo de 2014, 18:14
 */

#ifndef LINK_H
#define	LINK_H

/**
*@brief TAD que representa una union entre dos espacios
*@file union.h
*@author Albert Soler
*@version 0.01
*@date 13-03-2014
*/

#include "Types.h"

typedef struct _Link Link;

/* Functions to create and destroy links */
Link *create_link(Id id); void destroy_link(Link *link);
/* Functions to create a link between two spaces */ 
STATUS link_join_spaces(Link *link, Id space1_id, Id space2_id);
/* Functions to access the fields of a link */
 Id link_get_space(Link *link, int space); 
 BOOL link_is_openable (Link *link, BOOL openable);
/* Functions to update a link */ 
 STATUS link_open(Link *link); STATUS link_close(Link *link);
 /* Print a link. This function is included for debugging purposes */
  STATUS link_print (Link *link);
  
  BOOL link_ask_linked(Link *link, Id space1_id, Id space2_id);

#endif	/* LINK_H */

