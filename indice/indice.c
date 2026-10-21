#include "indice.h"

int cargarArchivoBinarioDesordenadoEnIndice(tArbol* indice,const char* nomArch,unsigned tamDato,unsigned tamIndice,
                                            void extraerClave(void*,const void*,unsigned),
                                            int cmp(const void*,const void*),void accion(void*,const void*))
{
    FILE* pf;
    void* bufferIndice,*bufferDato;
    int pos=0;
    pf=fopen(nomArch,"rb");

    if(!pf)
        return 0;

    bufferIndice=malloc(tamIndice);
    if(!bufferIndice)
    {
        fclose(pf);
        return 0;
    }

    bufferDato=malloc(tamDato);

    if(!bufferDato)
    {
        free(bufferIndice);
        fclose(pf);
        return 0;
    }

    fread(bufferDato,tamDato,1,pf);
    while(!feof(pf)){

        extraerClave(bufferDato,bufferIndice,pos);
        if(!insertarEnArbol(indice,bufferIndice,tamIndice,cmp)){
            free(bufferDato);
            free(bufferIndice);
            vaciarArbol(indice);
            fclose(pf);
            return 1;
        }
        fread(bufferDato,tamDato,1,pf);
        pos++;
    }

    free(bufferDato);
    free(bufferIndice);
    fclose(pf);
    return 1;
}

int cargarArchivoTextoDesordenadoEnIndice(tArbol* indice,const char* nomArch,unsigned tamDato,unsigned tamIndice,
                                          void extraerClave(void*,const void*,unsigned),void parseo(const char*,void*),
                                          int cmp(const void*,const void*),void accion(void*,const void*))
{
    FILE* pt;
    void* bufferDato,*bufferIndice;
    char linea[TAM_LINEA];
    int pos=0;
    pt=fopen(nomArch,"rt");
    if(!pt)
        return 0;

    bufferDato=malloc(tamDato);
    if(!bufferDato)
    {
        fclose(pt);
        return 0;
    }

    bufferIndice=malloc(tamIndice);
    if(!bufferIndice)
    {
        free(bufferDato);
        fclose(pt);
        return 0;
    }

    while(fgets(linea,TAM_LINEA-1,pt)){
        parseo(linea,bufferDato);
        extraerClave(bufferDato,bufferIndice,pos);
        if(!insertarEnArbol(indice,bufferIndice,tamIndice,cmp)){
            free(bufferDato);
            free(bufferIndice);
            vaciarArbol(indice);
            fclose(pt);
            return 1;
        }
        pos++;
    }

    free(bufferDato);
    free(bufferIndice);
    fclose(pt);
    return 1;
}

int cargarArchivoBinarioOrdenadoEnIndice(tArbol* indice,const char* nomArch,unsigned tamDato,unsigned tamIndice,
                                         int cmp(const void*,const void*),void extraerClave(const void*,void*,unsigned),
                                         void accion(const void*,void*))
{
    FILE* pf;
    int ce=0;
    void* bufferDato,*bufferIndice;
    pf=fopen(nomArch,"rb");
    if(!pf)
        return 0;

    bufferDato=malloc(tamDato);
    if(!bufferDato)
    {
        fclose(pf);
        return 0;
    }

    bufferIndice=malloc(tamIndice);
    if(!bufferIndice)
    {
        free(bufferDato);
        fclose(pf);
        return 0;
    }

    fseek(pf,0,SEEK_END);

    ce=ftell(pf)/tamDato;

    if(ce<=0)
        return 0;


    cargarDatosOrdenadosEnIndice(indice,pf,bufferDato,bufferIndice,tamDato,tamIndice,0,ce-1,extraerClave,cmp);

    return 1;
}

int cargarDatosOrdenadosEnIndice(tArbol* indice,FILE* pf,void* bufferDato,void* bufferIndice,
                                 unsigned tamDato,unsigned tamIndice,int ini,int fin,void extraerClave(const void*,void*,unsigned),
                                 int cmp(const void*,const void*))
{

    int medio=(ini+fin)/2;

    if(ini>fin)
        return 0; // no hay datos para cargar


    fseek(pf,tamDato*medio,SEEK_SET);
    fread(bufferDato,tamDato,1,pf);
    extraerClave(bufferDato,bufferIndice,medio);
    insertarEnArbol(indice,bufferIndice,tamIndice,cmp);

    cargarDatosOrdenadosEnIndice(indice,pf,bufferDato,bufferIndice,tamDato,tamIndice,0,medio-1,extraerClave,cmp);
    cargarDatosOrdenadosEnIndice(indice,pf,bufferDato,bufferIndice,tamDato,tamIndice,medio+1,fin,extraerClave,cmp);
    return 1;
}


int eliminarDatoIndice(tArbol* indice,void* dato,void* bufferRecuperado,unsigned tamIndice,int cmp(const void*,const void*),void extraerClave(const void*,void*,unsigned))
{
    void* bufferIndice;
    int result;
    bufferIndice=malloc(tamIndice);
    if(!bufferIndice)
        return 0;

    extraerClave(dato,bufferIndice,-1);

    result=buscarElementoYEliminarlo(indice,bufferIndice,tamIndice,cmp);

    memcpy(bufferRecuperado,bufferIndice,tamIndice); // le devolvemos al usuario lo que tenia el arbol y ademas le va a servir para saber la pos del registro en el archivo
    free(bufferIndice);
    return result;
}

int agregarDatoIndice(tArbol* indice,const char* nomArch,void* dato,unsigned tamDato,unsigned tamIndice,int cmp(const void*,const void*),void extraerClave(const void*,void*,unsigned ),int agregarAlArchivo(const void*,FILE*))
{
    FILE* pf;
    void *bufferIndice;
    int ce=0;


    pf=fopen(nomArch,"ab"); // lo abro para que agregue, no para que cree el archivo

    if(!pf)
        return 0;

    bufferIndice=malloc(tamIndice);
    if(!bufferIndice)
    {
        fclose(pf);
        return 0;
    }

    fseek(pf,0,SEEK_END);

    ce=ftell(pf)/tamDato; // la cant de elementos va de 1 a infinito (0 es si no tiene nada)

    extraerClave(dato,bufferIndice,ce);

    if(!insertarEnArbol(indice,bufferIndice,tamIndice,cmp)){
        free(bufferIndice);
        fclose(pf);
        return 0;
    }

    // una vez que insertamos en el indice, debemos agregarlo al archivo. Le dejamos la responsabilidad al programador/usuario para que el mismo codifique la funcion dependiendo del tipo de dato que quiere almacenar en el archivo
    if(!agregarAlArchivo(dato,pf))
    {
        eliminarDato(indice,bufferIndice,tamIndice,cmp);
        free(bufferIndice);
        fclose(pf);
        return 0;
    }

    free(bufferIndice);
    fclose(pf);
    return 1;
}
