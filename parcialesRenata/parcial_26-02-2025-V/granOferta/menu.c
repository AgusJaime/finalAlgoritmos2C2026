#include "menu.h"

char menu(const char* msj,const char* opcs)
{
    char opc;

    do{
        printf("\n %s",msj);
        fflush(stdin);
        scanf("%c",&opc);
    }while(strchr(opcs,opc)==NULL);

    return opc;
}
t_fecha ingresarFecha()
{
    t_fecha fecha;
    printf("\n Ingrese el dia actual:");
    scanf("%d",&fecha.dia);
    printf("\n Ingrese el mes actual:");
    scanf("%d",&fecha.mes);
    printf("\n Ingrese el anio actual:");
    scanf("%d",&fecha.anio);

    return fecha;
}


int ingresarN()
{
    int n;

    printf("\n ingresar N productos a revisar:");
    scanf("%d",&n);
    return n;
}
