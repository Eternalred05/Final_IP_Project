#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "Logica/Datos.h"
#include "Interfaz/Interfaz.h"
// funcion que mostrará un texto de bienvenida al programa, con un pequeño delay a la hora de mostrar las letras para que se asemeje a una animación
void textoInicial(){
    char *textos[3] = {
        "\41Bienvenido!\n",
        "Este programa a partir de los datos de los restaurantes tales como su nombre, la cantidad de comensales que admite\n la cantidad de platos que oferta diariamente y sus ventas por mes.\n",
        "Har\240 un peque\244o resumen de estos datos y otros reportes relacionados a los datos de los restaurantes.\n"
    };
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        for (j = 0; textos[i][j] != '\0'; j++) {
            printf("%c", textos[i][j]);
            fflush(stdout);
            Sleep(10);
        }
    }
    system("pause");
}
// Entrada de Datos
int entradaDatos(DatosRestaurantes infoRestaurantes [ ], int cantidad, bool lleno){
    bool repetir = false;
    if(lleno)
        cantidad = 0;
    do{
        obtenerNombre(infoRestaurantes,cantidad);
        infoRestaurantes[cantidad].capacidad = obtenerCapacidad(infoRestaurantes,cantidad);
        obtenerOfertasPlato(infoRestaurantes, cantidad);
        obtenerPromVentasMensuales(infoRestaurantes, cantidad);
        cantidad++;
        repetir = ingresarDatoNuevo();
    } while(repetir);
    if(lleno)
        cantidad = 100;
    printf("Se han ingresado los datos correctamente.\n");
    system("pause");
    return cantidad;
}
// Funcion para mostrar una lista con las informaciones de cada restaurante
void mostrarLista(DatosRestaurantes infoRestaurantes[], int tamLog){
    int i;
    int j;
    float total;
    char nomDias[7][10] = {"Lunes", "Martes", "Mi\202rcoles", "Jueves", "Viernes", "S\240bado", "Domingo"};
    char nomMeses[12][12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio","Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    system("cls");
    for (i = 0; i < tamLog; i++) {
        total = 0;
        char animar[100];
        sprintf(animar, "El restaurante n\243mero %d, llamado %s:\n", i + 1, infoRestaurantes[i].nomRestaurante);
        animarTexto(animar);
        sprintf(animar, "Tiene una capacidad total para %d personas\n", infoRestaurantes[i].capacidad);
        animarTexto(animar);
        animarTexto("La cantidad de platos que se ofertan en la semana son :\n");
        for (j = 0; j < 7; j++) {
            sprintf(animar, "El %s, %d platos\n", nomDias[j], infoRestaurantes[i].cantPlatos[j]);
            animarTexto(animar);
        }

        animarTexto("Este restaurante tuvo los siguientes promedios de ventas en los 12 meses del a\244o como se muestra\n");
        for (j = 0; j < 12; j++) {
            sprintf(animar, "En el mes de %s ganaron de promedio %.2f pesos.\n", nomMeses[j], infoRestaurantes[i].ventasMensuales[j]);
            animarTexto(animar);
            total += infoRestaurantes[i].ventasMensuales[j];
        }
        sprintf(animar, "Para un promedio total de %.2f pesos en todo el a\244o recaudados.\n", total);
        animarTexto(animar);
        system("pause");
        system("cls");

    }
}

void mostrarMayorPromedio(DatosRestaurantes infoRestaurantes[], int posicion, float promedio){
    printf("El restaurante %s, fue el restaurante con m\240s de 80 comensales con mayor promedio de ventas en el a\244o, con %.2f pesos de promedio total.\n",infoRestaurantes[posicion].nomRestaurante, promedio);
}
// funcion para mostrar los nombres que se guardan de algunos incisos
void mostrarNombres(char nombres[ ][50], int cantidad) {
    int i;
    for (i=0;i<cantidad;i++)
        printf("%d- %s\n",i+1, nombres[i]);
}
// Funcion para ingresar el valor con el que se harán las comparaciones del inciso c
float ingresarValor(){
    float valor;
    printf("Ingrese el valor del que quiere saber si la relacion del total del promedio de ventas por comensal se encuentra por encima, este debe ser positivo: \n");
    while (scanf("%f", &valor)!= 1 || valor<0){
        printf ("Usted ingres\242 un valor incorrecto, intente con un valor n\243merico mayor o igual que 0.\n");
        fflush (stdin);}
    return valor;
}
// Funciones relacionadas con la entrada de datos manulmente
bool ingresarDatoNuevo(){
    bool repetir = false;
    int decision;
    printf ("Si desea ingresar los datos de otro restaurante, por favor ingrese 1, en caso contrario ingrese otro n\243mero.\n");
    while (scanf("%d", &decision)!= 1)
    {
        printf ("Usted ingres\242 una letra, por favor ingrese un n\243mero.\n");
        fflush (stdin);
    }
    if(decision==1)
        repetir = true;
    return repetir;
}

void obtenerNombre(DatosRestaurantes infoRestaurantes[], int cantidad){
    bool error = false;
    do{
        system("cls");
        printf("Ingrese el nombre del restaurante n\243mero %d.\n", cantidad+1);
        fflush(stdin);
        fgets(infoRestaurantes[cantidad].nomRestaurante, 50, stdin);
        infoRestaurantes[cantidad].nomRestaurante[strcspn(infoRestaurantes[cantidad].nomRestaurante, "\n")] = '\0';
        error = validarNombre(infoRestaurantes, infoRestaurantes[cantidad].nomRestaurante, cantidad);
        system("pause");
    } while(error);
    system("cls");
}
bool validarNombre (DatosRestaurantes infoRestaurantes[] ,char nombre[], int cantidad){
    bool error = false;
    int i;
    for(i = 0; i<50; i++)
        nombre[i] = tolower(nombre[i]);
    for(i=0;i<cantidad;i++){
        if(strcmp(nombre, infoRestaurantes[i].nomRestaurante)== 0 && i !=cantidad){
            error = true;
            printf("Ya existe un restaurante ingresado con ese nombre.\n");
        }
    }
    if(!error){
        if (strlen(nombre) == 0){
            printf("Por favor no deje el nombre en blanco.\n");
            error = true;
        }
    }
    else {
        for (i = 0; i< 50 && !error; i++) {
            if (isdigit(nombre[i])) {
                printf("El nombre no debe contener valores n\243mericos. Por favor ingrese letras solamente.\n");
                error = true;
            }
        }
    }
    if(!error)
        printf("Nombre Ingresado Correctamente.\n");
    return error;
}
int obtenerCapacidad(DatosRestaurantes infoRestaurantes[], int posicion){
    int capacidad;
    bool error;
    do {
        error = false;
        printf("Ingrese la capacidad del restaurante llamado %s. Donde el m\241nimo es de 20 personas hasta 500.\n", infoRestaurantes[posicion].nomRestaurante);
        if (scanf("%d", &capacidad)!= 1) {
            printf ("Usted ingres\242 una letra, por favor intente con un n\243mero mayor que 20 y que no exceda de 500.\n");
            fflush (stdin);
            error = true;
        } else  if(capacidad<20 || capacidad>500){
            error=true;
            printf("El valor ingresado es incorrecto, la capacidad de los restaurantes van desde m\241nimo 20 personas hasta 500.\n");
        }
        if(!error)
            printf("Datos Ingresados correctamente.\n");
        system("pause");
        system("cls");
    } while(error);
    return capacidad;
}
void obtenerOfertasPlato(DatosRestaurantes infoRestaurantes[], int cantidad){
    char nomDias[7][10] = {"Lunes", "Martes", "Mi\202rcoles", "Jueves", "Viernes", "S\240bado", "Domingo"};
    int i;
    int ofertas;
    bool error;
    for(i=0;i<7;i++){
        do {
            error = false;
            printf("Ingrese la cantidad de platos que se ofertan el %s en el restaurante llamado %s:\n",nomDias[i],infoRestaurantes[cantidad].nomRestaurante);
            if (scanf("%d", &ofertas)!= 1) {
                printf ("Usted ingres\242 una letra, por favor intente con un n\243mero mayor que 0 y que no exceda de 30.\n");
                fflush (stdin);
                error = true;
            } else  if(ofertas < 1 || ofertas >30){
                error=true;
                printf("El valor ingresado es incorrecto, la cantidad de platos que ofrecen los restaurantes van desde m\241nimo 1 plato al d\241a hasta 30.\n");
            }
            if(!error)
                printf("Datos Ingresados correctamente.\n");
            system("pause");
            system("cls");
        } while(error);
        infoRestaurantes[cantidad].cantPlatos[i]= ofertas;
    }
}

void obtenerPromVentasMensuales(DatosRestaurantes infoRestaurantes[],int  cantidad){
    char nomMeses[12][12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio","Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    int i;
    float ventas;
    bool error;
    for(i=0;i<12;i++){
        do {
            error = false;
            printf("Ingrese el promedio de ventas del mes de %s correspondientes al restaurante llamado %s:\n",nomMeses[i],infoRestaurantes[cantidad].nomRestaurante);
            if (scanf("%f", &ventas)!= 1) {
                printf ("Usted ingres\242 una letra, por favor intente con un n\243mero mayor que 100 y que no exceda de 40000.\n");
                fflush (stdin);
                error = true;
            } else  if(ventas < 100 || ventas > 40000){
                error=true;
                printf("El valor ingresado es incorrecto, el promedio de venta de los restaurantes van desde m\241nimo 100 pesos hasta 40000.\n");
            }
            if(!error)
                printf("Datos Ingresados correctamente.\n");
            system("pause");
            system("cls");
        } while(error);
        infoRestaurantes[cantidad].ventasMensuales[i]= ventas;
    }
}
void animarTexto(char *texto) {
    int i;
    for ( i = 0; texto[i] != '\0'; i++) {
        printf("%c", texto[i]);
        fflush(stdout);
        Sleep(10);
    }
}

