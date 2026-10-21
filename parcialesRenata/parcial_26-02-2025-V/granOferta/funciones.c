#include "funciones.h"

int cmpFecha(const t_fecha* fecha1, const t_fecha* fecha2)
{
    if(fecha1->anio!=fecha2->anio)
        return fecha1->anio - fecha2->anio;
    if(fecha1->mes!=fecha2->mes)
        return fecha1->mes - fecha2->mes;

    return fecha1->dia - fecha2->dia;
}
int cmpVto(const void* datoLista,const void* datoParam)
{
    tProd* auxLista=(tProd*)datoLista;
    tProd* auxParam=(tProd*)datoParam;
    int result=0;


    result=cmpFecha(&auxLista->fecha,&auxParam->fecha);

    if(result!=0)
        return result;


    return auxParam->cant - auxLista->cant;
}


int generarLotePrueba(const char* nomArch)
{
    FILE* pf;
    tProd vecProd[]={ {"123456","Descripcion prod 1",1,{10,11,2026},100}//,
                    ,{"123456","Descripcion prod 1",2,{25,10,2026},50}
                    ,{"123465","Descripcion prod 2",5,{01,01,2027},100}
                    ,{"123465","Descripcion prod 2",7,{15,12,2026},100}
                    ,{"123477","Descripcion prod 3",9,{11,11,2026},100}
                    ,{"123477","Descripcion prod 3",2,{01,01,2025},100}
                    ,{"123477","Descripcion prod 3",1,{01,12,2026},100}
                    ,{"123488","Descripcion prod 4",3,{10,11,2026},50}//
                    ,{"123499","Descripcion prod 5",5,{20,12,2026},200}
                    ,{"123499","Descripcion prod 5",2,{10,11,2026},150}//
                   };

    pf=fopen(nomArch,"wb");
    if(!pf)
        return 0;

    for(int i=0;i<sizeof(vecProd)/sizeof(vecProd[0]);i++){
        fwrite(&vecProd[i],sizeof(tProd),1,pf);
    }

    fclose(pf);
    return 1;
}


int generarArchivoProdAVencer(const char* archProd,tLista* listaProd,int n,t_fecha* fechaActual)
{
    tProd bufferArch,anterior;
    FILE* pProd,*pVto;
    tNodo* aux;
    int cantAgregada=0,tieneAnterior=0,continuar=1;
    pProd=fopen(archProd,"rb");
    if(!pProd)
        return 0;
    pVto=fopen(ARCH_PROD_A_VENCER,"wt");
    if(!pVto)
    {
        fclose(pProd);
        return 0;
    }

    fread(&bufferArch,sizeof(tProd),1,pProd);
    while(!feof(pProd)){
        if(cmpFecha(fechaActual,&bufferArch.fecha)<=0){ // con el igual incluyo tambien los de la misma fecha
            if(!insertarOrdenadamente(listaProd,&bufferArch,sizeof(tProd),cmpVto)){
                vaciarLista(listaProd);
                fclose(pVto);
                fclose(pProd);
                return 0;
            }
        }
        fread(&bufferArch,sizeof(tProd),1,pProd);
    }

    fclose(pProd);

    aux=(*listaProd);

    while(aux && continuar){

        bufferArch=*(tProd*)aux->dato;
        if((cantAgregada < n) || (tieneAnterior && cmpFecha(&bufferArch.fecha,&anterior.fecha)==0)){
            fprintf(pVto,"%04d%-6s%02d/%02d/%04d%010d\n",cantAgregada+1,
                    bufferArch.codProd,bufferArch.fecha.dia,bufferArch.fecha.mes,
                    bufferArch.fecha.anio,bufferArch.cant);
        cantAgregada++;
        anterior=bufferArch;
        aux=aux->sig;
        tieneAnterior=1;
        }
        else
        {
            continuar=0; // si ya hay mas cant de n y la fecha no es la misma corto la carga
        }
    }

    fclose(pVto);
    return 1;
}
tProd mostrarProximoVencimiento(tLista* listaProd)
{
    return *(tProd*)((*listaProd)->dato); // como me encargue de que quede el primero con la fecha mas corta y el stock mas grande directamente devuelvo el primero.
}



void mostrarNProductosProximosAVencer(tLista* listaProd,int n)
{
    tNodo* aux;
    tProd buffer,anterior;
    int cantAgregada=0,tieneAnterior=0,continuar=1;
    aux=(*listaProd);

    if(!(aux))
        printf("\n la lista está vacia, primero generar el archivo de productos a vencer");


    while(aux && continuar){

        buffer=*(tProd*)aux->dato;
        if((cantAgregada < n) || (tieneAnterior && cmpFecha(&buffer.fecha,&anterior.fecha)==0)){
            printf("%d. %6s %d/%d/%d %d\n",cantAgregada+1,
                    buffer.codProd,buffer.fecha.dia,buffer.fecha.mes,
                    buffer.fecha.anio,buffer.cant);
        cantAgregada++;
        anterior=buffer;
        aux=aux->sig;
        tieneAnterior=1;
        }
        else
        {
            continuar=0; // si ya hay mas cant de n y la fecha no es la misma corto la carga
        }
    }
}
