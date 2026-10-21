#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
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

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarMejoresNLista(tLista* lista,const void* dato,unsigned tam,int n,int cmp(const void*,const void*));
void vaciarLista(tLista* lista);


#endif // LISTA_H_INCLUDED
