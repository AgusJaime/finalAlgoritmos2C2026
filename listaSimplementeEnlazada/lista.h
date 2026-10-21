#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ACEPTA_DUP 20
#define DUPLICADO 40
#define DUPLICATE 101
#define MIN(x,y) ((x)>(y)?(y):(x))
typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
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
int insertarOrdenado(tLista* lista,const void* dato,unsigned tam,int dup,int cmp(const void*,const void*),void accion(const void*,void*));
int insertarMejoresNListaV2(tLista* lista, const void* dato, unsigned tam, int n,
                          int cmp(const void*, const void*));
/// ELIMINAR
int eliminarAlPrincipio(tLista* lista, void* dato,unsigned tam);
int eliminarAlFinal(tLista* lista, void* dato,unsigned tam);
int eliminarOrdenado(tLista* lista, void* dato,unsigned tam,int cmp(const void*,const void*));
/// RECORRIDOS
void recorrerLista(const tLista* lista,void accion(const void*));
void recorridoInversoLista(const tLista* lista,void accion(const void*));
/// MAP, FILTER Y REDUCE
void mapLista(tLista* lista,void accion(void*,void*),void* contexto);
void filter(tLista* lista,void* dato,int cmp(const void*,const void*),void accion(const void*,void*),void* contexto);
void* reduceNoModifica(const tLista* lista,void accion(const void*,void*),void* contexto);
void* reduceSiModifica(tLista* lista,void accion(const void*,void*));
/// BUSQUEDAS
int buscarDatoEspecifico(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
int buscarUltimaCoincidencia(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));
/// ORDENAMIENTO
int ordenarLista(tLista* lista,unsigned tam,int cmp(const void*,const void*));
/// FUNCIONES PARA VER DATOS
int verPrimero(const tLista* lista,void* dato,unsigned tam);
int verUltimo(const tLista* lista,void* dato,unsigned tam);
int verMenor(const tLista* lista, void* dato,unsigned tam,int cmp(const void*,const void*));
int verMayor(const tLista* lista,void* dato,unsigned tam,int cmp(const void*,const void*));


#endif // LISTA_H_INCLUDED
