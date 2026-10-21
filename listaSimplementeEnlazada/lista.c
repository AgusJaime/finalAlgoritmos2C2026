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
    nue->sig=(*lista);
    (*lista)=nue;
    return 1;
}
int insertarAlFinal(tLista* lista,const void* dato,unsigned tam)
{
    tNodo* nue;

    /// AL MANEJARNOS DESDE EL SIGUIENTE DEL NODO ANTERIOR UNA VEZ QUE ESE SIGUIENTE ES NULL AL INSERTAR AHI YA QUEDARIA CONECTADA EL NUEVO ELEMENTO EN LA LISTA
    while((*lista))
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
int insertarOrdenado(tLista* lista,const void* dato,unsigned tam,int dup,int cmp(const void*,const void*),void accion(const void*,void*))
{
    tNodo* nue;

    while((*lista) && cmp((*lista)->dato,dato)>0) // ordena de forma descendente (mayor a menor)
        lista=&(*lista)->sig;

    if((*lista) && cmp((*lista)->dato,dato)==0)
    {
        if(dup!=ACEPTA_DUP && accion) // si no acepta dup y accion existe
            {
                accion(dato,(*lista)->dato);
                return DUPLICADO;
            }
        // si no acepta duplicados entra a este if, sino lo ingresa comunmente
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
    nue->sig=(*lista);
    (*lista)=nue;
    return 1;
}


int insertarMejoresNLista(tLista* lista,const void* dato,unsigned tam,int n,int cmp(const void*,const void*))
{
    tNodo* nue,*ant=NULL,*act,*sigElem;
    tLista* aux;
    unsigned cantOcurrencias=1,posActual=0;

    aux=lista;
    act=(*lista);

    while(act && cmp(act->dato,dato)<0)
    {
        if(ant)
        {
            if(cmp(act->dato,ant->dato)!=0){
                posActual+=cantOcurrencias;
                cantOcurrencias=1;
            }
            else
                cantOcurrencias++;
        }
        else
            cantOcurrencias=1;

        if(posActual>n)
        {
            return 0;
        }

        ant=act;
        aux=&(*aux)->sig;
        act=act->sig;
    }

    if(ant && (posActual + cantOcurrencias)>n)
        return 0;

    while(act && cmp(act->dato,dato)==0)
    {
        aux=&(*aux)->sig;
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

    posActual=1;
    cantOcurrencias=0;
    ant=NULL;
    act=(*lista);


    while(act && posActual<=n)
    {
        if(ant)
        {
            if(cmp(act->dato,ant->dato)!=0)
            {
                posActual+=cantOcurrencias;
                cantOcurrencias=1;
            }
            else
                cantOcurrencias++;
        }
        else
            cantOcurrencias=1;

        if(posActual<=n)
        {
            ant=act;
            act=act->sig;
            aux=&(*aux)->sig;
        }
    }

    if(act) // si salio del while por el posActual entonces elimino todo lo que seguia
    {
        (*lista)=NULL;

        while(act){
            sigElem=act->sig;
            free(act->dato);
            free(act);
            act=sigElem;
        }
    }

    return 1;
}
/// OTRA VERSION DE MEJORES N EN LISTA
int insertarMejoresNListaV2(tLista* lista, const void* dato, unsigned tam, int n,
                          int cmp(const void*, const void*))
{
    tLista* inicio = lista;
    tNodo *nue, *ant, *act, *elim;
    int menores = 0, pos, cant,band=1;

    if(n < 1)
        return 0;

    // 1) contar los estrictamente mejores y ubicar el punto de inserción
    while(*lista && cmp((*lista)->dato, dato) < 0)
    {
        menores++;
        lista = &(*lista)->sig;
    }

    if(menores >= n)          // su puesto sería menores + 1 > n
        return 0;

    // 2) los empatados quedan antes que el nuevo
    while(*lista && cmp((*lista)->dato, dato) == 0)
        lista = &(*lista)->sig;

    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->dato, dato, tam);
    nue->tam = tam;
    nue->sig = *lista;
    *lista = nue;

    // 3) recortar lo que quedó fuera de los n mejores puestos
    pos = 1; cant = 0; ant = NULL; act = *inicio;

    while(act && band)
    {
        if(ant && cmp(act->dato, ant->dato) != 0)
        {
            pos += cant;
            cant = 0;
        }
        if(pos > n)
            band=0;
        cant++;
        ant = act;
        act = act->sig;
    }

    if(act)
    {
        ant->sig = NULL;      // ant nunca es NULL: el primer puesto siempre es 1 <= n
        while(act)
        {
            elim = act;
            act = act->sig;
            free(elim->dato);
            free(elim);
        }
    }

    return 1;
}
/// ELIMINAR
int eliminarAlPrincipio(tLista* lista, void* dato,unsigned tam)
{
    tNodo* elim;
    if(!(*lista))
        return 0;
    elim=(*lista);
    (*lista)=elim->sig;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);
    return 1;
}
int eliminarAlFinal(tLista* lista, void* dato,unsigned tam)
{
    tNodo* elim;

    if(!(*lista))
        return 0;

    while((*lista)->sig)
        lista=&(*lista)->sig;

    elim=(*lista);
    (*lista)=elim->sig;
    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);
    return 1;
}
int eliminarOrdenado(tLista* lista, void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* elim;

    if(!(*lista))
        return 0;

    while((*lista) && cmp((*lista)->dato,dato)>0) // solo sirve si esta ordenado descendente
        lista=&(*lista)->sig;

    if(!(*lista) || cmp((*lista)->dato,dato)<0) /// Si no entro aca es porque la lista existe y salio del while porque encontro el dato correcto
        return 0;// no esta el dato

    elim=(*lista);
    (*lista)=elim->sig;
    memcpy(dato,elim->dato,MIN(elim->tam,tam));
    free(elim->dato);
    free(elim);
    return 1;
}
/// RECORRIDOS
void recorrerLista(const tLista* lista,void accion(const void*))
{
    while((*lista) && accion)
    {
        accion((*lista)->dato);
        lista=&(*lista)->sig;
    }
}
void recorridoInversoLista(const tLista* lista,void accion(const void*))
{
    if(!(*lista))
        return;

    recorridoInversoLista(&(*lista)->sig,accion);
    accion((*lista)->dato);
}
/// MAP, FILTER Y REDUCE
void mapLista(tLista* lista,void accion(void*,void*),void* contexto)
{
    while((*lista) && accion)
    {
        accion((*lista)->dato,contexto);
        lista=&(*lista)->sig;
    }
}
void filter(tLista* lista,void* dato,int cmp(const void*,const void*),void accion(const void*,void*),void* contexto)
{
    tNodo* aux;
    while((*lista) && accion)
    {
        if(cmp((*lista)->dato,dato)!=0)
        {
            accion((*lista)->dato,contexto);
            aux=(*lista);
            (*lista)=aux->sig;
            free(aux->dato);
            free(aux);
        }
        else
            lista=&(*lista)->sig;
    }
}
void* reduceNoModifica(const tLista* lista,void accion(const void*,void*),void* contexto)
{
    while((*lista) && accion)
    {
        accion((*lista)->dato,contexto);
        lista=&(*lista)->sig;
    }

    return contexto;
}
void* reduceSiModifica(tLista* lista,void accion(const void*,void*))
{
    tNodo* aux,*elim;
    if(!(*lista))
        return NULL;
    aux=(*lista);
    (*lista)=aux->sig;
    while((*lista) && accion)
    {
        accion((*lista)->dato,aux->dato);
        elim=(*lista);
        (*lista)=elim->sig;
        free(elim->dato);
        free(elim);
    }

    return aux->dato;
}
/// BUSQUEDAS

/**
FUNCION INTERNA DEL .C
*/
tNodo** buscarMenor(const tLista* lista,unsigned tam,int cmp(const void*,const void*))
{
    tNodo** menor=(tLista*)lista;
    while((*lista))
    {
        if(cmp((*lista)->dato,(*menor)->dato)<0)
            menor=(tLista*)lista;
        lista=&(*lista)->sig;
    }
    return menor;
}
tNodo** buscarMayor(const tLista* lista,unsigned tam,int cmp(const void*, const void*))
{
    tNodo** mayor=(tLista*)lista;
    while((*lista))
    {
        if(cmp((*lista)->dato,(*mayor)->dato)>0)
            mayor=(tLista*)lista;
        lista=&(*lista)->sig;
    }
    return mayor;
}
int buscarDatoEspecifico(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    while((*lista))
    {
        if(cmp((*lista)->dato,dato)==0)
        {
            memcpy(dato,(*lista)->dato,MIN(tam,(*lista)->tam));
            return 1; // encontrado
        }
        lista=&(*lista)->sig;
    }
    return 0; // no encontrado
}
int buscarUltimaCoincidencia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* aux=NULL;
    int encontrado=0;

    while((*lista))
    {
        if(cmp((*lista)->dato,dato)==0)
        {
            aux=(*lista);
            encontrado=1;
        }
        lista=&(*lista)->sig;
    }
    if(aux!=NULL)
        memcpy(dato,aux->dato,MIN(tam,aux->tam));

    return encontrado;
}
/// ORDENAMIENTO
int ordenarLista(tLista* lista,unsigned tam,int cmp(const void*,const void*))
{
    tNodo** menor,*aux;
    if(!(*lista))
        return 0; // lista vacia
    while((*lista))
    {
        menor=buscarMenor(lista,tam,cmp);

        if(menor!=lista)
        {
            aux=(*menor);
            (*menor)=aux->sig;
            aux->sig=(*lista);
            (*lista)=aux;
        }
        lista=&(*lista)->sig;
    }

    return 1;
}
/// FUNCIONES PARA VER DATOS
int verPrimero(const tLista* lista,void* dato,unsigned tam)
{
    if(!(*lista))
        return 0;

    memcpy(dato,(*lista)->dato,MIN(tam,(*lista)->tam));
    return 1;
}
int verUltimo(const tLista* lista,void* dato,unsigned tam)
{
    if(!(*lista))
        return 0;

    while((*lista)->sig)
        lista=&(*lista)->sig;

    memcpy(dato,(*lista)->dato,MIN(tam,(*lista)->tam));
    return 1;
}
int verMenor(const tLista* lista, void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo** menor;

    if(!(menor=buscarMenor(lista,tam,cmp)))
        return 0;
    memcpy(dato,(*menor)->dato,MIN(tam,(*menor)->tam));
    return 1;
}
int verMayor(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo** mayor;

    if(!(mayor=buscarMenor(lista,tam,cmp)))
        return 0;
    memcpy(dato,(*mayor)->dato,MIN(tam,(*mayor)->tam));
    return 1;
}
