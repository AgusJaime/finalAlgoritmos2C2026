#include "funciones.h"
void pasamanosFechaYHora(tEvento* evento,tAlarma* alarma, int cantAlarmasEstadoCritico){

    if(cantAlarmasEstadoCritico==CANT_MAX_EVENTOS_NIVEL_5){
        strcpy(alarma->ultFecha,evento->fecha);
        strcpy(alarma->ultHora,evento->hora);
    }
    else
    {
        alarma->codDisp=evento->codDisp;
        strcpy(alarma->priFecha,evento->fecha);
        strcpy(alarma->priHora,evento->hora);
    }

}

int cmpCodEvento(const void* datoLista,const void* datoParam){

    tAlarma* auxLista=(tAlarma*)datoLista;
    tEvento* auxParam=(tEvento*)datoParam;
    return auxLista->codDisp - auxParam->codDisp;
}
int cmpCodAlarma(const void* datoLista,const void* datoParam){

    tAlarma* auxLista=(tAlarma*)datoLista;
    tAlarma* auxParam=(tAlarma*)datoParam;
    return auxLista->codDisp - auxParam->codDisp;
}

void parsearLinea(char* linea,tEvento* evento)
{
    char* aux=NULL;
    aux=strrchr(linea,'\n');
    if(!aux)
        return;
    *aux='\0';
    aux=strrchr(linea,'|');
    sscanf(aux+1,"%d",&evento->nivel);
    *aux='\0';
    aux=strrchr(linea,'|');
    sscanf(aux+1,"%s",evento->hora);
    *aux='\0';
    aux=strrchr(linea,'|');
    sscanf(aux+1,"%s",evento->fecha);
    *aux='\0';
    sscanf(linea,"%d",&evento->codDisp);

}

void copiarAlarmaEnArchivo(tAlarma* alarma,FILE* pf)
{
    fprintf(pf,"%d|%s|%s|%s|%s\n",alarma->codDisp,alarma->priFecha,alarma->priHora,alarma->ultFecha,alarma->ultHora);
}

int generarArchAlarma(const char* nomArch){

    FILE* pf,*pAux;
    tLista lista;
    tEvento auxEvento;
    tAlarma auxAlarma;
    auxAlarma.codDisp=0; // la inicializo para que en la funcion de pasamanosDeDatos no haya errores
    char linea[TAM_LINEA];
    int cantAlarmasEstadoCritico=0,codActual=0;
    crearLista(&lista);
    pf=fopen(nomArch,"rt");
    if(!pf)
        return 0;

    pAux=fopen(ARCH_ALERTAS,"wt");
    if(!pAux)
    {
        fclose(pf);
        return 0;
    }

    while(fgets(linea,TAM_LINEA-1,pf)){
        parsearLinea(linea,&auxEvento);
        if(auxEvento.nivel==MAXIMO_NIVEL){
            if(codActual==auxEvento.codDisp){
                cantAlarmasEstadoCritico++;
            }
            else
            {
                cantAlarmasEstadoCritico=1;
                codActual=auxEvento.codDisp;
                pasamanosFechaYHora(&auxEvento,&auxAlarma,cantAlarmasEstadoCritico);
            }


            if(cantAlarmasEstadoCritico==CANT_MAX_EVENTOS_NIVEL_5){
                pasamanosFechaYHora(&auxEvento,&auxAlarma,cantAlarmasEstadoCritico); // este pasamanos es para grabar la ultima fecha

                if(!insertarAlFinalSinDuplicados(&lista,&auxAlarma,sizeof(tAlarma),cmpCodAlarma)){
                    printf("\n alarma con estado critico ya ingresado, no se puede alterar su estado luego de insertarlo como critico");
                }
            }
        }
    }
    fclose(pf);

    while(!listaVacia(&lista)){
        sacarPrimero(&lista,&auxAlarma,sizeof(tAlarma));
        copiarAlarmaEnArchivo(&auxAlarma,pAux);
    }

    fclose(pAux);
    return 1;
}


int mostrarArchivo(const char* nomArch){

    FILE* pf;
    char linea[TAM_LINEA];
    pf=fopen(nomArch,"rt");
    if(!pf)
        return 0;
    while(fgets(linea,TAM_LINEA-1,pf)){
        printf("\n %s",linea);
    }
    fclose(pf);
    return 1;
}

