/**
 *@brief contiene las pruebas de Set.c
 *@file test_set.c
 *@author Alfonso
 *@version 0.01
 *@date 22-03-2014
 */

#include "Set.h"
#include <assert.h>

int main(int argc, char** argv) {

    Set * s1=NULL;
    /*IDs del set de pruebas*/
    Id id1=1200,id2=1100,id3=1000,id4=900;
    int index=2;
    
    printf("\n>>>Pruebas del modulo Set:");
    
    /*P1*/
    printf("\nPasando prueba 1: ");
    s1 = new_set();
    assert(s1!=NULL);
    printf("OK");
    
    /*P2*/
    printf("\nPasando prueba 2: ");
    assert(add(s1,id1)==OK);
    assert(add(s1,id2)==OK);
    assert(add(s1,id3)==OK);
    assert(add(s1,id4)==OK);
    printf("OK");
    
    /*P3*/
    printf("\nPasando prueba 3: ");
    assert(remove_id(s1, id2)==OK);
    assert(contains(s1, id2)==FALSE);
    printf("OK");
    
    /*P4*/
    printf("\nPasando prueba 4: ");
    /*Comprobamos que funcione para el tamanyo del set de pruebas*/
    assert(get_size(s1)==3);
    printf("OK");
    
    /*P5*/
    printf("\nPasando prueba 5: ");
    /*Comprobamos que funcione para el indice de pruebas*/
    assert(get_i_id(s1, index)==900);
    printf("OK");
    
    /*P6*/
    printf("\nPasando prueba 6: ");
    /*Comprobamos que funcione para el indice de pruebas*/
    assert(remove_id(s1, id1)==OK);
    assert(remove_id(s1, id3)==OK);
    assert(remove_id(s1, id4)==OK);
    assert(is_empty(s1)==TRUE);
    printf("OK");
    
    /*funcion void, liberamos recursos de las pruebas*/
    destroy_set(s1);
    
    printf("\n");
    return (EXIT_SUCCESS);
}

