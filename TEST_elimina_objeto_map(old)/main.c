/* 
 * File:   main.c
 * Author: arave
 *
 * Created on April 23, 2014, 7:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

#define WORD_MAX 2000
#define SPOT_1 846 /* to 849*/
#define SPOT_2 851 /* to 854*/
#define SPOT_3 856 /* to 859*/
#define SPOT_4 861 /* to 864*/


char *elimina_verbo_accion(const char *txt_ent){
    int i,j,k;
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

STATUS elimina_objeto_map(const char *seps, char *map){
    int i,j;
    if(!map || !seps )
        return ERROR;
    for(i=0;i<strlen(map); i++){
        for(j=0; j<strlen(seps); j++){
            if(map[i]==seps[j])
                map[i]=' ';
        }
    }
    return OK;
}

STATUS iden_to_spot(char *map, char *iden, int spot){
    if(!map || !iden)
        return ERROR;
    map[spot]='[';
    map[spot+1]=iden[0];
    map[spot+2]=iden[1];
    map[spot+3]=']';
    return OK;
}

char *get_iden_from_obj_name(const char *obj_name, char *name_lista){
    int i;
    FILE *f=NULL;
    char list[WORD_MAX];
    char *p_found_obj=NULL;
    char *p_found_iden=NULL;
    
    if(!obj_name || !name_lista)
        return NULL;
     f = fopen(name_lista, "r");
    while ((fread(list, 1, sizeof list, f)) > 0);
    if(!(p_found_obj= strstr(list,obj_name))){
        return ERROR;
    }
     if((p_found_iden=(char*)calloc(1,5)) == NULL)
         return NULL;
    for(i=0; i<3; i++){
        p_found_iden[i]=p_found_obj[i+strlen(obj_name)];
    }
    if (p_found_iden[0] == ' ') 
        for (i=0; p_found_iden[i]!='\0'; i++)
            p_found_iden[i]=p_found_iden[i+1];
    fclose(f);
    return p_found_iden;
}

char *format_iden(char *iden){
    int i;
    char cpy[5]="";
    if(!iden)
        return NULL;
    
    for(i=0; i<3; i++){
        cpy[i+1]=iden[i];
    }
    cpy[0]=' ';
    for(i=0; i<4; i++){
        iden[i]=cpy[i];
    }
    iden[0]='[';
    iden[3]=']';
    iden[4]='\0';
    return iden;
}


STATUS add_objeto_map(const char *obj_name, char *map, char *name_lista){
    char *p_found_iden=NULL;
    
    if(!obj_name || !map || !name_lista)
        return ERROR;
    p_found_iden=get_iden_from_obj_name(obj_name, name_lista);
    if(!p_found_iden)
        return ERROR;
    /*colocar en el mapa*/
    if(map[SPOT_1]!= ' '){
        if(map[SPOT_2]!= ' '){
            if(map[SPOT_3]!= ' '){
                if(map[SPOT_4]!= ' '){
                    return ERROR;
                }else{
                    return iden_to_spot(map,p_found_iden,SPOT_4);
                }
            }
            else{
                return iden_to_spot(map,p_found_iden,SPOT_3);
            }
        }else{
            return iden_to_spot(map,p_found_iden,SPOT_2);
        }
    }else{
        return iden_to_spot(map,p_found_iden,SPOT_1);
    }
    return ERROR;
}

int main(int argc, char *argv[]) {
   
   char nombre_fichero_map[WORD_MAX]="";
   char nombre_fichero_lista[WORD_MAX]="";
   /*char seps[WORD_MAX]="()[]*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijkmnlopqrstuvwxyz";*/
   char mapa[WORD_MAX];
   char texto1[50]="DEJAR GUANTES DE TRAJE EVA";
   char texto2[50]="DEJAR DATOS DE PLAN DE VUELO";
   
   char *txt_sin_verbo1=NULL;
   char *txt_sin_verbo2=NULL;
   char *p_iden1=NULL;
   char *p_iden2=NULL;
   FILE *f=NULL;
   size_t nread;
  
   strcpy(nombre_fichero_map, argv[1]);
   f = fopen(nombre_fichero_map, "r");
   while ((nread = fread(mapa, 1, sizeof mapa, f)) > 0);
   fclose(f);
   strcpy(nombre_fichero_lista, argv[2]);
   /*f = fopen(nombre_fichero, "r");*/
   printf("\nstrlen %d",(int)strlen(mapa));
   
   txt_sin_verbo1= elimina_verbo_accion(texto1);
   txt_sin_verbo2= elimina_verbo_accion(texto2);
   
   p_iden1 = get_iden_from_obj_name(txt_sin_verbo1, nombre_fichero_lista);
   p_iden2 = get_iden_from_obj_name(txt_sin_verbo2, nombre_fichero_lista);
   printf("\nAntes texto1:%s", texto1);
   printf("\nAntes texto2:%s", texto2);
   printf("\nAntes mapa:\n%s", mapa);
   printf("\nDespues texto1:%s", txt_sin_verbo1);
   printf("\nDespues texto2:%s", txt_sin_verbo2);
   p_iden1=format_iden(p_iden1);
   p_iden2=format_iden(p_iden2);
   if(elimina_objeto_map(p_iden1,mapa) == ERROR)
       printf("\nERR elimina_objeto_map");
   if(elimina_objeto_map(p_iden2,mapa) == ERROR)
       printf("\nERR elimina_objeto_map");
   printf("\nMapa despues de quitar objetos:\n%s", mapa);
   if(add_objeto_map(txt_sin_verbo1, mapa, nombre_fichero_lista) == ERROR)
       printf("\nERR add_objeto_map");
   if(add_objeto_map(txt_sin_verbo2, mapa, nombre_fichero_lista) == ERROR)
       printf("\nERR add_objeto_map");
   printf("\nMapa despues de anyadir objeto por iden:\n%s",mapa);
   
   free(p_iden2);
   free(p_iden1);
   free(txt_sin_verbo1);
   free(txt_sin_verbo2);
   printf("\n");
    return (EXIT_SUCCESS);
}

