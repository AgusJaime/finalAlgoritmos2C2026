#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(x,y) ((x)>(y)?(y):(x))

typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* izq;
    struct sNodo* der;
}tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol,const void* dato,unsigned tam,int cmp(const void*,const void*));
int contarAparicionesDeDatoNoClave(tArbol* arbol,const void* dato,int cmp(const void*,const void*));
int espejarArbol(tArbol* arbol);
void vaciarArbol(tArbol* arbol);
int recorrerInOrden(tArbol* arbol,void accion(const void*));
#endif // ABB_H_INCLUDED
