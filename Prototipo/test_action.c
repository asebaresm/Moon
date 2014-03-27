/* 
 * File:   test_action.c
 * Author: pablete
 *
 * Created on 26 de marzo de 2014, 9:44
 */

#include <assert.h>
#include "Action.h"

/*
 * 
 */

/*World *mundo_prueba_espacios() {
    World *w = NULL;
    Space *spa1 = NULL, *spa2 = NULL, *spa3 = NULL, *spa4 = NULL;
    Player *player = NULL;
    Object *obj = NULL;
    Id id1 = 21, id2 = 22, id3 = 23, id4 = 24;
    Link *l1 = NULL, *l2 = NULL, *l3 = NULL;
    Id il1 = 32, il2 = 31, il3 = 30;

    w = create_world();
    if (w == NULL)return NULL;

    spa1 = create_space(id1);
    if (spa1 == NULL)return NULL;
    spa2 = create_space(id2);
    if (spa2 == NULL)return NULL;
    spa3 = create_space(id3);
    if (spa3 == NULL)return NULL;
    spa4 = create_space(id4);
    if (spa4 == NULL)return NULL;

    player = create_player();
    if (player == NULL)return NULL;
    if(player_set_location(player, id1)==ERROR)return NULL;

    l1 = create_link(il1);
    if (l1 == NULL)return NULL;
    l2 = create_link(il2);
    if (l2 == NULL)return NULL;
    l3 = create_link(il3);
    if (l3 == NULL)return NULL;

    if ((link_join_spaces(l1, id1, id2) == ERROR) || (link_join_spaces(l2, id1, id3)) == ERROR ||
            (link_join_spaces(l3, id1, id4)) == ERROR)return NULL;
    
    obj = obj_create();
    if(obj == NULL)return NULL;
    
    
    



}*/

int main(int argc, char** argv) {

    World *world = NULL;
    Space *s1 = NULL, *s2 = NULL, *s3 = NULL, *s4 = NULL;
    Player *p1 = NULL;
    Object *obj1 = NULL, *obj2 = NULL, *obj3 = NULL;
    Id id4 = 1400, id3 = 1300, id2 = 1200, id1 = 1100;


    BOOL light = TRUE;
    char nombre[WORD_SIZE] = "Linterna";
    char desc[WORD_SIZE] = "Linterna sin bateria";
    char return_desc[WORD_SIZE] = "\0";
    int max_len = 0;


    Action *a = NULL;
    Object *obj = NULL;
    Space *spa = NULL;
    Id id11 = 14, id21 = 18;
    char *name = "Pala", *descrip = "Descrito";

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
    assert(obj_set_name(obj3, nombre));
    assert(obj3 == world_get_obj_by_name(world, nombre));
    printf("OK");

    /*P7*/
    printf("\nPasando prueba 7: ");
    assert(space_set_light(world_get_space(world, id1), light) == OK);
    assert(space_add_obj(s1, id1) == OK);
    assert(obj_set_description_inspect(obj1, desc) == OK);
    assert(world_inspect_obj(world, obj1, return_desc, max_len) == OK);
    assert(strcmp(desc, return_desc) == 0);
    printf("OK");



    /*Prueba relacionada con link */
    /*P8*/
    printf("\n Pasando prueba 8.1: ");
    assert(link_join_spaces(world_add_link(world, 1), id1, id2) != ERROR);
    assert(space_add_link_west(s1, 1) == OK);
    assert(space_add_link_east(s2, 1) == OK);
    printf("OK");

    printf("\n Pasando prueba 8.2: ");
    assert(link_join_spaces(world_add_link(world, 2), id2, id3) != ERROR);
    assert(space_add_link_north(s2, 2) == OK);
    assert(space_add_link_south(s3, 2) == OK);
    printf("OK");

    printf("\n Pasando prueba 8.3: ");
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

    if (world != NULL) {
        printf("\nPasando prueba 1:");

        printf("\nAl norte...");
        /*assert((w = create_world()) != NULL);*/
        assert((a = new_action((const char*) "NORTE", (ActionType) A_GO)) != NULL);
        assert((action_execute(world, a)) == OK);
        /*destroy_action(a);*/
        /*assert(a == NULL);*/

        printf("\nAl sur...");
        assert((a = new_action("SUR", A_GO)) != NULL);
        assert((action_execute(world, a)) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/

        printf("\nAl este...");
        assert((a = new_action("ESTE", A_GO)) != NULL);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/

        printf("\nAl oeste...");
        assert((a = new_action("OESTE", A_GO)) != NULL);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/

        printf("\nArriba...");
        assert((a = new_action("ARRIBA", A_GO)) != NULL);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/

        printf("\nAbajo...");
        assert((a = new_action("ABAJO", A_GO)) != NULL);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/
        printf("OK1.");

        printf("\nPasando prueba 2:");

        printf("\nCogiendo objeto...");
        assert((a = new_action("Pala", A_PICK_UP)) != NULL);
        assert((obj = world_add_obj(world, id11)) != NULL);
        assert(obj_set_name(obj, "Pala") == OK);
        assert(obj_set_movable(obj, TRUE) == OK);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/
        printf("OK2.");

        printf("\nPasando prueba 4:");

        printf("\nEncendiendo objeto...");
        assert((a = new_action("Pala", A_TURN_LIGHT_ON)) != NULL);
        assert(obj_set_lightable(obj, TRUE) == OK);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/
        printf("OK4.");

        printf("\nPasando prueba 5:");

        printf("\nApagando objeto...");
        assert((a = new_action("Pala", A_TURN_LIGHT_OFF)) != NULL);
        assert(obj_is_lighted(obj) == TRUE);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/
        printf("OK5.");

        printf("\nPasando prueba 6:");

        printf("\nHablando...");
        assert((a = new_action("Hola", A_SPEAK)) != NULL);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/
        printf("OK6.");

        printf("\nPasando prueba 7a:");

        printf("\nInspeccionando espacio...");
        assert((spa = create_space(id21)) != NULL);
        assert(space_set_description_inspect(spa, descrip) == OK);
        assert((a = new_action("ESPACIO", A_INSPECT)) != NULL);
        destroy_space(spa);
        /*assert(spa = NULL);*/
        destroy_action(a);
        /*assert(a == NULL);*/

        printf("\nPasando prueba 7b:");

        printf("\nInspeccionando objeto...");
        assert((a = new_action("Pala", A_INSPECT)) != NULL);
        assert(obj_set_description_inspect(obj, descrip) == OK);
        obj_destroy(obj);
        /*assert(obj == NULL);*/
        destroy_action(a);
        /*assert(a == NULL);*/
        
        printf("\nPasando prueba 3:");

        printf("\nDejando objeto...");
        assert((a = new_action("Pala", A_DROP)) != NULL);
        assert(obj_set_name(obj, name) == OK);
        assert(obj_set_movable(obj, TRUE) == OK);
        assert(action_execute(world, a) == OK);
        destroy_action(a);
        /*assert(a == NULL);*/
        printf("OK3.");


    } else {
        printf("\nLas pruebas no se han podido pasar!!!!");
    }
    return (EXIT_SUCCESS);
}

