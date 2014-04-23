/**
 * @author Pablo Yus. 
 * @file UtilCadena.h
 * @brief Este módulo contiene los prototipos de las funciones de manejo de cadenas de caracteres. 
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UTILCADENA_H
#define	UTILCADENA_H
#define TAM 100

/**
 * @name char * elimina_cars(char * dst, const char * ori, const char * seps, size_t n).
 * 
 * @brief funcion que se encaraga de eliminar ciertos caracteres que en este caso serán: "/,?".
 *
 * @param dst un puntero a la cadena dst que contiene el resultado final tras la modificación.
 * @param ori un puntero a la cadena ori que contiene la cadena de origen antes de cualquier modificación.
 * @param n es el tamaño máximo que debe tener la cadena de caracteres.
 *
 * @return dst con todos los carcteres pasados a mayúsculas.
*/
char * elimina_cars(char * dst, const char * ori, const char * seps, size_t n);

/**
 * @name char * a_mayusculas(char * dst, const char * ori, size_t n);
 * 
 * @brief transforma los caracteres que están en minúsculas a caracteres que están en mayúsculas.
 *
 * @param dst cadena de cracteres que contendrá el resultado de cambiar la cadena origen a mayúsculas.
 * @param ori un puntero a la cadena ori que contiene la cadena de origen antes de cualquier modificación.
 * @param n es el tamaño máximo que debe tener la cadena de caracteres.
 * 
 * @return dst que contiene la cadena en ori pero con todos los caracteres en mayúsculas.
 * 
 */
char * a_mayusculas(char * dst, const char * ori, size_t n);

/**
 * @name char * reemplaza_asterisco(char * dst, const char * ori, const char * ins, size_t n);
 * 
 * @brief Sustituye un asterisco en la cadena origen por una nueva cadena que recibe como argumento.
 *
 * @param dst un puntero a la cadena dst que contiene el resultado final tras la modificación.
 * @param ori un puntero a la cadena ori que contiene la cadena de origen antes de cualquier modificación.
 * @param ins un puntero a la nueva cadena que sustituira al asterisco en la cadena origen.
 * @param n es el tamaño máximo que debe tener la cadena de caracteres.
 * 
 * @return dst cadena modificada compuesta por otras dos, tras sustituir el asterisco.
 * 
 */
char * reemplaza_asterisco(char * dst, const char * ori, const char * ins, size_t n);

/**
 * @name char * limpia_espacios(char * dst, const char * ori, size_t n);
 *
 * @brief limpia los espacios en blanco al principo y al final de la cadena pasada por el usurio.
 *
 * @param dst un puntero a la cadena dst que contiene el resultado final tras la modificación.
 * @param ori un puntero a la cadena ori que contiene la cadena de origen antes de cualquier modificación.
 * @param n es el tamaño máximo que debe tener la cadena de caracteres.
 * 
 * @return dst cadena sin espacios al principo ni al final, es decir la cadena resultante.
 * 
 */
char * limpia_espacios(char * dst, const char * ori, size_t n);    

/**
 * @name char *elimina_verbo_accion(const char *txt_ent); 
 *
 * @brief Crea una segunda cadena eliminandole el primer verbo
 *
 * @param txt_ent testo de entrada
 * 
 * @return char cadena sin primer verbo
 * 
 */
char *elimina_verbo_accion(const char *txt_ent); 

/**
 * @name char *elimina_objeto_map(const char *seps, const char *map); 
 *
 * @brief Elimina la representacion de un objeto del mapa
 *
 * @param seps cadena con los caracteres que pueden representar el objeto
 * 
 * @param map mapa del espacio donde esta el bojeto
 * 
 * @return char cadena sin primer verbo
 * 
 */
char *elimina_objeto_map(const char *seps, const char *map);

#endif	/* UTILCADENA_H */
