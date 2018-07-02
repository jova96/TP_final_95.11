#ifndef LISTA_IF__H
#define LISTA_IF__H

#define POSC_SALTO_LINEA 9
#define CARACTER_SEPARACION ' '
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Bool.h"

#define MASK_HIGH_BYTE 0x0000FF00
#define MASK_LOW_BYTE 0x000000FF

typedef struct nodo{
    int valor;
    struct nodo * siguiente;
}nodo_t;

typedef struct lista{
    size_t largo;
    nodo_t * inicio;
    nodo_t * fin;
}lista_t;

/*Crea un nodo con la palabra como valor */
nodo_t * crear_nodo(int dato);

/*Crea una lista */
lista_t  inicializar_lista();
/*Agrega al final de la lista un nodo */
bool_t agregar_al_final(lista_t * lista_nueva, int dato_nuevo);
/*Busca el nodo en la posicion deseada y lo devuelve */
nodo_t * buscar_posicion_lista(lista_t * lista_nueva , size_t posicion);
/*Imprime la lista */
void imprimir_lista(lista_t * lista_imprimir);
/*Libera los nodos de la lista */
void liberar_lista(lista_t * lista_liberar);

#endif
