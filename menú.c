#include <stdio.h>
#include <conio.h>

void pInicio() {
    printf("\n");
    printf("\tBienvenido al programa de calculos estadisticos\n\n");
}

void pSeleccion() {
    printf("\n");
    printf("\tSeleccione la operacion a realizar:\n\n");
    printf("\t1\tCalculos estadisticos\n");
    printf("\t2\tDatos actuales\n");
    printf("\t3\tIngresar datos\n");
    printf("\t4\tEliminar datos\n");
    printf("\t5\tSalir del programa\n\n");
}

void pCalculosEstadisticos() {
    printf("\n");
    printf("\tSeleccione el rango temporal:\n\n");
    printf("\t1\tAnual\n");
    printf("\t2\tAnual - Mensual\n");
    printf("\t3\tMensual\n");
    printf("\t4\tTotal\n\n");
}

void pVerDatos() {
    printf("\n");
    printf("\t1\tVer datos por mes - ano\n");
    printf("\t3\tVer datos por mes\n");
    printf("\t3\tVer datos por ano\n");
    printf("\t4\tOrdenar valores\n\n");
}

void pIngresarFecha() {
    printf("\n");
    printf("\tIngrese fecha:\n\n");
}

void pSalir() {
    printf("\n");
    printf("\tSeleccione una opcion:\n\n");
    printf("\t1\tGuardar cambios\n");
    printf("\t2\tNo guardar cambios\n");
    printf("\t3\tCancelar\n\n");
}

void pConfirmarSalir() {
    printf("\n");
    printf("\tSeguro que quiere salir?\n\n");
    printf("\t1\tSi\n");
    printf("\t2\tNo\n\n");
}