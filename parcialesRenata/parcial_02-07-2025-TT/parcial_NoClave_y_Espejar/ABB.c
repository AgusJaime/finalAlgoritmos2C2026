#include "ABB.h"

void crearArbol(tArbol* arbol)
{
    (*arbol)=NULL;
}
int insertarEnArbol(tArbol* arbol,const void* dato,unsigned tam,int cmp(const void*,const void*))
{
    if(!(*arbol))
    {
        (*arbol)=(tNodo*)malloc(sizeof(tNodo));
        if(!(*arbol))
            return 0;

        (*arbol)->dato=malloc(tam);
        if(!(*arbol)->dato)
        {
            free(*arbol);
            return 0;
        }
        memcpy((*arbol)->dato,dato,tam);
        (*arbol)->tam=tam;
        (*arbol)->izq=NULL;
        (*arbol)->der=NULL;
        return 1;
    }

    if(cmp((*arbol)->dato,dato)>0)
    {
        return insertarEnArbol(&(*arbol)->izq,dato,tam,cmp);
    }
    else if(cmp((*arbol)->dato,dato)<0)
        return insertarEnArbol(&(*arbol)->der,dato,tam,cmp);
    else
        return 0;

}
int contarAparicionesDeDatoNoClave(tArbol* arbol,const void* dato,int cmp(const void*,const void*))
{
    if(!(*arbol))
        return 0;


    if(cmp((*arbol)->dato,dato)==0)
        return 1 + contarAparicionesDeDatoNoClave(&(*arbol)->izq,dato,cmp) + contarAparicionesDeDatoNoClave(&(*arbol)->der,dato,cmp);

    return contarAparicionesDeDatoNoClave(&(*arbol)->izq,dato,cmp) + contarAparicionesDeDatoNoClave(&(*arbol)->der,dato,cmp);
}
int espejarArbol(tArbol* arbol)
{
    tNodo* aux;
    if(!(*arbol))
        return 0 ;
    aux=(*arbol)->izq;
    (*arbol)->izq=(*arbol)->der;
    (*arbol)->der=aux;
    espejarArbol(&(*arbol)->izq);
    espejarArbol(&(*arbol)->der);

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


int recorrerInOrden(tArbol* arbol,void accion(const void*))
{
    if(!(*arbol) || !accion)
        return 0;

    recorrerInOrden(&(*arbol)->izq,accion);
    accion((*arbol)->dato);
    recorrerInOrden(&(*arbol)->der,accion);

    return 1;
}
