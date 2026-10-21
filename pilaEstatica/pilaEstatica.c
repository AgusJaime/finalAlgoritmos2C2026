#include "pilaEstatica.h"


void crearPila(tPila* p)
{
    p->tope=TAM_PILA;
}
int apilar(tPila* p,const void* dato,unsigned tam)
{
    if(p->tope<(sizeof(unsigned)+tam))
        return 0;
    p->tope-=tam;
    memcpy(p->vec+p->tope,dato,tam);
    p->tope-=sizeof(unsigned);
    memcpy(p->vec+p->tope,&tam,sizeof(unsigned));
    return 1;

}
int desapilar(tPila* p,void* dato,unsigned tam)
{
    unsigned tamDato;
    if(p->tope==TAM_PILA)
        return 0;
    memcpy(&tamDato,p->vec+p->tope,sizeof(unsigned));
    p->tope+=sizeof(unsigned);
    memcpy(dato,p->vec+p->tope,MIN(tam,tamDato));
    p->tope+=tamDato;

    return 1;
}
int pilaLlena(const tPila* p,unsigned tam)
{
    return p->tope<(sizeof(unsigned)+tam);
}
int pilaVacia(const tPila* p)
{
    return TAM_PILA==p->tope;
}
int verTope(const tPila* p,void* dato,unsigned tam)
{
    unsigned tamDato;
    if(p->tope==TAM_PILA)
        return 0;
    memcpy(&tamDato,p->vec+p->tope,sizeof(unsigned));
    memcpy(dato,p->vec+p->tope+sizeof(unsigned),MIN(tam,tamDato));
    return 1;
}
void vaciarPila(tPila* p)
{
    p->tope=TAM_PILA;
}
