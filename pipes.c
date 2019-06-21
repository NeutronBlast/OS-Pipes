#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/time.h>
#include "encript.h"
#include "decypher.h"
#include "pipes.h"
#include "manejoArchivos.h"

void children(char entrada[], int length, int inicio, int op, int fin, char salida[]){
    /*Inicio indica donde va a iniciar cada hijo al cifrar el texto*/
    pid_t child_pid[100], wpid;
    char placeholder[1000];
    char final[1000]="";
    int status = 0;
    int pipes[2*2]; //2*numPipes
	int mult = 1; //Multiplicador
	fin = (mult*(length/2))-1;

    for (int progress=0; progress<2; progress++){
        if (pipe(pipes + progress*2)<0){
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int progress=0; progress<2; progress++) {
        if (progress > 0) fin = (mult*(length/2))-1;

        child_pid[progress] = fork();

        if (child_pid[progress]<0){
            perror("Hubo error al hacer el fork\n");
            exit(1);
        }

        if (child_pid[progress] == 0) {
        //printf("Pipe # %d\n", (progress*2)+0);
        close(pipes[(progress*2)]);
        fin = (mult*(length/2))-1;

        printf("child pid %d   parent pid %d\n",getpid(),getppid());fflush(stdout);
        printf("Hijo comienza en %d , termina en %d , con multiplicador %d\n", inicio, fin ,mult);

        if (progress+1 == 2){
        /*La ultima division termina cuando se termine el texto en lugar de seguir la formula*/
			fin = length;
        }

        if (op == 1){
            seek(entrada,placeholder,inicio,fin);
            desencriptarM(placeholder,0,fin-inicio);
        }

        else if (op == 2){
        /*Encriptar en cesar*/
            seek(entrada,placeholder,inicio,fin);
            encriptar(placeholder,0,fin-inicio);
        }
    
        write(pipes[(progress*2)+1], placeholder, sizeof(placeholder)+1);

        printf("Parte de texto encriptada es %s\n",placeholder);
        exit(0);

    }
	inicio = fin+1;
	mult++;
    }

while ((wpid = wait(&status)) > 0); // El padre espera que todos los procesos hijos terminen para poder generar el archivo final
    for (int progress=0; progress<2; progress++) {
        close(pipes[(progress*2)+1]);
        int k = read(pipes[(progress*2)], placeholder, sizeof(placeholder)+1);
        strcat(final,placeholder);
    }


    if (op == 1){
        desencriptar(final,0,length);
    }

    else{
        encriptarM(final,0,length);
    }
    
    printf("Padre texto es %s\n",final);
    replace(salida,final);
}
