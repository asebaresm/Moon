/**
 *@brief Implementación de las pruebas de space
 *@file test_space.c
 *@author Albert Soler
 *@version 0.01
 *@date 22-03-2014
 */

#include "Space.h"

int test_create_space();
int test2_create_space();
int test_space_set_description();
int test_space_set_description_inspect();
int test_space_set_light();
int test_space_add_link_north();
int test_space_add_obj();
int test_desc_space();
int test_desc_space_inspect();
int test_space_get_north();
int test_get_space_set_size();
int test_get_id_from_space_set_index();
int test_is_space_set_empty();
int test_is_space_lighted();
int test_space_get_id();
int test_space_get_object();

int main(int argc, char** argv) {


    printf("\n>>>Pruebas del modulo Space:");
    assert(test_create_space());
    assert(test2_create_space());
    assert(test_space_set_description());
    assert(test_space_set_description_inspect());
    assert(test_space_set_light());
    assert(test_space_add_link_north());
    assert(test_space_add_obj());
    assert(test_desc_space());
    assert(test_desc_space_inspect());
    assert(test_space_get_north());
    assert(test_get_space_set_size());
    assert(test_get_id_from_space_set_index());
    assert(test_is_space_set_empty());
    assert(test_is_space_lighted());
    assert(test_space_get_id());
    assert(test_space_get_object());
    printf("\nTodas las pruebas OK\n");

    return (EXIT_SUCCESS);
}

int test_create_space() {
    return NULL == create_space(NO_ID);
}

int test2_create_space() {
    return NULL != create_space(1);
}

int test_space_set_description() {

    return OK == space_set_description(create_space(1), "hohoho");
}

int test_space_set_description_inspect() {
    return OK == space_set_description_inspect(create_space(1), "okokok");
}

int test_space_set_light() {
    return OK == space_set_light(create_space(1), 1);
}

int test_space_add_link_north() {
    return OK == space_add_link_north(create_space(1), 1);
}

int test_space_add_obj() {
    return OK == space_add_obj(create_space(1), 1);
}

int test_desc_space() {
    Space *space;
    space = create_space(1);
    space_set_description(space, "hohoho");
    return (strcmp("hohoho", desc_space(space)) == 0);
}

int test_desc_space_inspect() {
    Space *space;
    space = create_space(1);
    space_set_description_inspect(space, "hohoho");
    return (strcmp("hohoho", desc_space_inspect(space)) == 0);
}

int test_space_get_north() {

    Space *space;
    space = create_space(1);
    space_add_link_north(space, 1);
    return 1 == space_get_north(space);
}

int test_get_space_set_size() {
    Space *space;
    int i;
    space = create_space(1);
    for (i = 0; i < 10; i++)
        space_add_obj(space, i);
    return 10 == get_space_set_size(space);
}

int test_get_id_from_space_set_index() {
    Space *space;
    int i;
    space = create_space(1);
    for (i = 0; i < 10; i++)
        space_add_obj(space, i);
    return 3 == get_id_from_space_set_index(space, 2);
}

int test_is_space_set_empty() {
    Space *space;
    space = create_space(1);
    return TRUE == is_space_set_empty(space);
}

int test_is_space_lighted() {
    Space *space;
    space = create_space(1);
    space_set_light(space, TRUE);
    return TRUE == is_space_lighted(space);
}

int test_space_get_id() {
    Space *space;
    space = create_space(1);
    return 1 == space_get_id(space);
}

int test_space_get_object() {
    Space *space;
    space = create_space(1);
    space_add_obj(space,50);
    return TRUE == space_get_object(space,50);
}
