#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(x,y) ((x)>(y)?(y):(x))

typedef struct sNodo{

    void* dato;
    unsigned tamDato;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarAlFinalSinDuplicados(tLista* lista,const void* dato,unsigned tam,int cmp(const void*,const void*));
int verConcordancia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int sacarPrimero(tLista* lista,void* dato,unsigned tam);
int listaLlena(const tLista* lista,unsigned tam);
int listaVacia(const tLista* lista);
void vaciarLista(tLista* lista);
#endif // LISTA_H_INCLUDED
