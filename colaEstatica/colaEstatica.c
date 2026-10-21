#include "colaEstatica.h"


void crearCola(tCola* cola)
{
    cola->tamDisp=TAM_COLA;
    cola->pri=cola->ult=INICIO; // el inicio es arbitrario, lo mejor es ponerlo en 0 para evitar lo maximo la fragmentacion
}
int encolar(tCola* cola,const void* dato,unsigned tam)
{
    unsigned ini,fin;
    if(cola->tamDisp<(sizeof(unsigned)+tam))
        return 0;
    cola->tamDisp-=sizeof(unsigned)+tam;

    ini=MIN(sizeof(unsigned),TAM_COLA-cola->ult);
    fin=sizeof(unsigned) - ini;

    if(ini>0)
        memcpy(cola->vec+cola->ult,&tam,ini);
    if(fin>0)
        memcpy(cola->vec,((char*)&tam)+ini,fin);

    cola->ult=fin?fin:cola->ult+ini;

    ini=MIN(tam,TAM_COLA-cola->ult);
    fin=tam - ini;

    if(ini>0)
        memcpy(cola->vec+cola->ult,dato,ini);
    if(fin>0)
        memcpy(cola->vec,((char*)dato)+ini,fin);

    cola->ult=fin?fin:cola->ult+ini;

    return 1;
}
int desencolar(tCola* cola,void* dato,unsigned tam)
{
    unsigned ini,fin,tamDato;

    if(cola->tamDisp==TAM_COLA)
        return 0;

    ini=MIN(sizeof(unsigned),TAM_COLA-cola->pri);
    fin=sizeof(unsigned)-ini;

    if(ini>0)
        memcpy(&tamDato,cola->vec+cola->pri,ini);
    if(fin>0)
        memcpy(((char*)&tamDato)+ini,cola->vec,fin);

    cola->pri=fin?fin:cola->pri+ini;
    cola->tamDisp+=sizeof(unsigned)+tamDato;

    ini=MIN(MIN(tamDato,tam),TAM_COLA-cola->pri);
    fin=MIN(tamDato,tam) - ini;

    if(ini>0)
        memcpy(dato,cola->vec+cola->pri,ini);
    if(fin>0)
        memcpy(((char*)dato)+ini,cola->vec,fin);

    cola->pri=fin?fin:cola->pri+ini;
    return 1;
}
int verPrimero(const tCola* cola,void* dato,unsigned tam)
{
    unsigned ini,fin,tamDato,pos=cola->pri;

    if(cola->tamDisp==TAM_COLA)
        return 0;

    ini=MIN(sizeof(unsigned),TAM_COLA-cola->pri);
    fin=sizeof(unsigned) - ini;

    if(ini>0)
        memcpy(&tamDato,cola->vec+cola->pri,ini);
    if(fin>0)
        memcpy(((char*)&tamDato)+ini,cola->vec,fin);

    pos=fin?fin:cola->pri+ini;

    ini=MIN(MIN(tamDato,tam),TAM_COLA-pos)
    fin=MIN(tam,tamDato) - ini;

    if(ini>0)
        memcpy(dato,cola->vec+pos,ini);
    if(fin>0)
        memcpy((char*)dato,cola->vec,fin);

    return 1;
}
int colaLlena(const tCola* cola,unsigned tam)
{
    return (cola->tamDisp<(sizeof(unsigned)+tam));
}
int colaVacia(const tCola* cola)
{
    return cola->tamDisp==TAM_COLA;
}
void vaciarCola(tCola* cola)
{
    cola->tamDisp=TAM_COLA;
    cola->pri=cola->ult=INICIO;
}
