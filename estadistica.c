#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "leerFichero.h"
#include "estadistica.h"

void calculos(int year, datos GWh[], int numYear) {
    int i, j, k, l, numdatos = 0;
    float sumatorio = 0, comodinfloat;
    int comodinint;
    float media[numYear][18], desvTip[numYear][18], varianza[numYear][18], mediana[numYear][18], cuartilUno[numYear][18], cuartilTres[numYear][18], minimo[8][18], maximo[8][18];
    
    float datosOrdenados[15][18][12];
    int numDatosOrdenados[15][18];

    FILE *destino;

    destino = fopen("resultados\\media.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    //Escribe las nuevas estadisticas
    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");

    fprintf(destino, "\n###MEDIAS\n");

    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            for (k = 0; k < 12; k++) {
                if (GWh[i].data[j].calculable[k] == 0 || GWh[i].data[j].eliminado[k] == 1) {
                    //nada
                } else {
                    sumatorio = sumatorio + GWh[i].data[j].valor_mes[k];
                    numdatos++;
                }
            }

            if (numdatos == 0) {
                media[i][j] = 0;
            } else {
                media[i][j] = sumatorio / numdatos;
            }

            fprintf(destino, "Media %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, media[i][j]);
            numdatos = 0;
            sumatorio = 0;
        }
    }

    fclose(destino);

    destino = fopen("resultados\\varianzas.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");

    //TODAS LAS DE ABAJO SON POBLACIONALES
    fprintf(destino, "\n###VARIANZAS (POBLACIONAL)\n");

    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            for (k = 0; k < 12; k++) {
                if (GWh[i].data[j].calculable[k] == 0 || GWh[i].data[j].eliminado[k] == 1) {
                    //nada
                } else {
                    sumatorio = sumatorio + pow(GWh[i].data[j].valor_mes[k] - media[i][j], 2);
                    numdatos++;
                }
            }

            if (numdatos == 0) {
                varianza[i][j] = 0;
            } else {
                varianza[i][j] = sumatorio / numdatos;
            }

            fprintf(destino, "Varianza %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, varianza[i][j]);
            numdatos = 0;
            sumatorio = 0;
        }
    }

    fclose(destino);

    destino = fopen("resultados\\desvtipicas.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");
    
    fprintf(destino, "\n###DESVIACIONES TIPICAS (POBLACIONAL)\n");

    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {

            desvTip[i][j] = sqrt(varianza[i][j]);

            fprintf(destino, "Desv. tip. %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, desvTip[i][j]);
        }
    }    

    
    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            for (k = 0; k < 12; k++) {
                if (GWh[i].data[j].calculable[k] == 0 || GWh[i].data[j].eliminado[k] == 1) {
                    //nada
                } else {
                    datosOrdenados[i][j][k] = GWh[i].data[j].valor_mes[k];
                    numdatos++;
                }
            }
            numDatosOrdenados[i][j] = numdatos;
            numdatos = 0;
        }
    }

    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            for (k = 0; k < numDatosOrdenados[i][j]; k++) {
                for (l = k + 1; l < numDatosOrdenados[i][j]; l++) {
                    if (datosOrdenados[i][j][k] > datosOrdenados[i][j][l]) {
                        comodinfloat = datosOrdenados[i][j][l];
                        datosOrdenados[i][j][l] = datosOrdenados[i][j][k];
                        datosOrdenados[i][j][k] = comodinfloat;
                    }
                }
            }
        }
    }   

    fclose(destino);

    destino = fopen("resultados\\medianas.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");
    
    fprintf(destino, "\n###MEDIANAS\n");
    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            if ((numDatosOrdenados[i][j] % 2) == 0) {
                comodinint = numDatosOrdenados[i][j] / 2;
                mediana[i][j] = (datosOrdenados[i][j][comodinint - 1] + datosOrdenados[i][j][comodinint]) / 2;
            } else {
                comodinint = numDatosOrdenados[i][j] / 2;
                mediana[i][j] = datosOrdenados[i][j][comodinint - 1];
            }

            fprintf(destino, "Mediana %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, mediana[i][j]);
        }
    }

    fclose(destino);

    destino = fopen("resultados\\cuateniones1.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");
    
    fprintf(destino, "\n###PRIMEROS CUATERNIONES\n");
    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            if ((numDatosOrdenados[i][j] % 4) == 0) {
                comodinint = numDatosOrdenados[i][j] / 4;
                mediana[i][j] = (datosOrdenados[i][j][comodinint - 1] + datosOrdenados[i][j][comodinint]) / 2;
            } else {
                comodinint = numDatosOrdenados[i][j] / 4;
                mediana[i][j] = datosOrdenados[i][j][comodinint - 1];
            }

            fprintf(destino, "Primer cuaternion %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, mediana[i][j]);
        }
    }    
    
    fclose(destino);

    destino = fopen("resultados\\cuarteniones3.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");
    
    fprintf(destino, "\n###TERCEROS CUATERNIONES\n");
    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            if ((numDatosOrdenados[i][j] % 4) == 0) {
                comodinint = 3 * numDatosOrdenados[i][j] / 4;
                mediana[i][j] = (datosOrdenados[i][j][comodinint - 1] + datosOrdenados[i][j][comodinint]) / 2;
            } else {
                comodinint = 3 * numDatosOrdenados[i][j] / 4;
                mediana[i][j] = datosOrdenados[i][j][comodinint - 1];
            }

            fprintf(destino, "Tercer cuaternion %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, mediana[i][j]);
        }
    }  

    fclose(destino);

    destino = fopen("resultados\\minimos.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");
    
    fprintf(destino, "\n###MINIMOS\n");
    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            fprintf(destino, "Minimo %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, datosOrdenados[i][j][0]);
        }
    }  

    fclose(destino);

    destino = fopen("resultados\\maximos.txt", "w");

    if (destino == NULL){
        printf("Problema al abrir fichero");
    }
    
    //Borra los calculos anteriores
    fprintf(destino, "");
    fseek(destino, 0, SEEK_SET);

    fprintf(destino, "CALCULOS ESTADISTICOS\n");
    fprintf(destino, "#####################");
    
    fprintf(destino, "\n###MAXIMOS\n");
    for (i = 0; i < numYear; i++) {
        for (j = 0; j < 18; j++) {
            fprintf(destino, "Maximo %s %i: %.15f\n", GWh[i].data[j].nombre_fuente, GWh[i].date[i].year, datosOrdenados[i][j][numDatosOrdenados[i][j] - 1]);
        }
    }

    fclose(destino);
}

void compilar_resultados(int numYear, resultado estadistica[]){
    FILE *resultados;
    int i = 0, j = 0, k = 0;
    char resu[100], sig_pag;

    memset(resu, 0, 100);

    resultados = fopen("resultados\\media.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###MEDIAS\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[0].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);

    resultados = fopen("resultados\\varianzas.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###VARIANZAS (POBLACIONAL)\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[1].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);

    resultados = fopen("resultados\\desvtipicas.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###DESVIACIONES TIPICAS (POBLACIONAL)\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[2].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);

    resultados = fopen("resultados\\medianas.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###MEDIANAS\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[3].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);

    resultados = fopen("resultados\\cuarteniones1.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###PRIMEROS CUATERNIONES\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[4].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);

    resultados = fopen("resultados\\cuarteniones3.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###TERCEROS CUATERNIONES\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[5].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);

    resultados = fopen("resultados\\minimos.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###MINIMOS\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[6].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);

    resultados = fopen("resultados\\maximos.txt","r");
    if (resultados == NULL){
        //xd
    }
    fscanf(resultados, "CALCULOS ESTADISTICOS\n#####################\n###MAXIMOS\n");
    for ( j = 0; j < numYear; j++){
        for ( k = 0; k < 18; k++){
            fgets(resu, 100, resultados);
            strcpy(estadistica[j].dato[7].dato_calculo[k], resu);
            memset(resu, 0, 100);
        }
    }
    
    fclose(resultados);
    
    strcpy(estadistica[0].dato[0].nombre_calculo, "MEDIAS"); 
    strcpy(estadistica[0].dato[1].nombre_calculo, "VARIANZAS (POBLACIONAL)");
    strcpy(estadistica[0].dato[2].nombre_calculo, "DESVIACIONES TIPICAS (POBLACIONAL)");
    strcpy(estadistica[0].dato[3].nombre_calculo, "MEDIANAS"); 
    strcpy(estadistica[0].dato[4].nombre_calculo, "PRIMEROS CUATERNIONES"); 
    strcpy(estadistica[0].dato[5].nombre_calculo, "TERCEROS CUATERNIONES"); 
    strcpy(estadistica[0].dato[6].nombre_calculo, "MINIMOS"); 
    strcpy(estadistica[0].dato[7].nombre_calculo, "MAXIMOS"); 
}

void imprimir_resultados(int numYear, resultado estadistica[]){
    int i = 0, j = 0, k = 0;
    char sig_pag;
    do
    {
        system("cls");
        printf("Pulsa 'A' y 'D' para cambiar el tipo de calculo estadistico, para cambiar el ano pulse 'S' y 'W':\n*Para volver al menu presiona espacio*\nDato estadistico mostrado: ");
        printf("\t%s\n", estadistica[0].dato[k].nombre_calculo);
        for ( i = 0; i < 18; i++){
            printf("\t%s\n", estadistica[j].dato[k].dato_calculo[i]);   
        }
        sig_pag = getch();
        if ((k != 0) && ((sig_pag == 'A') || (sig_pag == 'a'))){
            k = k - 1;
            if (k == -1){
                k = 0;
            }
        }
        if ((k != 7) && ((sig_pag == 'D') || (sig_pag == 'd'))){
            k = k + 1;
            if (k == 8){
                k = 7;
            }
        }
        if ((j != numYear-1) && ((sig_pag == 'S') || (sig_pag == 's'))){
            j++;
            if (j == numYear){
                j = numYear-1;
            }
        }
        if ((j != 0) && ((sig_pag == 'W') || (sig_pag == 'w'))){
            j--;
            if (j == -1){
                j = 0;
            }
        }
    } while (sig_pag != ' ');
}