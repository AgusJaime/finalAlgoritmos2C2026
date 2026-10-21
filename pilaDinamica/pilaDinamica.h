#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED
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

typedef tNodo* tPila;


void crearPila(tPila* pila);
int apilar(tPila* pila,const void* dato,unsigned tam);
int desapilar(tPila* pila,void* dato,unsigned tam);
int verTope(const tPila* pila,void* dato,unsigned tam);
int pilaLlena(const tPila* pila,unsigned tam);
int pilaVacia(const tPila* pila);
void vaciarPila(tPila* pila);
#endif // PILADINAMICA_H_INCLUDED
