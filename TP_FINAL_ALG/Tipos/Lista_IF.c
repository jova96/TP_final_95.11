#include "Lista_IF.h"

nodo_t * crear_nodo(int dato){
    nodo_t * nuevo_nodo;

    nuevo_nodo = (nodo_t *) malloc(sizeof(nodo_t));

    if(nuevo_nodo == NULL){
        return NULL;
    }

    nuevo_nodo->valor = dato;
    nuevo_nodo->siguiente = NULL;

    return nuevo_nodo;
}

lista_t  inicializar_lista(){
    lista_t nueva;

    nueva.inicio = NULL;
    nueva.fin = NULL;
    nueva.largo = 0;

    return nueva;
}

bool_t agregar_al_final(lista_t * lista_nueva, int dato_nuevo){

    if(lista_nueva->inicio == NULL && lista_nueva->fin == NULL){

        lista_nueva->inicio = crear_nodo(dato_nuevo);

        if(lista_nueva->inicio == NULL){
            return FALSO;
        }

        lista_nueva->fin = lista_nueva->inicio;
        lista_nueva->largo = 1;

        return VERDADERO;
    }

    lista_nueva->fin->siguiente = crear_nodo(dato_nuevo);

    if(lista_nueva->fin->siguiente == NULL){
        return FALSO;
    }

    lista_nueva->fin = lista_nueva->fin->siguiente;
    lista_nueva->largo++;

    return VERDADERO;
}

nodo_t * buscar_posicion_lista(lista_t * lista_nueva , size_t posicion){
    nodo_t * puntero_aux;
    size_t i;

    if((posicion + 1) > lista_nueva->largo){
        return NULL;
    }

    puntero_aux = lista_nueva->inicio;
    for(i = 0; i < posicion ; i++){
        puntero_aux = puntero_aux->siguiente;
    }

    return puntero_aux;
}
/*
void imprimir_lista(lista_t * lista_imprimir){
    nodo_t * puntero_aux;

    puntero_aux = lista_imprimir->inicio;
    while(puntero_aux != NULL){
        printf("Valor nodo : %i \n", puntero_aux->valor);
        puntero_aux = puntero_aux->siguiente;
    }
}
*/

void imprimir_lista(lista_t * lista_imprimir){
    nodo_t * ptr_aux;
    int posc,numero_linea,var_aux;
    int vtr_byte[(POSC_SALTO_LINEA - 1) * 2];

    ptr_aux = lista_imprimir->inicio;
    for(posc = 0,numero_linea = 0,var_aux = 0;ptr_aux != NULL;posc++){
        if(posc == 0){
            printf("%02X0:",numero_linea);
        }
        else if(posc == POSC_SALTO_LINEA){
            printf("%3c",CARACTER_SEPARACION);
            for(var_aux = 0;var_aux < (POSC_SALTO_LINEA - 1) * 2;var_aux++){
               /*if(vtr_byte[var_aux] != 0){*/
               if(isgraph(var_aux)){
                    printf("%X",vtr_byte[var_aux]);
                }
                else{
                    printf("%c",'.');
                }
            }
            numero_linea++;
            puts("");
            posc = -1;
            var_aux = 0;
        }
        else{
            printf("%2c%05X",CARACTER_SEPARACION,ptr_aux->valor);
            vtr_byte[var_aux++] = ptr_aux->valor & MASK_HIGH_BYTE;
            vtr_byte[var_aux++] = ptr_aux->valor & MASK_LOW_BYTE;
            ptr_aux = ptr_aux->siguiente;
        }
    }
    if(var_aux > 0){
        printf("%3c",CARACTER_SEPARACION);
        posc = 0;
        while(posc < var_aux ){
            /*if(vtr_byte[var_aux] != 0){*/
            if(isgraph(posc)){
                printf("%X",vtr_byte[posc]);
            }
            else{
                printf("%c",'.');
            }
            posc++;
        }
    }
}


void liberar_lista(lista_t * lista_liberar){
    nodo_t * puntero_aux;
    nodo_t * puntero_liberar;

    puntero_aux = lista_liberar->inicio;

    while(puntero_aux != NULL){
        puntero_liberar = puntero_aux;
        puntero_aux = puntero_aux->siguiente;
        free(puntero_liberar);
    }
}
