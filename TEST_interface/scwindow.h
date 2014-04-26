#include "Types.h"
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------
   Project:  General C utilities
   File:     scwindow.h
   Rev.      1.0
   Date:     Sept. 22, 2011


   Revisions:
   1.0       Sept. 22, 2011

   (C) Simone Santini, 2011

   This file defines the functions that form a library to manage 
   vitual windows on a character screen. The window is not marked in any
   way on the screen (marking it out, if necessary, is a purpose of the 
   calling program), but allows the user to position the cursor and print
   inside a window (almost) as if it were an independent screen. 

   In the examples that preceed the functions, we assume that we have
   a screen with 10 rows and 40 columns and in it we open a "window"
   of 5 rows and 15 column beginning at position 2, 19. The situation
   is therefore this:

   0                                        39
    +----------------------------------------+
  0 |                                        |
    |                   +---------------+    |
    |                   |               |    |
    |                   |               |    |
    |                   |               |    |
    |                   |               |    |
    |                   |               |    |
    |                   +---------------+    |
    |                                        |
   9|                                        |
    +----------------------------------------+

    Of course, the library doesn't mark the window on the screen, and
    in order to remark this fact, we shall write down the screen as:

                       19             33
     0                  v             v    39
    +----------------------------------------+
  0 |                                        |
    |                                        |
    |                                        | < 2
    |                                        | 
    |                                        |
    |                                        |
    |                                        | < 6
    |                                        | 
    |                                        |
   9|                                        |
    +----------------------------------------+


    NOTE:
    These functions are implemented using ASCII ESC codes for the control
    of the cursor. This might produce some incompatibility problem with 
    Windows and MS/DOS systems.

    Note also that the ESC code consider that the cursor coordinates
    begin with 1 (1, 1 is the position of the top left character of
    the screen). However, following the standard computing convention,
    this library will consider that the coordinates begin with 0. So,
    (0,0) are the coordinates of the top-left-most character in the
    screen and for a screen of size, say 40x80, the bottom-right
    character has coordinates (39,79).

  -------------------------------------------------------------------
*/

#ifndef ____SC_WINDOW___INCLUDED___
#define ____SC_WINDOW___INCLUDED___


/*

  This is the structure used to store the information about a window:
  this is the structure returned by the function that creates a new
  window, and must be passed as a parameter to all functions that
  write in the window.
*/
typedef struct {
  int  c1;     /* column on the screen where the window begins */
  int  r1;     /* row on the screen where the window begins */
  int  nr;     /* number of rows in the window  */
  int  nc;     /* number of column in the window  */

  int  crs_r;  /* last position of the cursor in this window */
  int  crs_c;  /* last position of the cursor in this window */

  int  last_line;
  int  bg_color; /* the background color for this window */
  int  fg_color; /* the foreground color for this window */
  int  ch_effect; /* the character effect for this window */
} sc_window;


void _move_to(sc_window *sc, int r, int c);

int last_line(sc_window *sc);

/*
  Creates a window on the screen. 
  Parameters:
     r1, c2: row and column where the window begins;
     nr, nc: number of rows and columns of the window.

  Returns:
    a pointer to a newly allocated sc_window structure with the 
    information for the window.

  Note that this function will do absolutely nothing on the screen
  itself. In particular, it will NOT clear the window. This function
  will simply create the structure, initialize its fields, and return
  it.
*/
sc_window *win_new(int r1, int c1, int nr, int nc, int bg, int fg);


/*
  Clears a window, leaving it all in the current background color

  Parameters:
      sc: the window structure on which the function operates.

  Returns:
      nothing.
*/

STATUS win_draw(sc_window *sc, char **d, int r, int c);

STATUS win_draw_in_color(sc_window *sc, char **d, int **bg, int **fg, int r, int c);

void win_cls(sc_window *sc);

/*
  Releases the structure allocated for a window. After calling this
  function it is no longer possible to use the window.

  This function doesn't erase the window contents from the screen.

  Parameters:
      sc: the window structure on which the function operates.

  Returns:
      nothing.
*/
void win_delete(sc_window *sc);

/*
  Sets the background color for the window

  Parameters:
      sc:  the window structure on which the function operates.
      col: the new background color;

  Returns:
      1: regular execution
      0: incorrect color parameter
*/
STATUS win_bgcol(sc_window *sc, int col);


/*
  Sets the foreground color for the window

  Parameters:
      sc:  the window structure on which the function operates.
      col: the new foreground color;

  Returns:
      1: regular execution
      0: incorrect color parameter
*/
STATUS win_fgcol(sc_window *sc, int col);


/*
  This function writes a string in a single line starting at a given
  position of the window, and without changing line. Each new line
  character contained in the string will be considered as a string
  termination, and if the string is too long to fit in the screen, it
  will be truncated. 

  So, if on the screen of the example we execute the functions:

  win_write_line_at(sc, 1, 7, "en un lugar de la mancha");
  win_write_line_at(sc, 3, 5, "oh!\nI didn't know");
 

  we get:

                       19             33
     0                  v             v    39
    +----------------------------------------+
  0 |                                        |
    |                                        |
    |                          en un lu      | < 2
    |                                        | 
    |                        oh!             |
    |                                        |
    |                                        | < 6
    |                                        | 
    |                                        |
   9|                                        |
    +----------------------------------------+

    Parameters:
      sc:  the window structure on which the function operates.
      r:   the row of the window at which the writing begins
      c:   the column of the window at which the writing begins
      str: the screen that we must write

    Returns:
      the number of characters actually written on the screen.

*/
int win_write_line_at(sc_window *sc, int r, int c, char *str);

/*
  This function writes a string on multiple, left-aligned lines
  starting at a given position of the window. Each new line character
  contained in the string will cause a new line to be started aligned
  with the first position of the string. If a line is too long to fit
  in the screen, it will be truncated. If there are more lines than
  fit the window, the non-fitting lines will be ignored.


  So, if on the screen of the example we execute the functions:

  win_write_at(sc, 1, 7, "en un lugar de la mancha");
  win_write_at(sc, 3, 5, "oh!\nI didn't know that.\nNot quite\nNot really");
 

  we get:

                       19             33
     0                  v             v    39
    +----------------------------------------+
  0 |                                        |
    |                                        |
    |                          en un lu      | < 2
    |                                        | 
    |                        oh!             |
    |                        I didn't k      |
    |                        Not quite       | < 6
    |                                        | 
    |                                        |
   9|                                        |
    +----------------------------------------+

    Parameters:
      sc:  the window structure on which the function operates.
      r:   the row of the window at which the writing begins
      c:   the column of the window at which the writing begins
      str: the screen that we must write

    Returns:
      The number of characters actually written on the screen.

*/
int win_write_at(sc_window *sc, int r, int c, char *str);



#endif
