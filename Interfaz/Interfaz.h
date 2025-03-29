#include "Logica/Datos.h"
#include <stdbool.h>
void animarTexto(char *texto) ;
void textoInicial();
int entradaDatos(DatosRestaurantes[ ],int, bool);
void mostrarLista(DatosRestaurantes[], int);
void mostrarMayorPromedio(DatosRestaurantes[], int, float);
void mostrarNombres(char [][50], int );
float ingresarValor();
void obtenerNombre(DatosRestaurantes[], int);
int obtenerCapacidad(DatosRestaurantes[], int);
bool validarNombre(DatosRestaurantes[] ,char [], int);
void obtenerOfertasPlato(DatosRestaurantes [], int );
void obtenerPromVentasMensuales(DatosRestaurantes infoRestaurantes[],int);
bool ingresarDatoNuevo();
