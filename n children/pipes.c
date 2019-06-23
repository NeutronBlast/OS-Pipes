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

void children(char entrada[], int hijos, int length, int inicio, int op, int fin, char salida[]){
    /*Inicio indica donde va a iniciar cada hijo al cifrar el texto*/
    pid_t child_pid,wpid;
    P pipes[2*hijos];
    char placeholder[1000];
    char text[1000];
    char final[1000]="";
    int status = 0;
	int mult = 1; //Multiplicador
	fin = (mult*(length/hijos))-1;

    //printf("Voy a crear %d pipes\n",2*hijos);
    for (int progress=0; progress<2*hijos; progress++){
        if (pipe(pipes[progress].myPipe)<0){
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    //printf("Texto inicial es %s\n", entrada);

    for (int progress=0; progress<hijos; progress++) {
        fin = (mult*(length/hijos))-1;


        if (progress+1 == hijos){
        /*La ultima division termina cuando se termine el texto en lugar de seguir la formula*/
			fin = length;
        }

        child_pid = fork();

        if (child_pid<0){
            perror("Hubo error al hacer el fork\n");
            exit(1);
        }

        else if (child_pid>0){
        //    printf("Numero de caracteres %d\n", fin-inicio);
            strncpy(placeholder,entrada+inicio,(fin-inicio)+1);
        //    printf("Parte de texto es %s\n",placeholder);
            close(pipes[progress*2].myPipe[0]);
            write(pipes[progress*2].myPipe[1], placeholder, sizeof(placeholder)+1);
        }

        else if (child_pid == 0) {

        //printf("child pid %d   parent pid %d\n",getpid(),getppid());fflush(stdout);

        //Cierro pipe de escritura en el hijo
        close(pipes[progress*2].myPipe[1]);
        int k = read(pipes[progress*2].myPipe[0], text, 1000);
        text[k] = 0;

         if (op == 1){
            desencriptarM(text,0,strlen(text));
        }

        else if (op == 2){
            encriptar(text,0,strlen(text));
        }
    
        //printf("Parte de texto encriptada es %s\n",text);
        close(pipes[(progress*2)+1].myPipe[0]);
        write(pipes[(progress*2)+1].myPipe[1], text, sizeof(text)+1);
        exit(0);

    }
	inicio = fin+1;
	mult++;
    }
while ((wpid = wait(&status)) > 0){
//
}
     for (int progress=0; progress<hijos; progress++) {
        close(pipes[(progress*2)+1].myPipe[1]);
        int k = read(pipes[(progress*2)+1].myPipe[0], text, sizeof(text)+1);
        text[k] = 0;
    //    printf("text %s\n",text);
        strcat(final,text);
    }

    //printf("padre antes de encriptar en M %s\n", final);

    if (op == 1){
        desencriptar(final,0,strlen(final));
    }

    else{
        encriptarM(final,0,strlen(final));
    }
    
    //printf("Padre texto es %s\n",final);
    replace(salida,final);
}

