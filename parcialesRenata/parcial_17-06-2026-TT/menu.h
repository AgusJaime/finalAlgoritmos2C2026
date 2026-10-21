#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPC_GENERAR_ARCHIVO '1'
#define OPC_MOSTRAR_ARCH_ENTRADA '2'
#define OPC_MOSTRAR_ARCH_SALIDA '3'
#define OPC_SALIR '4'
#define OPCS "1234"
#define MSJ "\n ELIJA UNA OPCION:\n(1)GENERAR ARCHIVO DE ALARMAS \n"\
            "(2)MOSTRAR ARCHIVO ENTRADA\n"\
            "(3)MOSTRAR ARCHIVO SALIDA\n"\
            "(4)SALIR\n"

char menu(const char* msj,const char* opc);

#endif // MENU_H_INCLUDED
