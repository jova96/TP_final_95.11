#include "argumentos.h"


bool_t validar_no_argumento(char * cadena_validar){
    int i;
    char * cadena_cortada;

    for(i = 0; i < ST_ARG_OPCIONES_ARGUMENTOS_COMPLETO;i++){
        /*Si encuentra que es igual a un argumento de la lista, retorna falso */
        if(strcmp(cadena_validar, argumentos_lista_completa[i]) == 0){
            return FALSO;
        }
    }

    /*Si fuera una palabra de menor largo, entonces estariamos tocando memoria que no deberiamos tocar */
    cadena_cortada = cortar_cadena(cadena_validar, ST_ARG_CORTADO_CADENA_ARGUMENTO);
    if(contar_largo_cadena(cadena_validar) >= ST_ARG_CORTADO_CADENA_ARGUMENTO){
        for(i = 0; i < ST_ARG_OPCIONES_ARGUMENTOS_ABREVIADO; i++){
            /*Si encuentra que es igual a un argumento de la lista, retorna falso */
            if(strcmp(cadena_cortada, argumentos_lista_abreviada[i]) == 0){
                free(cadena_cortada);
                return FALSO;
            }
        }
    }

    free(cadena_cortada);

    if(strcmp(cadena_validar, ST_ARG_OPCION_ENTRADA_STDIN) == 0){
        return FALSO;
    }
    

    return VERDADERO;
}

status_t procesar_argumentos(contenedor_de_argumentos_t * arg_guardar, char ** argumentos_pasados, int cantidad_argumentos){
    int i;
    char * puntero_aux;
    char * cadena_cortada;

    for( i = 1; i < cantidad_argumentos; i++){

        /*Si se ingresa el argumento -h o --help */
        if(strcmp(argumentos_pasados[i],argumentos_lista_abreviada[ARG_H]) == 0 ||
        strcmp(argumentos_pasados[i],argumentos_lista_completa[ARG_H]) == 0){
            arg_guardar->ayuda = VERDADERO;
        }

        /*Si se ingresa el argumento -h o --help */
        else if(strcmp(argumentos_pasados[i],argumentos_lista_abreviada[ARG_M]) == 0 ||
        strcmp(argumentos_pasados[i],argumentos_lista_completa[ARG_M]) == 0){
            
            /*Valido que no se haya olvidado escribir la cantidad de memoria */
            if(argumentos_pasados[i + 1] == NULL || validar_no_argumento(argumentos_pasados[i + 1]) == FALSO){
                return ARG_MEMORIA_NO_ESPECIFICADA;
            }
            
            /*Se ingreso una cantidad de memoria negativa */
            if(strtol(argumentos_pasados[i + 1],&puntero_aux,10) <= 0){
                return ARG_MEMORIA_NEGATIVA;
            }

            /*Valido que sea un numero el siguiente argumento */
            arg_guardar->memoria = strtol(argumentos_pasados[i + 1],&puntero_aux,10);

            /*No se ingreso una cantidad de memoria que sea un numero */
            if(arg_guardar->memoria == 0 && puntero_aux != NULL){
                return ARG_MEMORIA_INV;
            }
            

            i++;
        }

        /*Si se ingresa el argumento -f o --formato */
        else if(strcmp(argumentos_pasados[i],argumentos_lista_abreviada[ARG_F]) == 0 ||
        strcmp(argumentos_pasados[i],argumentos_lista_completa[ARG_F]) == 0){
            
            /*Valido que se especifica el tipo de salida */
            
            /*Valido que no se haya olvidado escribir el formato de salida */
            if(argumentos_pasados[i + 1] == NULL || validar_no_argumento(argumentos_pasados[i + 1]) == FALSO){
                return ARG_FORMATO_SALIDA_NO_ESPECIFICADO;
            }

            /*En caso de que sea txt, solo le sumo a i++ ya que el valor de
            salida default es txt */
            else if(strcmp(argumentos_pasados[i + 1], formatos_archivos_permitidos[TXT]) == 0){
                i++;
            }
            
            /*En caso deuq e sea bin , cambio el valor del formato de salida a bin */
            else if(strcmp(argumentos_pasados[i + 1], formatos_archivos_permitidos[BIN]) == 0){
                arg_guardar->tipo_archivo_salida = BIN;
                i++;
            }

            /*El tipo de salida es invalido */
            else{
                return ARG_FORMATO_SALIDA_INV;
            }
        }

        /*Si fuera una palabra de menor largo, entonces estariamos tocando memoria que no deberiamos tocar */
        else if(contar_largo_cadena(argumentos_pasados[i]) >= ST_ARG_CORTADO_CADENA_ARGUMENTO){
            /*Algunas validaciones */
            cadena_cortada = cortar_cadena(argumentos_pasados[i], ST_ARG_CORTADO_CADENA_ARGUMENTO);

            /*Si ya se dijo que la entrada es stdin , retorna error */
            if(arg_guardar->entrada_stdin == VERDADERO){
                free(cadena_cortada);
                return ARG_STDIN_VERDADERO;
            }
                
            /*Si es del mismo tamaño que t: o b: significa que no le puso nombre al archivo */
            else if(contar_largo_cadena(argumentos_pasados[i]) == ST_ARG_CORTADO_CADENA_ARGUMENTO){
                free(cadena_cortada);
                return ARG_NOMBRE_NO_ESPECIFICADO;
            }
            
            /*Si se ingresa un archivo de entrada t: */
            else if(strcmp(cadena_cortada, argumentos_lista_abreviada[ARG_T]) == 0){
        
                /*Se carga al contenedor el tipo de archivo y su nombre , si hay un error con la memoria devuelve Error */
                if(agregar_archivo_al_contenedor(arg_guardar , TXT , dividir_cadena(argumentos_pasados[i], ST_ARG_CORTADO_CADENA_ARGUMENTO)) == FALSO){
                    free(cadena_cortada);
                    return ARG_NULL;
                }
                
            }

            /*Si se ingresa un archivo de entrada b: */
            else if(strcmp(cadena_cortada , argumentos_lista_abreviada[ARG_B]) == 0){

                /*Se carga al contenedor el tipo de archivo y su nombre , si hay un error con la memoria devuelve Error */
                if(agregar_archivo_al_contenedor(arg_guardar , BIN , dividir_cadena(argumentos_pasados[i], ST_ARG_CORTADO_CADENA_ARGUMENTO)) == FALSO){
                    free(cadena_cortada);
                    return ARG_NULL;
                }
            }
            
            /*No es ninguna de las opciones, entonces argumento invalido */
            else{
                free(cadena_cortada);
                return ARG_NO_VALIDO;
            }
        
        free(cadena_cortada);
        }

        /*Si se ingresa "-" para que la entrada sea stdin */
        else if(strcmp(argumentos_pasados[i],ST_ARG_OPCION_ENTRADA_STDIN) == 0){
            /*Si ya se ingreso un archivo antes, devuelve error */
            if(arg_guardar->cantidad_de_archivos != 0){
                return ARG_ARCHIVO_YA_INGRESADO;
            }

            arg_guardar->entrada_stdin = VERDADERO;
        }
        

        /*Si no coindice con ninguno de los argumentos validos */
        else{
            return ARG_NO_VALIDO;
        }
    }

    return OK;
}
