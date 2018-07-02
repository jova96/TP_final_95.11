

estado_arg_t procesar_argumentos(parametro_t ** pvtr_parametro,char * argv[],int argc){
/*para los distintos estados del proceso*/
    estado_arg_t estado_proceso;
/*los estados dela funcion como los errores*/
    estado_arg_t estado;
    size_t cant_archivo,posc,cant_palabras;
    frmt_archivo_t frmt_entrada;
    char nombre_archivo[MAX_LARGO_NOMBRE_ARCHIVO];

    if(argv == NULL || !argc){
        return ST_PTR_NULO;
    }
    for(estado_proceso = ST_PROCESAR_ARGUMENTO,estado = ST_OK,cant_archivo = 0;
        estado_proceso == ST_OK;
        poc++){

        }
    swith(estado_proceso){
        case ST_PROCESAR_ARGUMENTO:
            estado = validar_argumento
    }

}
