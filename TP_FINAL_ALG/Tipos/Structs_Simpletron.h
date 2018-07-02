#ifndef CONTENEDOR_ARG_H
#define CONTENEDOR_ARG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Bool.h"
#include "Formatos.h"
#include "Cadenas.h"
#include "Lista_IF.h"

#define MACRO_CONTENEDOR_AYUDA_DEFAULT FALSO
#define MACRO_CONTENEDOR_STDIN_DEFAULT FALSO
#define MACRO_CONTENEDOR_MEMORIA_DEFAULT 50
#define MACRO_CONTENEDOR_TIPO_SALIDA_DEFAULT TXT

/*Estructura del Simpletron */
struct simpletron{
    int acumulador;
    size_t contador;
    int registro;
    lista_t * memoria;
};

/*Estructura que guarda todos los argumentos para usar despues en el programa */
typedef struct contenedor_de_argumentos{
    bool_t ayuda;
    size_t memoria;
    bool_t entrada_stdin;
    size_t cantidad_de_archivos;
    char ** nombres_archivos_entrada;
    formato_t * tipo_archivos_entrada;
    formato_t tipo_archivo_salida;
}contenedor_de_argumentos_t;


/*Inicializar simpletron con los valores default */
struct simpletron inicializar_simpletron();
/*Imprimir simpletron con los valores que tiene actualmente */
void imprimir_simpletron(struct simpletron * imprimir_cabeza);

/************************************/

/*Crea un mensajero con los valores default */
contenedor_de_argumentos_t inicializar_contenedor_argumentos();
/*Agrega un archivo y su tipo al contenedor */
bool_t agregar_archivo_al_contenedor(contenedor_de_argumentos_t * contenedor, formato_t fmt , char * nombre);
/*Imprime la informacion del contenedor */
void imprimir_contenedor(contenedor_de_argumentos_t * contenedor_imprimir);
/*Libera toda memoria usada en el contenedor */
void liberar_contenedor_argumentos(contenedor_de_argumentos_t * arg_eliminar);

#endif