#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "menu.h"

int main() {
    int entrada;

    //Inicio con la pantalla de bienvenida
    system("cls");
    pInicio();
    system("pause");
    system("cls");

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
