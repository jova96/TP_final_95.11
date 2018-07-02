#ifndef EJECUTAR__H
#define EJECUTAR__H

#include <stdio.h>
#include <stdlib.h>

#include "Tipos/Structs_Simpletron.h"
#include "Tipos/Lista_IF.h"
#include "Tipos/Bool.h"

#include "Estados/estados_programa.h"

/*Para sacar el opcode y la direccion de memoria de una palabra */
#define EXE_DIVISOR 10000

/*Opcode que significa que termina la ejecucion del programa */
#define EXE_OPERADOR_HALT 45

/*Que tan larga es la entrada */
#define EXE_MAXIMO_LARGO_ENTRADA 20

/*Mensajes de input/output */
#define EXE_MSJ_OPERACION_LEER "Ingrese un valor :"
#define EXE_MSJ_OPERACION_ESCRIBIR "Valor en memoria "

/* Valida si la direccion de memoria de la palabra existe */
bool_t validar_dir_memoria(lista_t * memoria_programa);

/*Ejecuta el programa */
status_t ejecutar_memoria(struct simpletron * cabeza);

/*Operaciones de entrada/salida */
status_t operacion_leer(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_escribir(int posicion_memoria, struct simpletron * cabeza);

/*Operaciones de movimiento */
status_t operacion_cargar(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_guardar(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_pcargar(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_pguardar(int posicion_memoria, struct simpletron * cabeza);

/*Operaciones aritmeticas */
status_t operacion_suma(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_resta(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_division(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_multiplicar(int posicion_memoria, struct simpletron * cabeza);

/*Operaciones de control */
status_t operacion_jmp(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_jmpneg(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_jmpzero(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_jnz(int posicion_memoria, struct simpletron * cabeza);
status_t operacion_djnz(int posicion_memoria, struct simpletron * cabeza);


/*Diccionario con los opcdes y sus funciones correspondientes */
#define EXE_CANTIDAD_DE_OPCODES 15
static const int opcodes_validos[] = {10 ,11 ,20 ,21 ,22 ,23 ,30 ,31 ,32 ,33 ,40 ,41 ,42 ,43 ,44};
typedef status_t (*funciones_opcode)(int , struct simpletron *);
static const funciones_opcode func[EXE_CANTIDAD_DE_OPCODES]={
	operacion_leer,
	operacion_escribir,
	operacion_cargar,
	operacion_guardar,
	operacion_pcargar,
	operacion_pguardar,
	operacion_suma,
	operacion_resta,
	operacion_division,
	operacion_multiplicar,
	operacion_jmp,
	operacion_jmpneg,
	operacion_jmpzero,
	operacion_jnz,
	operacion_djnz
};

#endif