/* 
 * File:   main.c
 * Author: arave
 *
 * Created on April 23, 2014, 7:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD_MAX 2000

char *elimina_objeto_map(const char *seps, const char *map){
    int i,j;
    char *pmap=NULL;
    if(!map || !seps || !(pmap=(char*)calloc(1,strlen(map)+1)))
        return NULL;
    strcpy(pmap,map);
    for(i=0;i<strlen(map); i++){
        for(j=0; j<strlen(seps); j++){
            if(pmap[i]==seps[j])
                pmap[i]=' ';
        }
    }
    return pmap;
}

int main(int argc, char** argv) {

   char nombre_fichero[WORD_MAX]="";
   char seps[WORD_MAX]="()[]*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkmnlopqrstuvwxyz";
   char mapa[WORD_MAX];
   char *preturn=NULL;
   FILE *f=NULL;
   size_t nread;
   
   strcpy(nombre_fichero, argv[1]);
   f = fopen(nombre_fichero, "r");
   while ((nread = fread(mapa, 1, sizeof mapa, f)) > 0);
   fclose(f);
   printf("\nstrlen %d",(int)strlen(mapa));
   preturn = elimina_objeto_map(seps,mapa);
   printf("\nAntes:\n%s", mapa);
   printf("\nDespues:\n%s", preturn);
   
   free(preturn);
   printf("\n");
    return (EXIT_SUCCESS);
}

