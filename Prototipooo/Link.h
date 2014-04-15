
/**
 *@file Link.h
 *@brief TAD que representa una union entre dos espacios
 *@author Albert Soler
 *@version 0.01
 *@date 13-03-2014
 */

#ifndef _LINK
#define _LINK


#include "Types.h"

 /** @brief TAD Link*/

typedef struct _Link Link;

/**
 * @name Link *create_link(Id id);
 * @brief crea un nuevo link
 * @param id
 * @return devuelve el link creado o NULL en caso de error
 */
Link *create_link(Id id);

/**
 * @name void destroy_link(Link *link);
 * @brief destruye un link
 * @param link
 */
void destroy_link(Link *link);

/**
 * @name STATUS link_join_spaces(Link *link, Id space1_id, Id space2_id);
 * @brief se encarga de crear un link entre dos espacios
 * @param link
 * @param space1_id
 * @param space2_id
 * @return OK si ha ido todo bien y ERROR en cualquier otro caso
 */
STATUS link_join_spaces(Link *link, Id space1_id, Id space2_id);

/**
 * @name Id link_get_space(Link *link, int space);
 * @brief devuelve el id de uno de los dos espacios que posee un link
 * @param link
 * @param space
 * @return devuelve el id del esapcio1 o del espacio2, o NO_ID en caso contrario
 */
Id link_get_space(Link *link, int space);

/**
 * @name BOOL link_is_openable(Link *link, BOOL openable);
 * @brief comprueba si el link se puede abrir o no
 * @param link
 * @param openable
 * @return devuelve TRUE si se puede abrir o FALSE en caso contrario
 */
BOOL link_is_openable(Link *link, BOOL openable);

/**
 * @name STATUS link_set_openable(Link *link, BOOL openable);
 * @brief estable el campo openable de un link a el bool que le pasan
 * @param link
 * @param openable
 * @return OK si ha ido todo bien y ERROR en cualquier otro caso
 */
STATUS link_set_openable(Link *link, BOOL openable);

/**
 * @name STATUS link_open(Link *link);
 * @brief hace que un link este abierto
 * @param link
 * @return OK en caso de haya ido todo bien o ERROR en cualquier otro caso
 */
STATUS link_open(Link *link);

/**
 * @name STATUS link_close(Link *link);
 * @brief hace que un link este cerrado
 * @param link
 * @return OK en caso de haya ido todo bien o ERROR en cualquier otro caso
 */
STATUS link_close(Link *link);

/**
 * @name STATUS link_print(Link *link);
 * @brief imprime un link con todos sus campos
 * @param link
 * @return OK en caso de haya ido todo bien o ERROR en cualquier otro caso 
 */
STATUS link_print(Link *link);

/**
 * @name BOOL link_ask_linked(Link *link, Id space1_id, Id space2_id);
 * @brief comprueba si  una union esta unida
 * @param link
 * @param space1_id
 * @param space2_id
 * @return TRUE en caso de unido o FALSE en caso contrario 
 */
BOOL link_ask_linked(Link *link);


/**
 * @name Id link_get_id(Link *link);
 * @brief Devuelve la id de un link
 * @param link
 * @return Id
 */
Id link_get_id(Link *link);
#endif	/* LINK_H */
