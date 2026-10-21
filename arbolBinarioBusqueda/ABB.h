#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MIN(x,y) ((x)>(y)?(y):(x))

typedef struct sNodo
{
    void* dato;
    unsigned tam;
    struct sNodo* izq,*der;
}tNodoA;

typedef tNodoA* tArbol;


void crearArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol,const void* dato,unsigned tam,int cmp(const void*,const void*));
int alturaArbol(tArbol* arbol);
int eliminarRaiz(tArbol* arbol);
int eliminarDato(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*));
int contarNodos(tArbol* arbol);
int contarHojas(tArbol* arbol);
int buscarElemento(const tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*));
int buscarElementoYEliminarlo(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*));
int menorElemento(const tArbol* arbol,void* dato,unsigned tam);
int mayorElemento(const tArbol* arbol,void* dato,unsigned tam);
int cortarHojas(tArbol* arbol);
int vaciarArbol(tArbol* arbol);
int contarNodosDesdeXNivel(tArbol* arbol,int nivel);
int contarNodosHastaXNivel(tArbol* arbol,int nivel);
int contarNodosDeXNivel(tArbol* arbol,int nivel);
int podarNodosConHijosXIzquierda(tArbol* arbol);
int contarNodosConHijosSOLOXIzquierda(const tArbol* arbol);
int contarNodosConHijosXIzquierda(const tArbol* arbol);
int contarNodosDondeDatoMayorA(const tArbol* arbol,void* dato,int resolverCondicion(const void*,const void*));
int contarNodosDondeDatoMayorAReducido(const tArbol* arbol,void* dato,int resolverCondicion(const void*,const void*));
int mostrarNodosDeXAltura(const tArbol* arbol,int nivelElegido,void accion(const void*));
int mostrarNodosHastaXAltura(const tArbol* arbol,int nivelMax,int inclusive,void accion(const void*));
int mostrarNodosDesdeXAltura(const tArbol* arbol,int nivelMax,int inclusive, void accion(const void*));
///////////////////////////////////////////////////////////////////////
int esCompletoHastaXNivel(tArbol* arbol,int nivel);
int contarNodosHastaXNivel(tArbol* arbol,int nivel);
int esBalanceado(tArbol* arbol);
int esBalanceadoHastaXNivel(tArbol* arbol,int nivel);
int esAVL(tArbol* arbol);
int esAVLConAltura(tArbol* arbol);
///FILTER Y REDUCE ///////////////////////////////////////////////////
void filterArbol(tArbol* arbol, void* filtro, int cmp(const void*,const void*), void accion(void*));
void reduceArbol( tArbol* arbol, void* acc, void accion(void*,const void*));
#endif // ABB_H_INCLUDED
