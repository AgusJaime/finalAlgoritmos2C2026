#include "menu.h"
#include "funciones.h"



int main()
{
    char opcion=menu(MSJ,OPCS);

    while(opcion!=OPC_SALIR){

        if(opcion==OPC_GENERAR_ARCHIVO){
            generarArchAlarma("eventos.txt");
        }
        if(opcion==OPC_MOSTRAR_ARCH_ENTRADA){
            if(!mostrarArchivo("eventos.txt"))
                printf("\n el archivo de eventos no existe! creelo para poder visualizarlo");
        }
        if(opcion==OPC_MOSTRAR_ARCH_SALIDA){
            if(!mostrarArchivo("alarmas.txt"))
                printf("\n el archivo aun no fue creado! Elija la opcion de generar archivo para visualizarlo");

        }
        opcion=menu(MSJ,OPCS);
    }
    return 0;
}
