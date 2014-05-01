#ifndef _TYPE
#define _TYPE
/**
 *@brief tipos de datos comunes
 *@file Types.h
 *@author Albert Soler
 *@version 0.01
 *@date 13-03-2014
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_OBJECT 101  /*!< maximo de objetos*/
#define WORD_SIZE 1024  /*!< maximo de tamanyo de palabra*/
#define NO_TAM -1       /*!< define de errores de tamanyo*/
#define NO_ID -1        /*!< define de errores de ID*/
#define PLAYER_BAG -2   /*!< localizacion de objetos que lleva el player*/
#define U 1             /*!< operando para sizeof*/
#define MAX_SPACES 101  /*!< maximo de espacios de woprld*/
#define MAX_OBJ 101     /*!< maximo de espacios de world*/
#define MAX_LINKS 101   /*!< maximo de links*/
#define LINTERNA 28     /*!<id de linterna*/

typedef unsigned int Size; /** * @brief tipo Size*/
typedef long Id; /** * @brief tipo Id*/

typedef enum {
    FALSE, TRUE
} BOOL; /** * @brief Lista de booleanas */

typedef enum {
    ERROR, OK
} STATUS; /** * @brief Lista de posibles errores */

typedef enum {
    N, S, E, W, UP, DOWN
} DIRECTION;

#endif /* _TYPE */
