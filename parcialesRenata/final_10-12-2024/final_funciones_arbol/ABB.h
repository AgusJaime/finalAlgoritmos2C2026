#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MIN(x,y)((x)>(y)?(y):(x))
#define DUPLICATE 101

typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* izq;
    struct sNodo* der;
}tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* arbol);
//ITEM A
int insertarEnArbol(tArbol* arbol,const void* dato,unsigned tam,int cmp(const void*,const void*));
// ITEM B
int contarNodosDeXNivel(tArbol* arbol,int nivel);
// ITEM C
int esCompletoXNivel(tArbol* arbol,int nivel);
#endif // ABB_H_INCLUDED
