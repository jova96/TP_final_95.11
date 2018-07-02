#include "Structs_Simpletron.h"

struct simpletron inicializar_simpletron(){
	struct simpletron nuevo;
	
	nuevo.acumulador = 0;
	nuevo.contador = 0;
	nuevo.registro = 0;
	nuevo.memoria = NULL;

	return nuevo;
}

void imprimir_simpletron(struct simpletron * imprimir_cabeza){
    
    /*SUPER HARCODEADO CUIDADO !!!!!!!!!*/
    printf("Acumulador : %i \n", imprimir_cabeza->acumulador);
    printf("Contador : %i \n",(int) imprimir_cabeza->contador);
    printf("Registro : %i \n", imprimir_cabeza->registro);
    printf("Memoria : \n");
    imprimir_lista(imprimir_cabeza->memoria);
    printf("\n\n");
}

contenedor_de_argumentos_t  inicializar_contenedor_argumentos(){
    contenedor_de_argumentos_t  msj;

    msj.ayuda = MACRO_CONTENEDOR_AYUDA_DEFAULT;
    msj.memoria = MACRO_CONTENEDOR_MEMORIA_DEFAULT;
    msj.entrada_stdin = MACRO_CONTENEDOR_STDIN_DEFAULT;
    msj.cantidad_de_archivos = 0;
    msj.nombres_archivos_entrada = NULL;
    msj.tipo_archivos_entrada = NULL;
    msj.tipo_archivo_salida = MACRO_CONTENEDOR_TIPO_SALIDA_DEFAULT;

    return msj;
}

bool_t agregar_archivo_al_contenedor(contenedor_de_argumentos_t * contenedor,formato_t fmt , char * nombre){
    contenedor->cantidad_de_archivos++;
    
    contenedor->tipo_archivos_entrada = (formato_t *) realloc( contenedor->tipo_archivos_entrada,sizeof(formato_t) * contenedor->cantidad_de_archivos);

    /*Si no hay memoria retorna falso, sino agrega el fmt */
    if(contenedor->tipo_archivos_entrada == NULL){
        return FALSO;
    }
    contenedor->tipo_archivos_entrada[contenedor->cantidad_de_archivos - 1] = fmt;

    contenedor->nombres_archivos_entrada = (char **) realloc(contenedor->nombres_archivos_entrada, sizeof(char *) * contenedor->cantidad_de_archivos);

    /*Si no hay memoria retorna falso, sino se busca memoria para agregar el nombre del archivo */
    if(contenedor->nombres_archivos_entrada == NULL){
        free(contenedor->tipo_archivos_entrada);
        return FALSO;
    }

    contenedor->nombres_archivos_entrada[contenedor->cantidad_de_archivos - 1] = (char *) malloc(sizeof(char) * contar_largo_cadena(nombre) + sizeof(char));
    if(contenedor->nombres_archivos_entrada[contenedor->cantidad_de_archivos - 1] == NULL){
        free(contenedor->tipo_archivos_entrada);
        free(contenedor->nombres_archivos_entrada);
        return FALSO;
    }

    /*Si todo sale bien, paso el nombre al archivo */
    strcpy(contenedor->nombres_archivos_entrada[contenedor->cantidad_de_archivos - 1], nombre);

    return VERDADERO;
}

void imprimir_contenedor(contenedor_de_argumentos_t * contenedor_imprimir){
    int i;

    printf("Ayuda : ");
    if(contenedor_imprimir->ayuda == VERDADERO){
        printf("VERDADERO \n");
    }
    if(contenedor_imprimir->ayuda == FALSO){
        printf("FALSO \n");
    }
    
    printf("Memoria : %i \n", (int) contenedor_imprimir->memoria);
    
    printf("Entrada STDIN : ");
    if(contenedor_imprimir->entrada_stdin == VERDADERO){
        printf("VERDADERO \n");
    }
    if(contenedor_imprimir->entrada_stdin == FALSO){
        printf("FALSO \n");
    }

    printf("Cantidad de archivos : %i \n" ,(int) contenedor_imprimir->cantidad_de_archivos);

    if(contenedor_imprimir->nombres_archivos_entrada != NULL){
        
        for( i = 0; i < contenedor_imprimir->cantidad_de_archivos; i++){
            printf("Nombre de archivo %i : %s\n" , i , contenedor_imprimir->nombres_archivos_entrada[i]);
        }

        for(i = 0; i < contenedor_imprimir->cantidad_de_archivos; i++){
            printf("Formato del archivo %i : ", i);
            if(contenedor_imprimir->tipo_archivos_entrada[i] == TXT){
                printf("TXT \n");
            }

            else if(contenedor_imprimir->tipo_archivos_entrada[i] == BIN){
                printf("BIN \n");
            }
        }
    }
    
    printf("Tipo archivo salida : ");
    if(contenedor_imprimir->tipo_archivo_salida == TXT){
        printf("TXT \n");
    }
    if(contenedor_imprimir->tipo_archivo_salida == BIN){
        printf("BIN \n");
    }

}

void liberar_contenedor_argumentos(contenedor_de_argumentos_t * arg_eliminar){
    size_t i;

    for(i = 0; i <arg_eliminar->cantidad_de_archivos; i++){
        free(arg_eliminar->nombres_archivos_entrada[i]);
    }
    free(arg_eliminar->nombres_archivos_entrada);
    arg_eliminar->nombres_archivos_entrada = NULL;

    free(arg_eliminar->tipo_archivos_entrada);
    arg_eliminar->tipo_archivos_entrada = NULL;
}