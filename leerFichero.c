#pragma once

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "leerFichero.h"

//Cuenta el numero de datos que hay por fila
void numeroColumnas(char filas[], int *numDatos) {
    int i;
    for ( i = 0; i < strlen(filas); i++){
        if (filas[i] == ','){
            *numDatos = *numDatos + 1;
        }
    }
}

//Compila las fechas, esta función es separada de los demas datos 
//dado que las fechas son un tipo especial de dato que tiene dos 
//componentes
void compilarFechas(char fila[], datos memoria[]){
    int i = 0, j = 0, k = 0, mes = 0, year = 0;
    char titulo[50], separador[] = ",/", *cad_aux;
    cad_aux = strtok(fila, separador);
    strcpy(titulo, cad_aux);
    while (cad_aux != NULL){
        if (cad_aux != NULL){
            cad_aux = strtok(NULL, separador);
            mes = atoi(cad_aux);
            memoria[k].date[j].month = mes;
            cad_aux = strtok(NULL, separador);
            year = atoi(cad_aux);
            memoria[k].date[j].year = year;
            j++;
            if ((j == 12)){
                k++;
                j = 0;
            }
            if (k != 0 && memoria[k-1].date[j].year != atoi(cad_aux) && memoria[k-1].date[11].month == 0){
                k++;
                j = 0;
            }
        }   
    }
}

//Cuenta el numero de años que hay en total para usarlo de dato 
//a la hora de hacer el resto de cosas
void numeroYears(datos GWh[], int *numYear) {
    int i;
    *numYear = 0;
    for ( i = 0; i < 15; i++){
        if (GWh[i].date[0].year != 0){
            *numYear = *numYear + 1;
        }
    }
}

//Lee el titulo de la fuente y lo aplica al año dado
void leerTitulo(char fila[], datos memoria[], int numYear, int num_fuente){
    char *cad_aux, separador[] = ",";
    int i = 0;
    //puts(fila);
    cad_aux = strtok(fila, separador);
    strcpy(memoria[numYear].data[num_fuente].nombre_fuente, cad_aux);
}

//Lee los datos, separando filas de datos en partes, para leerlas 
//y asignarle su valor numerico a un vector de estructura usado en el 
//codigo.
void compilarDatos(char fila[], datos memoria[], int num_years, int num_fuentes, int meses[]){
    int i = 0, j = 0, k = 0;
    char separador[] = {'"',','}, *cad_aux, comprobante_calculos[] = "-*";
    //puts(fila);
    cad_aux = strtok(fila, separador);
    if (cad_aux != NULL){
        while (cad_aux != NULL){
            cad_aux = strtok(NULL, separador);
            if (cad_aux != NULL){
                if (strcmp(cad_aux, comprobante_calculos) == 0){
                    memoria[k].data[num_fuentes].calculable[i] = 0;
                }
                else{
                    memoria[k].data[num_fuentes].calculable[i] = 1;
                }
                memoria[k].data[num_fuentes].valor_mes[i] = atof(cad_aux);
                i++;
                if (i == meses[k]){
                    k++;
                    i = 0;
                }
            }
            memoria[k].data[num_fuentes].eliminado[i] = 0;
        }
    }
}

//Imprime todos los datos existentes fuente a fuente junto a las fechas
void Imprimir_tabla(datos GWh[], int numYear, int num_mes_por_year[]){
    int i = 0, j = 0, k = 0, cond = 1, mes = 0, decision2 = 1;
    char pasar_pag, decision, comprobante[] = "Fuel + Gas";
    do
    {
        system("cls");
        printf("¿Como desea ver los datos?\n\n1. Ver tabla con todos los valores existentes\n\n2. Buscar dato concreto\n\n3. Volver atras\n");
        decision = getch();
        switch (decision)
        {
        case ('1'):
            //Caso ver tabla completa
            k = 0;
            i = 0;
            j = 0;
            do
            {
                system("cls");
                printf("  Pulsa 'A' para pasar a la pagina anterior, y 'D' para pasar a la siguiente\n\t\tPara cambiar el ano pulse 'S' y 'W'\n*Para volver al menu presiona espacio*\t*Las unidades estan en GWh producidos*\n");
                printf("\t\t\tFecha:\t%s:\n", GWh[0].data[k].nombre_fuente);
                for ( i = 0; i < num_mes_por_year[j]; i++){
                        cond = strcmp(GWh[j].data[k].nombre_fuente, comprobante);
                        if (((cond == 0) && (GWh[j].data[k].valor_mes[i] == 0)) || (GWh[j].data[k].eliminado[i] == 1)){
                            printf("\t\t\t%i/%i: -\n", GWh[j].date[i].month, GWh[j].date[i].year);
                        }
                        else{
                            if ((GWh[j].data[k].calculable[i] == 0)){
                                printf("\t\t\t%i/%i: -*\n", GWh[j].date[i].month, GWh[j].date[i].year);
                            }
                            else{
                                printf("\t\t\t%i/%i: %.15f\n", GWh[j].date[i].month, GWh[j].date[i].year, GWh[j].data[k].valor_mes[i]);
                            }
                        }
                        cond = 1;
                    }
                pasar_pag = getch();
                if ((k != 0) && ((pasar_pag == 'A') || (pasar_pag == 'a'))){
                    k = k - 1;
                    if (k == -1){
                        k = 0;
                    }
                }
                if ((k != 17) && ((pasar_pag == 'D') || (pasar_pag == 'd'))){
                    k = k + 1;
                    if (k == 18){
                        k = 17;
                    }
                }
                if ((j != numYear-1) && ((pasar_pag == 'S') || (pasar_pag == 's'))){
                        j++;
                        if (j == numYear){
                            j = numYear-1;
                        }
                    }
                if ((j != 0) && ((pasar_pag == 'W') || (pasar_pag == 'w'))){
                        j--;
                        if (j == -1){
                            j = 0;
                        }
                    }
                if (pasar_pag == ' '){
                    k = 18;
                }
            } while ((k != 18));
            break;

        case('2'):
            //Caso buscar dato concreto
            k = 0;
            i = 0;
            j = 0;
            do{
                system("cls");
                printf("Buscador de datos:\n\n");
                if (((strcmp(GWh[i].data[k].nombre_fuente, comprobante) == 0) && (GWh[i].data[k].valor_mes[j] == 0)) || (GWh[i].data[k].eliminado[j] == 1)){
                    printf("\t\t\t%s(%i/%i): -\n", GWh[i].data[k].nombre_fuente, GWh[i].date[j].month, GWh[i].date[j].year);
                }
                else{
                    if ((GWh[i].data[k].calculable[j] == 0)){
                        printf("\t\t\t%s(%i/%i): -*\n", GWh[i].data[k].nombre_fuente, GWh[i].date[j].month, GWh[i].date[j].year);
                    }
                    else{
                        printf("\t\t\t%s(%i/%i): %.15f\n", GWh[i].data[k].nombre_fuente, GWh[i].date[j].month, GWh[i].date[j].year, GWh[i].data[k].valor_mes[j]);
                    }
                }
                printf("\nCon 'A' y 'D' Se cambian las fuentes, con 'W' y 'S' se cambia la fecha, presiona 'espacio' para saber que se esta cambiando:\n\nActualmente cambiando: ");
                if (mes == 1){
                    printf("\x1b[32m meses\x1b[0m\n");
                }
                if(mes == 0){
                    printf("\x1b[32m a%cos\x1b[0m\n", 164);
                }
                printf("\nPresione enter cuando quiera seleccionar salir del buscador\n");
                pasar_pag = getch();
                if (((pasar_pag == 'A') || (pasar_pag == 'a')) && (k != 0)){
                    k = k - 1;
                    if (k == -1){
                        k = 0;
                    }
                }
                if (((pasar_pag == 'D') || (pasar_pag == 'd')) && (k != 17)){
                    k = k + 1;
                    if (k == 18){
                        k = 17;
                    }
                }
                if ((pasar_pag == 'W') || (pasar_pag == 'w')){
                    if (mes == 0){
                        i++;
                        if (i == numYear){
                            i = numYear-1;
                        }
                    }
                    if (mes == 1){
                        j++;
                        if (j == num_mes_por_year[i]){
                            j = num_mes_por_year[i]-1;
                        }
                    }
                }
                if ((pasar_pag == 'S') || (pasar_pag == 's')){
                    if (mes == 0){
                        i--;
                        if (i == -1){
                            i = 0;
                        }
                    }
                    if (mes == 1){
                        j--;
                        if (j == -1){
                            j = 0;
                        }
                    }
                }
                if (pasar_pag == 32){
                    if (mes == 1){
                        mes = 0;
                    }
                    else{
                        mes = 1;
                    }
                }
                if (pasar_pag == 13){
                    decision2 = 0;
                }
                system("cls");
            } while (decision2 == 1);
            decision2 = 1;
            break;

        case('3'):
            break;
        default:
            break;
        }
    } while (decision != '3');
}