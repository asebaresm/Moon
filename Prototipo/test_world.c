/* 
 * File:   test_mundo.c
 * Author: Albert
 *
 * Created on 23 de marzo de 2014, 19:54
 */

#include "World.h"

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

    printf("\n>>>Pruebas del modulo World:");

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


    /*liberar recursos utilizados (funcion void)*/
    destroy_world(world);

    printf("\n");
    return (EXIT_SUCCESS);
}

