/* 
 * File:   main.c
 * Author: e279987
 *
 * Created on 24 de abril de 2014, 17:19
 */

#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
#define wi wi: printf(":D "); goto wi;
#define rewii rewii: wi goto rewii;
#define rewiii rewiii: rewii goto rewiii;

/*copiar ori a dest, modificar dest, devolver dest*/

/**
 * @name char * reemplaza_asterisco(char * dst, const char * ori, const char * ins, size_t n);
 * 
 * @brief Sustituye un asterisco en la cadena origen por una nueva cadena que recibe como argumento.
 *
 * @param dst un puntero a la cadena dst que contiene el resultado final tras la modificación.
 * @param ori un puntero a la cadena ori que contiene la cadena de origen antes de cualquier modificación.
 * @param ins un puntero a la nueva cadena que sustituira al asterisco en la cadena origen.
 * @param n es el tamaño máximo que debe tener la cadena de caracteres.
 * 
 * @return dst cadena modificada compuesta por otras dos, tras sustituir el asterisco.
 * 
 */
char *reemplaza_asterisco(char *dst, const char *ori, const char *ins, size_t n) {
    int i, j, k, n_sust, empieza_pa = 0;
    if (!dst || !ori || !ins || n < 0 || strlen(ori)+strlen(ins) > n)
        return NULL;
    strcpy(dst, ori);
    n_sust = strlen(ins);
    /*calcula el indice de cuando empieza a escribir*/
    for (i = 0; ori[i] != '*'; i++) {
        empieza_pa++;
    }
    /*deja hueco para ins*/
    for (j = 0; j < n_sust - 1; j++) {
        for (k = 0; dst[empieza_pa + k] != '\0'; k++) {
            dst[empieza_pa + k + 1 + j] = ori[empieza_pa + k];
        }
    }
    /*empieza a copiar a partir de asterisco en cadena destino*/
    for (i = 0; i < n_sust; i++) {
        dst[empieza_pa + i] = ins[i];
    }
    dst[strlen(dst)]='\0';
    return dst;
}

char * a_mayusculas(char * dst, const char * ori, size_t n) {
    int i;
    if (!dst || !ori || n < 0)
        return NULL;
    strcpy(dst, ori);
    for (i = 0; i < strlen(ori); i++) {
        if (ori[i] >= 97 && ori[i] <= 122 && ori[i] != '\0')
            dst[i] = dst[i] - 32;
    }
    return dst;
}

int clean(char *dst){
    int i,j,R=0;
    for(i=0; dst[i]!='\0';i++){
        if(dst[i]==' '){
            if(dst[i+1]==' '){
                for(j=i+1; dst[j]!='\0'; j++)
                    dst[j] = dst[j+1];
                if(clean(dst) == 1)
                    break;
            }
            if(dst[i-1]==' '){
                for(j=i-1; dst[j]!='\0'; j++)
                    dst[j] = dst[j+1];
                 if(clean(dst) == 1)
                    break;
            }
        }
        if(dst[i]=='\0')
            break;
    }
    R=1;
    return R;
}

char * limpia_espacios(char * dst, const char * ori, size_t n) {
    int i, j;
    if (!dst || !ori || n < 0 || strlen(ori)>n)
        return NULL;
    strcpy(dst, ori);
    for (i = 0; dst[i] == ' '; i++);
    /*1.Quitar espacios principio y final*/
    while (i > 0) {
        for (j = 0; dst[j] != '\0'; j++) {
            dst[j] = dst[j + 1];
        }
        i--;
    }
    for(i=strlen(dst)-1; dst[i]== ' '; i--){
        dst[i]='\0';
    }
    /*2.Espacios de en medio*/
    while(clean(dst)!=1);
    return dst;
}
/*wee:
    for(i=0; dst[i]!='\0';i++){
        if(dst[i]==' '){
            if(dst[i+1]==' '){
                for(j=i+1; dst[j]!='\0'; j++)
                    dst[j] = dst[j+1];
                goto wee;
            }
            if(dst[i-1]==' '){
                for(j=i-1; dst[j]!='\0'; j++)
                    dst[j] = dst[j+1];
                goto wee;
            }
        }
    }*/
    /*2.Quitar espacios enmedio*/

int main(int argc, char** argv) {
    char txt_ent[100] = "TU RECOGES * QUE ESTAN TIRADOS POR EL SUELO";
    char txt_ent2[100] = "pasar a mayusuculas";
    char txt_ent3[100] = "     Esto   es          una     cadena        ";
    char ins[100] = "MUCHOS PALOS";
    char dst[100] = "";
    char *reemplazado;
    size_t size = 10;

    reemplazado = reemplaza_asterisco(dst, txt_ent, ins, size);
    printf("\nOriginal:%s", txt_ent);
    printf("\nInserta:%s", ins);
    printf("\nReemplazado:%s", reemplazado);
    printf("\n\nOriginal:%s", txt_ent2);
    reemplazado = a_mayusculas(dst, txt_ent2, size);
    printf("\nPasado a mayus:%s", reemplazado);
    reemplazado = limpia_espacios(dst, txt_ent3, size);
    printf("\n\nOriginal:%s", txt_ent3);
    printf("\nLimpiados espacios:%s", reemplazado);/*rewiii;*/
    return (EXIT_SUCCESS);
}

