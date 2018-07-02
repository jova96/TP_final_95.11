#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "etapa_entrada.h"

int main(void){
    estado_t estado;
    vtr_palabra_t * pvtr_palabra;
    parametro_t parametro;
    size_t posc;

    parametro.largo = 20;
    parametro.nombre_archivo = "suma.lms";
    parametro.frmt_archivo_entrada = FRMT_TXT;
    parametro.frmt_archivo_salida = FRMT_TXT;

    estado = leer_archivo_de_palabras(&pvtr_palabra,&parametro);
    if(estado != ST_OK){
        puts("ERROR EN LA LECTURA DEL ARCHIVO");
        return EXIT_FAILURE;
    }
    for(posc = 0;posc < parametro.largo;posc++){
        printf("en la posicion%2lu: %i\n",posc,(pvtr_palabra->vtr_palabra)[posc]);
    }
    vector_destruir(&pvtr_palabra);
    return EXIT_SUCCESS;
}



/** esta funcion saca la informacion del archivo (palabras) y las guarda en un vector **/
/** validar antes de guardar **/

estado_t leer_archivo_de_palabras(vtr_palabra_t ** ppvtr_palabra,parametro_t * ptr_parametro){
    vtr_palabra_t * pvtr_palabra;
    FILE * archivo;
    char cadena_ingreso[MAX_LARGO_INGRESO],*cadena_limpia;
    estado_t estado;
    size_t posc;
    int palabra;
    int high_byte,low_byte;

    if(ppvtr_palabra == NULL || ptr_parametro == NULL){
        return ST_PTR_NULO;
    }
    pvtr_palabra = vector_crear(ptr_parametro->largo);
    if(pvtr_palabra == NULL){
        return ST_NO_MEMORIA;
    }
    if(ptr_parametro->frmt_archivo_entrada == FRMT_TXT){
        archivo = fopen(ptr_parametro->nombre_archivo,"r");
        if(archivo == NULL){
            vector_destruir(&pvtr_palabra);
            return ST_ERROR_ABRIR_ARCHIVO;
        }
        for( estado = ST_OK,posc = 0;estado == ST_OK;posc++){
            if(fgets(cadena_ingreso,MAX_LARGO_INGRESO,archivo) != NULL){
                estado = limpiar_cadena(cadena_ingreso,&cadena_limpia);
                if(estado == ST_OK){
                    estado = convertir_cadena_palabra(cadena_limpia,&palabra);
                    free(cadena_limpia);
                    cadena_limpia = NULL;
                    if(estado == ST_OK){
                        estado = vector_guardar(pvtr_palabra,palabra,posc);
                        if(estado != ST_OK){
                            estado = ST_ERROR_GUARDAR_PALABRA;
                        }
                    }
                    else{
                        estado = ST_ERROR_CONVERTIR_CADENA;
                    }
                }
                else{
                    estado = ST_ERROR_LIMPIAR_CADENA;
                }
            }
            else{
                estado = ST_SALIR_CICLO;
            }
        }
    }
    else if(ptr_parametro->frmt_archivo_entrada == FRMT_BIN){
           archivo = fopen(ptr_parametro->nombre_archivo,"rb");
            if(archivo == NULL){
            vector_destruir(&pvtr_palabra);
            return ST_ERROR_ABRIR_ARCHIVO;
            }
            for(estado = ST_OK,posc = 0;estado == ST_OK;posc++){
                if(fread(&high_byte,sizeof(char),1,archivo)){
                    if(fread(&low_byte,sizeof(char),1,archivo)){
                        palabra &= ~MASK_OPERANDO;
                        palabra |= (low_byte << SHIFT_OPERANDO);
                        palabra &= ~MASK_OPCODE;
                        palabra |= (high_byte << SHIFT_OPCODE);
                        palabra &= (MASK_OPCODE | MASK_OPERANDO);
                        estado = vector_guardar(pvtr_palabra,palabra,posc);
                        if(estado != ST_OK){
                            estado = ST_ERROR_GUARDAR_PALABRA;
                        }
                    }
                    else{
                        estado = ST_ERROR_PALABRA_INCOMPLETA;
                    }
                }
                else{
                    estado = ST_SALIR_CICLO;
                }

            }
    }
    else{
        vector_destruir(&pvtr_palabra);
        return ST_ERROR_FRMT_INVALIDO;
    }
    --posc;
    if( estado == ST_SALIR_CICLO){
        if(feof(archivo)){
            fclose(archivo);
            if(!posc){
                vector_destruir(&pvtr_palabra);
                return ST_ARCHIVO_VACIO;
            }
            *ppvtr_palabra = pvtr_palabra;
            return ST_OK;
        }
    }
    fclose(archivo);
    vector_destruir(&pvtr_palabra);
    return estado;
}


estado_t convertir_cadena_palabra(char * cadena,int * ptr_palabra){
    int palabra_aux;
    int opcode,operando;
    char * ptr_cfinal;

    if(ptr_palabra == NULL || cadena == NULL){
        return ST_PTR_NULO;
    }
    palabra_aux = strtol(cadena,&ptr_cfinal,10);
    if(*ptr_cfinal != '\0'){
        return ST_ERROR_CONVERTIR_CADENA;
    }
    if(palabra_aux < MIN_VALOR_PALABRA || palabra_aux > MAX_VALOR_PALABRA){
        return ST_ERROR_PALABRA_FUERA_DE_RANGO;
    }
    /*ya se sabe qeu es mayor al minimo*/
    if(palabra_aux < 0){
        *ptr_palabra = palabra_aux;
        return ST_OK;
    }
    opcode = palabra_aux/10000;
    operando = palabra_aux%10000;
    if(opcode > MAX_VALOR_OPCODE || operando > MAX_VALOR_OPERANDO){
        return ST_ERROR_PALABRA_FUERA_DE_RANGO;
    }
    palabra_aux &= (~MASK_OPCODE);
    palabra_aux |= (opcode << SHIFT_OPCODE);
    palabra_aux &= (~MASK_OPERANDO);
    palabra_aux |= (operando << SHIFT_OPERANDO);
    palabra_aux &= (MASK_OPCODE | MASK_OPERANDO);
    *ptr_palabra = palabra_aux;

    return ST_OK;

}

estado_t limpiar_cadena(char * cadena_sucia,char ** cadena_limpia){
    char * ptr_inicio , * ptr_final,*cadena_modificada;

    ptr_final = strchr(cadena_sucia,'\n');
    if(ptr_final != NULL){
        *ptr_final = '\0';
    }
    for(ptr_inicio = cadena_sucia;isspace(*ptr_inicio) && *ptr_inicio != '\0';ptr_inicio++)
                    {}
    if( (*ptr_inicio) == '\0' ){
        return ST_CADENA_VACIA;
    }
    for(ptr_final = cadena_sucia + strlen(cadena_sucia) - 1;
        isspace(*ptr_final) && ptr_inicio != ptr_final ;ptr_final--)
                    {}
    *(++ptr_final) = '\0';
    cadena_modificada =(char *)calloc(ptr_final - ptr_inicio + 1,sizeof(char));
    if(cadena_modificada == NULL){
        return ST_NO_MEMORIA;
    }
    memcpy(cadena_modificada,cadena_sucia,ptr_final - ptr_inicio + 1);
    *cadena_limpia = cadena_modificada;
    return ST_OK;
}
