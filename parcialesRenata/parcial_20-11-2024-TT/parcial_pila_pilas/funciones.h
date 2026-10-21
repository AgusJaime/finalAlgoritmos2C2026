#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "pilaDinamica.h"

int cargarPilaGeneral(tPila* ppe,tPila* p1,tPila* p2,tPila* p3,tPila* p4);
int cargarPilaEspecifica(tPila* pila,void* cadDatos,int cantDatos,int tam);
tPila* crearPilaEnteros(tPila* pilaGral,tPila* pilaEnteros,int tam);
void mostrarPilas(tPila* pila,int tam);
void mostrarPila(tPila* pe,int tam);
#endif // FUNCIONES_H_INCLUDED
