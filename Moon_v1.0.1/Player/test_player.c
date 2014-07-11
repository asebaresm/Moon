/**
 *@file test_player.c
 *@brief contiene las pruebas de Player.c
 *@author Alfonso
 *@date 23-03-2014
 *@version 0.01
 */
#include "Player.h"
#include <assert.h>


int main(int argc, char** argv) {
    
    Player * p1=NULL;
    Size max_items=2;
    Id posicion=2900;
    Id objeto1=1100,objeto2=1000,objeto3=900;
    char name[WORD_SIZE]="Jugador1";
    
    
    printf("\n>>>Pruebas del modulo Player:");
    
    /*P1*/
    printf("\nPasando prueba 1: ");
    assert((p1=create_player())!=NULL);
    printf("OK");
    
    /*P2*/
    printf("\nPasando prueba 2: ");
    assert(player_set_name(p1,name)==OK);
    printf("OK");
    
    /*P3*/
    printf("\nPasando prueba 3: ");
    assert(strcmp(name,player_get_name(p1))==0);
    printf("OK");
    
  
    /*P4*/
    printf("\nPasando prueba 4: ");
    assert(player_set_location(p1,posicion)==OK);
    printf("OK");
    
    /*P5*/
    printf("\nPasando prueba 5: ");
    assert(player_set_max_objects(p1, max_items)==OK);
    printf("OK");
    
    /*P6*/
    printf("\nPasando prueba 6: ");
    assert(player_add_obj(p1, objeto1)==OK);
    assert(player_add_obj(p1, objeto2)==OK);
    printf("OK");
    
    /*P7*/
    printf("\nPasando prueba 7: ");
    assert(is_player_inv_full(p1)==TRUE);
    printf("OK");
    
    /*P8*/
    printf("\nPasando prueba 8: ");
    assert(player_add_obj(p1, objeto3)==ERROR);
    printf("OK");
    
    /*P9*/
    printf("\nPasando prueba 9: ");
    assert(player_inv_size(p1)==max_items);
    printf("OK");
    
    /*P10*/
    printf("\nPasando prueba 10: ");
    assert(get_player_inv(p1)!=NULL);
    printf("OK");
    
    /*P11*/
    printf("\nPasando prueba 11: ");
    assert(get_id_from_player_inv_set_index(p1,0)==objeto1);
    printf("OK");
    
    /*liberamos los recursos de las pruebas*/
    destroy_player(p1);
    
    printf("\n");
    return (EXIT_SUCCESS);
}

