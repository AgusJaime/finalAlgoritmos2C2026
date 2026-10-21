#include "funciones.h"


int procesarCSV(const char* nomArch,tArbol* arbol,void* buffer,unsigned tam,void parsearCSV(const char* linea,void* buffer),int cmp(const void*,const void*))
{
    FILE* pf;
    char linea[MAX_LINEA];
    pf=fopen(nomArch,"rt");
    if(!pf)
    {
        printf("\n El archivo csv pasado no existe, revisar el parametro mandado o crear el archivo");
        return 0;
    }

    if(!fgets(linea,MAX_LINEA-1,pf)) // leo los nombres de las variables que en el contexto generico poco me importan. De paso reviso si el archivo tiene algo
    {
        printf("\n Archivo vacio");
        return 0;
    }

    while(fgets(linea,MAX_LINEA-1,pf)) // leo el archivo completo
    {
        parsearCSV(linea,buffer);
        insertarEnArbol(arbol,buffer,tam,cmp);
    }

    fclose(pf);
}


int espejarDatos(tArbol* arbol)
{
    return espejarArbol(arbol);
}

int contarOcurrencias(tArbol* arbol,const void* dato,int cmp(const void*,const void*))
{
    return contarAparicionesDeDatoNoClave(arbol,dato,cmp);
}


int mostrarDatos(tArbol* arbol,void accion(const void*))
{
    return recorrerInOrden(arbol,accion);
}
