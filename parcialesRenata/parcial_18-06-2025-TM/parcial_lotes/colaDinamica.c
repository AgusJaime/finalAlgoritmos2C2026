#include "colaDinamica.h"

void crearCola(tCola* cola)
{
    cola->pri=cola->ult=NULL;
}
int encolar(tCola* cola,const void* dato,unsigned tam)
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
    nue->sig=NULL;
    if(cola->pri==NULL)
        cola->pri=nue;
    else
        cola->ult->sig=nue;

    cola->ult=nue;

    return 1;
}
int desencolar(tCola* cola,void* dato,unsigned tam)
{
    tNodo* elim;

    if(!cola->pri)
        return 0;

    elim=cola->pri;
    cola->pri=elim->sig;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);

    if(!cola->pri)// tenia un solo elemento y ya lo elimine
        cola->ult=NULL;

    return 1;

}
int verPrimero(const tCola* cola,void* dato,unsigned tam)
{
    if(!cola->pri)
        return 0;

    memcpy(dato,cola->pri->dato,MIN(tam,cola->pri->tam));
    return 1;
}
int colaVacia(const tCola* cola)
{
    return NULL==cola->pri;
}
int colaLlena(const tCola* cola,unsigned tam)
{
    tNodo* nue;

    nue=(tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 1;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 1;
    }
    free(nue->dato);
    free(nue);
    return 0;
}
void vaciarCola(tCola* cola)
{
    tNodo* aux;

    while(cola->pri)
    {
        aux=cola->pri;
        cola->pri=aux->sig;
        free(aux->dato);
        free(aux);
    }
    cola->pri=cola->ult=NULL;
}
