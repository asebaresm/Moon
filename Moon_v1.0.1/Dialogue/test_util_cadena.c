 /**
 * @author Pablo Yus. 
 * @file test_util_cadena.c
 * @brief Este módulo contiene las pruebas de UtilCadena.c
 * @version 0.1 
 * @date 24-04-2014 
 */
#include <assert.h>
#include "UtilCadena.h"

#define MCARS 100  /**!Tamaño de palabra*/
int main(int argc, char** argv) {
    char seps[]="!%&/()=?¿";
    char txt_ent[MCARS] = "RECOGES * QUE ESTAN TIRADOS POR EL SUELO";
    char txt_ent2[MCARS] = "pasar a mayusculas";
    char txt_ent3[MCARS] = "     Esto   es          una     cadena        0";
    char txt_ent4[MCARS] = "¿Eliminar caracteres? (no deseados!!)";
    char txt_ent5[MCARS] = "DEJAR PALA";
    char ins[MCARS] = "MUCHOS PALOS";
    char dst[MCARS] = "";
    char *reemplazado = NULL;
    size_t size = 100;
    
    printf(">>>Pruebas de util cadena:");
    printf("\nPasando prueba 1:");
    reemplazado = reemplaza_asterisco(dst, txt_ent, ins, size);
    assert(reemplazado);
    printf("\nOriginal:%s", txt_ent);
    printf("\nInserta:%s", ins);
    printf("\nReemplazado:%s\n", reemplazado);
    assert(strcmp(reemplazado,"RECOGES MUCHOS PALOS QUE ESTAN TIRADOS POR EL SUELO")==0);
    printf("OK");
    
    printf("\n\nPasando prueba 2:");
    printf("\nOriginal:%s", txt_ent2);
    reemplazado = NULL;
    reemplazado = a_mayusculas(dst, txt_ent2, size);
    assert(reemplazado);
    assert(strcmp(reemplazado,"PASAR A MAYUSCULAS")==0);
    printf("\nPasado a mayus:%s", reemplazado);
    printf("\nOK");
    
    printf("\n\nPasando prueba 3:");
    reemplazado = NULL;
    reemplazado = limpia_espacios(dst, txt_ent3, size);
    assert(reemplazado);
    assert(strcmp(reemplazado,"Esto es una cadena 0")==0);
    printf("\nOriginal:%s", txt_ent3);
    printf("\nLimpiados espacios:%s", reemplazado);
    printf("\nOK\n");
    
    printf("\n\nPasando prueba 4:");
    reemplazado = NULL;
    reemplazado = elimina_cars(dst,txt_ent4,seps,size);
    assert(reemplazado);
    assert(strcmp(reemplazado,"  Eliminar caracteres   no deseados   ")==0);
    printf("\nOriginal:%s", txt_ent4);
    printf("\nLimpiados espacios:%s", reemplazado);
    printf("\nOK\n");
    
    printf("\n\nPasando prueba 5:");
    reemplazado = NULL;
    reemplazado = elimina_verbo_accion(dst,txt_ent5);
    assert(reemplazado);
    assert(strcmp(reemplazado,"PALA")==0);
    printf("\nOriginal:%s", txt_ent5);
    printf("\nLimpiados espacios:%s", reemplazado);
    printf("\nOK\n");
    return (EXIT_SUCCESS);
}

