#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "colaDinamica.h"
#include <ctype.h>
typedef struct
{
    char codLote[5];
    int idProducto;
    char resultadoControl[6];
}Registro;

int generarRegistroLote(const char* nomArch);
int procesarArchivo(int x);
void cerrarLote(tCola *ok, tCola *falla, int total, int fallas,
                int x, FILE *fObs, FILE *fApr) ;
void volcarCola(tCola *c, FILE *f);
#endif // FUNCIONES_H_INCLUDED
