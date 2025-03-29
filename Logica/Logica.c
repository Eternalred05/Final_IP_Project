#include "Logica/Datos.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Funcion para inicializar 10 datos de prueba
int inicializarDatos(DatosRestaurantes infoRestaurantes[ ], int cantidad){
    srand(time(NULL));
    char nombresPrueba[10][50]= {"flor de loto", "la taberna", "hatelia", "hyrule","gorontia","el carbon", "bello caribe", "akkala", "rancho lon lon", "bazar sekken"};
    int i;
    int j;
    int k;
    for (i=cantidad;i<cantidad+10;i++ ){
        infoRestaurantes[i].capacidad= rand() % 481 + 20;
        for (j=0;j<7;j++){
            infoRestaurantes[i].cantPlatos[j] = rand() % 30 + 1;
        }
        for(k=0;k<12;k++){
            infoRestaurantes[i].ventasMensuales[k] = rand() % 3901 + 100;
        }
    }
    j=0;
    for (i=cantidad;i<cantidad+10;i++){
        strcpy(infoRestaurantes[i].nomRestaurante, nombresPrueba[j]);
        j++;
    }
    cantidad = i;
    return cantidad;
}
// Funcion para buscar que restaurante con mas de 80 comensales tiene el mayor promedio de ventas.
int buscarPromRestaurantesGrandes (DatosRestaurantes infoRestaurantes[ ], int cantidad, float promedios[ ] ){
    int i;
    int posicion = -1;
    float mayor = 0;
    for (i=0;i<cantidad;i++){
        if(infoRestaurantes[i].capacidad > 80)
            if(mayor < promedios[i]){
                mayor = promedios[i];
                posicion = i;
            }
    }
    return posicion;
}
// Funcion para calcular el promedio total en los incisos que correspondientes al uso de los mismos
float calcularPromedio (DatosRestaurantes infoRestaurantes[],int posicionActual){
    float total = 0;
    int i;
    for(i=0;i<12;i++){
        total += infoRestaurantes[posicionActual].ventasMensuales[i];
    }
    return total;
}
// Funcion para buscar que restaurantes venden más de 5 platos los Domingos (inciso d)
int buscarOfertasDomingo(DatosRestaurantes infoRestaurantes[ ], int cantidad, char nombres[ ][50]){
    int ofertasDom = 0;
    int i;
    for(i=0;i<cantidad;i++){
        if(infoRestaurantes[i].cantPlatos[6] > 5){
            strcpy(nombres[ofertasDom], infoRestaurantes[i].nomRestaurante);
            ofertasDom++;
        }
    }
    return ofertasDom;
}
// Funcion para buscar aquellos restaurantes que en algun mes no hayan vendido mas de 300 pesos.
int buscarRestaurantesDebajoTrescientos(DatosRestaurantes infoRestaurantes[ ], int cantidad, char nombres[][50]){
    int i;
    int j;
    int existentes = 0;
    bool encontrado;
    for(i=0;i<cantidad;i++){
        encontrado = false;
        j=0;
        while(j<12 && !encontrado ){
            if(infoRestaurantes[i].ventasMensuales[j]<300){
                encontrado = true;
                strcpy(nombres[existentes], infoRestaurantes[i].nomRestaurante);
                existentes++;
            } else
                j++;
        }
    }
    return existentes;
}

// Funcion para buscar Restaurantes cuyo promedio de ventas por comensales se encuentren por debajo de un valor dado
int buscarRestaurantesDebajoValor(DatosRestaurantes infoRestaurantes[],float promedios[], int cantidad,float valor,char nombres[][50]){
    int existentes = 0;
    float relacionVenta[100] = {0};
    int i;
    for (i=0;i<cantidad;i++){
        relacionVenta[i]=promedios[i]/infoRestaurantes[i].capacidad;
    }
    for(i=0;i<cantidad;i++){
        if(relacionVenta[i] <valor){
            strcpy(nombres[existentes], infoRestaurantes[i].nomRestaurante);
            existentes++;
        }
    }
    return existentes;
}
