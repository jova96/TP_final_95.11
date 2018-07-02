#include <stdio.h>
#include <stdlib.h>

enum estado_arg{
    ST_OK,
    ST_SALIR_CICLO,
    ST_PROCESAR_ARCHIVO,
    ST_PROCESAR_ARGUMENTO,
    ST_PROCESAR_PARAMETRO
};
typedef enum estado_arg estado_arg_t;


