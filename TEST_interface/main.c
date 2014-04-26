/* 
 * File:   main.c
 * Author: arave
 *
 * Created on April 25, 2014, 6:59 PM
 */

#include "Types.h"
#include "interface.h"
#include "scwindow.h"
/*
 * 
 */
int main(int argc, char** argv) {

    FILE *f = NULL;
    char* buf = (char*) malloc(50 * sizeof(char)); 
    interface * inter = NULL;
    
    /*We create the interface*/
    f = fopen("dimensions.txt", "r");
    if (f == NULL) {
        return (EXIT_FAILURE);
    }
    inter = intrf_create(f);
    if (inter == NULL) {
        return (EXIT_FAILURE);
    }
   
   interface_write(inter, 0, 5, 3, "What do you want to do?");
   interface_write(inter, 0, 6, 3, "Type LOAD to load an old game.");
   interface_write(inter, 0, 7, 3, "Type NEW to start a new game,");
   interface_write(inter, 0, 1, 3, "There's no previous game.");
   buf=interface_read(inter);
   
   fclose(f);
   free(buf);
   return (EXIT_SUCCESS);
}

