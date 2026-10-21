#include <stdlib.h>
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

/// La lista apunta al ULTIMO nodo. (*lista)->sig es el primero.
typedef tNodo* tListaC;

/// ================= PROTOTIPOS =================
/// 4 PRIMITIVAS GENERICAS
void crearListaCircular(tListaC* lista);
int listaLlena(const tListaC* lista,unsigned tam);
int listaVacia(const tListaC* lista);
void vaciarListaCircular(tListaC* lista);
/// INSERTAR
int insertarAlPrincipio(tListaC* lista,const void* dato,unsigned tam);
int insertarAlFinal(tListaC* lista,const void* dato,unsigned tam);
int insertarOrdenado(tListaC* lista,const void* dato,unsigned tam,int cmp(const void*,const void*),void accion(const void*,void*));
/// ELIMINAR
int eliminarAlPrincipio(tListaC* lista,void* dato,unsigned tam);
int eliminarAlFinal(tListaC* lista,void* dato,unsigned tam);
int eliminarOrdenado(tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
/// RECORRIDOS
void recorrerLista(const tListaC* lista,void accion(const void*));
void recorridoInversoLista(const tListaC* lista,void accion(const void*));
/// MAP, FILTER Y REDUCE
void mapLista(tListaC* lista,void accion(void*,void*),void* contexto);
void filter(tListaC* lista,void* dato,int cmp(const void*,const void*),void accion(const void*,void*),void* contexto);
void* reduceNoModifica(const tListaC* lista,void accion(const void*,void*),void* contexto);
void* reduceSiModifica(tListaC* lista,void accion(const void*,void*));
/// BUSQUEDAS
int buscarDatoEspecifico(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int buscarUltimaCoincidencia(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
/// ORDENAMIENTO
int ordenarLista(tListaC* lista,unsigned tam,int cmp(const void*,const void*));
/// FUNCIONES PARA VER DATOS
int verPrimero(const tListaC* lista,void* dato,unsigned tam);
int verUltimo(const tListaC* lista,void* dato,unsigned tam);
int verMenor(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int verMayor(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));


/// ================= AUXILIARES (privadas) =================
static tNodo* crearNodo(const void* dato,unsigned tam)
{
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo));

    if(!nue)
        return NULL;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;

    return nue;
}

static void recorridoInversoRec(const tNodo* act,const tNodo* ult,void accion(const void*))
{
    if(act!=ult)
        recorridoInversoRec(act->sig,ult,accion);
    accion(act->dato);
}


/// ================= 4 PRIMITIVAS GENERICAS =================
void crearListaCircular(tListaC* lista)
{
    (*lista)=NULL;
}

int listaLlena(const tListaC* lista,unsigned tam)
{
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo));
    void* dato=malloc(tam);

    (void)lista;
    free(nue);
    free(dato);

    return !nue || !dato;
}

int listaVacia(const tListaC* lista)
{
    return (*lista)==NULL;
}

void vaciarListaCircular(tListaC* lista)
{
    tNodo* aux;

    if(!(*lista))
        return;
    aux=(*lista)->sig; // apuntamos al primero
    (*lista)->sig=NULL;  // cortamos el circulo para que el while termine en NULL

    while((*lista))
    {
        (*lista)=aux->sig; // nos salteamos el "primero" ya que ese es el que vamos a liberar
        free(aux->dato);
        free(aux);
        aux=(*lista); // ahora seguimos con el nuevo primero
    }
}


/// ================= INSERTAR =================
int insertarAlPrincipio(tListaC* lista,const void* dato,unsigned tam)
{
    tNodo* nue=crearNodo(dato,tam);

    if(!nue)
        return 0;

    if((*lista))
    {
        nue->sig=(*lista)->sig;
        (*lista)->sig=nue;
    }
    else
    {
        nue->sig=nue;
        (*lista)=nue;
    }
    // NO actualizo (*lista): tiene que seguir apuntando al ultimo

    return 1;
}

int insertarAlFinal(tListaC* lista,const void* dato,unsigned tam)
{
    tNodo* nue=crearNodo(dato,tam);

    if(!nue)
        return 0;

    if((*lista))
    {
        nue->sig=(*lista)->sig;
        (*lista)->sig=nue;
    }
    else
        nue->sig=nue;

    (*lista)=nue;

    return 1;
}

/// Si el dato ya existe (cmp==0) y accion!=NULL: no inserta, llama accion(dato nuevo, dato existente).
/// Si accion==NULL inserta el duplicado igual.
int insertarOrdenado(tListaC* lista,const void* dato,unsigned tam,int cmp(const void*,const void*),void accion(const void*,void*))
{
    tNodo *ant,*act,*nue;

    if(!(*lista) || cmp((*lista)->dato,dato)<0) // lista vacia o dato mayor que el ultimo
        return insertarAlFinal(lista,dato,tam);

    ant=(*lista);
    act=ant->sig; // primero
    while(cmp(act->dato,dato)<0) // frena a lo sumo en el ultimo, que es >= dato
    {
        ant=act;
        act=act->sig;
    }

    if(accion && cmp(act->dato,dato)==0)
    {
        accion(dato,act->dato);
        return 1;
    }

    nue=crearNodo(dato,tam);
    if(!nue)
        return 0;

    nue->sig=act;
    ant->sig=nue;
    // (*lista) no cambia: si entro antes del primero, ant era el ultimo y sigue siendolo

    return 1;
}


/// ================= ELIMINAR =================
int eliminarAlPrincipio(tListaC* lista,void* dato,unsigned tam)
{
    tNodo* elim;

    if(!(*lista))
        return 0;

    elim=(*lista)->sig; // apunto al primero
    if(elim==(*lista))
        (*lista)=NULL;
    else
        (*lista)->sig=elim->sig;

    memcpy(dato,elim->dato,MIN(elim->tam,tam));

    free(elim->dato);
    free(elim);

    return 1;
}

int eliminarAlFinal(tListaC* lista,void* dato,unsigned tam)
{
    tNodo* elim;

    if(!(*lista))
        return 0;

    elim=(*lista);

    if(elim==(*lista)->sig)
        (*lista)=NULL;
    else
    {
        while(elim!=(*lista)->sig)
            (*lista)=(*lista)->sig;
        (*lista)->sig=elim->sig;
        //ahora (*lista) apunta al nuevo ultimo
    }

    memcpy(dato,elim->dato,MIN(tam,elim->tam));
    free(elim->dato);
    free(elim);

    return 1;
}

/// Lista ordenada: elimina la primera coincidencia (cmp==0) y la devuelve en dato.
int eliminarOrdenado(tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo *ant,*act;

    if(!(*lista))
        return 0;

    ant=(*lista);
    act=ant->sig; // primero
    while(act!=(*lista) && cmp(act->dato,dato)<0)
    {
        ant=act;
        act=act->sig;
    }

    if(cmp(act->dato,dato)!=0)
        return 0;

    if(act==ant) // era el unico nodo
        (*lista)=NULL;
    else
    {
        ant->sig=act->sig;
        if(act==(*lista)) // elimine el ultimo: el nuevo ultimo es ant
            (*lista)=ant;
    }

    memcpy(dato,act->dato,MIN(tam,act->tam));
    free(act->dato);
    free(act);

    return 1;
}


/// ================= RECORRIDOS =================
void recorrerLista(const tListaC* lista,void accion(const void*))
{
    tNodo* act;

    if(!(*lista))
        return;

    act=(*lista);
    do
    {
        act=act->sig;
        accion(act->dato);
    }while(act!=(*lista));
}

/// Recursivo (la lista circular simple no tiene puntero al anterior)
void recorridoInversoLista(const tListaC* lista,void accion(const void*))
{
    if(!(*lista))
        return;

    recorridoInversoRec((*lista)->sig,(*lista),accion);
}


/// ================= MAP, FILTER Y REDUCE =================
void mapLista(tListaC* lista,void accion(void*,void*),void* contexto)
{
    tNodo* act;

    if(!(*lista))
        return;

    act=(*lista);
    do
    {
        act=act->sig;
        accion(act->dato,contexto);
    }while(act!=(*lista));
}

/// Aplica accion a los elementos que coinciden con dato (cmp==0). No modifica la estructura.
void filter(tListaC* lista,void* dato,int cmp(const void*,const void*),void accion(const void*,void*),void* contexto)
{
    tNodo* act;

    if(!(*lista))
        return;

    act=(*lista);
    do
    {
        act=act->sig;
        if(cmp(act->dato,dato)==0)
            accion(act->dato,contexto);
    }while(act!=(*lista));
}

/// Acumula sobre contexto y lo devuelve. La lista queda intacta.
void* reduceNoModifica(const tListaC* lista,void accion(const void*,void*),void* contexto)
{
    tNodo* act;

    if(!(*lista))
        return contexto;

    act=(*lista);
    do
    {
        act=act->sig;
        accion(act->dato,contexto);
    }while(act!=(*lista));

    return contexto;
}

/// El dato del primer nodo es el acumulador inicial; se va consumiendo la lista.
/// Al final la lista queda vacia y se devuelve el acumulador (el que llama debe hacer free).
void* reduceSiModifica(tListaC* lista,void accion(const void*,void*))
{
    tNodo* elim;
    void* acum;

    if(!(*lista))
        return NULL;

    elim=(*lista)->sig;
    acum=elim->dato; // este dato NO se libera: queda como acumulador
    if(elim==(*lista))
        (*lista)=NULL;
    else
        (*lista)->sig=elim->sig;
    free(elim);

    while((*lista))
    {
        elim=(*lista)->sig;
        accion(elim->dato,acum);
        if(elim==(*lista))
            (*lista)=NULL;
        else
            (*lista)->sig=elim->sig;
        free(elim->dato);
        free(elim);
    }

    return acum;
}


/// ================= BUSQUEDAS =================
/// Primera coincidencia (desde el primero). Devuelve el dato encontrado en dato.
int buscarDatoEspecifico(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo* act;

    if(!(*lista))
        return 0;

    act=(*lista);
    do
    {
        act=act->sig;
        if(cmp(act->dato,dato)==0)
        {
            memcpy(dato,act->dato,MIN(tam,act->tam));
            return 1;
        }
    }while(act!=(*lista));

    return 0;
}

int buscarUltimaCoincidencia(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo *act,*enc=NULL;

    if(!(*lista))
        return 0;

    act=(*lista);
    do
    {
        act=act->sig;
        if(cmp(act->dato,dato)==0)
            enc=act;
    }while(act!=(*lista));

    if(!enc)
        return 0;

    memcpy(dato,enc->dato,MIN(tam,enc->tam));
    return 1;
}


/// ================= ORDENAMIENTO =================
/// Insercion estable relinkeando nodos (sin copiar datos ni pedir memoria). tam no se usa.
int ordenarLista(tListaC* lista,unsigned tam,int cmp(const void*,const void*))
{
    tNodo *ord=NULL,*nodo,*sig,*ult,**p;

    (void)tam;

    if(!(*lista))
        return 1;

    nodo=(*lista)->sig; // primero
    (*lista)->sig=NULL; // rompo el circulo

    while(nodo)
    {
        sig=nodo->sig;
        p=&ord;
        while(*p && cmp((*p)->dato,nodo->dato)<=0)
            p=&(*p)->sig;
        nodo->sig=*p;
        *p=nodo;
        nodo=sig;
    }

    ult=ord;
    while(ult->sig)
        ult=ult->sig;
    ult->sig=ord; // cierro el circulo
    (*lista)=ult; // el puntero queda en el ultimo

    return 1;
}


/// ================= FUNCIONES PARA VER DATOS =================
int verPrimero(const tListaC* lista,void* dato,unsigned tam)
{
    if(!(*lista))
        return 0;

    memcpy(dato,(*lista)->sig->dato,MIN(tam,(*lista)->sig->tam));
    return 1;
}

int verUltimo(const tListaC* lista,void* dato,unsigned tam)
{
    if(!(*lista))
        return 0;

    memcpy(dato,(*lista)->dato,MIN(tam,(*lista)->tam));
    return 1;
}

int verMenor(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo *act,*men;

    if(!(*lista))
        return 0;

    men=(*lista)->sig;
    act=men;
    while(act!=(*lista))
    {
        act=act->sig;
        if(cmp(act->dato,men->dato)<0)
            men=act;
    }

    memcpy(dato,men->dato,MIN(tam,men->tam));
    return 1;
}

int verMayor(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tNodo *act,*may;

    if(!(*lista))
        return 0;

    may=(*lista)->sig;
    act=may;
    while(act!=(*lista))
    {
        act=act->sig;
        if(cmp(act->dato,may->dato)>0)
            may=act;
    }

    memcpy(dato,may->dato,MIN(tam,may->tam));
    return 1;
}
