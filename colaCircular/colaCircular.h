#ifndef COLACIRCULAR_H_INCLUDED
#define COLACIRCULAR_H_INCLUDED
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

typedef tNodo* tColaC;

void crearColaCircular(tColaC* cola);
int encolarCircularmente(tColaC* cola,const void* dato,unsigned tam);
int desencolarCircularmente(tColaC* cola,void* dato,unsigned tam);
int colaCircularLlena(const tColaC* cola,unsigned tam);
int colarCircularVacia(const tColaC* cola);
int verPrimeroCircularmente(const tColaC* cola,void* dato,unsigned tam);
void vaciarColaCircular(tColaC* cola);

#endif // COLACIRCULAR_H_INCLUDED
