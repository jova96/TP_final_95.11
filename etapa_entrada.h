#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/** MASCARAS **/
#define MASK_OPCODE 0x0000FE00
#define MASK_OPERANDO 0x000001FF

/** CORRIMIENTOS **/
#define SHIFT_OPCODE 9
#define SHIFT_OPERANDO 0

#define MAX_LARGO 20
#define MAX_LARGO_INGRESO 126

#define MAX_VALOR_PALABRA 999999
#define MIN_VALOR_PALABRA -32768
#define MAX_VALOR_OPCODE 0x0000007F
#define MAX_VALOR_OPERANDO 0x000001FF

enum estado{
    ST_OK,
    ST_PTR_NULO,
    ST_POSC_INVALIDA,
    ST_NO_MEMORIA,
    ST_ERROR_ABRIR_ARCHIVO,
    ST_ERROR_GUARDAR_PALABRA,
    ST_ERROR_CONVERTIR_CADENA,
    ST_ERROR_LIMPIAR_CADENA,
    ST_SALIR_CICLO,
    ST_ERROR_PALABRA_INCOMPLETA,
    ST_ERROR_FRMT_INVALIDO,
    ST_ERROR_PALABRA_FUERA_DE_RANGO,
    ST_CADENA_VACIA,
    ST_ARCHIVO_VACIO
};
typedef enum estado estado_t;

enum frmt_archivo{
    FRMT_BIN,
    FRMT_TXT,
    FRMT_INV
};
typedef enum frmt_archivo frmt_archivo_t;

/*cuando usado = 0 el vector se considera vacio*/
struct vtr_palabra{
    int * vtr_palabra;
    size_t largo;
};
typedef struct vtr_palabra vtr_palabra_t;

struct nodo{
    struct nodo * ptr_sig_nodo;
    struct simpletron * ptr_simpletron;
};
typedef struct nodo nodo_t;
/*pensar la lista como un puntero a un nodo*/
typedef nodo_t * lista_t;

struct simpletron{
    struct vtr_palabra * ptr_memoria;
};
typedef struct simpletron simpletron_t;

struct parametro{
    size_t largo;
    char * nombre_archivo;
    enum frmt_archivo frmt_archivo_salida;
    enum frmt_archivo frmt_archivo_entrada;

};
typedef struct parametro parametro_t;

/*** TDA vtr_palabra ***/
vtr_palabra_t * vector_crear(size_t largo);
void vector_destruir(vtr_palabra_t ** ppvtr_palabra);
estado_t vector_guardar(vtr_palabra_t * pvtr_palabra,int palabra,size_t posc);
int vector_buscar(vtr_palabra_t * pvtr_palabra, int palabra);

/*
estado_t lista_crear_nodo(nodo_t ** pptr_nodo,simpletron_t * ptr_dato);
estado_t lista_destruir_nodo(nodo_t ** pptr_nodo,estado_t(*destruir_dato)(simpletron_t*));
estado_t lista_destruir(lista_t * ptr_lista,estado_t(*destruir_dato)(simpletron_t*));
estado_t lista_destruir_primero(lista_t * ptr_lista,estado_t(*destructor_dato)(simpletron_t **));
estado_t lista_insertar_al_principio(lista_t * ptr_lista,simpletron_t * ptr_dato);
estado_t lista_insertar_al_final(lista_t * ptr_lista , simpletron_t * ptr_dato);
*/

estado_t leer_archivo_de_palabras(vtr_palabra_t ** ppvtr_palabra,parametro_t * ptr_parametro);
estado_t convertir_cadena_palabra(char * cadena,int * ptr_palabra);
estado_t limpiar_cadena(char * cadena_sucia,char ** cadena_limpia);

vtr_palabra_t * vector_crear(size_t largo){
    vtr_palabra_t * ptr_vector;
    int * pptr_aux;

    ptr_vector =(vtr_palabra_t *)calloc(1,sizeof(vtr_palabra_t));
    if(!ptr_vector){
        return NULL;
    }
    pptr_aux = (int*)calloc(largo,sizeof(int));
    if(!pptr_aux){
        free(ptr_vector);
        return NULL;
    }
    ptr_vector->vtr_palabra = pptr_aux;
    ptr_vector->largo = largo;
    return ptr_vector;
}


void vector_destruir(vtr_palabra_t ** pptr_vector){
    if(pptr_vector && *pptr_vector){
        if((*pptr_vector)->vtr_palabra){
            free((*pptr_vector)->vtr_palabra);
        }
        free(*pptr_vector);
        *pptr_vector = NULL;
    }
}


estado_t vector_guardar(vtr_palabra_t * ptr_vector,int palabra,size_t posc){
    if(!ptr_vector){
        return ST_PTR_NULO;
    }
    if( posc >= ptr_vector->largo ){
        return ST_POSC_INVALIDA;
    }
    if(ptr_vector->vtr_palabra){
        (ptr_vector->vtr_palabra)[posc] = palabra;
    }
    return ST_OK;
}

int vector_buscar(vtr_palabra_t * pvtr_palabra, int palabra){
    int posc;

    if(!pvtr_palabra){
        return -1;
    }
    if(palabra > 0xFE3F){
        return -1;
    }
    for(posc = 0; posc < pvtr_palabra->largo; posc++){
        if((pvtr_palabra->vtr_palabra)[posc] == palabra)
            return posc;
    }
    return -1;
}

/*

estado_t lista_crear_nodo(nodo_t ** pptr_nodo,simpletron_t * ptr_dato){
    nodo_t * ptr_nodo;
    if(!pptr_nodo){
        return ST_PTR_NULO;
    }
    ptr_nodo =(nodo_t*)calloc(1,sizeof(nodo_t));
    if(!ptr_nodo){
        return ST_NO_MEMORIA;
    }
    ptr_nodo->ptr_sig_nodo = NULL;
    ptr_nodo->ptr_simpletron = ptr_dato;
    (*pptr_nodo) = ptr_nodo;
    return ST_OK;
}

estado_t lista_destruir_nodo(nodo_t ** pptr_nodo,estado_t(*destruir_dato)(simpletron_t*)){
    simpletron_t * ptr_dato;

    if(!pptr_nodo){
        return ST_PTR_NULO;
    }
    if(*pptr_nodo){
        return ST_OK;
    }
    ptr_dato = (*pptr_nodo)->ptr_dato;
    (*pptr_nodo)->ptr_simpletron = NULL;
    (*pptr_nodo)->ptr_sig_nodo = NULL;
    free(*pptr_nodo);
    *pptr_nodo = NULL;

    return (destruir_dato != NULL)? (*destruir_dato)(ptr_dato):ST_OK;

}

estado_t lista_destruir(lista_t * ptr_lista,estado_t(*destruir_dato)(simpletron_t*)){
    nodo_t * ptr_nodo_borrar;
    estado_t estado;
    if(!ptr_lista){
        return ST_PTR_NULO;
    }
    while(*ptr_lista != NULL){
        ptr_nodo_borrar = *ptr_lista;
        (*ptr_lista) = (*ptr_lista)->ptr_sig_nodo;
        estado = lista_destruir_nodo(&ptr_nodo_borrar,destruir_dato);
        if(estado != ST_OK){
            return estado;
        }
    }
    return ST_OK;
}


estado_t lista_destruir_primero(lista_t * ptr_lista,estado_t(*destructor_dato)(simpletron_t **)){
    nodo_t * primero;

    if(!ptr_lista){
        return ST_PTR_NULO;
    }
    if(!*ptr_lista){
        return ST_OK;
    }
    primero = *ptr_lista;
    *ptr_lista = (*ptr_lista)->ptr_nodo_sig;
    return lista_destruir_nodo(&primero,destructor_dato);
}

estado_t lista_insertar_al_principio(lista_t * ptr_lista,simpletron_t * ptr_dato){
    estado_t estado;
    nodo_t * ptr_nodo_nuevo;

    if(!ptr_lista){
        return ST_PTR_NULO;
    }
    estado = lista_crear_nodo(&ptr_nodo_nuevo,ptr_dato);
    if(estado != ST_OK){
        return estado;
    }
    (ptr_nodo_nuevo)->ptr_sig_nodo = *ptr_lista;
    *ptr_lista = ptr_nodo_nuevo;
    return ST_OK;
}

estado_t lista_insertar_al_final(lista_t * ptr_lista , simpletron_t * ptr_dato){
    estado_t estado;
    nodo_t * ptr_nodo_nuevo;
    nodo_t * ptr_aux;

    if(!ptr_lista){
        return ST_PTR_NULO;
    }
    estado = lista_crear_nodo(&ptr_nodo_nuevo,ptr_dato);
    if(estado != ST_OK){
        return estado;
    }
    if(((*ptr_lista)->ptr_nodo_sig) == NULL){
        (*ptr_lista)->ptr_sig_nodo = ptr_nodo_nuevo;
    }
    else{
        for(ptr_aux = *ptr_lista;(ptr_aux->ptr_sig_nodo) != NULL;ptr_aux = ptr_aux->ptr_sig_nodo)
                                    {}
        (ptr_aux->ptr_sig_nodo) = ptr_nodo_nuevo;
    }
    return ST_OK;
}
*/
