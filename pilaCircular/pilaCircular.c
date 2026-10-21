#include "pilaCircular.h"

void crearPilaCircular(tPilaC* pila)
{
    (*pila)=NULL;
}
int apilarCircularmente(tPilaC* pila,const void* dato,unsigned tam)
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

    if((*pila))
    {
        nue->sig=(*pila)->sig; // (*pila) es el primer nodo, (*pila)->sig es el ultimo
    }
    else
        (*pila)=nue;

    (*pila)->sig=nue;

    return 1;

}
int desapilarCircularmente(tPilaC* pila,void* dato,unsigned tam)
{
    tNodo* elim;

    if(!(*pila))
        return 0;
    elim=(*pila)->sig;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    if((*pila)!=elim)
    {
        (*pila)->sig=elim->sig;
    }
    else
        (*pila)=NULL;

    free(elim->dato);
    free(elim);

    return 1;
}
int pilaCircularLlena(const tPilaC* pila,unsigned tam)
{
    tNodo* aux;
    aux=(tNodo*)malloc(sizeof(tNodo));
    if(!aux)
        return 1;
    aux->dato=malloc(tam);
    if(!aux->dato)
        return 1;
    free(aux->dato);
    free(aux);
    return 0;
}
int pilaCircularVacia(const tPilaC* pila)
{
    return NULL==(*pila);
}
int verUltimoCircularmente(const tPilaC* pila,void* dato,unsigned tam)
{
    if(!(*pila))
        return 0;

    memcpy(dato,(*pila)->sig->dato,MIN(tam,(*pila)->sig->tam));
    return 1;
}
void vaciarPilaCircular(tPilaC* pila)
{
    tNodo* aux;
    while((*pila))
    {
        aux=(*pila)->sig;
        if(aux==(*pila))
            (*pila)=NULL;
        else
            (*pila)->sig=aux->sig;
        free(aux->dato);
        free(aux);
    }
}
