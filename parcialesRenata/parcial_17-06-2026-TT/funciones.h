#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "lista.h"
#define TAM_LINEA 200
#define ARCH_ALERTAS "alarmas.txt"
#define MAXIMO_NIVEL 5
#define CANT_MAX_EVENTOS_NIVEL_5 3
typedef struct{

    int codDisp;
    char fecha[9];
    char hora[7];
    int nivel;
}tEvento;

typedef struct{
    int codDisp;
    char priFecha[9];
    char priHora[7];
    char ultFecha[9];
    char ultHora[7];
}tAlarma;

void pasamanosFechaYHora(tEvento* evento,tAlarma* alarma, int cantAlarmasEstadoCritico);
int cmpCodEvento(const void*,const void*);
int cmpCodAlarma(const void* datoLista,const void* datoParam);
void parsearLinea(char* linea,tEvento* evento);
int generarArchAlarma(const char* nomArch);
int mostrarArchivo(const char* nomArch);
#endif // FUNCIONES_H_INCLUDED
