#include "menu.h"


/*
    En este examen no se puede usar insertarNenLista ya que no dice que se deben guardar SOLO N productos menores
    Ya que por ejemplo el de mayor fecha puede estar repetido N veces y el de menor fecha tambien
    Cosa que en insertarNenLista no podria pasar, ya que esa funcion solo permite que se repita
    el ultimo valor de la lista.
*/
int main()
{
    tLista listaProd;
    t_fecha fechaActual;
    tProd prod;
    int n, fechaIngresada = 0;
    char opcion;

    crearLista(&listaProd);

    opcion = menu(MSJ, OPCS);

    while (opcion != OPC_SALIR) {

        if (opcion == OPC_GENERAR_LOTE) {
            if (generarLotePrueba("stock.dat"))
                printf("\n Lote de prueba generado en ""stock.dat"".");
            else
                printf("\n No se pudo crear el archivo ""stock.dat"".");
        }

        if (opcion == OPC_INGRESAR_FECHA) {
            fechaActual = ingresarFecha();
            fechaIngresada = 1;
            vaciarLista(&listaProd);   // la lista dependia de la fecha anterior
            printf("\n Fecha cargada. Genere el archivo para actualizar los productos.");
        }

        if (opcion == OPC_MOSTRAR_N) {
            if (!listaProd)
                printf("\n No hay productos cargados. Primero ingrese la fecha y genere el archivo.");
            else {
                n = ingresarN();
                mostrarNProductosProximosAVencer(&listaProd, n);
            }
        }

        if (opcion == OPC_GENERAR_ARCH) {
            if (!fechaIngresada)
                printf("\n Primero ingrese la fecha actual.");
            else {
                n = ingresarN();
                vaciarLista(&listaProd);   // evita duplicar registros si se genera dos veces
                if (generarArchivoProdAVencer("stock.dat", &listaProd, n, &fechaActual))
                    printf("\n Archivo '%s' generado.", ARCH_PROD_A_VENCER);
                else
                    printf("\n No se pudo generar el archivo. Verifique que exista '%s' (opcion 1).", "stock.dat");
            }
        }

        if (opcion == OPC_MOSTRAR_PRIMERO) {
            if (!listaProd)
                printf("\n No hay productos vigentes cargados. Primero ingrese la fecha y genere el archivo.");
            else {
                prod = mostrarProximoVencimiento(&listaProd);
                printf("\n Producto mas proximo a vencer:");
                printf("\n Codigo: %.6s  Vto: %02d/%02d/%04d  Stock: %d\n",
                       prod.codProd, prod.fecha.dia, prod.fecha.mes, prod.fecha.anio, prod.cant);
            }
        }

        opcion = menu(MSJ, OPCS);
    }

    vaciarLista(&listaProd);
    return 0;
}
