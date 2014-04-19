/* 
 * File:   main.c
 * Author: Arave
 *
 * Created on 19 de abril de 2014, 5:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 
 */

char *elimina_verbo_accion(const char *txt_ent){
    int i,j,k;
    char c = ' ';
    char *ps;

    if(!txt_ent)
        return NULL;
    ps = (char*)calloc(1,strlen(txt_ent)+1);
    strcpy(ps,txt_ent);
    for(i=0; txt_ent[i]!=' '; i++);
    for(j=0; ps[i]!='\0';i++,j++)
        ps[j]=ps[i];
    k=j-1;
    if (ps[0] == ' ') 
        for (j=0; ps[j]!='\0'; j++)
            ps[j]=ps[j+1];
    ps[k]='\0';
    return ps;
}

int main(int argc, char** argv) {

   char texto[50]="DEJAR GUANTES DEL TRAJE";
   char *preturn=NULL;
   
   preturn = elimina_verbo_accion(texto);
   printf("\nAntes:%s", texto);
   printf("\nDespues:%s", preturn);
   
   free(preturn);
   printf("\n");
    return (EXIT_SUCCESS);
}

