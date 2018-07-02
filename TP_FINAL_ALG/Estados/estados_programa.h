#ifndef ESTADOS_PROGRAMA__H
#define ESTADOS_PROGRAMA__H

#include <stdio.h>

/************************** MSJ ARGUMENTOS ***********************/
/*Mensaje default de errores de argumentos */
#define MSJ_ARG_ERROR "Ha ocurrido un error con los argumentos  "

/*Mensajes relacionados con la memoria */
#define MSJ_ARG_ERROR_MEMORIA_NO_ESPECIFICADA "-m / --memoria : No se ha ingresado la cantidad de memoria "
#define MSJ_ARG_ERROR_MEMORIA_INV "-m/--memoria : Se ingreso un valor invalido para la memoria"
#define MSJ_ARG_ERROR_MEMORIA_NEG "-m/ --memoria : Se ingreso un valor negativo o igual a 0 para la memoria"

/*Mensajes relacionados con el formato de salida */
#define MSJ_ARG_ERROR_SALIDA_FORMATO_NO_ESP "-f / --formato : No se especifico el formato de salida"
#define MSJ_ARG_ERROR_SALIDA_FORMATO_INV "-f/ --formato : El formato de salida es invalido "

/*Mensajes relacionados con el formato de salida */
#define MSJ_ARG_ERROR_ENTRADA_STDIN "-/b:/t: : No se puede agregar archivos si se declaro antes que la entrada es por consola"
#define MSJ_ARG_ERROR_ENTRADA_NOMBRE_NO_ESP "b:/t: No se especifico el nombre del archivo"
#define MSJ_ARG_ERROR_ENTRADA_ARCHIVO "-/b:/t: No se puede pedir entrada por consola si ya se agrego un archivo"

/*Mensajerelacionado con errores de memoria dinamica */
#define MSJ_ARG_ERROR_MEMORIA_DIN "Hubo un error con el uso de memoria del programa, no hay suficiente memoria"

/*Mensaje relacionado con argumentos invalidos */
#define MSJ_ARG_ERROR_NO_VALIDO "Se ingreso un argumento no valido"

/**************************MSJ ENTRADAS ***********************/
#define MSJ_INP_ERROR "Hubo un error en la entrada de palabras "

#define MSJ_INP_MEMORIA_INSF "Error , no hay suficiente memoria en el simpletron"
#define MSJ_INP_ERROR_LISTA_NULL "Error en el cargado de las listas"
#define MSJ_INP_ERROR_PALABRA_INV "Se ha ingresado una palabra invalida"
#define MSJ_INP_ERROR_PALABRA_RANGO "Se ingreso una palabra que estaba fuera de rango"
#define MSJ_INP_ERROR_ARCHIVO "Uno de los archivos ingresados no existe"

/**********************MSJ EJECUCION *************************/
#define MSJ_EXE_ERROR "Ha ocurrido un error en la ejecucion"
#define MSJ_EXE_ERROR_OPCODE_INV "Se ha ingresado un opcode invalido"
#define MSJ_EXE_ERROR_MEMORIA_RANGO "Una direccion de memoria apunta fuera del rango de la memoria"
#define MSJ_EXE_ERROR_ENTRADA "Entrada invalida"
#define MSJ_EXE_ERROR_NULL "Error en la memoria dinamica, falta memoria"

/*Status_t de los argumentos */

typedef enum status{
	/*Estados relacionados con los argumentos*/
    ARG_MEMORIA_NO_ESPECIFICADA,
    ARG_MEMORIA_INV,
    ARG_MEMORIA_NEGATIVA,
    ARG_FORMATO_SALIDA_NO_ESPECIFICADO,
    ARG_FORMATO_SALIDA_INV,
    ARG_STDIN_VERDADERO,
    ARG_NOMBRE_NO_ESPECIFICADO,
    ARG_ARCHIVO_YA_INGRESADO,
    ARG_NULL,
    ARG_NO_VALIDO,
	/*Estados relacionados con las entradas */
	INP_MEMORIA_INSF,
	INP_LISTA_NULL,
	INP_PALABRA_INV,
	INP_PALABRA_FUERA_RANGO,
	INP_ARCHIVO_INV,
	/*Estados relacionados con la ejecucion del simpletron */
	EXE_OPCODE_INV,
	EXE_MEMORIA_FUERA_RANGO,
	EXE_ERROR_ENTRADA,
	EXE_NULL,
	/*Estado de que todo salio bien */
    OK,
    SALIR
}status_t;

void imprimir_mensajes_error(status_t estado);


#endif
