#include "funciones.h"

int generarRegistroLote(const char* nomArch)
{
    FILE* pf;
    Registro registros[]={ {"L001",5,"OK"}
                          ,{"L001",6,"OK"}
                          ,{"L001",4,"OK"}
                          ,{"L001",7,"FALLA"}
                          ,{"L001",9,"FALLA"}
                          ,{"L004",10,"FALLA"}
                          ,{"L004",2,"FALLA"}
                          ,{"L004",2,"FALLA"}
                          ,{"L004",2,"FALLA"}
                          ,{"L004",2,"OK"}
                          ,{"L004",2,"OK"}
                          ,{"L004",2,"OK"}
                          ,{"L004",2,"OK"}
                         };

    pf=fopen(nomArch,"wb");
    if(!pf)
        return 0;


    fwrite(registros,sizeof(Registro),sizeof(registros)/sizeof(registros[0]),pf);

    fclose(pf);
    return 1;

}
/* Vuelca toda la cola al archivo de texto, dejándola vacía */
void volcarCola(tCola *c, FILE *f) {
    Registro r;
    while (desencolar(c, &r,sizeof(Registro)))
        fprintf(f, "%s,%d,%s\n", r.codLote, r.idProducto, r.resultadoControl);
}

/* Decide si el lote es observado o aprobado y lo vuelca en el orden pedido */
void cerrarLote(tCola *ok, tCola *falla, int total, int fallas,
                int x, FILE *fObs, FILE *fApr) {
    if (total == 0) return;                  /* archivo vacío: no hace nada */

    if (fallas * 100 >= x * total) {         /* observado: FALLA primero */
        volcarCola(falla, fObs);
        volcarCola(ok, fObs);
    } else {                                 /* aprobado: OK primero */
        volcarCola(ok, fApr);
        volcarCola(falla, fApr);
    }
}

int procesarArchivo(int x) {
    tCola ok, falla;
    FILE *fe = fopen("entrada.bin", "rb");
    FILE *fObs;
    FILE *fApr;
    Registro r;
    char codActual[10] = "";
    int total = 0, fallas = 0;

    if (!fe) {
        printf("No se pudo abrir entrada.bin\n");
        return 0;
    }

    char nomObs[40], nomApr[40];
    sprintf(nomObs, "lotesObservados-%d.txt", x);
    sprintf(nomApr, "lotesAprobados-%d.txt", x);


    fObs=fopen(nomObs,"wt");
    if(!fObs)
    {
        fclose(fe);
        return 0;
    }
    fApr=fopen(nomApr,"wt");
    if(!fApr)
    {
        fclose(fe);
        fclose(fApr);
        return 0;
    }

    crearCola(&ok);
    crearCola(&falla);
    fread(&r, sizeof(Registro), 1, fe);      /* lectura previa */
    if (!feof(fe))
        strcpy(codActual, r.codLote);

    while (!feof(fe)) {
        if (strcmp(r.codLote, codActual) != 0) {   /* cambió el lote */
            cerrarLote(&ok, &falla, total, fallas, x, fObs, fApr);
            total = 0;
            fallas = 0;
            strcpy(codActual, r.codLote);
        }

        total++;
        if (strcmp(r.resultadoControl, "FALLA") == 0) {
            fallas++;
            encolar(&falla, &r,sizeof(Registro));
        } else {
            encolar(&ok, &r,sizeof(Registro));
        }

        fread(&r, sizeof(Registro), 1, fe);        /* siguiente lectura */
    }

    cerrarLote(&ok, &falla, total, fallas, x, fObs, fApr);  /* último lote */

    fclose(fe);
    fclose(fObs);
    fclose(fApr);
    printf("Archivos generados: %s y %s\n", nomObs, nomApr);
    return 1;
}
