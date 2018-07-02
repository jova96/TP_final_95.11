#include "ejecutar.h"


bool_t validar_dir_memoria(lista_t * memoria_programa){
	nodo_t * nodo_aux;
	int i;

	for(i = 0; i < memoria_programa->largo; i++){
		nodo_aux = buscar_posicion_lista(memoria_programa, i);

		/*Si llega al HALT no nos importa las palabras que siguen */
		if(nodo_aux->valor / EXE_DIVISOR == EXE_OPERADOR_HALT){
			return VERDADERO;
		}

		/*Si la direccion de memoria es mayor al largo de la lista  devuelve error*/
		if((nodo_aux->valor % EXE_DIVISOR) >= memoria_programa->largo){
			return FALSO;
		}
	}
	return FALSO;
}

status_t ejecutar_memoria( struct simpletron * cabeza){
	int i;
	nodo_t * nodo_aux;
	int direccion_memoria;
	int opcode;
	status_t estado_exe = EXE_OPCODE_INV;

	/*Valida que ninguna memoria de la palabra este fuera de rango */
	if(validar_dir_memoria(cabeza->memoria) == FALSO){
		return EXE_MEMORIA_FUERA_RANGO;
	}

	while(1){

		/*Saca el opcode y direccion de memoria de la palabra */
		nodo_aux = buscar_posicion_lista(cabeza->memoria,cabeza->contador);
		cabeza->registro = nodo_aux->valor;
		direccion_memoria = nodo_aux->valor % EXE_DIVISOR;
		opcode = nodo_aux->valor / EXE_DIVISOR;

		if(opcode == EXE_OPERADOR_HALT){
			return OK;
		}

		/*Compara con cada uno de los opcodes para ejecutar la funcion correspondiente */
		for(i = 0; i < EXE_CANTIDAD_DE_OPCODES; i++){
			if(opcode == opcodes_validos[i]){
				estado_exe = func[i](direccion_memoria, cabeza);
			}
		}

		/*Si la funcion devuelve un error o simplemente el opcode es invalido, devuelve el error */
		if(estado_exe != OK){
			return estado_exe;
		}
	}
}

status_t operacion_leer(int posicion_memoria , struct simpletron * cabeza){
	char * palabra_ingresada;
	char * puntero_validar;
	int palabra_convertida;
	nodo_t * nodo_guardar;

	palabra_ingresada = (char *) malloc(sizeof(char) * EXE_MAXIMO_LARGO_ENTRADA);
	if(palabra_ingresada == NULL){
		return EXE_NULL;
	}

	printf("%s ",EXE_MSJ_OPERACION_LEER);
	fgets(palabra_ingresada,EXE_MAXIMO_LARGO_ENTRADA, stdin);

	palabra_convertida = strtol(palabra_ingresada , &puntero_validar, 10);

	/*Si se ingreso un valor invalido */
	if(puntero_validar == NULL && (*puntero_validar != '\n' && *puntero_validar != ' ')){
		return EXE_ERROR_ENTRADA;
	}

	nodo_guardar = buscar_posicion_lista(cabeza->memoria, posicion_memoria);
	
	/*Si hay un error */
	if(nodo_guardar == NULL){
		return EXE_NULL;
	}

	nodo_guardar->valor = palabra_convertida;
	cabeza->contador++;

	free(palabra_ingresada);
	return OK;
}

status_t operacion_escribir(int posicion_memoria ,struct simpletron * cabeza){
	nodo_t * nodo_leer;

	nodo_leer = buscar_posicion_lista(cabeza->memoria , posicion_memoria);
	
	/*Si hay un error */
	if(nodo_leer == NULL){
		return EXE_NULL;
	}

	printf("%s %i : %i \n",EXE_MSJ_OPERACION_ESCRIBIR, posicion_memoria , nodo_leer->valor);
	cabeza->contador++;
	return OK;
}


status_t operacion_cargar(int posicion_memoria , struct simpletron * cabeza){
	nodo_t * nodo_aux;

	nodo_aux = buscar_posicion_lista(cabeza->memoria, posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	cabeza->acumulador = nodo_aux->valor;
	cabeza->contador++;
	return OK;
}

status_t operacion_guardar(int posicion_memoria, struct simpletron * cabeza){
	nodo_t * nodo_aux;

	nodo_aux = buscar_posicion_lista(cabeza->memoria , posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	nodo_aux->valor = cabeza->acumulador;
	cabeza->contador++;
	return OK;
}

status_t operacion_pcargar(int posicion_memoria , struct simpletron * cabeza){
	nodo_t * nodo_aux;
	int memoria2;

	nodo_aux = buscar_posicion_lista(cabeza->memoria , posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	memoria2 = nodo_aux->valor % EXE_DIVISOR;
	nodo_aux = buscar_posicion_lista(cabeza->memoria, memoria2);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	cabeza->acumulador = memoria2;
	cabeza->contador++;
	return OK;
}

status_t operacion_pguardar(int posicion_memoria , struct simpletron * cabeza){
	nodo_t * nodo_aux;
	int memoria2;

	nodo_aux = buscar_posicion_lista(cabeza->memoria , posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	memoria2 = nodo_aux->valor % EXE_DIVISOR;
	nodo_aux = buscar_posicion_lista(cabeza->memoria, memoria2);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	nodo_aux->valor = cabeza->acumulador;
	cabeza->contador++;
	return OK;
}

status_t operacion_suma(int posicion_memoria , struct simpletron * cabeza){
	nodo_t * nodo_aux;

	nodo_aux = buscar_posicion_lista(cabeza->memoria , posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	cabeza->acumulador = cabeza->acumulador + nodo_aux->valor;
	cabeza->contador++;
	return OK;
}

status_t operacion_resta(int posicion_memoria , struct simpletron * cabeza){
	nodo_t * nodo_aux;

	nodo_aux = buscar_posicion_lista(cabeza->memoria , posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	cabeza->acumulador = cabeza->acumulador - nodo_aux->valor;
	cabeza->contador++;
	return OK;
}

status_t operacion_division(int posicion_memoria , struct simpletron * cabeza){
	nodo_t * nodo_aux;

	nodo_aux = buscar_posicion_lista(cabeza->memoria , posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	cabeza->acumulador = cabeza->acumulador / nodo_aux->valor;
	cabeza->contador++;
	return OK;
}

status_t operacion_multiplicar(int posicion_memoria , struct simpletron * cabeza){
	nodo_t * nodo_aux;

	nodo_aux = buscar_posicion_lista(cabeza->memoria , posicion_memoria);

	/*Si hay un error */
	if(nodo_aux == NULL){
		return EXE_NULL;
	}

	cabeza->acumulador = cabeza->acumulador * nodo_aux->valor;
	cabeza->contador++;
	return OK;
}

status_t operacion_jmp(int posicion_memoria , struct simpletron * cabeza){

	cabeza->contador = posicion_memoria;
	return OK;
}

status_t operacion_jmpneg(int posicion_memoria, struct simpletron * cabeza){
	if(cabeza->acumulador < 0){
		operacion_jmp(posicion_memoria, cabeza);
	}
	else{
		cabeza->contador++;
	}

	return OK;
}

status_t operacion_jmpzero(int posicion_memoria , struct simpletron * cabeza){
	if(cabeza->acumulador == 0){
		operacion_jmp(posicion_memoria, cabeza);
	}
	else{
		cabeza->contador++;
	}

	return OK;
}

status_t operacion_jnz(int posicion_memoria, struct simpletron * cabeza){
	if(cabeza->acumulador != 0){
		operacion_jmp(posicion_memoria, cabeza);
	}
	else{
		cabeza->acumulador++;
	}

	return OK;
}

status_t operacion_djnz(int posicion_memoria, struct simpletron * cabeza){
	cabeza->acumulador--;
	if(cabeza->acumulador != 0){
		operacion_jmp(posicion_memoria, cabeza);
	}
	else{
		cabeza->acumulador++;
	}

	return OK;
}
