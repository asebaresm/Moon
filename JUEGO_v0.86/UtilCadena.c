/**
 * @author Pablo Yus. 
 * @file UtilCadena.c
 * @brief Este módulo contiene las implementaciones de las funciones de manejo de cadenas de caracteres. 
 */


#include "UtilCadena.h"

char * elimina_cars(char * dst, const char * ori, const char *seps, size_t n) {
    int i = 0, j = 0, flag = 0;

    if (ori == NULL || seps == NULL || dst == NULL || n < 0)
        return NULL;

    for (i = 0; ori[i] != '\0'; i++) { /*Contamos el numero de chars que tiene nuestra cadena de origen hasta el '\0' sin incluirlo*/
        flag++;
    }

    if (flag > n)
        return NULL;

    strcpy(dst, ori); /*Copiamos la cadena origen en la de destino*/
    if (dst == NULL)
        return NULL;

    /*Recorremos tanto la cadena origen como la cadena seps en busca de algun caracter "invalido"*/
    for (i = 0; ori[i] != '\0'; i++) {
        for (j = 0; seps[j] != '\0'; j++) {
            if (ori[i] == seps[j])
                dst[i] = ' '; /*Si encontramos un caracter invalido lo sustituimos por un espacio*/
        }
    }
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

char *reemplaza_asterisco(char *dst, const char *ori, const char *ins, size_t n) {

    char *ptr = NULL; /*Strtok*/
    char hope [MAX] = {'\0'};
    char *nohope = NULL;
    char *pch = NULL;
    char c = '*';
    if (!ori || !ins || n < 0 || strlen(ori) + strlen(ins) > n)
        return NULL;
    strcpy(dst, ori);
    /*Comprobacion no asterisco*/
    if ((pch = strchr(dst, c)) == NULL)
        return dst;

    ptr = strtok(dst, "*"); /*Primer token*/
    nohope = strtok(NULL, "*");
    if (nohope != NULL) {
        strcpy(hope, nohope);
    }

    /*Quitar primer espacio*/
    if (ins[0] == ' ')
        /*espacio extra que salia*/
        dst[strlen(dst) - 1] = '\0';
    strcat(dst, ins);
    strcat(dst, hope);

    ptr++;
    ptr--;

    return dst;
}

int clean(char *dst) {
    int i, j, R = 0;
    for (i = 0; dst[i] != '\0'; i++) {
        if (dst[i] == ' ') {
            if (dst[i + 1] == ' ') {
                for (j = i + 1; dst[j] != '\0'; j++)
                    dst[j] = dst[j + 1];
                if (clean(dst) == 1)
                    break;
            }
            if (dst[i - 1] == ' ') {
                for (j = i - 1; dst[j] != '\0'; j++)
                    dst[j] = dst[j + 1];
                if (clean(dst) == 1)
                    break;
            }
        }
        if (dst[i] == '\0')
            break;
    }
    R = 1;
    return R;
}

char * limpia_espacios(char * dst, const char * ori, size_t n) {
    int i, j;
    if (!dst || !ori || n < 0 || strlen(ori) > n)
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
    for (i = strlen(dst) - 1; dst[i] == ' '; i--) {
        dst[i] = '\0';
    }
    /*2.Espacios de en medio*/
    while (clean(dst) != 1);
    return dst;
}

char *elimina_verbo_accion(char *txt_return, const char *txt_ent) {
    int i, j, k;
    char c = ' ';
    if (!txt_ent)
        return NULL;

    strcpy(txt_return, txt_ent);
    /*Comprobacion si hay espacio en cadena*/
    if (strchr(txt_ent, c) == NULL)
        return txt_return;

    for (i = 0; txt_ent[i] != ' '; i++)
        if (txt_ent[i] == '\0') {
            return txt_return;
        }

    for (j = 0; txt_return[i] != '\0'; i++, j++)
        txt_return[j] = txt_return[i];
    k = j - 1;
    if (txt_return[0] == ' ')
        for (j = 0; txt_return[j] != '\0'; j++)
            txt_return[j] = txt_return[j + 1];
    txt_return[k] = '\0';
    return txt_return;
}
