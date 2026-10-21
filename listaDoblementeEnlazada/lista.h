#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y) ((x)>(y)?(y):(x))

typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* ant,*sig;
}tNodo;

typedef tNodo* tLista;


/// 4 PRIMITIVAS GENERICAS
void crearLista(tLista* lista);
int listaLlena(const tLista* lista,unsigned tam);
int listaVacia(const tLista* lista);
void vaciarLista(tLista* lista);
/// INSERTAR
int insertarAlPrincipio(tLista* lista,const void* dato,unsigned tam);
int insertarAlFinal(tLista* lista,const void* dato,unsigned tam);
int insertarOrdenado(tLista* lista,const void* dato,unsigned tam,int cmp(const void*,const void*));
int insertarEnPos(tLista* lista,const void* dato,unsigned tam,int pos);
/// ELIMINAR
int eliminarAlPrincipio(tLista* lista,void* dato,unsigned tam);
int eliminarAlFinal(tLista* lista,void* dato,unsigned tam);
int eliminarElemento(tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int eliminarPorPos(tLista* lista,void* dato,unsigned tam,int pos);
/// MAP,FILTER Y REDUCE
void mapLista(tLista* lista,void accion(const void*,void*),void* contexto);
int filter(tLista* lista,void* dato,int cmp(const void*,const void*));
int reduceSiModifica(tLista* lista,void accion(const void*,void*));
int reduceNoModifica(const tLista* lista, void accion(const void*,void*),void* contexto);
/// BUSQUEDAS EXTERNAS
int buscarElemento(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
/// VISTAS
int verPrimero(const tLista* lista,void* dato,unsigned tam);
int verUltimo(const tLista* lista,void* dato,unsigned tam);
int verCoincidencia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int verUltimaCoincidencia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));

#endif // LISTA_H_INCLUDED
