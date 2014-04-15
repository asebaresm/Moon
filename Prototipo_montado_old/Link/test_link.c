/* 
 * File:   test_union.c
 * Author: Albert
 *
 * Created on 22 de marzo de 2014, 18:13
 */


#include "Link.h"

/*
 * 
 */

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

    Link *link;

    assert(test_create_new_link());
    assert(test2_create_new_link());
    assert(test_destroy_link(link));
    assert(test_link_join_spaces());
    assert(test_link_get_space());
    assert(test_link_is_openable());
    assert(test_link_open());
    assert(test_link_close());
    assert(test_link_ask_linked());

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
