#include "lista.h"

void crearLista(tLista* lista)
{
    (*lista)=NULL;
}
int insertarMejoresNLista(tLista* lista,const void* dato,unsigned tam,int n,int cmp(const void*,const void*))
{
    tNodo* nue,*act,*ant=NULL,*sigElim;
    tLista* aux;
    unsigned contadorOcurrencias=0,posActual=1;

    if(!lista || !dato || !cmp)
        return 0;
    if(n==0)
        return 1; // ningun elemento puede entrar a un podio vacio

    aux=lista;
    act=(*aux);

    while(act && cmp(act->dato,dato)<0)
    {
        if(ant)
        {
            if(cmp(act->dato,ant->dato)!=0)
            {
                posActual+=contadorOcurrencias;
                contadorOcurrencias=1;
            }
            else
                contadorOcurrencias++;
        }
        else
            contadorOcurrencias=1;

        if(posActual>n)
        {
            return 1; // no se inserta ya que es mayor/menor (dependiendo el orden elegido) de los datos que ya estan en la lista y no hay espacio
        }
        ant=act;
        act=act->sig;
        aux=&(*aux)->sig;
    }

    if(ant && (posActual + contadorOcurrencias)>n)
        return 1; // el nuevo seria el puesto n+1 o peor, no entra

    while(act && cmp(act->dato,dato)==0) // se salta los empates para insertar al final de ellos (orden de llegada)
    {
        aux=&act->sig;
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

    nue->sig=(*aux);
    (*aux)=nue;

    posActual = 1;
    contadorOcurrencias = 0;
    ant = NULL; // se reinicia para empezar el segundo recorrido desde cero
    act = (*lista);

    while(act && posActual<=n)
    {
        if(ant)
        {
            if(cmp(act->dato,ant->dato)!=0)
            {
                posActual+=contadorOcurrencias;
                contadorOcurrencias=1;
            }
            else
                contadorOcurrencias++;
        }
        else
        {
            contadorOcurrencias=1;
        }
        if(posActual<=n)
        {
            ant=act;
            lista=&act->sig;
            act=act->sig;
        }
    }

    if(act)
    {
        *lista=NULL;

        while(act)
        {
            sigElim=act->sig;
            free(act->dato);
            free(act);
            act=sigElim;
        }
    }

    return 1;
}

///NUEVA VERSION

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

    (*lista)=NULL;
}
