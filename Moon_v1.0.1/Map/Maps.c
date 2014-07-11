/**
 *@file Maps.c
 *@brief contiene las implementaciones de las funciones de maps
 *@author Alfonso
 *@date 10-05-2014
 *@version 0.1
 */

#include "Maps.h"

/*Introduce un identificador (sin formato) en una posicion del mapa*/
char *iden_to_spot(char *map, char *iden, int spot) {
    if (!map || !iden) {
        return NULL;
    }
    map[spot] = '[';
    map[spot + 1] = iden[0];
    map[spot + 2] = iden[1];
    map[spot + 3] = ']';
    return map;
}

/* Obtiene el identificador de un objeto a partir de su nombre y una lista de objetos*/
char *get_iden_from_obj_name(const char *obj_name, char *name_lista) {
    int i;
    FILE *f = NULL;
    char list[WORD_MAX];
    char *p_found_obj = NULL;
    char *p_found_iden = NULL;

    if (!obj_name || !name_lista)
        return NULL;
    f = fopen(name_lista, "r");
    while ((fread(list, 1, sizeof list, f)) > 0);
    if (!(p_found_obj = strstr(list, obj_name))) {
        return ERROR;
    }
    if ((p_found_iden = (char*) calloc(1, 5)) == NULL)
        return NULL;
    for (i = 0; i < 3; i++) {
        p_found_iden[i] = p_found_obj[i + strlen(obj_name)];
    }
    if (p_found_iden[0] == ' ')
        for (i = 0; p_found_iden[i] != '\0'; i++)
            p_found_iden[i] = p_found_iden[i + 1];
    fclose(f);
    return p_found_iden;
}

/*Obtiene el identificador de un objeto a partir de su nombre y una lista de objetos*/
char *format_iden(char *iden) {
    int i;
    char cpy[5] = "";
    if (!iden)
        return NULL;

    for (i = 0; i < 3; i++) {
        cpy[i + 1] = iden[i];
    }
    cpy[0] = ' ';
    for (i = 0; i < 4; i++) {
        iden[i] = cpy[i];
    }
    iden[0] = '[';
    iden[3] = ']';
    iden[4] = '\0';
    return iden;
}

/* Añade un objeto en el mapa a traves de un identificador con formato*/
char *add_objeto_map(char *obj_name, char *map, char *name_lista) {
    int i;
    char *p_found_iden = NULL;
    char iden[WORD_MAX] = "";
    if (!obj_name || !map || !name_lista)
        return NULL;
    p_found_iden = get_iden_from_obj_name(obj_name, name_lista);
    if (!p_found_iden)
        return NULL;
    strcpy(iden, p_found_iden);
    free(p_found_iden);
    /*colocar en el mapa*/
    for(i=0;i<strlen(map);i++){
        if(map[i]=='!')
            break;
    }
    
    
    
    
    if (map[i+2] != ' ') {
        if (map[i+7] != ' ') {
            if (map[i+12] != ' ') {
                if (map[i+17] != ' ') {
                    return NULL;
                } else {
                    return iden_to_spot(map, iden, i+17);
                }
            } else {
                return iden_to_spot(map, iden, i+12);
            }
        } else {
            return iden_to_spot(map, iden, i+7);
        }
    } else {
        return iden_to_spot(map, iden, i+2);
    }
    free(p_found_iden);
    return NULL;
}

/*Elimina un objeto en el mapa a traves de un identificador con formato*/
char *elimina_objeto_map(char *obj_name, char *map, char *name_lista) {
    char *piden = NULL;
    char iden[WORD_MAX] = "";
    int i, tam_map;
    piden = get_iden_from_obj_name(obj_name, name_lista);
    piden = format_iden(piden);
    if (!map || !piden || !name_lista)
        return NULL;
    strcpy(iden, piden);
    free(piden);
    for (i = 0; iden[i] != '\0'; i++)
        iden[i] = iden[i + 1];
    iden[strlen(iden) - 1] = '\0';
    tam_map = strlen(map);
    for (i = 0; i < tam_map; i++) {
        if (map[i] == iden[0] && map[i + 1] == iden[1]) {
            map[i] = ' ';
            map[i+1]=' ';
            break;
        }
    }
    map[i-1]=' ';
    map[i+2]=' ';
    return map;
}



