#include "ABB.h"


void crearArbol(tArbol* arbol)
{
    (*arbol)=NULL;
}
//ITEM A
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
            free((*arbol));
            return 0;
        }
        memcpy((*arbol)->dato,dato,tam);
        (*arbol)->tam=tam;
        (*arbol)->izq=NULL;
        (*arbol)->der=NULL;
        return 1;
    }

    if(cmp((*arbol)->dato,dato)>0)
        return insertarEnArbol(&(*arbol)->izq,dato,tam,cmp);
    else if(cmp((*arbol)->dato,dato)<0)
        return insertarEnArbol(&(*arbol)->der,dato,tam,cmp);
    else
        return DUPLICATE;
}
// ITEM B
int contarNodosDeXNivel(tArbol* arbol,int nivel)
{
    if(!(*arbol) || nivel<0)
        return 0;

    if(nivel==0)
        return 1;

    return contarNodosDeXNivel(&(*arbol)->izq,nivel-1) + contarNodosDeXNivel(&(*arbol)->der,nivel-1);
}
// ITEM C



int esCompletoXNivel(tArbol* arbol,int nivel)
{
    return pow(2,nivel) - contarNodosDeXNivel(arbol,nivel);
}
