#ifndef LISTASIMPLE_H_INCLUDED
#define LISTASIMPLE_H_INCLUDED
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
int insertarNenLista(tLista* lista,const void* dato,unsigned tam,int n,int cmp(const void*,const void*));
int insertarOrdenadamente(tLista* lista,const void* dato,unsigned tam,int cmp(const void*,const void*));
int eliminarOcurrencia(tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int eliminarPrimero(tLista* lista,void* dato,unsigned tam);
void vaciarLista(tLista* lista);


#endif // LISTASIMPLE_H_INCLUDED
