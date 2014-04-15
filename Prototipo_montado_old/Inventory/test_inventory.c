/* 
 * File:   main.c
 * Author: Arave
 *
 * Created on 23 de marzo de 2014, 1:10
 */

#include "Inventory.h"

/*
 * 
 */
int main(int argc, char** argv) {

    /*variables para las pruebas*/
    Inventory *inv=NULL;
    Id id1=100,id2=110,id3=120,id4=130;
    int indice;
    unsigned int max_objects=10;
   
    
    printf("\n>>>Pruebas del modulo Inventory:");
    
    /*P1*/
    printf("\nPasando prueba 1: ");
    assert((inv = create_inventory())!=NULL);
    printf("OK");
    
    /*P2*/
    printf("\nPasando prueba 2: ");
    assert(inventory_set_max_objects(inv, max_objects)==OK);
    printf("OK");
    
    /*P3*/
    printf("\nPasando prueba 3: ");
    assert(inventory_add_obj(inv, id1)==OK);
    assert(inventory_add_obj(inv, id2)==OK);
    assert(inventory_add_obj(inv, id3)==OK);
    assert(inventory_add_obj(inv, id4)==OK);
    printf("OK");
    
    /*P4*/
    printf("\nPasando prueba 4: ");
    assert(inventory_search_obj(inv, id3)==TRUE);
    printf("OK");
    
    /*P5*/
    printf("\nPasando prueba 5: ");
    assert(inventory_remove_obj(inv, id2));
    printf("OK");
    
    /*P6*/
    printf("\nPasando prueba 6: ");
    assert(get_inventory_set_size(inv)==3);
    printf("OK");
    
    /*P7*/
    printf("\nPasando prueba 7: ");
    indice=0;
    assert(get_id_from_inv_index(inv,indice)==id1);
    printf("OK");
    
    /*P8*/
    printf("\nPasando prueba 8: ");
    assert(get_id_from_inv_obj(inv, id2)==NO_ID);
    printf("OK");
    
    /*liberamos los recursos de las pruebas*/
    destroy_inventory(inv);
    
    printf("\n");
    return (EXIT_SUCCESS);
}

