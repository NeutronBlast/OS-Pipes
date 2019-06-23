#ifndef PIPES_H
#define PIPES_H

typedef struct {
    int myPipe[2];
}P;

void children(char entrada[], int hijos,int length, int inicio, int op, int fin, char salida[]);

#endif // PIPES_H