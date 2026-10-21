#include "menu.h"


char menu(const char* msj,const char* opc){

    char opcion;

    do{
        printf("%s",msj);
        fflush(stdin);
        scanf("%c",&opcion);
    }while(strchr(opc,opcion)==NULL);

    return opcion;
}
