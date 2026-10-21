#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "..\arbolBinarioBusqueda\ABB.h"
#define TAM_LINEA 200 // se establece un largo promedio

int cargarArchivoBinarioDesordenadoEnIndice(tArbol* indice,const char* nomArch,unsigned tamDato,unsigned tamIndice,
                                            void extraerClave(void*,const void*,unsigned),int cmp(const void*,const void*),void accion(void*,const void*));

int cargarArchivoTextoDesordenadoEnIndice(tArbol* indice,const char* nomArch,unsigned tamDato,unsigned tamIndice,
                                          void extraerClave(void*,const void*,unsigned),void parseo(const char*,void*),int cmp(const void*,const void*),void accion(void*,const void*));

int cargarArchivoBinarioOrdenadoEnIndice(tArbol* indice,const char* nomArch,unsigned tamDato,unsigned tamIndice,
                                         int cmp(const void*,const void*),void extraerClave(const void*,void*,unsigned),void accion(const void*,void*));


int cargarDatosOrdenadosEnIndice(tArbol* indice,FILE* pf,void* bufferDato,void* bufferIndice,
                                 unsigned tamDato,unsigned tamIndice,int ini,int fin,void extraerClave(const void*,void*,unsigned),
                                 int cmp(const void*,const void*));

int eliminarDatoIndice(tArbol* indice,void* dato,void* bufferRecuperado,unsigned tamIndice,int cmp(const void*,const void*),void extraerClave(const void*,void*,unsigned));
int agregarDatoIndice(tArbol* indice,const char* nomArch,void* dato,unsigned tamDato,unsigned tamIndice,int cmp(const void*,const void*),void extraerClave(const void*,void*,unsigned ),int agregarAlArchivo(const void*,FILE*));

#endif // INDICE_H_INCLUDED
