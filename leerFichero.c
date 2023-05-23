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

//Realiza una copia de seguridad por si no se quiere guardar
void hacer_copia_seguridad(char filas[][10000], int numYear, int num_mes_por_year[], datos GWh[]){
    FILE *copia;
    int i = 0, j = 0, k = 0, cond = 1;
    char comprobante[] = "Fuel + Gas";
    copia = fopen("copia.txt","w");
    if (copia == NULL){
        printf("No se ha abierto correctamente");
    }
    fprintf(copia, "");
    fseek(copia, 0, SEEK_SET);
    for ( i = 0; i < 4; i++){
        fprintf(copia, "%s", filas[i]);
    }
    fprintf(copia,"Fechas");
    for ( i = 0; i < numYear; i++){
        for ( j = 0; j < num_mes_por_year[i]; j++){
            if ((10 == GWh[i].date[j].month) || (11 == GWh[i].date[j].month) || (12 == GWh[i].date[j].month)){
                fprintf(copia,",%i/%i", GWh[i].date[j].month, GWh[i].date[j].year);
            }
            else{
                fprintf(copia,",0%i/%i", GWh[i].date[j].month, GWh[i].date[j].year);
            }
        }
    }
    fprintf(copia,"\n");
    for ( i = 0; i < 18; i++){
        fprintf(copia, "%s", GWh[0].data[i].nombre_fuente);
        for ( k = 0; k < numYear; k++){
            for ( j = 0; j < num_mes_por_year[k]; j++){
                cond = strcmp(GWh[k].data[i].nombre_fuente, comprobante);
                if (((cond == 0) && (GWh[k].data[i].valor_mes[j] == 0)) || (GWh[k].data[i].eliminado[j] == 1)){
                    fprintf(copia, ",%c-%c", 34, 34);
                }
                if ((GWh[k].data[i].calculable[j] == 0)){
                    fprintf(copia, ",%c-*%c", 34, 34);
                }
                else{
                    fprintf(copia, ",%c%.15f%c", 34, GWh[k].data[i].valor_mes[j], 34);
                }
                cond = 1;
            }
        }
        fprintf(copia,"\n");
    }
    fclose(copia);
}

//Funcion que te deja escoger si guardar los cambios de forma 
//definitiva
void escoger_fichero_salida(char filas[][10000], int numYear, int num_mes_por_year[], datos GWh[]){
    int i = 0, j = 0, k = 0, compr = 0, nY = 0, n_m_y[15], m = 0, bucle = 0;
    char decision, cfila[10000], cfilas[23][10000];;
    FILE *archivo_nuevo;
    datos cGWh[15];
    do
    {
        system("cls");
        printf("¿Que archivo quiere que se quede guardado?:\n\n1. Archivo editado durante el programa\n\n2. Archivo sin los cambios aplicados\n");
        decision = getch();
        if (decision == '1'){
            compr = 1;
            bucle = 1;
        }
        if (decision == '2'){
            compr = 2;
            bucle = 1;
        }
    } while (bucle == 0);
    if (compr == 1){
        system("cls");
        guardar_datos(filas, numYear, num_mes_por_year, GWh);
        printf("Guardado realizado\n\n");
        system("pause");
        system("cls");
    }
    if (compr == 2){
        system("cls");
        archivo_nuevo = fopen("copia.txt","r");
        if (archivo_nuevo == NULL){
            printf("No se ha podido abrir el archivo");
        }
        memset(cfila, 0, 10000);
        for ( i = 0; i < 23; i++){
            fgets(cfila, 10000, archivo_nuevo);
            strcpy(cfilas[i], cfila);
            memset(cfila, 0, 10000);
        }

        fclose(archivo_nuevo);

        //Compilación fechas
        compilarFechas(cfilas[4], cGWh);

        //Guarda el numero de anos en numYear
        numeroYears(cGWh, &nY);

        //Compilacion de datos 2.0
        memset(n_m_y, 0, 15);

        for ( i = 0; i < nY; i++){
            for ( j = 0; j < 12; j++){
                if (cGWh[i].date[j].month != 0){
                    n_m_y[i] = n_m_y[i] + 1;
                }
            }
        }
            
        for ( i = 0; i < 18; i++){
            m = i + 5;
            for ( j = 0; j < nY; j++){
                memset(cfila, 0, 10000);
                strcpy(cfila, cfilas[m]);
                leerTitulo(cfila, cGWh, j, i);
            }
            compilarDatos(cfilas[m], cGWh, nY, i, n_m_y);
        }
        guardar_datos(cfilas, nY, n_m_y, cGWh);
        printf("Guardado realizado\n\n");
        system("pause");
        system("cls");
    }
}

//Funcion que guarda los datos, sustituyendo al archivo original, 
//luego se hara al usuario decidir si quedarse con el editado o la 
//copia de seguridad
void guardar_datos(char filas[][10000], int numYear, int num_mes_por_year[], datos GWh[]){
    FILE *guardar;
    int i, j, k, cond = 1;
    char comprobante[] = "Fuel + Gas";
    guardar = fopen("documento.txt","w");
    if (guardar == NULL){
        printf("No se ha abierto correctamente");
    }
    fprintf(guardar, "");
    fseek(guardar, 0, SEEK_SET);
    for ( i = 0; i < 4; i++){
        fprintf(guardar, "%s", filas[i]);
    }
    fprintf(guardar,"Fechas");
    for ( i = 0; i < numYear; i++){
        for ( j = 0; j < num_mes_por_year[i]; j++){
            if ((10 == GWh[i].date[j].month) || (11 == GWh[i].date[j].month) || (12 == GWh[i].date[j].month)){
                fprintf(guardar,",%i/%i", GWh[i].date[j].month, GWh[i].date[j].year);
            }
            else{
                fprintf(guardar,",0%i/%i", GWh[i].date[j].month, GWh[i].date[j].year);
            }
        }
    }
    fprintf(guardar,"\n");
    for ( i = 0; i < 18; i++){
        fprintf(guardar, "%s", GWh[0].data[i].nombre_fuente);
        for ( k = 0; k < numYear; k++){
            for ( j = 0; j < num_mes_por_year[k]; j++){
                cond = strcmp(GWh[k].data[i].nombre_fuente, comprobante);
                if (((cond == 0) && (GWh[k].data[i].valor_mes[j] == 0)) || (GWh[k].data[i].eliminado[j] == 1)){
                    fprintf(guardar, ",%c-%c", 34, 34);
                }
                else{
                    if ((GWh[k].data[i].calculable[j] == 0)){
                        fprintf(guardar, ",%c-*%c", 34, 34);
                    }
                    else{
                        fprintf(guardar, ",%c%.15f%c", 34, GWh[k].data[i].valor_mes[j], 34);
                    }
                }
                cond = 1;
            }
        }
        fprintf(guardar,"\n");
    }
    fclose(guardar);
}