#include "estados_programa.h"

void imprimir_mensajes_error(status_t estado){
	switch(estado){
		/************** MSJ ARGUMENTOS ****************/
		/*Mensajes relacionados con la memoria */
        case ARG_MEMORIA_NO_ESPECIFICADA:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_MEMORIA_NO_ESPECIFICADA);
            break;
        case ARG_MEMORIA_INV:
            fprintf(stderr,"%s : %s \n",MSJ_ARG_ERROR ,MSJ_ARG_ERROR_MEMORIA_INV);
            break;
        case ARG_MEMORIA_NEGATIVA:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_MEMORIA_NEG);
            break;
        
        /*Mensajes relacionados con el formato de salida */
        case ARG_FORMATO_SALIDA_NO_ESPECIFICADO:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR, MSJ_ARG_ERROR_SALIDA_FORMATO_NO_ESP);
            break;
        case ARG_FORMATO_SALIDA_INV:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_SALIDA_FORMATO_INV);
            break;
        
        /*Mensajes relacionados con la entrada del programa */
        case ARG_STDIN_VERDADERO:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_ENTRADA_STDIN);
            break;
        case ARG_NOMBRE_NO_ESPECIFICADO:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_ENTRADA_NOMBRE_NO_ESP);
            break;
        case ARG_ARCHIVO_YA_INGRESADO:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_ENTRADA_ARCHIVO);
            break;
        
        /*Mensaje en caso de falta de memoria */
        case ARG_NULL:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_MEMORIA_DIN);
            break;
        
        /*Argumento invalido */
        case ARG_NO_VALIDO:
            fprintf(stderr,"%s : %s \n", MSJ_ARG_ERROR , MSJ_ARG_ERROR_NO_VALIDO);
            break;

		/************************MSJ ENTRADA *********************/
		case INP_MEMORIA_INSF:
			fprintf(stderr , "%s : %s \n", MSJ_INP_ERROR , MSJ_INP_MEMORIA_INSF);
			break;
		case INP_LISTA_NULL:
			fprintf(stderr , "%s : %s \n", MSJ_INP_ERROR , MSJ_INP_ERROR_LISTA_NULL);
			break;
		case INP_PALABRA_INV:
			fprintf(stderr , "%s : %s \n", MSJ_INP_ERROR , MSJ_INP_ERROR_PALABRA_INV);
			break;
		case INP_PALABRA_FUERA_RANGO:
			fprintf(stderr , "%s : %s \n", MSJ_INP_ERROR , MSJ_INP_ERROR_PALABRA_RANGO);
			break;
		case INP_ARCHIVO_INV:
			fprintf(stderr , "%s : %s \n",MSJ_INP_ERROR , MSJ_INP_ERROR_ARCHIVO);
			break;

		/******************* MSJ EJECUCION *************************/
		case EXE_OPCODE_INV:
			fprintf(stderr , "%s : %s \n", MSJ_EXE_ERROR , MSJ_EXE_ERROR_OPCODE_INV);
			break;
		case EXE_MEMORIA_FUERA_RANGO:
			fprintf(stderr , "%s : %s \n", MSJ_EXE_ERROR , MSJ_EXE_ERROR_MEMORIA_RANGO);
			break;
		case EXE_ERROR_ENTRADA:
			fprintf(stderr , "%s : %s \n", MSJ_EXE_ERROR , MSJ_EXE_ERROR_ENTRADA);
			break;
		case EXE_NULL:
			fprintf(stderr, "%s : %s \n",MSJ_EXE_ERROR, MSJ_EXE_ERROR_NULL);
			break;
		
		/*Si todo salio bien */
		case OK:
			break;
	}
}