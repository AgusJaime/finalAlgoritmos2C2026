#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "funciones.h"
#define MSJ "Elegir entre estas opciones:\n"\
            "(1)Generar lote de prueba\n"\
            "(2)Ingresar fecha actual\n"\
            "(3)Mostrar los ""n"" productos más proximos a vencer\n"\
            "(4)Generar archivo ""prod_a_vencer.txt""\n"\
            "(5)Mostrar producto mas proximo a vencer\n"\
            "(6)Salir"

#define OPCS "123456"
#define OPC_GENERAR_LOTE   '1'
#define OPC_INGRESAR_FECHA '2'
#define OPC_MOSTRAR_N      '3'
#define OPC_GENERAR_ARCH   '4'
#define OPC_MOSTRAR_PRIMERO '5'
#define OPC_SALIR          '6'

char menu(const char* msj,const char* opcs);
t_fecha ingresarFecha();
int ingresarN();

#endif // MENU_H_INCLUDED
