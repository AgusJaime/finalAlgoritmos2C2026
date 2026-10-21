#include "ABB.h"

tNodo** buscarMayor(tArbol* arbol)
{
    if(!(*arbol))
        return NULL;

    while((*arbol)->der)
        arbol=&(*arbol)->der;

    return arbol;
}


tNodo** buscarMenor(tArbol* arbol)
{
    if(!(*arbol))
        return NULL;

    while((*arbol)->izq)
        arbol=&(*arbol)->izq;

    return arbol;
}


tNodo** buscarNodo(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    if(!(*arbol))
        return NULL;

    while((*arbol) && cmp((*arbol)->dato,dato)>0)
        arbol=&(*arbol)->izq;

    while((*arbol) && cmp((*arbol)->dato,dato)<0)
        arbol=&(*arbol)->der;

    return arbol;
}



void crearArbol(tArbol* arbol)
{
    (*arbol)=NULL;
}
int insertarEnArbol(tArbol* arbol, const void* dato,unsigned tam,int cmp(const void*,const void*),void accion(const void*,void*))
{
    if(!(*arbol))
    {
        (*arbol)=(tNodo*)malloc(sizeof(tNodo));
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
        return insertarEnArbol(&(*arbol)->izq,dato,tam,cmp,accion);
    }
    else if(cmp((*arbol)->dato,dato)<0){
        return insertarEnArbol(&(*arbol)->der,dato,tam,cmp,accion);
    }
    else
    {
        if(accion)
            accion(dato,(*arbol)->dato);

        return DUPLICADO;
    }

}
int eliminarRaiz(tArbol* arbol)
{
    tNodo** remp,*elim;
    if(!(*arbol))
        return 0;

    free((*arbol)->dato);

    if(!(*arbol)->izq && !(*arbol)->der)
    {
        free((*arbol));
        (*arbol)=NULL;
        return 1;
    }

    remp=alturaArbol(&(*arbol)->izq)>alturaArbol(&(*arbol)->der)?buscarMayor(&(*arbol)->izq):buscarMenor(&(*arbol)->der);

    elim=*remp;

    (*arbol)->dato=elim->dato;
    (*arbol)->tam=elim->tam;
    *remp=elim->izq?elim->izq:elim->der;

    free(elim);
    return 1;
}
int eliminarDato(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tArbol* bsq;
    if((bsq=buscarNodo(arbol,dato,tam,cmp))==NULL){
        return 0;
    }

    memcpy(dato,(*bsq)->dato,MIN((*bsq)->tam,tam));

    return eliminarRaiz(bsq);
}
int buscarDato(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tArbol* bsq;
    if((bsq=buscarNodo(arbol,dato,tam,cmp))==NULL){
        return 0;
    }

    memcpy(dato,(*bsq)->dato,MIN((*bsq)->tam,tam));

    return 1;
}
void vaciarArbol(tArbol* arbol)
{
    if(!(*arbol))
        return;

    vaciarArbol(&(*arbol)->izq);
    vaciarArbol(&(*arbol)->der);
    free((*arbol)->dato);
    free((*arbol));
}
int alturaArbol(tArbol* arbol)
{
    int hd=0,hi=0;

    if(!(*arbol))
        return 0;
    hi=alturaArbol(&(*arbol)->izq);
    hd=alturaArbol(&(*arbol)->der);

    return ((hi>hd?hi:hd) + 1);
}
