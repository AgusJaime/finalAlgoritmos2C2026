#include "funciones.h"

int cargarPilaGeneral(tPila* ppe,tPila* p1,tPila* p2,tPila* p3,tPila* p4)
{
    crearPila(ppe);

    crearPila(p1);
    crearPila(p2);
    crearPila(p3);
    crearPila(p4);
    int vec1[]={1,2,3,4},
        vec2[]={5,6,7,8},
        vec3[]={9,10,11,12},
        vec4[]={13,14,15,16};
    cargarPilaEspecifica(p1,vec1,(sizeof(vec1)/sizeof(vec1[0])),sizeof(int));
    cargarPilaEspecifica(p2,vec2,(sizeof(vec2)/sizeof(vec2[0])),sizeof(int));
    cargarPilaEspecifica(p3,vec3,(sizeof(vec3)/sizeof(vec3[0])),sizeof(int));
    cargarPilaEspecifica(p4,vec4,(sizeof(vec4)/sizeof(vec4[0])),sizeof(int));
    apilar(ppe,p1,sizeof(tPila));
    apilar(ppe,p2,sizeof(tPila));
    apilar(ppe,p3,sizeof(tPila));
    apilar(ppe,p4,sizeof(tPila));

    return 1;
}


int cargarPilaEspecifica(tPila* pila,void* cadDatos,int cantDatos,int tam)
{
    // suponemos que la pila ya esta creada
    int ce=0;

    while(ce<cantDatos){

        if(!apilar(pila,cadDatos,tam))
           {
               vaciarPila(pila);
               return 0;
           }
        cadDatos+=tam;
        ce++;
    }
    return 1;
}

tPila* crearPilaEnteros(tPila* pilaGral,tPila* pilaEnteros,int tam)
{
    tPila pilaAux;
    crearPila(pilaEnteros);
    crearPila(&pilaAux);
    void* dato;
    if(!(*pilaGral))
        return NULL;

    dato=malloc(tam);
    if(!(dato))
    {
        return NULL;
    }
    while(desapilar(pilaGral,&pilaAux,sizeof(tPila))){
        while(desapilar(&pilaAux,dato,tam)){
            apilar(pilaEnteros,dato,tam);
        }
    }
    return pilaEnteros;
}


void mostrarPilas(tPila* pila,int tam)
{
    tPila aux1;
    crearPila(&aux1);
    while(desapilar(pila,&aux1,sizeof(tPila))){
        mostrarPila(&aux1,tam);
    }
    vaciarPila(&aux1);
}


void mostrarPila(tPila* pe,int tam)
{
    int entero;
    while(desapilar(pe,&entero,tam)){
        printf("-%d",entero);
    }
}
