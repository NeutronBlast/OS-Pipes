#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef MANEJO_ARCHIVOS_H
#define MANEJO_ARCHIVOS_H

void seek (char * nombre, char texto[], int inicio,int fin);

void llenarVector(FILE *e, char texto []);

void abrirArchivoEntrada (char * nombre, char texto[]);

void replace (char * nombre, char texto[]);

#endif // MANEJO_ARCHIVOS_H