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
    int i, j, k, n_sust, empieza_pa = 0;
    if (!dst || !ori || !ins || n < 0)
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
    return dst;
}
/*
char * limpia_espacios(char * dst, const char * ori, size_t n) {
    int i = 0;

    if (ori == NULL || dst == NULL || n < 0 || strlen(ori) > n)
        return NULL;
    strcpy(dst, ori);

    while (dst[0] == ' ') { 
        strcpy((dst + sizeof (char) *i), dst + sizeof (char) *(i + 1));
    }

    i = 0;
    while (dst[i] != '\0') { 
        i++;
    }

    while (dst[strlen(dst) - 1] == ' ') { 
        dst[(strlen(dst) - sizeof (char))] = '\0';
    }

    return dst;
}*/

/*int cont_espacios(){
	
for(i=0;i<strlen(dst);i++){
        while(dst[i] == ' '){
                for(j=i;j<((strlen(dst))-i);j++){
                        if(dst[i]!=' ')
                                return 
                }
        }
}
}*/

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
char *elimina_verbo_accion(const char *txt_ent) {
    int i, j, k;
    char *ps;

    if (!txt_ent)
        return NULL;
    ps = (char*) calloc(1, strlen(txt_ent) + 1);
    strcpy(ps, txt_ent);
    for (i = 0; txt_ent[i] != ' '; i++);
    for (j = 0; ps[i] != '\0'; i++, j++)
        ps[j] = ps[i];
    k = j - 1;
    if (ps[0] == ' ')
        for (j = 0; ps[j] != '\0'; j++)
            ps[j] = ps[j + 1];
    ps[k] = '\0';
    return ps;
}
