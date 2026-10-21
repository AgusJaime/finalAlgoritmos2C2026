#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y) ((x)>(y)?(y):(x))
typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tListaC;

void crearListaCircular(tListaC* lista);
int listaLlena(const tListaC* lista,unsigned tam);
int listaVacia(const tListaC* lista);
void vaciarListaCircular(tListaC* lista);
/// INSERTAR
int insertarAlPrincipio(tListaC* lista,const void* dato,unsigned tam);
int insertarAlFinal(tListaC* lista,const void* dato,unsigned tam);
int insertarOrdenado(tListaC* lista,const void* dato,unsigned tam,int cmp(const void*,const void*),void accion(const void*,void*));
/// ELIMINAR
int eliminarAlPrincipio(tListaC* lista,void* dato,unsigned tam);
int eliminarAlFinal(tListaC* lista,void* dato,unsigned tam);
int eliminarOrdenado(tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
/// RECORRIDOS
void recorrerLista(const tListaC* lista,void accion(const void*));
void recorridoInversoLista(const tListaC* lista,void accion(const void*));
/// MAP, FILTER Y REDUCE
void mapLista(tListaC* lista,void accion(void*,void*),void* contexto);
void filter(tListaC* lista,void* dato,int cmp(const void*,const void*),void accion(const void*,void*),void* contexto);
void* reduceNoModifica(const tListaC* lista,void accion(const void*,void*),void* contexto);
void* reduceSiModifica(tListaC* lista,void accion(const void*,void*));
/// BUSQUEDAS
int buscarDatoEspecifico(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int buscarUltimaCoincidencia(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
/// ORDENAMIENTO
int ordenarLista(tListaC* lista,unsigned tam,int cmp(const void*,const void*));
/// FUNCIONES PARA VER DATOS
int verPrimero(const tListaC* lista,void* dato,unsigned tam);
int verUltimo(const tListaC* lista,void* dato,unsigned tam);
int verMenor(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int verMayor(const tListaC* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
#endif // LISTACIRCULAR_H_INCLUDED
