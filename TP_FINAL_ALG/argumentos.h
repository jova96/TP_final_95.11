#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tipos/Bool.h"
#include "Tipos/Cadenas.h"
#include "Tipos/Formatos.h"
#include "Tipos/Structs_Simpletron.h"

#include "Estados/estados_programa.h"

/*Para la funcion cortar cadena, cuanto quiere cortar el argumento */
#define ST_ARG_CORTADO_CADENA_ARGUMENTO 2

/*Diccionario con posibles argumentos */
#define ST_ARG_OPCION_ENTRADA_STDIN "-"
#define ST_ARG_OPCIONES_ARGUMENTOS_ABREVIADO 5
#define ST_ARG_OPCIONES_ARGUMENTOS_COMPLETO 3
static const char * const argumentos_lista_abreviada[] = {"-h" , "-m", "-f" ,  "t:" , "b:"};
static const char * const argumentos_lista_completa[] = {"--help", "--memoria" , "--formato"};

enum index_argumentos{
    ARG_H = 0,
    ARG_M = 1,
    ARG_F = 2,
    ARG_T = 3,
    ARG_B = 4
};

/*Busca si no es argumento, si es argumento retorna falso, sino, retorna verdader */
bool_t validar_no_argumento(char * cadena_validar);
status_t procesar_argumentos(contenedor_de_argumentos_t * arg_subidos, char ** argumentos_pasados, int cantidad_argumentos);

#endif