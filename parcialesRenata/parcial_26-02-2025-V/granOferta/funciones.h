#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "listaSimple.h"
#define ARCH_PROD_A_VENCER "prod_a_vencer.txt"

typedef struct
{
    int dia;
    int mes;
    int anio;
}t_fecha;

typedef struct
{
    char codProd[7];
    char descrip[26];
    int lote;
    t_fecha fecha;
    int cant;
}tProd;

int generarArchivoProdAVencer(const char* archProd,tLista* listaProd,int n,t_fecha* fechaActual);
tProd mostrarProximoVencimiento(tLista* listaProd);
void mostrarNProductosProximosAVencer(tLista* listaProd,int n);
int generarLotePrueba(const char* nomArch);
#endif // FUNCIONES_H_INCLUDED
