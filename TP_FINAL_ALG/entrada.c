#include "entrada.h"

status_t validar_palabra(char * palabra_ingresada , int * palabra_convertida){
	int i = 0;
	char * puntero_validar = NULL;

	/*Convierte la palabra a int  */
	*palabra_convertida = strtol(palabra_ingresada , &puntero_validar , 10);

	/*Empiezan las validaciones del a palabra ingresada */
	/*Si se ingreso un numero */
	if(puntero_validar != NULL){
		if(*puntero_validar != '\n' && *puntero_validar != '\0'){
			while(puntero_validar[i] != ';'){
				if(puntero_validar[i] != ' '){
					return INP_PALABRA_INV;
				}
				i++;
			}
		}
	}

	/*Si se ingresa un valor mayor a 8 digitos */
	if(*palabra_convertida < ST_INP_LIMITE_PALABRA_INF || *palabra_convertida > ST_INP_LIMITE_PALABRA_SUP){
		return INP_PALABRA_FUERA_RANGO;
	}

	return OK;
}

status_t seleccionar_entrada(contenedor_de_argumentos_t * info , lista_t ** vector_lista){
	int i;
	status_t estado_entrada;

	/*Creo la memoria para almacenar las palabras de entrada por consola*/
	if(info->entrada_stdin == VERDADERO){
		*vector_lista = (lista_t *) malloc(sizeof(lista_t));

		/*Si hubo un error con la asignacion de memoria */
		if(*vector_lista == NULL){
			return INP_LISTA_NULL;
		}

		/*Llamo a la funciond e entrada por consola, cualquier error lo retornara */
		estado_entrada = entrada_consola(*vector_lista, info->memoria);

		/*Si hubo un error , libera la memoria utilizada para la lista */
		if(estado_entrada != OK){
			liberar_lista(*vector_lista);
			free(*vector_lista);
		}

		/*Devuelve el estado de la funcion */
		return estado_entrada;
	}

	else{
		/*La entrada es por archivo, entonces creo x cantidad de listas
		para almacenar las palabras de cada archivo */
		*vector_lista = (lista_t *) malloc(sizeof(lista_t) * info->cantidad_de_archivos);

		/*Si hubo un error con la asignacion de memoria */
		if(*vector_lista == NULL){
			return INP_LISTA_NULL;
		}

		/*Itero para cada archivo */
		for(i = 0; i < info->cantidad_de_archivos; i++){
			(*vector_lista)[i] = inicializar_lista();

			/*Si es un archivo de txt */
			if(info->tipo_archivos_entrada[i] == TXT){
				/*Llamo a la funcion archivo entrada */
				estado_entrada = entrada_archivo_txt(&(*vector_lista)[i] , info->nombres_archivos_entrada[i], info->memoria);

				/*Si hay un error, libera la mememoria usada para las listas */
				if(estado_entrada != OK){

					for(i = 0; i < info->cantidad_de_archivos;i++){
						liberar_lista(&(*vector_lista)[i]);
					}
					free(*vector_lista);

					/*Devuelve el estado */
					return estado_entrada;
				}
			}

			/*Si es un archivo bin */
			else if(info->tipo_archivos_entrada[i] == BIN){
				estado_entrada = entrada_archivo_bin(&(*vector_lista)[i] , info->nombres_archivos_entrada[i], info->memoria);
				if(estado_entrada != OK){
                    for(i = 0; i < info->cantidad_de_archivos;i++){
						liberar_lista(&(*vector_lista)[i]);
					}
					free(*vector_lista);
                    return estado_entrada;
				}
			}
		}
	}

	return OK;
}

status_t entrada_consola(lista_t * lista_cargar, int memoria_disponible){
	int i = 0;
	char palabra_ingresada[ST_INP_MAXIMO_ENTRADA_PALABRA];
	int palabra_convertida;
	status_t estado_conversion;

	/*********** NO TE OLVIDEA HARCODE ************/
	printf("Ingreso por consola : \n");

	do{
		/*Si se sobrepasa el limite de memoria, devuelve error */
		if(lista_cargar->largo >= memoria_disponible){
			return INP_MEMORIA_INSF;
		}

		printf("%.2i:" , i);
		fgets(palabra_ingresada , ST_INP_MAXIMO_ENTRADA_PALABRA , stdin);

		/*Si es igual al valor de salida, sale del ciclo */
		if(strcmp(palabra_ingresada,ST_INP_VALOR_SALIDA_CONSOLA) == 0){
			return OK;
		}

		/*Valido si hay algun error en la palabra, si hay, devuelve el error */
		estado_conversion = validar_palabra(palabra_ingresada , &palabra_convertida);

		if(estado_conversion != OK){
			return estado_conversion;
		}

		/*Finalmente agrego a la lista la palabra */
		agregar_al_final(lista_cargar , palabra_convertida);
		i++;

	}while(strcmp(palabra_ingresada, ST_INP_VALOR_SALIDA_CONSOLA) != 0);
	while(i < memoria_disponible){
        agregar_al_final(lista_cargar,0);
        i++;
    }

	return OK;
}

status_t entrada_archivo_txt(lista_t * lista_cargar , char * nombre_archivo, int memoria_disponible){
	FILE * puntero_archivo;
	char palabra_ingresada[ST_INP_MAXIMO_ENTRADA_PALABRA];
	int palabra_convertida;
	status_t estado_conversion;
	size_t var_aux = 0;

	puntero_archivo = fopen(nombre_archivo , "rt");

	/*Si no se encontro el archivo, devuelve error */
	if(puntero_archivo == NULL){
		return INP_ARCHIVO_INV;
	}

	while(fgets(palabra_ingresada , ST_INP_MAXIMO_ENTRADA_PALABRA , puntero_archivo)){
		/*Si se sobrepasa el limite de memoria, devuelve error */
		if(lista_cargar->largo >= memoria_disponible){
			return INP_MEMORIA_INSF;
		}

		/*Si hay un error en la validacion, devuelve error */
		estado_conversion = validar_palabra(palabra_ingresada , &palabra_convertida);

		if(estado_conversion != OK){
			return estado_conversion;
		}

		/*Si se sobrepasa el limite de memoria, devuelve error */
		if(lista_cargar->largo >= memoria_disponible){
			return INP_MEMORIA_INSF;
		}

		/*Finalmente agrego a la lista la palabra */
		var_aux++;
		agregar_al_final(lista_cargar , palabra_convertida);
	}

    if(feof(puntero_archivo)){
        fclose(puntero_archivo);
        while(var_aux < memoria_disponible){
            agregar_al_final(lista_cargar,0);
            var_aux++;
        }
        return OK;
    }
    fclose(puntero_archivo);
    return estado_conversion;
}

status_t entrada_archivo_bin(lista_t * lista_cargar , char * nombre_archivo, int memoria_disponible){
    FILE * archivo;
    char high_byte,low_byte;
    int palabra_convertida;
    status_t estado;
    size_t var_aux;

    if(lista_cargar == NULL || nombre_archivo == NULL){
        return INP_LISTA_NULL;
    }
    archivo = fopen(nombre_archivo,"rb");
    if(archivo == NULL){
        return INP_ARCHIVO_INV;
    }
    if(lista_cargar->largo >= memoria_disponible){
        return INP_MEMORIA_INSF;
    }
    estado = OK;
    var_aux = 0;
    while(estado == OK){
        if(fread(&high_byte,sizeof(char),1,archivo)){
            if(fread(&low_byte,sizeof(char),1,archivo)){
                palabra_convertida = (high_byte * 10000) + low_byte;
                if(palabra_convertida > ST_INP_LIMITE_PALABRA_SUP ||
                   palabra_convertida < ST_INP_LIMITE_PALABRA_INF){
                    return INP_PALABRA_FUERA_RANGO;
                }
                var_aux++;
                agregar_al_final(lista_cargar , palabra_convertida);
            }
            else{
                estado = INP_PALABRA_INV;
            }
        }
        else{
            estado = SALIR;
        }
    }
    if( estado == SALIR){
        if(feof(archivo)){
            fclose(archivo);
            while(var_aux < memoria_disponible){
                agregar_al_final(lista_cargar,0);
                var_aux++;
            }
            return OK;
        }
    }
    fclose(archivo);
    return estado;
}
