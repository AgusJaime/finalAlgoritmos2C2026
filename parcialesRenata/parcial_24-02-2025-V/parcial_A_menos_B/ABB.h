#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y) ((x)>(y)?(y):(x))
#define DUPLICADO 2
typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* izq;
    struct sNodo* der;
}tNodo;

typedef tNodo* tArbol;


void crearArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol, const void* dato,unsigned tam,int cmp(const void*,const void*),void accion(const void*,void*));
int eliminarRaiz(tArbol* arbol);
int eliminarDato(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*));
int buscarDato(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*));
void vaciarArbol(tArbol* arbol);
int alturaArbol(tArbol* arbol);



#endif // ABB_H_INCLUDED
