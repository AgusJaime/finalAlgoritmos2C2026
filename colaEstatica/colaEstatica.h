#ifndef COLAESTATICA_H_INCLUDED
#define COLAESTATICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_COLA 256 // cant*(sizeof(unsigned)+cantBytes)
#define INICIO 0
#define MIN(x,y) ((x)>(y)?(y):(x))
typedef struct
{
    char vec[TAM_COLA];
    unsigned tamDisp,pri,ult;
}tCola;

void crearCola(tCola* cola);
int encolar(tCola* cola,const void* dato,unsigned tam);
int desencolar(tCola* cola,void* dato,unsigned tam);
int verPrimero(const tCola* cola,void* dato,unsigned tam);
int colaLlena(const tCola* cola,unsigned tam);
int colaVacia(const tCola* cola);
void vaciarCola(tCola* cola);


#endif // COLAESTATICA_H_INCLUDED
