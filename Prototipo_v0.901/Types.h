#ifndef _TYPE
#define _TYPE
/**
*@brief tipos de datos comunes
*@file union.h
*@author Albert Soler
*@version 0.01
*@date 13-03-2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MAX_OBJECT 100/*annadida*/
#define WORD_SIZE 50/*annadida*/
#define NO_TAM -1
#define NO_ID -1
#define U 1/*annadida*/


typedef unsigned int Size;
typedef long Id;
typedef enum {FALSE, TRUE} BOOL;
typedef enum {ERROR, OK} STATUS;
typedef enum {N, S, E, W, UP, DOWN} DIRECTION;

#endif /* _TYPE */
