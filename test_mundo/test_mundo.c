/* 
 * File:   test_mundo.c
 * Author: Albert
 *
 * Created on 23 de marzo de 2014, 19:54
 */

#include "World.h"


int main(int argc, char** argv) {
    
    World *world;
    
    printf("\n>>>Pruebas del modulo Player:");
    
    /*P1*/
    printf("\nPasando prueba 1: ");
    assert((world=create_world())!=NULL);
    printf("OK");
    
    
    /*P2*/
    printf("\nPasando prueba 2: ");
    assert();
    printf("OK");
    
    printf("\n");
    return (EXIT_SUCCESS);
}

