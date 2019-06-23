#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/time.h>
#include <locale.h>
#include "encript.h"
#include "decypher.h"
#include "manejoArchivos.h"
#include "pipes.h"

int verify(int nh, int length){
    if (nh>length)
        return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"");
    struct timeval begin, end;
    gettimeofday(&begin,NULL);
    /*Tomar los argumentos de la linea de comando*/
    int op = 0;
    int NumHijos;

    if (argc != 5){
        printf("Mal uso de argumentos\n");
        printf("Ejemplo de uso correcto: ./cript_p -c/-d NumHijos ArchivoEntrada, ArchivoSalida\n");
        return 0;
    }

    /*Encriptar o desencriptar*/
    size_t len = strlen(argv[1]);
    char * operacion = malloc(len+2);
    strcpy(operacion, argv[1]);

    /*Verificar campo NumHijos*/
    char *en;
    NumHijos = strtol(argv[2], &en,  10);
        if (NumHijos == 0){
            printf("Numero de hijos debe ser un numero entero positivo mayor a 0\n");
            return 0;
        }

        else if (NumHijos<0){
            printf("Numero de hijos debe ser un numero entero positivo mayor a 0\n");
            return 0;
        }
        
    len = strlen(argv[3]);
    /*Nombre archivo de entrada*/
    char * file1 = malloc(len+5);
    strcpy(file1, argv[3]);
    strcat(file1,".txt");

    len = strlen(argv[4]);
    /*Nombre archivo de salida*/
    char * file2 = malloc(len+10);
    strcpy(file2, argv[4]); 
    strcat(file2,".txt");  

    /*Texto a encriptar o desencriptar*/
    char vector [1000];

    abrirArchivoEntrada(file1, vector);

    int length = strlen(vector);
    

    if (operacion[1] == 'd'){
        /*Toca desencriptar*/
        op = 1;
    }

    else if (operacion[1] == 'c'){
        /*Toca encriptar*/
        op = 2;
    }

    else {
        printf("Argumento 1 %s incorrecto, uso: -c o -d,",operacion);
    }

    if (op == 2)
    length = removeSpace(vector,length);

    else 
    length = strlen(vector);

    //printf("Texto luego de quitarle los espacios\n%s\n", vector);
    //printf("Longitud %d\n", length);

    int verif = verify(NumHijos,length);
        if (verif == 0){
            printf("Numero de hijos ingresado es mayor a la longitud del texto\n");
            return 0;
        }

    /*Reemplazar archivo de entrada con texto sin espacios*/

    /*Crear arbol de procesos*/
    children(vector,NumHijos,length,0,op,0,file2);
    gettimeofday(&end,NULL);
    
    printf("Fin del programa, tiempo total de ejecucion %f segundos\n", (double)(end.tv_usec - begin.tv_usec)/1000000+ (double)(end.tv_sec - begin.tv_sec)) ;
    return 0; 
}