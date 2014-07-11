/**
 *@file test_object.c
 *@brief contiene las pruebas de Object.c
 *@author Alfonso
 *@version 0.01
 *@date 22-03-2014
 */
#include "Object.h"

int main(int argc, char** argv) {
    
    /*variables apra las pruebas:*/
    Object * obj;
    Id id1=1400;
    
    BOOL lighted=TRUE;
    BOOL lightable=TRUE;
    BOOL movable=TRUE;
    
    char descripcion[WORD_SIZE]="Linterna amarilla simple con asa";
    char descripcionMueve[WORD_SIZE]="<descripocion del campo moved>";
    char descripcionInspec[WORD_SIZE]="La linterna no tiene pilas";
    char nombre[WORD_SIZE]="Linterna";
    
    char *return1;
    char *return2;
    char *return3;
    char *return4;
    
   
    printf("\n>>>Pruebas del modulo Object:");
    
    /*P1*/
    printf("\nPasando prueba 1: ");
    obj=obj_create(id1);
    assert(obj!=NULL);
    printf("OK");
    
    /*P2*/
    printf("\nPasando prueba 2: ");
    assert(get_object_id(obj)==id1);
    printf("OK");
    
    /*P3*/
    printf("\nPasando prueba 3: ");
    assert(obj_set_movable (obj,movable)==OK);
    assert(obj_set_lighted (obj,lighted)==OK);
    assert(obj_set_lightable (obj,lightable)==OK);
    printf("OK");
    
    /*P4*/
    printf("\nPasando prueba 4: ");
    assert(obj_is_lightable(obj)==TRUE);
    assert(obj_is_lighted (obj)==TRUE);
    assert(obj_is_lightable (obj)==TRUE);
    printf("OK");
    
    /*P5*/
    printf("\nPasando prueba 5: ");
    assert(obj_set_name(obj,nombre)==OK);
    assert(obj_set_description(obj,descripcion)==OK);
    assert(obj_set_description_moved(obj,descripcionMueve)==OK);
    assert(obj_set_description_inspect(obj,descripcionInspec)==OK);
    printf("OK");
    
    /*P6*/
    printf("\nPasando prueba 6: ");
    return1=obj_get_name(obj);
    return2=obj_get_description(obj);
    return3=obj_get_descInspect(obj);
    return4=obj_get_descMoved(obj);
    
    assert(strcmp(return1,nombre)==0);
    assert(strcmp(return2,descripcion)==0);
    assert(strcmp(return3,descripcionInspec)==0);
    assert(strcmp(return4,descripcionMueve)==0);
    printf("OK");
    
    
    /*P7*/
    printf("\nPasando prueba 7: ");
    assert(obj_print(obj)==OK);
    printf("OK");
    
    /*liberamos recursos de las pruebas*/
    obj_destroy(obj);
    
    printf("\n");
    return (EXIT_SUCCESS);
}
