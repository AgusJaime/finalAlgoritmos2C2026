#include "lista.h"


void crearLista(tLista* lista)
{
    (*lista)=NULL;
}
int insertarAlFinalSinDuplicados(tLista* lista,const void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* nue;

    while((*lista) && cmp((*lista)->dato,dato)!=0){
        lista=&(*lista)->sig;
    }

    if((*lista) && cmp((*lista)->dato,dato)==0){
        return 0;// dato duplicado
    }
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
    nue->tamDato=tam;
    nue->sig=NULL;
    (*lista)=nue;
    return 1;
}
int verConcordancia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{

    while((*lista) && cmp((*lista)->dato,dato)!=0){
        lista=&(*lista)->sig;
    }

    if(!(*lista))
        return 0;
    memcpy(dato,(*lista)->dato,MIN(tam,(*lista)->tamDato));
    return 1;
}
int sacarPrimero(tLista* lista,void* dato,unsigned tam)
{
    tNodo* elim;
    if(!(*lista))
        return 0;
    elim=(*lista);
    (*lista)=elim->sig;
    memcpy(dato,elim->dato,MIN(tam,elim->tamDato));
    free(elim->dato);
    free(elim);
    return 1;
}
int listaLlena(const tLista* lista,unsigned tam)
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
int listaVacia(const tLista* lista)
{
    return NULL==(*lista);
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
