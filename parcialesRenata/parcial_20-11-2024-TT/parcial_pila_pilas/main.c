#include "funciones.h"
#include "menu.h"



int main()
{
    tPila ppe,pe,p1,p2,p3,p4;

    char opc;

    cargarPilaGeneral(&ppe,&p1,&p2,&p3,&p4);

    opc=menu(MSJ,OPCS);


    while(opc!='3'){

        if(opc=='1'){
            if(pilaVacia(&ppe)==1)
                printf("\n pila vacia");
            else{
                mostrarPilas(&ppe,sizeof(int));
            }
        }
        if(opc=='2'){
            crearPilaEnteros(&ppe,&pe,sizeof(int));
            if(pilaVacia(&pe)){
                printf("\n pila vaciaa");
            }
            mostrarPila(&pe,sizeof(int));

        }
        cargarPilaGeneral(&ppe,&p1,&p2,&p3,&p4);
        opc=menu(MSJ,OPCS);
    }

    return 0;
}
