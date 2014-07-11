/**
 *@file test_action.c
 *@brief contiene las implementaciones de las pruebas de Action.c
 *@author Pablo Yus
 *@version 1.0
 *@date 26-03-2014
 */
#include <assert.h>
#include "Action.h"



int main(int argc, char** argv) {

    /*Variables utilizadas en el mundo de pruebas*/
    World *world = NULL;
    Space *s1 = NULL, *s2 = NULL, *s3 = NULL, *s4 = NULL;
    Player *p1 = NULL;
    Object *obj1 = NULL, *obj2 = NULL, *obj3 = NULL;
    Id id4 = 1400, id3 = 1300, id2 = 1200, id1 = 1100;


    BOOL light = TRUE;
    char nombre[WORD_SIZE] = "Linterna";
    char nombre3[WORD_SIZE]="Destornillador";
    char desc[WORD_SIZE] = "Linterna sin bateria";
    char desc_grafica[WORD_SIZE]="*Imagen ASCII del objeto*";
    char return_desc[WORD_SIZE] = "";
    int max_len = 0;


    /*Variables propias de las pruebas de Action*/
    Action *a = NULL;
    Object *obj = NULL;

    Id id11 = 14;
    char nombre2[WORD_SIZE] = "PALA";
    char nombre4[WORD_SIZE]="LLAVE";
    char desc2[WORD_SIZE] = "Descripcion de inspeccion";
    
    char do_act[WORD_SIZE]="";
    /*P1*/
    printf("\nPasando prueba 1: ");
    assert((world = create_world()) != NULL);
    printf("OK");


    /*P2*/
    printf("\nPasando prueba 2: ");
    assert((s1 = world_add_space(world, id1)) != NULL);
    assert((s2 = world_add_space(world, id2)) != NULL);
    assert((s3 = world_add_space(world, id3)) != NULL);
    assert((s4 = world_add_space(world, id4)) != NULL);
    printf("OK");

    /*P3*/
    printf("\nPasando prueba 3: ");
    assert((obj1 = world_add_obj(world, id1)) != NULL);
    assert((obj2 = world_add_obj(world, id2)) != NULL);
    assert((obj3 = world_add_obj(world, id3)) != NULL);
    printf("OK");

    /*P4*/
    printf("\nPasando prueba 4: ");
    assert((p1 = world_set_player(world)) != NULL);
    assert(set_player_location(world, id1) == OK);
    printf("OK");

    /*P5*/
    printf("\nPasando prueba 5: ");
    assert(s1 == world_get_space(world, id1));
    assert(obj2 == world_get_obj(world, id2));
    printf("OK");

    /*P6*/
    printf("\nPasando prueba 6: ");
    /*assert(obj_set_name(obj, nombre4) == OK);*/
    assert(obj_set_name(obj1, nombre2));
    assert(obj_set_name(obj2, nombre3));
    assert(obj_set_name(obj3, nombre));
    assert(obj3 == world_get_obj_by_name(world, nombre));
    printf("OK");

    /*P7*/
    printf("\nPasando prueba 7: ");
    assert(space_set_light(world_get_space(world, id1), light) == OK);
    assert(space_add_obj(s1, id1) == OK);
    assert(obj_set_description_inspect(obj1, desc) == OK);
    assert(obj_set_description_graphical(obj1,desc_grafica)==OK);
    assert(world_inspect_obj(world, obj1, return_desc, max_len) == OK);
    assert(strcmp(desc, return_desc) == 0);
    printf("OK");



    /*Pruebas relacionadas con link */
    /*P8*/
    printf("\nPasando prueba 8.1: ");
    assert(link_join_spaces(world_add_link(world, 1), id1, id2) != ERROR);
    assert(space_add_link_west(s1, 1) == OK);
    assert(space_add_link_east(s2, 1) == OK);
    printf("OK");

    printf("\nPasando prueba 8.2: ");
    assert(link_join_spaces(world_add_link(world, 2), id2, id3) != ERROR);
    assert(space_add_link_north(s2, 2) == OK);
    assert(space_add_link_south(s3, 2) == OK);
    printf("OK");

    printf("\nPasando prueba 8.3: ");
    assert(link_join_spaces(world_add_link(world, 3), id3, id4) != ERROR);
    assert(space_add_link_down(s3, 3) == OK);
    assert(space_add_link_up(s4, 3) == OK);
    printf("OK");

    /*Pruebas de mover player*/
    /*P9*/
    printf("\nPasando prueba 9: ");
    assert(world_move_player(world, W) == OK);
    assert(world_move_player(world, N) == OK);
    assert(world_move_player(world, DOWN) == OK);
    assert(world_move_player(world, UP) == OK);
    assert(world_move_player(world, S) == OK);
    assert(world_move_player(world, E) == OK);
    printf("OK");



    printf("\n>>>Pruebas del modulo Action:");

    printf("\n\tPasando prueba 1:");

    printf("\n\tAl oeste...");
    strcpy(do_act,"OESTE");
    assert((a = new_action(do_act, A_GO)) != NULL);
    assert(action_execute(world, a) == OK);
    
    
    printf("\n\tAl norte...");
    strcpy(do_act,"NORTE");
    assert((set_action(a, do_act, A_GO))==OK);
    assert((action_execute(world, a)) == OK);

    
    printf("\n\tAbajo...");
    strcpy(do_act,"ABAJO");
    assert((set_action(a, do_act, A_GO))==OK);
    assert(action_execute(world, a) == OK);
    
    
    printf("\n\tArriba...");
    strcpy(do_act, "ARRIBA");
    assert((set_action(a, do_act, A_GO))==OK);
    assert(action_execute(world, a) == OK);
    
    
    printf("\n\tAl sur...");
    strcpy(do_act,"SUR");
    assert((set_action(a, do_act, A_GO))==OK);
    assert((action_execute(world, a)) == OK);


    printf("\n\tAl este...");
    strcpy(do_act,"ESTE");
    assert((set_action(a, do_act, A_GO))==OK);
    assert(action_execute(world, a) == OK);


    printf("\n\tPasando prueba 2:");
    printf("\n\tCogiendo objeto...");
    assert((set_action(a, nombre4, A_PICK_UP))==OK);
    assert((obj = world_add_obj(world, id11)) != NULL);
    assert(obj_set_movable(obj, TRUE) == OK);
    assert(obj_set_name(obj,nombre4)==OK);
    assert(space_add_obj(s1,id11));
    assert(action_execute(world, a) == OK);


    printf("\n\tPasando prueba 4:");
    printf("\n\tEncendiendo objeto...");
    assert((set_action(a, nombre4, A_TURN_LIGHT_ON))==OK);
    assert(obj_set_lightable(obj, TRUE) == OK);
    assert(action_execute(world, a) == OK);


    printf("\n\tPasando prueba 5:");
    printf("\n\tApagando objeto...");
    assert((set_action(a, nombre4, A_TURN_LIGHT_OFF))==OK);
    assert(obj_is_lighted(obj) == TRUE);
    assert(action_execute(world, a) == OK);


    printf("\n\tPasando prueba 6:");
    printf("\n\tHablando...");
    strcpy(do_act,"Hola");
    assert((set_action(a, do_act, A_SPEAK))==OK);
    assert(action_execute(world, a) == OK);


    printf("\n\tPasando prueba 7:");
    printf("\n\tInspeccionando espacio...");
    assert(space_set_description_inspect(s4, desc2) == OK);
    strcpy(do_act,"SPACE");
    assert((set_action(a, do_act, A_INSPECT))==OK);
    assert(action_execute(world, a) == OK);


    printf("\n\tPasando prueba 8:");
    printf("\n\tInspeccionando objeto...");
    assert((set_action(a, nombre2, A_INSPECT))==OK);
    assert(obj_set_description_inspect(obj, desc2) == OK);
    assert(action_execute(world,a) == OK);
    

    printf("\n\tPasando prueba 9:");
    printf("\n\tDejando objeto...");
    assert((set_action(a, nombre4, A_DROP))==OK);
    assert(action_execute(world, a) == OK);
    printf("\n>>>Pruebas del modulo Action: OK\n");

    /*free de recursos de las pruebas:*/
    destroy_action(a);
    destroy_world(world);
    
    return (EXIT_SUCCESS);
    
}

