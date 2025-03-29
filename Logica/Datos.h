#ifndef DATOS_H
#define DATOS_H
struct datosRestaurantes {
    char nomRestaurante[50]; // nombre de los restaurantes
    int capacidad; // capacidad de los restaurantes
    int cantPlatos[7]; // cantidad de platos que se ofertan en los 7 dias de la semana
    float ventasMensuales[12]; // ventas de cada mes
};
typedef struct datosRestaurantes DatosRestaurantes;

#endif

