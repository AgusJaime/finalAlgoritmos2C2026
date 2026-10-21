#include "lista.h"

/// 4 PRIMITIVAS GENERICAS
void crearLista(tLista* lista)
{
    (*lista)=NULL;
}
int listaLlena(const tLista* lista,unsigned tam)
{
    tNodo* aux=(tNodo*)malloc(sizeof(tNodo));
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
int listaVacia(const tLista* lista)
{
    return NULL==(*lista);
}
void vaciarLista(tLista* lista)
{
    tNodo* aux;
    if(!(*lista))
        return;

    while((*lista)->ant)
        lista=&(*lista)->ant;

    while((*lista))
    {
        aux=(*lista);
        (*lista)=aux->sig;
        free(aux->dato);
        free(aux);
    }
    (*lista)=NULL;
}
/// INSERTAR
int insertarAlPrincipio(tLista* lista,const void* dato,unsigned tam)
{
    tNodo* nue,*act;


    act=(*lista);
    if(act)
    {
        while(act)
            act=act->ant;
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
    nue->tam=tam;
    nue->ant=NULL;

    nue->sig=act;
    if(act)
    {
        act->ant=nue;
    }
    (*lista)=nue; // posiciono el puntero a la lista hacia el nuevo "Primer elemento"

    return 1;
}
int insertarAlFinal(tLista* lista,const void* dato,unsigned tam)
{
    tNodo* nue,*act;

    act=(*lista);

    if(act)
    {
        while(act)
            act=act->sig;
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
    nue->tam=tam;
    nue->sig=NULL;

    nue->ant=act;

    if(act)
    {
        act->sig=nue;
    }
    (*lista)=nue;
    return 1;
}
int insertarOrdenado(tLista* lista,const void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* nue,*act,*auxSig,*auxAnt;
    int comp=0;
    act=(*lista);
    while(act->sig && (comp=cmp(act->dato,dato)<0))
        act=act->sig;

    while(act->ant && (comp=cmp(act->dato,dato)>0))
        act=act->ant;


    if(comp==0)
    {
        *lista=act; // duplicado, dejamos la lista en la operacion mas cercana
        return 0;
    }
    else if(comp<0)
    {
        auxAnt=act;
        auxSig=act->sig;
    }
    else
    {
        auxAnt=act->ant;
        auxSig=act;
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
    nue->tam=tam;
    nue->ant=auxAnt;
    nue->sig=auxSig;

    if(auxAnt)
        auxAnt->sig=nue;
    if(auxSig)
        auxSig->ant=nue;

    (*lista)=nue;
    return 1;
}
int insertarEnPos(tLista* lista,const void* dato,unsigned tam,int pos)
{
    tNodo* nue,*act,*auxAnt=NULL;
    int posLista=0;
    act=(*lista);

    if(act)
    {
        while(act->ant)
            act=act->ant;
    }

    while(act && posLista<pos)
    {
        act=act->sig;
        posLista++;
    }

    if(posLista<pos)
        return 0;
    auxAnt=act->ant;

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
    nue->ant=auxAnt;
    nue->sig=act;

    if(act)
        act->ant=nue;
    if(auxAnt)
        auxAnt->sig=nue;

    (*lista)=nue;

    return 1;
}
/// ELIMINAR
int eliminarAlPrincipio(tLista* lista,void* dato,unsigned tam)
{
    tNodo* elim,*act;

    if(!(*lista))
        return 0;
    act=(*lista);

    while(act->ant)
        act=act->ant;

    elim=act;
    act=elim->sig;

    if(act)
        act->ant=NULL;

    (*lista)=act;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);

    return 1;
}
int eliminarAlFinal(tLista* lista,void* dato,unsigned tam)
{
    tNodo* elim,* act;

    if(!(*lista))
        return 0;

    act=(*lista);

    while(act->sig)
        act=act->sig;

    elim=act;
    act=elim->ant;

    if(act)
        act->sig=NULL;

    (*lista)=act;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);

    return 1;

}
int eliminarElemento(tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo*act,*auxSig,*auxAnt;

    if(!(*lista))
        return 0;
    act=(*lista);

    while(act && cmp(act->dato,dato)!=0)
        act=act->sig;

    if(!act)
    {
        act=(*lista)->ant;
        while(act && cmp(act->dato,dato)!=0)
            act=act->ant;

        if(!act) // si act no existe significa que recorrio toda la lista y no encontro una coincidencia
            return 0;
    }


    auxSig=act->sig;
    auxAnt=act->ant;


    if(auxSig)
        auxSig->ant=auxAnt;

    if(auxAnt)
    {
        auxAnt->sig=auxSig;
        (*lista)=auxAnt;
    }
    else
        (*lista)=auxSig;

    memcpy(dato,act->dato,MIN(tam,act->tam));
    free(act->dato);
    free(act);
    return 1;
}
int eliminarPorPos(tLista* lista,void* dato,unsigned tam,int pos)
{
    tNodo* elim,*act,*auxAnt;
    int posLista=0;
    if(!(*lista))
        return 0;
    act=(*lista);

    while(act->ant)
        act=act->ant;

    while(act && posLista<pos)
    {
        act=act->sig;
        posLista++;
    }

    if(!act) //Si no entra aca la lista tiene elementos
        return 0; // la posicion pasada por parametro no existe en la lista

    auxAnt=act->ant;
    elim=act;
    act=elim->sig;// dado que la lista tiene elementos puedo hacer esto y no ocurrira un memory leak

    if(act)
        act->ant=auxAnt;
    if(auxAnt)
    {
        auxAnt->sig=act;
        (*lista)=auxAnt;
    }
    else
        (*lista)=act;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));

    free(elim->dato);
    free(elim);

    return 1;
}
/// MAP,FILTER Y REDUCE
void mapLista(tLista* lista,void accion(const void*,void*),void* contexto)
{
    tNodo* act;
    act=(*lista);

    while(act && accion)
    {
        accion(act->dato,contexto);
        act=act->sig;
    }
}
int filter(tLista* lista,void* dato,int cmp(const void*,const void*))
{
    tNodo* act,*auxAnt,*elim;

    if(!(*lista))
        return 0;
    act=(*lista);

    while(act->ant) // me posiciono al inicio de la lista
        act=act->ant;

    while(act)
    {
        if(cmp(act->dato,dato)!=0) // si no es igual al dato pasado como condicion se elimina
        {
            elim=act;
            act=elim->sig;
            auxAnt=elim->ant;
            if(auxAnt)
                auxAnt->sig=act;
            if(act)
            {
                act->ant=auxAnt;
                (*lista)=act;
            }
            else
                (*lista)=auxAnt;
            free(elim->dato);
            free(elim);
        }
        else
            act=act->sig;
    }

    return 1;
}
int reduceSiModifica(tLista* lista,void accion(const void*,void*))
{
    tNodo* aux,*act,*elim;

    if(!(*lista))
        return 0;
    act=(*lista);
    while(act->ant)
        act=act->ant;
    aux=act;
    act=aux->sig;
    while(act)
    {
        elim=act;
        act=elim->sig;
        accion(elim->dato,aux->dato);
        free(elim->dato);
        free(elim);
    }
    aux->sig=NULL;
    (*lista)=aux;
    return 1;
}
int reduceNoModifica(const tLista* lista, void accion(const void*,void*),void* contexto)
{
    tNodo* act;

    if(!(*lista))
        return 0;
    act=(*lista);

    while(act->ant)
        act=act->ant;

    while(act && accion)
    {
        accion(act->dato,contexto);
        act=act->sig;
    }

    return 1;
}
/// BUSQUEDAS EXTERNAS
int buscarElemento(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* izq,*der;

    if(!(*lista))
        return 0;

    if(cmp((*lista)->dato,dato)==0) // si el dato al que apunta la lista es el buscado lo retorno
    {
        memcpy(dato,(*lista)->dato,MIN(tam,(*lista)->tam));
        return 1;
    }
    izq=(*lista)->ant;
    der=(*lista)->sig;

    while(izq)
    {
        if(cmp(izq->dato,dato)==0)
        {
            memcpy(dato,izq->dato,MIN(izq->tam,tam));
            return 1;
        }
        izq=izq->ant;
    }

    while(der)
    {
        if(cmp(der->dato,dato)==0)
        {
            memcpy(dato,der->dato,MIN(der->tam,tam));
            return 1;
        }
        der=der->sig;
    }

    return 0;
}
/// VISTAS
int verPrimero(const tLista* lista,void* dato,unsigned tam)
{
    tNodo* act;

    if(!(*lista))
        return 0;
    act=(*lista);

    while(act->ant)
        act=act->ant;

    memcpy(dato,act->dato,MIN(tam,act->tam));
    return 1;
}
int verUltimo(const tLista* lista,void* dato,unsigned tam)
{
        tNodo* act;

    if(!(*lista))
        return 0;
    act=(*lista);

    while(act->sig)
        act=act->sig;

    memcpy(dato,act->dato,MIN(tam,act->tam));
    return 1;
}
int verCoincidencia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* act;
    if(!(*lista))
        return 0;

    act=(*lista);

    while(act->ant)
    {
        if(cmp(act->dato,dato)==0)
        {
            memcpy(dato,act->dato,MIN(tam,act->tam));
            return 1;
        }
        act=act->ant;
    }
    act=(*lista);
    while(act->sig)
    {
        if(cmp(act->dato,dato)==0)
        {
            memcpy(dato,act->dato,MIN(tam,act->tam));
            return 1;
        }
        act=act->sig;
    }

    return 0; /// si pasa por aca significa que no lo encontro ni para la izquierda ni para la derecha
}
int verUltimaCoincidencia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
