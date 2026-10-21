#include "lista.h"


void crearLista(tLista* lista)
{
    (*lista)=NULL;
}
int insertarOrdenado(tLista* lista,const void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* nue;

    while((*lista) && cmp((*lista)->dato,dato)<0)
        lista=&(*lista)->sig;

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
    nue->sig=(*lista);
    (*lista)=nue;
    return 1;
}
void mostrarListaRecusivaConCondicion(tLista* lista,void accion(const void*),void* contexto,int cumpleCondicion(const void*,void*))
{
    if(!(*lista))
        return;

    mostrarListaRecusivaConCondicion(&(*lista)->sig,accion,contexto,cumpleCondicion);
    if(cumpleCondicion((*lista)->dato,contexto)==CUMPLE_CONDICION)
        accion((*lista)->dato);
}
void vaciarLista(tLista* lista)
{
    tNodo* aux;
    while((*lista))
    {
        aux=(*lista);
        (*lista)=aux->sig;
        free(aux->dato);
        free(aux);
    }
}
