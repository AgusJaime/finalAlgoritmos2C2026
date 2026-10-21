#include  "colaCircular.h"

void crearColaCircular(tColaC* cola)
{
    (*cola)=NULL;
}
int encolarCircularmente(tColaC* cola,const void* dato,unsigned tam)
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

    /// PRIMERA PARTE
    // nue->sig=(*cola)->sig || nue->sig=nue

    /// SEGUNDA PARTE
    // (*cola)->sig=nue; // conectamos el ultimo de la cola con el nuevo

    /// TERCERA PARTE
    // (*cola)=nue

    if((*cola))
    {
        nue->sig=(*cola)->sig;/// PRIMERA PARTE
        (*cola)->sig=nue;/// SEGUNDA PARTE
    }
    else
    {
        nue->sig=nue;/// PRIMERA PARTE
    }

    (*cola)=nue;/// TERCERA PARTE

    return 1;
}
int desencolarCircularmente(tColaC* cola,void* dato,unsigned tam)
{
    tNodo* elim;

    if(!(*cola))
        return 0;

    /// PRIMERA PARTE
    // elim=(*cola)->sig

    ///SEGUNDA PARTE
    // (*cola)->sig=elim->sig || (*cola)=NULL  (si la cola tiene un elemento)

    ///TERCERA PARTE
    // LIBERAR TODO


    elim=(*cola)->sig;

    if((*cola)!=elim)
        (*cola)->sig=elim->sig;
    else
        (*cola)=NULL;

    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);
    return 1;
}
int colaCircularLlena(const tColaC* cola,unsigned tam)
{
    tNodo* aux;
    aux=(tNodo*)malloc(sizeof(tNodo));
    if(!aux)
        return 1;
    aux->dato=malloc(tam);
    if(!aux->dato)
    {
        free(aux);
        return 1;
    }
    free(aux->dato);
    free(aux);
    return 0;
}
int colarCircularVacia(const tColaC* cola)
{
    return NULL==(*cola);
}
int verPrimeroCircularmente(const tColaC* cola,void* dato,unsigned tam)
{
    if(!(*cola))
        return 0;
    memcpy(dato,(*cola)->sig->dato,MIN((*cola)->sig->tam,tam));
    return 1;
}
void vaciarColaCircular(tColaC* cola)
{
    tNodo* aux;

    while((*cola))
    {
        aux=(*cola)->sig;
        if(aux==(*cola))
            (*cola)=NULL;
        else
            (*cola)->sig=aux->sig;

        free(aux->dato);
        free(aux);
    }
}
