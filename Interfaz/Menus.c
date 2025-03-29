#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Logica/Datos.h"
#include "Interfaz/Interfaz.h"
#include "Logica/Logica.h"
#include "Interfaz/Menus.h"

void menuPrincipal(DatosRestaurantes infoRestaurantes[ ]){
    char opcion[10];
    int cantidad = 0;
    bool error;
    bool ingreso = false; // variable para saber si al menos se ha ingresado un dato al menos
    bool automatico = false; // variable para saber si ya se uso la inicializacion automatica
    do {
        error = false;
        system("cls");
        printf(" Escoja una opci\242n dependiendo de lo que desea hacer en el programa\n");
        printf("1. Entrada de los datos de los restaurantes\n");
        printf("2. Listado de Restaurantes \n");
        printf("3. Reportes \n");
        printf("4. Terminar \n");
        fflush(stdin);
        fgets(opcion, 10, stdin);
        opcion[strcspn(opcion, "\n")] = '\0';
        if(strlen(opcion)==1) {
            switch (opcion[0]){
            case '1':
                cantidad = menuEntradaDatos(infoRestaurantes, cantidad, &automatico, &ingreso);
                break;
            case '2':
                if(ingreso)
                    mostrarLista(infoRestaurantes, cantidad);
                else
                {
                    printf("No se ha ingresado ning\243n dato, pruebe ingresando alguno para utilizar esta funcionalidad\n");
                    system("pause");
                }
                break;
            case '3':
                if(ingreso)
                    menuReportes(infoRestaurantes, cantidad);
                else
                {
                    printf("No se ha ingresado ning\243n dato, pruebe ingresando alguno para utilizar esta funcionalidad\n");
                }
                system("pause");
                break;
            case '4':
                printf("El programa ha terminado.\n");
                system("pause");
                break;
            default:
                printf("Opci\242n err\242nea. Intente de nuevo \n");
                system("pause");
            }
        } else {
            error = true;
            printf("Opci\242n err\242nea. Intente de nuevo \n");
            system("pause");
        }
    }
    while (opcion[0] != '4' || error);
}
int menuEntradaDatos(DatosRestaurantes infoRestaurantes[], int  cantidad, bool* automatico, bool* ingreso){
    char opcion[10];
    bool error;
    bool chequeo = *automatico;
    bool lleno = false;
    do{
        error = false;
        system("cls"),
                printf("\250Como desea ingresar los datos?\n");
        printf("1. Manualmente por teclado.\n");
        printf("2. Inicializar de forma autom\240tica\n");
        printf("3. Regresar.\n");
        fflush(stdin);
        fgets(opcion, 10, stdin);
        opcion[strcspn(opcion, "\n")] = '\0';
        if(strlen(opcion)==1) {
            switch (opcion[0]){
            case '1':
                if(cantidad==100){
                    printf("Se ha llenado el espacio de la memoria, a partir de ahora se empezar\240n a sobrescribir los primeros valores\n");
                    lleno = true;
                }
                cantidad= entradaDatos(infoRestaurantes, cantidad,lleno);
                *ingreso=true;

                break;
            case '2':
                if(cantidad>90)
                    printf("Se ha llenado el espacio de la memoria, esta funci\242n no se puede utilizar ahora. \n");
                else if(!chequeo) {
                    printf("Se inicializar\240n 10 datos extras, independientemente de los ingresados anteriormente.\n");
                    cantidad = inicializarDatos(infoRestaurantes,cantidad);
                    *automatico = true;
                    *ingreso=true;
                    printf("\41Datos Inicializados Correctamente!.\n");
                }
                else
                    printf("Ya se us\242 esta opci\242n una vez.No es necesario hacerlo de nuevo.\n");
                system("pause");
                break;
            case '3':
                break;
            default:
                printf("Opci\242n err\242nea. Intente de nuevo \n");
                system("pause");
                error = true;
                break;
            }
        } else{
            error = true;
            printf("Opci\242n err\242nea. Intente de nuevo \n");
            system("pause");
        }
    }  while(error);
    return cantidad;
}

void menuReportes (DatosRestaurantes infoRestaurantes[ ], int cantidad) {
    char opcion[10];
    bool error; // variable para repetir el programa en caso de ingresa algo incorrecto
    int posicion; // variable pàra guardar la posicion del mayor promedio de ventas
    int i;
    float promedios[100] = {0}; // variable para almacenar los promedios totales
    char nombres[100][50] = {{0}}; // variable para almacenar algunos nombres de los restaurantes que cumplan algunos requisitos en especifico
    int existentes;  // variable para guardar el tamaño logico de algunas funcionalidades como la de inciso c,d y e
    float valor;
    for (i=0;i<cantidad;i++) // para calcular los promedios totales de cada restaurante
        promedios[i] = calcularPromedio(infoRestaurantes, i);
    do{
        error = false;
        system("cls"),
                printf("\250A que funcionalidad desea acceder?\n");
        printf("1. Mayor Promedio de Venta de los restaurantes Grandes (m\240s de 80 comensales.\n");
        printf("2. Los restaurantes en los que la relaci\242n venta por comensal est\240 por debajo de un valor dado por usted.\n");
        printf("3. Nombres de los restaurantes que ofertan m\240s de 5 platos los domingos .\n");
        printf("4. Nombre de los restaurantes cuyo promedio de ventas en alg\243n mes se encuentra por debajo de los 300 pesos.\n");
        printf("5. Regresar.\n");
        fflush(stdin);
        fgets(opcion, 10, stdin);
        opcion[strcspn(opcion, "\n")] = '\0';
        if(strlen(opcion)==1) {
            switch (opcion[0]){
            case '1':
                posicion = buscarPromRestaurantesGrandes(infoRestaurantes,cantidad, promedios);
                if(posicion == -1)
                    printf("No existen restaurantes grandes con m\240s de 80 comensales.\n");
                else
                    mostrarMayorPromedio(infoRestaurantes, posicion, promedios[posicion]);
                break;
            case '2':
                valor = ingresarValor();
                existentes = buscarRestaurantesDebajoValor(infoRestaurantes,promedios,cantidad,valor,nombres);
                if(existentes == 0)
                    printf("No existe ning\243n restaurante cuya relaci\242n del promedio de ventas total por comensal este por debajo de %.2f .\n", valor);
                else{
                    printf("Los restaurantes cuya relaci\242n del promedio de ventas total por comensal est\240 por debajo de %.2f, son: \n", valor);
                    mostrarNombres(nombres, existentes);
                }
                break;
            case '3':
                existentes = buscarOfertasDomingo(infoRestaurantes, cantidad, nombres);
                if(existentes == 0)
                    printf("Ning\243n Restaurante oferta m\240s de 5 platos los Domingos.\n");
                else{
                    printf("Los restaurantes que ofertan m\240s de 5 platos los Domingos son: \n");
                    mostrarNombres(nombres, existentes);
                }
                break;
            case '4':
                existentes = buscarRestaurantesDebajoTrescientos(infoRestaurantes, cantidad, nombres);
                if(existentes == 0)
                    printf("No existe ning\243n restaurante que tenga en alg\243n mes menos de 300 pesos como promedio.\n");
                else{
                    printf("Los restaurantes que en un mes tienen menos de 300 pesos de promedio recaudados son:\n");
                    mostrarNombres(nombres, existentes);
                }
                break;
            case '5':
                break;
            default:
                printf("Opci\242n err\242nea. Intente de nuevo \n");
                system("pause");
                error = true;
                break;
            }
        }
        else{
            error = true;
            printf("Opci\242n err\242nea. Intente de nuevo \n");
            system("pause");
        }
    } while(error);
}

