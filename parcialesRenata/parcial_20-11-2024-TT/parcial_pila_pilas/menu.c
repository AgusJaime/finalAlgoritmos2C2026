#include "menu.h"

char menu(const char* msj,const char* opcs)
{
    char opcion;

    do{
        printf("%s",msj);
        fflush(stdin);
        scanf("%c",&opcion);

    }while(strchr(opcs,opcion)==NULL);

    return opcion;

}
