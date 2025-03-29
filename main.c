#include <stdio.h>
#include "Logica/Datos.h"
#include "Interfaz/Menus.h"
#include "Interfaz/Interfaz.h"
#define SIZE 100
int main(void) {
    DatosRestaurantes infoRestaurantes[SIZE];
    textoInicial();
    menuPrincipal(infoRestaurantes);
    return 0;
}

