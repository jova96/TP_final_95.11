#ifndef CADENAS__H
#define CADENAS__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Cuenta el largo de una cadena */
int contar_largo_cadena(char * cadena_pasada);
/*Recrota la cantidad de caracteres que uno especifica y devuelve una nueva cadena */
char * cortar_cadena(char * cadena_pasada, int cuanto_cortar);
/*Devuelve un puntero hacia la parte de la cadena que se quiera contando desde el inicio */
char * dividir_cadena(char * cadena_pasada , int cuanto_dividir);


#endif