#include <stdio.h>
#include <stdlib.h>
#include "probador.h"

#define COLOR_BLANCO   "\x1b[37m\x1b[1m"
#define COLOR_ROJO     "\x1b[31m\x1b[1m"
#define COLOR_VERDE    "\x1b[32m\x1b[1m"
#define COLOR_AMARILLO "\x1b[33m\x1b[1m"
#define COLOR_NORMAL   "\x1b[0m"

#define COLOR_FROJO     "\x1b[41m"
#define COLOR_FVERDE    "\x1b[42m"
#define COLOR_FNORMAL   "\x1b[40m"

/*
* No hay precondiciones
* Postcondiciones: Devuelve un puntero a un probador inicializado en todos 0
*/

probador_t* crear_probador(){
  return calloc(1, sizeof(probador_t));
}

/*
* Precondiciones: El probador debe haber sido creado con crear_probador
* Postcondiciones: Muestra un mensaje por pantalla avisando que prueba se ejecuta
*/

void avisar_probador(probador_t* probador, char* aviso){
  if(!probador || !aviso)
    return;
  printf( COLOR_AMARILLO "AVISO: %s" COLOR_NORMAL "\n", aviso);
}

/*
* Precondiciones: El probador debe haber sido creado con crear_probador
* Postcondiciones: Muestra un mensaje mostrando si se paso la prueba o no
*/

void asegurar_probador(probador_t* probador, char* descripcion, bool caso){
  if(!probador || !descripcion)
    return;
  if(caso){
    probador->pruebas_exitosas++;
    probador->pruebas_locales_exitosas++;
  }
  probador->pruebas_locales++;
  probador->pruebas_totales++;
  if(caso)
    printf( COLOR_FVERDE "PRUEBA: %s %s" COLOR_FNORMAL "\n",descripcion,"EXITO");
  else
    printf( COLOR_FROJO "PRUEBA: %s %s" COLOR_FNORMAL "\n",descripcion,"FALLO");
}

/*
* Precondiciones: El probador debe haber sido creado con crear_probador
* Postcondiciones: Muesta un mensaje por pantalla con todas las pruebas que se corrieron a lo largo del programa
*/

void mostrar_estadisticas_totales(probador_t* probador){
  if(!probador)
    return;
  printf("Total de pruebas exitosas %zu de %zu\n",probador->pruebas_exitosas, probador->pruebas_totales);
}

/*
* Precondiciones: El probador debe haber sido creado con crear_probador
* Postcondiciones: Muestra un mensaje por pantalla para un determinado set de pruebas
*/

void mostrar_estadisticas_locales(probador_t* probador){
  if(!probador)
    return;
  printf("Pruebas exitosas %zu de %zu\n\n", probador->pruebas_locales_exitosas, probador->pruebas_locales);
  probador->pruebas_locales = 0;
  probador->pruebas_locales_exitosas = 0;
}

/*
* Precondiciones: El probador debe haber sido creado con crear_probador
* Postcondiciones: Libera la memoria asignada en crear_probador
*/

void destruir_probador(probador_t* probador){
  free(probador);
}
