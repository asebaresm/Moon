/**
 *@file test_link.c
 *@brief Pruebas de Link.c
 *@author Albert Soler
 *@version 0.01
 *@date 22-03-2014
 */

#include "Link.h"

int test_create_new_link();
int test2_create_new_link();
int test_destroy_link(Link *link);
int test_link_join_spaces();
int test_link_get_space();
int test_link_is_openable();
int test_link_open();
int test_link_close();
int test_link_ask_linked();

int main(int argc, char** argv) {
    Link *link = NULL;
     
     /*P1*/
    printf("\nPasando prueba 1: ");
    assert(test_create_new_link());
    printf("OK");

     /*P2*/
    printf("\nPasando prueba 2: ");
    assert(test2_create_new_link());
    printf("OK");

     /*P3*/
    printf("\nPasando prueba 3: ");
    assert(test_destroy_link(link));
    printf("OK");

     /*P4*/
    printf("\nPasando prueba 4: ");
    assert(test_link_join_spaces());
    printf("OK");

     /*P5*/
    printf("\nPasando prueba 5: ");
    assert(test_link_get_space());
    printf("OK");

     /*P6*/
    printf("\nPasando prueba 6: ");
    assert(test_link_is_openable());
    printf("OK");

     /*P7*/
    printf("\nPasando prueba 7: ");
    assert(test_link_open());
    printf("OK");

     /*P8*/
    printf("\nPasando prueba 8: ");
    assert(test_link_close());
    printf("OK");

     /*P9*/
    printf("\nPasando prueba 9: ");
    assert(test_link_ask_linked());
    printf("OK\n");

    return (EXIT_SUCCESS);
}

int test_create_new_link() {
    return NULL != create_link(1);
}

int test2_create_new_link() {
    return NULL == create_link(NO_ID);
}

int test_destroy_link(Link *link) {
    destroy_link(link);
    return NULL == link;
}

int test_link_join_spaces() {

    return OK == link_join_spaces(create_link(2), 2, 3);
}

int test_link_get_space() {
    Link *link = NULL;
    link = create_link(2);
    link_join_spaces(link, 2, 3);
    return 3 == link_get_space(link, 2);
}

int test_link_is_openable() {
    Link *link = NULL;
    link = create_link(2);
    link_join_spaces(link, 2, 3);
    return TRUE == link_is_openable(link, TRUE);
}

int test_link_open() {
    Link *link = NULL;
    link = create_link(2);
    link_join_spaces(link, 2, 3);

    return OK == link_open(link);
}

int test_link_close() {
    Link *link = NULL;
    link = create_link(2);
    link_join_spaces(link, 2, 3);

    return OK == link_close(link);
}
int test_link_ask_linked(){
    
        Link *link = NULL;
    link = create_link(2);
    link_join_spaces(link, 2, 3);
    
    return TRUE == link_ask_linked(link);
}
