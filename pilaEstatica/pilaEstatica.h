#ifndef PILAESTATICA_H_INCLUDED
#define PILAESTATICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PILA 256
#define MIN(x,y) ((x)>(y)?(y):(x))
typedef struct
{
    char vec[TAM_PILA];
    unsigned tope;
}tPila;

void crearPila(tPila* p);
int apilar(tPila* p,const void* dato,unsigned tam);
int desapilar(tPila* p,void* dato,unsigned tam);
int pilaLlena(const tPila* p,unsigned tam);
int pilaVacia(const tPila* p);
int verTope(const tPila* p,void* dato,unsigned tam);
void vaciarPila(tPila* p);
#endif // PILAESTATICA_H_INCLUDED
