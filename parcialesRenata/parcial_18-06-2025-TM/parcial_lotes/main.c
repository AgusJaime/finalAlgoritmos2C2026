#include "funciones.h"

#define MSJ  "\n--- MENU ---\n" \
             "A. Ingresar porcentaje de fallas x\n" \
             "B. Procesar archivo de entrada\n" \
             "C. Mostrar archivo de entrada\n" \
             "D. Mostrar archivos de salida\n" \
             "S. Salir\n" \
             "Opcion: "
#define OPCS "ABCDS"

/* ... acá van Registro, Cola y sus funciones, volcarCola, cerrarLote, procesarArchivo ... */

/* Muestra el mensaje, pide un carácter y repite hasta que sea una opción válida */
char menu(const char *msj, const char *opcs) {
    char op;
    do {
        printf("%s", msj);
        scanf(" %c", &op);
        while (getchar() != '\n');          /* limpia el buffer */
        op = toupper((unsigned char)op);
        if (strchr(opcs, op) == NULL)
            printf("Opcion invalida.\n");
    } while (strchr(opcs, op) == NULL);
    return op;
}

void mostrarEntrada(void) {
    FILE *f = fopen("entrada.bin", "rb");
    if (!f) { printf("No se pudo abrir entrada.bin\n"); return; }

    Registro r;
    printf("\n=== ARCHIVO DE ENTRADA ===\n");
    fread(&r, sizeof(Registro), 1, f);
    while (!feof(f)) {
        printf("%s, %d, %s\n", r.codLote, r.idProducto, r.resultadoControl);
        fread(&r, sizeof(Registro), 1, f);
    }
    fclose(f);
}

void mostrarTexto(const char *nombre, const char *titulo) {
    FILE *f = fopen(nombre, "r");
    if (!f) { printf("No se pudo abrir %s\n", nombre); return; }

    char linea[100];
    printf("\n=== %s ===\n", titulo);
    while (fgets(linea, sizeof(linea), f))
        printf("%s", linea);
    fclose(f);
}

int main(void) {
    char op;
    int x = -1;                              /* -1 = todavía no se ingresó */
    char nomObs[40], nomApr[40];
    generarRegistroLote("entrada.bin");
    op = menu(MSJ, OPCS);
    while (op != 'S') {
        if (op == 'A') {
            do {
                printf("Ingrese el porcentaje de fallas x (0-100): ");
                scanf("%d", &x);
                while (getchar() != '\n');
            } while (x < 0 || x > 100);
        }
        if (op == 'B') {
            if (x < 0) printf("Primero ingrese el porcentaje x (opcion A).\n");
            else       procesarArchivo(x);
        }
        if (op == 'C') {
            mostrarEntrada();
        }
        if (op == 'D') {
            if (x < 0) {
                printf("Primero ingrese el porcentaje x (opcion A).\n");
            } else {
                sprintf(nomObs, "lotesObservados-%d.txt", x);
                sprintf(nomApr, "lotesAprobados-%d.txt", x);
                mostrarTexto(nomObs, "LOTES OBSERVADOS");
                mostrarTexto(nomApr, "LOTES APROBADOS");
            }
        }
        op = menu(MSJ, OPCS);
    }
    printf("Programa finalizado.\n");
    return 0;
}
