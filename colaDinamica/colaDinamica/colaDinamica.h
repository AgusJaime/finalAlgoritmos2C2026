#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(x,y) ((x)>(y)?(y):(x))

typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

typedef struct
{
    tNodo* pri;
    tNodo* ult;
}tCola;

void crearCola(tCola* cola);
int encolar(tCola* cola,const void* dato,unsigned tam);
int desencolar(tCola* cola,void* dato,unsigned tam);
int colaLlena(const tCola* cola,unsigned tam);
int colaVacia(const tCola* cola);
int verPrimero(const tCola* cola,void* dato,unsigned tam);
void vaciarCola(tCola* cola);


#endif // COLADINAMICA_H_INCLUDED
