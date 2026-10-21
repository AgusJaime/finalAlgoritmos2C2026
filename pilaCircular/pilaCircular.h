#ifndef PILACIRCULAR_H_INCLUDED
#define PILACIRCULAR_H_INCLUDED
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

typedef tNodo* tPilaC;

void crearPilaCircular(tPilaC* pila);
int apilarCircularmente(tPilaC* pila,const void* dato,unsigned tam);
int desapilarCircularmente(tPilaC* pila,void* dato,unsigned tam);
int pilaCircularLlena(const tPilaC* pila,unsigned tam);
int pilaCircularVacia(const tPilaC* pila);
int verUltimoCircularmente(const tPilaC* pila,void* dato,unsigned tam);
void vaciarPilaCircular(tPilaC* pila);


#endif // PILACIRCULAR_H_INCLUDED
