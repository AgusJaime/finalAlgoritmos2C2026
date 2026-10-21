#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PILA 256

typedef struct
{
    char vec[TAM_PILA];
    unsigned tope;
}tPila;

void crearPila(tPila* p)
{
    (*p)=NULL;
}
int apilar(tPila* p,const void* dato,unsigned tam)
{
    if(p)
}
int desapilar(tPila* p,void* dato,unsigned tam);
int pilaLlena(const tPila* p,unsigned tam);
int pilaVacia(const tPila* p);
int verUltimo(const tPila* p,void* dato,unsigned tam);
void vaciarPila(tPila* p);
