#include "Cadenas.h"

/*Cuenta cuantos caracteres tiene la cadena */
int contar_largo_cadena(char * cadena_pasada){
    int i = 0;
    int contador = 0;

    while(cadena_pasada[i] != '\0'){
        contador++;
        i++;
    }

    return contador;
}

char * cortar_cadena(char * cadena_pasada , int cuanto_cortar){
    char * nueva_cadena;

    /*En caso de que se le pase una cadena vacia */
    if(cadena_pasada == NULL){
        return NULL;
    }

    /*En caso de que el largo de la cadena sea menor a la cantidad que 
    se quiere recortar */
    if(contar_largo_cadena(cadena_pasada) < cuanto_cortar){
        return NULL;
    }

    /*Pido memoria para la nueva_cadena, en caso de que no tenga memoria
    retorno NULL */
    nueva_cadena = (char *) calloc(contar_largo_cadena(cadena_pasada) + 1,sizeof(char));
    if(nueva_cadena == NULL){
        return NULL;
    }

    strcpy(nueva_cadena, cadena_pasada);
    nueva_cadena[cuanto_cortar] = '\0';

    return  nueva_cadena;
}

/*Devuelve un puntero hacia la parte de la cadena que se quiera */
char * dividir_cadena(char * cadena_pasada , int cuanto_dividir){
    char * cadena_dividida;
    cadena_dividida = &cadena_pasada[cuanto_dividir];

    return cadena_dividida;
}