#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CUMPLE_CONDICION 10

typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarOrdenado(tLista* lista,const void* dato,unsigned tam,int cmp(const void*,const void*));
void mostrarListaRecusivaConCondicion(tLista* lista,void accion(const void*),void* contexto,int cumpleCondicion(const void*,void*));
void vaciarLista(tLista* lista);

#endif // LISTA_H_INCLUDED
