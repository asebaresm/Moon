/**
 * @author Pablo Yus. 
 * @file UtilCadena.c
 * @brief Este módulo contiene las implementaciones de las funciones de manejo de cadenas de caracteres. 
 */


#include "UtilCadena.h"


char * elimina_cars(char * dst, const char * ori, const char *seps, size_t n) {
    int i=0, j=0, flag = 0;

    if (ori == NULL || seps == NULL || dst == NULL ||n < 0)
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


char * a_mayusculas(char * dst, const char * ori, size_t n){

    int i=0;
    
    if (ori == NULL){
        printf("ERROR");
        return NULL;
    }

    for (i=0; i<strlen(ori); i++)
     /*Se utiliza la funcion toupper, que ya se encarga de pasar a mayusculas la cadena de caracteres es necesario añadir la libreria ctype.h*/
		dst[i] = toupper(ori[i]);
    
    return dst;
}


 
char * reemplaza_asterisco(char * dst, const char * ori, const char * ins, size_t n){
	
	int i=0,numAst=0;

	if (dst==NULL || ori == NULL || ins == NULL || (strlen(ori)+strlen(ins)) < n)
		return NULL;
	/*Copiamos la cadena de origen en la destino*/
	strcpy(dst,ori);
	/*if(dst == NULL)
		return NULL;*/

	for(numAst=0,i=0;dst[i];i++){
		if(dst[i] == '*')
			numAst++;
	}

	if(numAst > 1)return NULL;	

	for(i=0;dst[i]!= '\n';i++){
		if(dst[i] == '*'){
		/*Si encontramos el caracter a sustituir, '*', lo reemplazamos por un espacio*/
			dst[i] = ' ';
		/*Incrementamos el indice*/
			i++;
		/*Copiamos la cadena que debemos insertar a partir de la posicion en la que se encontraba el asterisco*/
			strcpy(&(dst[i]),ins);
			return dst;
		}
	}
	return dst;
}


char * limpia_espacios(char * dst, const char * ori, size_t n){
   int i = 0;

    if (ori == NULL || dst == NULL || n < 0 || strlen(ori) > n)
        return NULL;
	/*Copiamos la cadena de origen en la de destino*/
    strcpy(dst, ori);

    /*Buscamos espacios en blanco al inicio de la cadena*/
    while (dst[0] == ' ') { /* Mientras no encontremos un caracter distinton de ' ' en el origen de la cadena*/
        /*Si el primer caracter es un espacio, corremos toda la cadena una posicion a la izquierda*/
        strcpy((dst + sizeof (char) *i), dst + sizeof (char) *(i + 1));
    }

    /*Reiniciamos el contador*/
    i=0;
    while(dst[i] != '\0'){ /*Comprobamos la longitud de la cadena destino*/
        i++;
    }

    /*Se buscan los espcaios en blanco al final de la cadena*/
    while (dst[strlen(dst)-1] == ' ') { /*En caso de encontrar un algun espacio en blanco, lo sustituimos con un '\0', que hara que finalice la cadena*/
		dst[(strlen(dst) - sizeof (char))] = '\0';
    }

    return dst;	
}



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
