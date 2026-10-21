#include "indice.h"




int crearArcIndiceAPartirDeArchivoSecuencial(const char* nomArch,tArbol* arbol,unsigned tamReg,unsigned tamIndice,void extraerClave(const void*,void*),int cmp(const void*,const void*),void grabarRegEnIdx(const void*,void*))
{
    void* bufferArch,*bufferIdx;
    FILE* pf,*pIdx;

    pf=fopen(nomArch,"rb");
    if(!pf)
        return 0;

    pIdx=fopen("prodTC.idx","wb");
    if(!pIdx)
    {
        fclose(pf);
        return 0;
    }
    bufferArch=malloc(tamReg);
    if(!bufferArch)
    {
        fclose(pf);
        return 0;
    }
    bufferIdx=malloc(tamIndice);
    if(!bufferIdx)
    {
        free(bufferArch);
        fclose(pf);
        return 0;
    }

    fread(bufferArch,tamReg,1,pf);
    while(!feof(pf))
    {
        extraerClave(bufferArch,bufferIdx);
        if(!insertarEnArbol(arbol,bufferIdx,tamIndice,cmp))
        {
            fclose(pf);
            free(bufferArch);
            free(bufferIdx);
            return 0;
        }
        fread(bufferArch,tamReg,1,pf);
    }

    fclose(pf);
    free(bufferArch);
    free(bufferIdx);

    recorrerInOrden(arbol,grabarRegEnIdx,pIdx);
    return 1;
}

int cargarDatosDeArchOrdenado(tArbol* indice,FILE* pf,void* bufferArch,unsigned tam,int ini,int fin,int cmp(const void*,const void*))
{
    int medio;

    if(ini>fin)
        return 0;



    medio=(ini+fin)/2;

    fseek(pf,medio*tam,SEEK_SET);

    fread(bufferArch,tam,1,pf);

    if(!insertarEnArbol(indice,bufferArch,tam,cmp))
        return 0; // fallo la carga


    cargarDatosDeArchOrdenado(indice,pf,bufferArch,tam,ini,medio-1,cmp);
    cargarDatosDeArchOrdenado(indice,pf,bufferArch,tam,medio+1,fin,cmp);
    return 1;
}

int cargarArbolIndiceDesdeIndice(const char* nomArch,tArbol* indice,unsigned tam,int cmp(const void*,const void*))
{
    FILE* pf;
    int ce=0;
    void* bufferArch;
    pf=fopen(nomArch,"rb");
    if(!pf)
        return 0;

    bufferArch=malloc(tam);
    if(!bufferArch)
    {
        fclose(pf);
        return 0;
    }

    fseek(pf,0,SEEK_END);

    ce=ftell(pf)/tam;

    if(ce<=0)
    {
        free(bufferArch);
        fclose(pf);
        return 0;
    }


    cargarDatosDeArchOrdenado(indice,pf,bufferArch,tam,0,ce-1,cmp);

    fclose(pf);
    free(bufferArch);

    return 1;
}


