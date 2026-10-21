#include "funciones.h"

typedef struct
{
    int id;
    char nom[21];
    float montoTotal;
}tCliente;

void clientesCSV(const char* lineaArchivo,void* bufferCliente)
{
    tCliente* auxCliente=(tCliente*)bufferCliente;

    char* aux;

    aux=strrchr(lineaArchivo,'\n');
    *aux='\0';

    aux=strrchr(lineaArchivo,';');
    sscanf(aux+1,"%f",&auxCliente->montoTotal);
    *aux='\0';

    aux=strrchr(lineaArchivo,';');
    strcpy(auxCliente->nom,aux+1);
    *aux='\0';

    sscanf(lineaArchivo,"%d",&auxCliente->id);
}

int cmpCliente(const void* datoArbol,const void* datoParam)
{
    tCliente* auxArbol=(tCliente*)datoArbol;
    tCliente* auxParam=(tCliente*)datoParam;

    return auxArbol->id - auxParam->id;
}

int main()
{

    return 0;
}
