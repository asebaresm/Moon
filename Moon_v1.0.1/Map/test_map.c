/**
 *@file test_map.c
 *@brief contiene pruebas de Maps.c
 *@author Alfonso
 *@date 10-05-2014
 *@version 0.1
 */

#include "Maps.h"

int main(int argc, char *argv[]) {
   
   char nombre_fichero_map[WORD_MAX]="Map/MAPA_plantilla.txt";
   char nombre_fichero_lista[WORD_MAX]="Lista_objetos.txt";
   char mapa[WORD_MAX];
   char texto1[50]="GUANTES DE TRAJE EVA";
   char texto2[50]="DATOS DE PLAN DE VUELO";
   
   char *p_iden1=NULL;
   char *p_iden2=NULL;
   FILE *f=NULL;
   size_t nread;
  
   f = fopen(nombre_fichero_map, "r");
   while ((nread = fread(mapa, 1, sizeof mapa, f)) > 0);
   fclose(f);
   printf("\nMap strlen: %d",(int)strlen(mapa));
   
   
   p_iden1 = get_iden_from_obj_name(texto1, nombre_fichero_lista);
   p_iden2 = get_iden_from_obj_name(texto2, nombre_fichero_lista);
   printf("\nTexto original 1: %s", texto1);
   printf("\nTexto original 2: %s", texto2);
   printf("\nMapa original:\n%s", mapa);
   p_iden1=format_iden(p_iden1);
   p_iden2=format_iden(p_iden2);
   printf("\nIdentificador con formato de texto 1: %s", p_iden1);
   printf("\nIdentificador con formato de texto 2: %s", p_iden2);
   if(elimina_objeto_map(texto1,mapa,nombre_fichero_lista) == ERROR)
       printf("\nERR elimina_objeto_map");
   if(elimina_objeto_map(texto2,mapa,nombre_fichero_lista) == ERROR)
       printf("\nERR elimina_objeto_map");
   printf("\nMapa despues de quitar objetos:\n%s", mapa);
   if(add_objeto_map(texto1, mapa, nombre_fichero_lista) == ERROR)
       printf("\nERR add_objeto_map");
   if(add_objeto_map(texto2, mapa, nombre_fichero_lista) == ERROR)
       printf("\nERR add_objeto_map");
   printf("\nMapa despues de anyadir objeto por iden:\n%s",mapa);
   
   free(p_iden2);
   free(p_iden1);
   printf("\n");
    return (EXIT_SUCCESS);
}