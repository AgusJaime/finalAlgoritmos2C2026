#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char cod[6];
    char tipo;
    int cantStock;
}tProd;

typedef struct
{
    char cod[6];
    char tipo;
    int pos;
}tProdIdx;

void imprimirProdEnArbolConForma(const void* dato,unsigned nivel,void* params)
{
    tProdIdx *auxArbol=(tProdIdx*)dato;
    printf("%*s-%s|%c-\n",nivel*4,"",auxArbol->cod,auxArbol->tipo);
}

void grabarRegEnIdx(const void* datoArbol,void* contexto)
{
    tProdIdx* auxArbol=(tProdIdx*)datoArbol;
    FILE* pf=(FILE*)contexto;

    fwrite(auxArbol,sizeof(tProdIdx),1,pf);
}



int main()
{
    int i=-1;

    printf("%d",i);
    return 0;
}
