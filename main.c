#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"
#include "leerFichero.h"

int main() {
    //Declaracion de variables necesarias
    int entrada;
    int i, j, k, m;
    int numDatos = 0, numYear = 0, num_mes_por_year[15];
    char filas[23][10000], fila[10000], *cad_aux, separador1[] = ",/", titulo[50], separador2[] = {'"',','};

    datos GWh[30];

    FILE *archivo;

    //Inicio con la pantalla de bienvenida
    system("cls");
    pInicio();
    system("pause");
    system("cls");

    //Apertura de fichero
    archivo = fopen("documento.txt", "r");
    if (archivo == NULL) {
        printf("No se ha podido abrir el archivo");
        return 0;
    }

    //Lectura de documento.txt
    for (i = 0; i < 23; i++) {
        fgets(fila, 10000, archivo);
        strcpy(filas[i], fila);
        memset(fila, 0, 10000);
    }
    fclose(archivo);

    //Guarda el numero de columnas en numDatos
    numeroColumnas(filas[3], &numDatos);

    //Compilación fechas
    compilarFechas(filas[4], GWh);

    //Guarda el numero de anos en numYear
    numeroYears(GWh, &numYear);

    //Compilacion de datos 2.0
    memset(num_mes_por_year, 0, 15);

    for ( i = 0; i < numYear; i++){
        for ( j = 0; j < 12; j++){
            if (GWh[i].date[j].month != 0){
                num_mes_por_year[i] = num_mes_por_year[i] + 1;
            }
        }
    }
    
    for ( i = 0; i < 18; i++){
        m = i + 5;
        for ( j = 0; j < numYear; j++){
            memset(fila, 0, 10000);
            strcpy(fila, filas[m]);
            leerTitulo(fila, GWh, j, i);
        }
        compilarDatos(filas[m], GWh, numYear, i, num_mes_por_year);
    }

    pantallaSeleccion:
        pSeleccion();
        entrada = getch();
        switch (entrada) {
            case '1':
                //Caso calculos estadisticos
                system("cls");
                break;

            case '2':
                //Caso datos actuales
                system("cls");
                Imprimir_tabla(GWh, numYear, num_mes_por_year);
                system("cls");
                goto pantallaSeleccion;
                break;

            case '3':
                //Caso ingresar datos
                system("cls");
                break;
            
            case '4':
                //Caso eliminar datos
                system("cls");
                break;
            
            case '5':
                //Caso salir
                system("cls");
                goto salir;
                break;

            default:
                //Caso mismo menu
                system("cls");
                goto pantallaSeleccion;
                break;
        }

    salir:
    pConfirmarSalir();
    entrada = getch();
    switch (entrada) {
        case '1':
            //Caso cerrar programa
            system("cls");
            break;

        case '2':
            //caso volver a pantalla inicial
            system("cls");
            goto pantallaSeleccion;
            break;

        default:
            //Caso mismo menu
            system("cls");
            goto salir;
            break;
    }
    return 0;
}