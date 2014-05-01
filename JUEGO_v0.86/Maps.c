

#include "Maps.h"

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

char *add_objeto_map(char *obj_name, char *map, char *name_lista) {
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
    if (map[SPOT_1] != ' ') {
        if (map[SPOT_2] != ' ') {
            if (map[SPOT_3] != ' ') {
                if (map[SPOT_4] != ' ') {
                    return NULL;
                } else {
                    return iden_to_spot(map, iden, SPOT_4);
                }
            } else {
                return iden_to_spot(map, iden, SPOT_3);
            }
        } else {
            return iden_to_spot(map, iden, SPOT_2);
        }
    } else {
        return iden_to_spot(map, iden, SPOT_1);
    }
    free(p_found_iden);
    return NULL;
}

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



