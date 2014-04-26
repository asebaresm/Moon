/***************************************************************** 
Name: interface.h 
   
Description: functions that control the interface.
 
Authors: Ana Lopez, Javier Santos, Maria Rojo y Jose Luis Suarez
  
 *****************************************************************/

#include <malloc.h>
#include <memory.h>
#include <termios.h>
#include <time.h>
#include "scwindow.h"
#include "Types.h"

/* 
 * File:   interfaz.h
 * Author: e282455
 *
 * Created on 30 de septiembre de 2013, 18:50
 */

#ifndef INTERFAZ_H
#define	INTERFAZ_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct {
        int n_windows;
        sc_window **windows;
        sc_window *input;
        int scr_r;
        int scr_c;
        char **draw;
    } interface;

    int aleat_num(int inf, int sup);
    
    /*
     Creates the interface
     */
    interface *intrf_create(FILE *f);
    
    /*
     Clears the interface
     */
    int intrf_clear(interface *q, int n);
    
   

    /*The following function only draws the interface, now we need to fill
    it in with windows, so we need the next function*/
    
    /*cx and fx point to the number of the row and column where the
    window begins. Meanwhile, nc and nf, point to the number of rows
    and columns that the window takes*/
    
    /* Window_number points the window where we want to write. R and
    c point the row of the window where the writing begins. Str is the
    string which is goingto be written.*/
    
    STATUS interface_draw(interface *inter, int num_window, char **d, int r, int c);
    
    STATUS interface_draw_in_color(interface *inter, int num_window, char **d, int **bg, int **fg, int r, int c);
    
    STATUS interface_write(interface *inter, int window_number, int r, int c, char * str);
    
    char*  interface_read(interface *inter);
    

    STATUS interface_win_fgcol (interface *inter, int window_number, int color);
    
    STATUS interface_win_bgcol (interface *inter, int window_number, int color);
    


#ifdef	__cplusplus
}
#endif

#endif	/* INTERFAZ_H */

