#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#include "menu.h"

int main() {
    //Declaracion de variables necesarias
    int entrada;
    int i, j, k;
    char filas[23][10000], fila[10000];

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