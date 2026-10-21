#include "pilaDinamica.h"


void crearPila(tPila* pila)
{
    (*pila)=NULL;
}
int apilar(tPila* pila,const void* dato,unsigned tam)
{
    tNodo* nue;
    nue=(tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;

    nue->sig=(*pila);
    (*pila)=nue;

    return 1;
}
int desapilar(tPila* pila,void* dato,unsigned tam)
{
    tNodo* elim;

    if(!(*pila))
        return 0;

    elim=(*pila);
    (*pila)=elim->sig;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);
    return 1;
}
int verTope(const tPila* pila,void* dato,unsigned tam)
{
    if(!(*pila))
        return 0;
    memcpy(dato,(*pila)->dato,MIN(tam,(*pila)->tam));
    return 1;
}
int pilaLlena(const tPila* pila,unsigned tam)
{
    tNodo* aux=(tNodo*)malloc(sizeof(tNodo));
    if(!aux)
        return 1;
    aux->dato=malloc(tam);
    if(!aux->dato)
        return 1;
    free(aux->dato);
    free(aux);
    return 0;
}
int pilaVacia(const tPila* pila)
{
    return NULL==(*pila);
}
void vaciarPila(tPila* pila)
{
    tNodo* aux;

    while((*pila))
    {
        aux=(*pila);
        (*pila)=aux->sig;
        free(aux->dato);
        free(aux);
    }
}
