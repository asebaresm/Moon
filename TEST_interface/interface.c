/*------------------------------------------------------------------
   Project:  General C utilities
   File:     interfaz.c
   Rev.      1.0
   Date:     Oct. 14, 2012


   Revisions:
   1.0       Oct. 14, 2012


   Implementation of the functions defined in interfaz.h

  -------------------------------------------------------------------
 */

#include "interface.h"


/*For loseItem we need a function that generates a random number to point
  at the item, our hero is going to lose. This functions is the following one.
  It has no much to do it in this .c, but it has much in common with any .c else*/

int aleat_num(int inf, int sup) {
    if (inf > sup || inf < 0)

        return -1;

    return rand() % (sup - inf + 1) + inf;
}


interface *intrf_create(FILE *f) {
    int r, c, i;
    int r1, c1, nr, nc, bg, fg;

    interface *q = (interface *) malloc(sizeof (interface));
    fscanf(f, "%d %d\n", &r, &c);
    q->scr_r = r;
    q->scr_c = c;
    fscanf(f, "%d %d %d %d %d %d\n", &r1, &c1, &nr, &nc, &bg, &fg);
    q->input = win_new(r1, c1, nr, nc, bg, fg);
    fscanf(f, "%d\n", &nr);
    q->n_windows = nr;
    q->windows = (sc_window **) malloc(nr * sizeof (sc_window *));
    for (i = 0; i < q->n_windows; i++) {
        fscanf(f, "%d %d %d %d %d %d\n", &r1, &c1, &nr, &nc, &bg, &fg);
        q->windows[i] = win_new(r1, c1, nr, nc, bg, fg);
    }
    q->draw = (char **) malloc(q->scr_r * sizeof (char *)); /*create the picture*/
    for (i = 0; i < q->scr_r; i++) {
        q->draw[i] = (char *) malloc(q->scr_c+1);
        fgets(q->draw[i], q->scr_c+1, f);
        q->draw[i][strlen(q->draw[i])-1] = 0;
    }

    printf("%c[8;%d;%dt", 27, q->scr_r, q->scr_c); 
    printf("%c[2J", 27); /*print the picture*/
    printf("%c[1;1m", 27);
    for (i = 0; i < q->scr_r; i++) {
        printf("%c[%d;1H", 27, i+1);
        printf("%s", q->draw[i]);
    }
    fflush(stdout);
    return q;
}

int intrf_clear(interface *q, int n) {
    if (n >= q->n_windows) return 0;
    win_cls(q->windows[n]);
    return 1;
}


STATUS interface_draw(interface *inter, int num_window, char **d, int r, int c) {
    
    if (inter==NULL || num_window < 0 || num_window > inter->n_windows || d ==NULL)
        return ERROR;

    if (win_draw(inter->windows[num_window], d, r, c)==ERROR) {        
        return ERROR;        
    }   
    return OK;
}

STATUS interface_draw_in_color(interface *inter, int num_window, char **d, int **bg, int **fg, int r, int c) {
    
    if (inter==NULL || num_window < 0 || num_window > inter->n_windows || d ==NULL)
        return ERROR;

    if (win_draw_in_color(inter->windows[num_window], d, bg, fg, r, c)==ERROR) {        
        return ERROR;        
    }   
    return OK;
}

STATUS interface_write(interface *inter, int window_number, int r, int c, char * str) {

    int length = 0, i = 0;
    char *copia = NULL, *aux = NULL;

    if (!inter || !str)
        return ERROR;
    copia = strdup(str);
    aux = copia;
    length = inter->windows[window_number]->nc - c -2;
    if (r<0) r = last_line(inter->windows[window_number])+1;

    
  /*Comprobamos que la longitud de la cadena es mayor o menor que la que disponemos
   para escribir*/  
    while (strlen(aux) > length) {
  /*Si es mayor la longitud de la cadena, empezamos en la última posición que podríamos
   escribir y recorremos la array de atrás alante hasta que encontremos un espacio en blanco.*/      
        for (i = length; i > 0 && aux[i] != ' '; i--);

/*Cuando encontremos este espacio en blanco cortamos ahi la cadena, y escribimos hasta ahi*/
        aux[i] = '\0'; 
        if (win_write_at(inter->windows[window_number], r, c, aux)== 0)
            return ERROR;
/*Aumentamos la fila, y reasignamos aux como el array que comienza en la siguiente posición donde
 se encontraba el espacio*/        
        r++;
        aux = &(aux[i + 1]);

    }
    if (win_write_at(inter->windows[window_number], r, c, aux)== 0)
        return ERROR;
    free(copia);
    return OK;
}


char* interface_read(interface *inter) {
/*Primero colocamos una flecha para indicar que se escribe en la terminal*/

    char *cmd_buf;
    
    cmd_buf = (char *) malloc(80);
    if(!cmd_buf)
        return NULL;
    win_cls(inter->input);
    fflush(stdout);
    win_write_at(inter->input, 0, 0, "> ");
    fflush(stdout);
    
            
    cmd_buf[0] = '\0';
    
    fgets(cmd_buf, 80, stdin);
    cmd_buf[strlen(cmd_buf)-1] = 0;
    
    return cmd_buf;

}

STATUS interface_win_fgcol (interface *inter, int window_number, int color){
    
    if (!inter || window_number<0 || window_number > inter->n_windows)
        return ERROR;
    
    if(win_fgcol(inter->windows[window_number], color)==ERROR)
        return ERROR;
    
    return OK;
}

STATUS interface_win_bgcol (interface *inter, int window_number, int color){
    
    if (!inter || window_number<0 || window_number > inter->n_windows)
        return ERROR;
    
    if(win_bgcol(inter->windows[window_number], color)==ERROR)
        return ERROR;
    
    return OK;
}
