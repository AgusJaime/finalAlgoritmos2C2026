#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED
#include "ABB.h"


int crearArcIndiceAPartirDeArchivoSecuencial(const char* nomArch,tArbol* arbol,unsigned tamReg,unsigned tamIndice,void extraerClave(const void*,void*),int cmp(const void*,const void*),void grabarRegEnIdx(const void*,void*));

#endif // INDICE_H_INCLUDED
