#include "ABB.h"


tArbol* buscarNodo(const tArbol* arbol,const void* dato,int cmp(const void*,const void*)){
    int comp=0;
    if(!(*arbol))
        return NULL;

    comp=cmp((*arbol)->dato,dato);

    if(comp>0)
        return buscarNodo(&(*arbol)->izq,dato,cmp);
    else if(comp<0){
        return buscarNodo(&(*arbol)->der,dato,cmp);
    }
    else
        return (tArbol*)arbol;

}

tArbol* buscarMayorNodo(const tArbol* arbol){

    if(!(*arbol))
        return NULL;

    while((*arbol)->der)
        arbol=&(*arbol)->der;

    return (tArbol*)arbol;
}

tArbol* buscarMenorNodo(const tArbol* arbol){

    if(!(*arbol))
        return NULL;

    while((*arbol)->izq)
        arbol=&(*arbol)->izq;

    return (tArbol*)arbol;
}

void crearArbol(tArbol* arbol)
{
    (*arbol)=NULL;
}
int insertarEnArbol(tArbol* arbol,const void* dato,unsigned tam,int cmp(const void*,const void*))
{
    int comp=0;
    if(!(*arbol)){
        (*arbol)=(tNodoA*)malloc(sizeof(tNodoA));
        if(!(*arbol))
            return 0;

        (*arbol)->dato=malloc(tam);
        if(!(*arbol)->dato){
            free((*arbol));
            return 0;
        }
        memcpy((*arbol)->dato,dato,tam);
        (*arbol)->tam=tam;
        (*arbol)->der=(*arbol)->izq=NULL;

        return 1;
    }
    comp=cmp((*arbol)->dato,dato);
    if(comp>0){
        return insertarEnArbol(&(*arbol)->izq,dato,tam,cmp);
    }
    else if(comp<0){
        return insertarEnArbol(&(*arbol)->der,dato,tam,cmp);
    }
    else
        return -1; // DUPLICADO

}


int alturaArbol(tArbol* arbol){

    int hd,hi;
    if(!(*arbol))
        return 0;
    hi=alturaArbol(&(*arbol)->izq);
    hd=alturaArbol(&(*arbol)->der);

    return 1 + (hi>hd?hi:hd);
}
int eliminarRaiz(tArbol* arbol)
{
    tNodoA** remp,*elim;

    if(!(*arbol)){
        return 0;
    }

    free((*arbol)->dato);

    if(!(*arbol)->der && !(*arbol)->izq){
        free((*arbol));
        (*arbol)=NULL;
        return 1;
    }

    remp=alturaArbol(&(*arbol)->izq)>alturaArbol(&(*arbol)->der)?buscarMayorNodo(&(*arbol)->izq):buscarMenorNodo(&(*arbol)->der);

    elim=(*remp);
    (*arbol)->dato=elim->dato;
    (*arbol)->tam=elim->tam;
    (*remp)=elim->izq?elim->izq:elim->der;

    free(elim);

    return 1;

}
int eliminarDato(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tArbol* bsq;

    if(!(bsq=buscarNodo(arbol,dato,cmp))){
        return 0; // no se encontro el elemento
    }

    memcpy(dato,(*bsq)->dato,MIN(tam,(*bsq)->tam));

    return eliminarRaiz(bsq);
}

int contarNodos(tArbol* arbol)
{
    if(!(*arbol))
        return 0;

    return 1 + contarNodos(&(*arbol)->izq) + contarNodos(&(*arbol)->der);
}
int contarHojas(tArbol* arbol)
{
    if(!(*arbol))
        return 0;

    if(!(*arbol)->izq && !(*arbol)->der)
        return 1;

    return contarHojas(&(*arbol)->izq) + contarHojas(&(*arbol)->der);
}
int buscarElemento(const tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*))
{
    tArbol* bsq;

    if(!(bsq=buscarNodo(arbol,dato,cmp)))
        return 0;
    memcpy(dato,(*bsq)->dato,MIN(tam,(*bsq)->tam));

    return 1;
}

int buscarElementoYEliminarlo(tArbol* arbol,void* dato,unsigned tam,int cmp(const void*,const void*))
{

    tArbol* bsq;

    if(!(bsq=buscarNodo(arbol,dato,cmp)))
        return 0; // el dato no esta en el arbol

    memcpy(dato,(*bsq)->dato,MIN(tam,(*bsq)->tam));

    return eliminarRaiz(bsq);
}

int menorElemento(const tArbol* arbol,void* dato,unsigned tam){
    tArbol* menor;

    if(!(menor=buscarMenorNodo(arbol)))
        return 0;
    memcpy(dato,(*menor)->dato,MIN(tam,(*menor)->tam));
    return 1;
}

int mayorElemento(const tArbol* arbol,void* dato,unsigned tam){

    tArbol* mayor;

    if(!(mayor=buscarMayorNodo(arbol)))
        return 0;
    memcpy(dato,(*mayor)->dato,MIN(tam,(*mayor)->tam));
    return 1;
}

int cortarHojas(tArbol* arbol)
{
    if(!(*arbol))
        return 0;

    if(!(*arbol)->izq && !(*arbol)->der)
    {
        free((*arbol)->dato);
        free((*arbol));
        return 1;
    }

    return cortarHojas(&(*arbol)->izq) + cortarHojas(&(*arbol)->der);
}


int vaciarArbol(tArbol* arbol){

    if(!(*arbol))
        return 0;

    vaciarArbol(&(*arbol)->izq);
    vaciarArbol(&(*arbol)->der);
    free((*arbol)->dato);
    free((*arbol));
    return 1;
}
int contarNodosDesdeXNivel(tArbol* arbol,int nivel){

    if(!(*arbol))
        return 0;

    if(nivel<=0){
        return 1 + contarNodosDesdeXNivel(&(*arbol)->izq,nivel-1) + contarNodosDesdeXNivel(&(*arbol)->der,nivel-1);
    }
    return 0 + contarNodosDesdeXNivel(&(*arbol)->izq,nivel-1) + contarNodosDesdeXNivel(&(*arbol)->der,nivel-1);
}
int contarNodosHastaXNivel(tArbol* arbol,int nivel){

    if(!(*arbol) || nivel<0)
        return 0;

    return 1+ contarNodosHastaXNivel(&(*arbol)->izq,nivel-1) + contarNodosHastaXNivel(&(*arbol)->der,nivel-1);
}
int contarNodosDeXNivel(tArbol* arbol,int nivel){

    if(!(*arbol) || nivel<0)
        return 0;

    if(nivel==0)
        return 1;

    return contarNodosDeXNivel(&(*arbol)->izq,nivel -1) + contarNodosDeXNivel(&(*arbol)->der,nivel-1);
}


void espejarArbol(tArbol* arbol){
    tNodoA* aux;
    if(!(*arbol))
        return;

    aux=(*arbol)->izq;
    (*arbol)->izq=(*arbol)->der;
    (*arbol)->der=aux;
    espejarArbol(&(*arbol)->izq);
    espejarArbol(&(*arbol)->der);
}

int esCompleto(tArbol* arbol){

    return contarNodos(arbol)==pow(2,alturaArbol(arbol))-1;
}

int alturaHastaXNivel(tArbol* arbol,int nivel){

    int hi=0,hd=0;

    if(!(*arbol) || nivel<0)
        return 0;

    hi=alturaHastaXNivel(&(*arbol)->izq,nivel-1);
    hd=alturaHastaXNivel(&(*arbol)->der,nivel-1);

    return 1 + (hi>hd?hi:hd);
}


int podarNodosSOLOConHijosXIzquierda(tArbol* arbol){
    tNodoA* elim;
    if(!(*arbol))
        return 0;

    if((*arbol)->izq && !(*arbol)->der)
    {
        elim=(*arbol);
        (*arbol)=elim->izq;
        free(elim->dato);
        free(elim);
        elim=NULL;
        return podarNodosSOLOConHijosXIzquierda(arbol) + 1; // se evalua tambien el mismo nodo que acaba de actualizarse
    }

    return podarNodosSOLOConHijosXIzquierda(&(*arbol)->izq) + podarNodosSOLOConHijosXIzquierda(&(*arbol)->der);
}
int podarNodosConHijosXIzquierda(tArbol* arbol){
    ///APLICAMOS LOGICA DOWN-UP para podar desde abajo
    int tieneHijosIzq=0,podados=0;
    if(!(*arbol))
        return 0;

    if((*arbol)->izq)
        tieneHijosIzq=1;
    ///SUMA TODOS LOS NODOS ELIMINADOS DESDE CADA RAMA
    podados+=podarNodosConHijosXIzquierda(&(*arbol)->izq);///POS-ORDEN (I)
    podados+=podarNodosConHijosXIzquierda(&(*arbol)->der);///POS-ORDEN (D)

    if(tieneHijosIzq){
        podados+=eliminarRaiz(arbol); // suma 1 cada vez que elimina un nodo
    }

    return podados;///POS-ORDEN (R)
}
int contarNodosConHijosSOLOXIzquierda(const tArbol* arbol){

    if(!(*arbol))
        return 0;

    if(!(*arbol)->der && (*arbol)->izq)
        return contarNodosConHijosSOLOXIzquierda(&(*arbol)->izq)+1;


    return contarNodosConHijosSOLOXIzquierda(&(*arbol)->izq) + contarNodosConHijosSOLOXIzquierda(&(*arbol)->der);
}
int contarNodosConHijosXIzquierda(const tArbol* arbol){

    if(!(*arbol))
        return 0;

    if((*arbol)->izq)
        return contarNodosConHijosXIzquierda(&(*arbol)->izq) + contarNodosConHijosXIzquierda(&(*arbol)->der) + 1;

    return contarNodosConHijosXIzquierda(&(*arbol)->izq) + contarNodosConHijosXIzquierda(&(*arbol)->der);
}
int contarNodosDondeDatoMayorA(const tArbol* arbol,void* dato,int resolverCondicion(const void*,const void*))
{

    if(!(*arbol))
        return 0;
    if(resolverCondicion((*arbol)->dato,dato)){
            return 1 + contarNodosDondeDatoMayorA(&(*arbol)->izq,dato,resolverCondicion) + contarNodosDondeDatoMayorA(&(*arbol)->der,dato,resolverCondicion);
    }

    return contarNodosDondeDatoMayorA(&(*arbol)->der,dato,resolverCondicion); // solo llamo a derecha ya que si no resolvio la condicion quiere decir que es menor que el dato pasado, entonces la rama izq tambien.

}
int mostrarNodosDeXAltura(const tArbol* arbol,int nivelElegido,void accion(const void*))
{
    if(!(*arbol) || nivelElegido<0)
        return 0;

    if(nivelElegido==0 && accion){
        accion((*arbol)->dato);
        return 1;
    }

    return mostrarNodosDeXAltura(&(*arbol)->izq,nivelElegido-1,accion) + mostrarNodosDeXAltura(&(*arbol)->der,nivelElegido-1,accion);

}
int mostrarNodosHastaXAltura(const tArbol* arbol,int nivelMax,int inclusive,void accion(const void*))
{
    int cant=0;
    if(!(*arbol) || nivelMax<0)
        return 0;

    if((nivelMax>0 || (nivelMax==0 && inclusive)) && accion)
    {
        accion((*arbol)->dato);
        cant=1;
    }

    return cant + mostrarNodosHastaXAltura(&(*arbol)->izq,nivelMax-1,inclusive,accion) + mostrarNodosHastaXAltura(&(*arbol)->der,nivelMax-1,inclusive,accion);
}
int mostrarNodosDesdeXAltura(const tArbol* arbol,int nivelMax,int inclusive, void accion(const void*))
{
    int cant=0;
    if(!(*arbol))
        return 0;

    if((nivelMax<0 || (nivelMax==0 && inclusive)) && accion)
    {
        accion((*arbol)->dato);
        cant=1;
    }

    return cant + mostrarNodosDesdeXAltura(&(*arbol)->izq,nivelMax-1,inclusive,accion) + mostrarNodosDesdeXAltura(&(*arbol)->der,nivelMax-1,inclusive,accion);
}
///////////////////////////////////////////////////////////////////////
int esCompletoHastaXNivel(tArbol* arbol,int nivel)
{
    return contarNodosHastaXNivel(arbol,nivel)== pow(2,alturaHastaXNivel(arbol,nivel))-1;
}
int esBalanceado(tArbol* arbol) // para que sea balanceado tiene que ser completo hasta una altura menor a la maxima
{
    int nivelMaximo=alturaArbol(arbol)-1;
    return contarNodosHastaXNivel(arbol,nivelMaximo-1) == pow(2,nivelMaximo)-1;
}
int esBalanceadoHastaXNivel(tArbol* arbol,int nivel)
{
    int nivelAnterior=alturaHastaXNivel(arbol,nivel);
    return contarNodosHastaXNivel(arbol,nivelAnterior-1) == pow(2,nivelAnterior)-1;
}
int esAVL(tArbol* arbol) ///AVL: que de cada rama tenga como maximo diferencia altura 1
{
    int hd,hi;
    if(!(*arbol))
        return 1;

    hi=alturaArbol(&(*arbol)->izq);
    hd=alturaArbol(&(*arbol)->der);

    if((abs(hi-hd)>1))
        return 0; // significa que no es AVL

    return esAVL(&(*arbol)->izq) + esAVL(&(*arbol)->der);

}
int esAVLConAltura(tArbol* arbol){

    int hi=0,hd=0;

    if(!(*arbol))
        return 0; // ES AVL CON ALTURA=1/NIVEL=0

    hi=esAVLConAltura(&(*arbol)->izq);
    hd=esAVLConAltura(&(*arbol)->der);

    if(hi<0 || hd<0 || (abs(hi-hd)>1))
        return -1; // no es AVL

    return 1 + (hi>hd?hi:hd);
}
///FILTER Y REDUCE ///////////////////////////////////////////////////
void filterArbol(tArbol* arbol, void* filtro, int cmp(const void*,const void*), void accion(void*))
{
    if(!(*arbol))
        return;

    filterArbol(&(*arbol)->izq,filtro,cmp,accion);
    filterArbol(&(*arbol)->der,filtro,cmp,accion);


    if(cmp((*arbol)->dato,filtro)!=0)
        eliminarRaiz(arbol);
    else if(accion)
        accion((*arbol)->dato);
}
void reduceArbol( tArbol* arbol, void* acc, void accion(void*,const void*)){

    if(!(*arbol))
        return;

    reduceArbol(&(*arbol)->izq,acc,accion);
    reduceArbol(&(*arbol)->der,acc,accion);
    if(!(*arbol)->izq && !(*arbol)->der){
        accion(acc,(*arbol)->dato);
        free((*arbol)->dato);
        free((*arbol));
        (*arbol)=NULL;
    }
}

void consumirArbol(tArbol* arbol,void* acc,void accion(const void*,void*))
{
    if(!(*arbol))
        return;

    consumirArbol(&(*arbol)->izq,acc,accion);
    consumirArbol(&(*arbol)->der,acc,accion);
    accion((*arbol)->dato,acc);
    free((*arbol)->dato);
    free((*arbol));
    (*arbol)=NULL;
}


void reduceArbolSiModifica(tArbol* arbol,void accion(const void*,void*))
{
    if(!(*arbol))
        return;

    consumirArbol(&(*arbol)->izq,(*arbol)->dato,accion);
    consumirArbol(&(*arbol)->der,(*arbol)->dato,accion)
}




