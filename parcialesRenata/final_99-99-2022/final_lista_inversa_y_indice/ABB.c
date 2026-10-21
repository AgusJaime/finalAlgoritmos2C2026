#include "ABB.h"

void crearArbol(tArbol* arbol)
{
    (*arbol)=NULL;
}
int insertarEnArbol(tArbol* arbol,const void* dato,unsigned tam,int cmp(const void*,const void*))
{
    if(!(*arbol))
    {
        (*arbol)=(tNodoA*)malloc(sizeof(tNodoA));
        if(!(*arbol))
            return 0;
        (*arbol)->dato=malloc(tam);
        if(!(*arbol)->dato)
        {
            free((*arbol));
            return 0;
        }
        memcpy((*arbol)->dato,dato,tam);
        (*arbol)->tam=tam;
        (*arbol)->izq=NULL;
        (*arbol)->der=NULL;
        return 1;
    }

    if(cmp((*arbol)->dato,dato)>0){
        return insertarEnArbol(&(*arbol)->izq,dato,tam,cmp);
    }
    else if(cmp((*arbol)->dato,dato)<0)
        return insertarEnArbol(&(*arbol)->der,dato,tam,cmp);
    else
        return DUPLICATE;
}
void vaciarArbol(tArbol* arbol)
{
    if(!(*arbol))
        return;

    vaciarArbol(&(*arbol)->izq);
    vaciarArbol(&(*arbol)->der);
    free((*arbol)->dato);
    free((*arbol));
    (*arbol)=NULL;
}

void recorrerInOrden(tArbol* arbol,void accion(const void*,void*),void* contexto)
{
    if(!(*arbol))
        return;
    recorrerInOrden(&(*arbol)->izq,accion,contexto);
    accion((*arbol)->dato,contexto);
    recorrerInOrden(&(*arbol)->der,accion,contexto);
}

void mostrarArbolInverso(tArbol* arbol,void accion(const void*,unsigned,void*),void* contexto)
{
    mostrarArbolEnOrdenInverso(arbol,0,accion,contexto);
}

void mostrarArbolEnOrdenInverso(tArbol* arbol,int nivel,void accion(const void*,unsigned,void*),void* contexto)
{
    if(!(*arbol))
        return;

    mostrarArbolEnOrdenInverso(&(*arbol)->der,nivel,accion,contexto);
    accion((*arbol)->dato,nivel,contexto);
    mostrarArbolEnOrdenInverso(&(*arbol)->izq,nivel,accion,contexto);
}
