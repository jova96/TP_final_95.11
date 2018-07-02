#ifndef ENTRADA__H
#define ENTRADA__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Tipos/Bool.h"
#include "Tipos/Structs_Simpletron.h"
#include "Tipos/Formatos.h"
#include "Tipos/Lista_IF.h"

#include "Estados/estados_programa.h"

/*Que valor debo ingresar en la consola para terminar la entrada de palabras */
#define ST_INP_VALOR_SALIDA_CONSOLA "EXIT\n"

/* Numero maximo de caracteres que lee */
#define ST_INP_MAXIMO_ENTRADA_PALABRA 100

/*Limites MAX-MIN de la palabra que se puede ingresar */
#define ST_INP_LIMITE_PALABRA_INF -10000000
#define ST_INP_LIMITE_PALABRA_SUP 10000000


/*Valida las palabras ingresadas */
status_t validar_palabra(char * palabra , int * palabra_convertida);

/*Selecciona cual es la entrada dependiendo de los argumentos ingresados */
status_t seleccionar_entrada(contenedor_de_argumentos_t * info , lista_t ** vector_lista);
/*Entrada a traves de la consola */
status_t entrada_consola(lista_t * lista_cargar, int memoria_disponible);
/*Entrada a traves de archivos de textos */
status_t entrada_archivo_txt(lista_t * lista_cargar, char * nombre_archivo, int memoria_disponible);
status_t entrada_archivo_bin(lista_t * lista_cargar , char * nombre_archivo, int memoria_disponible);

#endif
