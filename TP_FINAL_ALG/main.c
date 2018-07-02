#include "argumentos.h"
#include "entrada.h"
#include "ejecutar.h"


int main(int argc, char *argv[]){
    /*Los estados de cada parte del programa */
    status_t estado_programa;

    /*Estructuras del programa */
    struct simpletron cabeza;
    contenedor_de_argumentos_t cargado;
    lista_t * vector_palabras;

    /*Variable para iteraciones */
    int i;

    /*Inicializo las estructuras con sus valores default */
    cargado = inicializar_contenedor_argumentos();
    cabeza = inicializar_simpletron();

    estado_programa = procesar_argumentos(&cargado, argv , argc);
/*    imprimir_contenedor(&cargado);
*/
    if(estado_programa != OK){
        imprimir_mensajes_error(estado_programa);
        return 1;
    }

    estado_programa = seleccionar_entrada(&cargado , &vector_palabras);

    if(estado_programa != OK){
        imprimir_mensajes_error(estado_programa);;
        return 1;
    }
/*
    for(i = 0; i < cargado.cantidad_de_archivos ; i++){
        printf("ARCHIVO NUMERO : %i \n" , i + 1);
        imprimir_lista(&(vector_palabras[i]));
        printf("\n \n");
    }
*/
    for( i = 0; i < cargado.cantidad_de_archivos; i++){
        printf("ARCHIVO NUMERO : %i \n" , i + 1);
        cabeza = inicializar_simpletron();
        cabeza.memoria = &vector_palabras[i];
        estado_programa= ejecutar_memoria(&cabeza);

        imprimir_simpletron(&cabeza);

        if(estado_programa != OK){
            imprimir_mensajes_error(estado_programa);
            return 1;
        }
    }

    /*Tendria que convertirlo en funcion de borrar en caso de error y tambien para el final dela archivo */
    for(i = 0; i < cargado.cantidad_de_archivos; i++){
        liberar_lista(&vector_palabras[i]);
    }

    liberar_contenedor_argumentos(&cargado);
    free(vector_palabras);

    return 0;
}
