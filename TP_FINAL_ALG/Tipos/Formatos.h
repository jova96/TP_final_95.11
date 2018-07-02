#ifndef FORMATOS__H
#define FORMATOS__H

typedef enum formato{
    TXT = 0,
    BIN = 1
}formato_t;

/*Diccionario de formato de archivos permitidos */
static const char * const formatos_archivos_permitidos[] = {"txt" , "bin"};

#endif