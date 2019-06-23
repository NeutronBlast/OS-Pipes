#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "manejoArchivos.h"

void llenarVector(FILE *e, char texto []) {
        fgets(texto, 1000, e);
 fclose(e);
}

void abrirArchivoEntrada (char * nombre, char texto[]){
    FILE *e;
    e = fopen(nombre, "r");
			if (e == NULL) 
				/*Si hay errores en el archivo*/
			{
                perror("No fue posible abrir el archivo de entrada\n");
                exit(0);
			}
            else { 
                //printf("Archivo cargado con exito\n");    
                llenarVector(e,texto);
            }
}

void replace (char * nombre, char texto[]){
    FILE *e;
    e = fopen(nombre, "w");
    		if (e == NULL) 
				/*Si hay errores en el archivo*/
			{
                perror("No fue posible abrir el archivo de entrada\n");
                exit(0);
			}
			if (e != NULL) 
			{
				//int f = removeSpace(texto,strlen(texto));
                fprintf(e,"%s",texto);
			}
    fclose(e);
    }
