#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DUPLICATE 101
typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* izq;
    struct sNodo* der;
}tNodoA;

typedef tNodoA* tArbol;


void crearArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol,const void* dato,unsigned tam,int cmp(const void*,const void*));
void vaciarArbol(tArbol* arbol);
void recorrerInOrden(tArbol* arbol,void accion(const void*,void*),void* contexto);
void mostrarArbolEnOrdenInverso(tArbol* arbol,int nivel,void accion(const void*,unsigned,void*),void* contexto);
void mostrarArbolInverso(tArbol* arbol,void accion(const void*,unsigned,void*),void* contexto);
#endif // ABB_H_INCLUDED
