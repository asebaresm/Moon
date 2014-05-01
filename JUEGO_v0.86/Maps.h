
#include "Types.h"
#include "UtilCadena.h"

#define WORD_MAX 2000
#define SPOT_1 858 /* to 861*/
#define SPOT_2 863 /* to 866*/
#define SPOT_3 868 /* to 871*/
#define SPOT_4 873 /* to 876*/
/**
 * @name STATUS iden_to_spot(char *map, char *iden, int spot);
 * @brief Introduce un identificador (sin formato) en una posicion del mapa
 * @param *map un puntero a la cadena que contiene el mapa.
 * @param *iden un puntero a la cadena con el identificador.
 * @param spot posicion en el mapa donde se insertará.
 * @return Mapa si todo ha ido bien, NULL si error.
 */
char *iden_to_spot(char *map, char *iden, int spot);

/**
 * @name char *get_iden_from_obj_name(const char *obj_name, char *name_lista);
 * @brief Obtiene el identificador de un objeto a partir de su nombre y una lista de objetos
 * @param *obj_name un puntero a la cadena que contiene el nombre del objeto.
 * @param *name_lista un puntero a la cadena con el nombre de la lista con los identificadores.
 * @return puntero al identificador del objeto (sin formato).
 */
char *get_iden_from_obj_name(const char *obj_name, char *name_lista);

/**
 * @name char *format_iden(char *iden);
 * @brief Obtiene el identificador de un objeto a partir de su nombre y una lista de objetos
 * @param *iden un puntero al identificador (sin formato) de un objeto.
 * @return puntero al identificador con formato de un objeto.
 */
char *format_iden(char *iden);

/**
 * @name STATUS add_objeto_map(const char *obj_name, char *map, char *name_lista);
 * @brief Añade un objeto en el mapa a traves de un identificador con formato
 * @param *obj_name un puntero a la cadena que contiene el nombre del objeto
 * @param *map un puntero a la cadena que contiene el mapa.
 * @param *name_lista puntero a la cadena que contiene el nombre de la lista con los identificadores.
 * @return NULL si error/Mapa si todo ha ido bien.
 */
char *add_objeto_map(char *obj_name, char *map, char *name_lista);

/**
 * @name STATUS elimina_objeto_map(char *obj_name, char *map, char *name_lista);
 * @brief Elimina un objeto en el mapa a traves de un identificador con formato
 * @param *obj_name un puntero a la cadena que contiene el nombre del objeto
 * @param *map un puntero a la cadena que contiene el mapa.
 * @param *name_lista puntero a la cadena que contiene el nombre de la lista con los identificadores.
 * @return NULL si error/Mapa si todo ha ido bien.
 */
char *elimina_objeto_map(char *obj_name, char *map, char *name_lista);
