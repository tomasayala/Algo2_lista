#ifndef __PROBADOR_H__
#define __PROBADOR_H__

#include <stdio.h>
#include <stdbool.h>

typedef struct probador{
  size_t pruebas_totales;
  size_t pruebas_exitosas;
  size_t pruebas_locales;
  size_t pruebas_locales_exitosas;
}probador_t;

/*
* Devuelve los una direccion de memoria al probador o NULL
* En caso de funcionar, crea un probador con todos los parametros inicializados en 0
*/
probador_t* crear_probador();

/*
* Para pruebas que pueden fallar
*
*/

void avisar_probador( probador_t* probador, char* aviso);

/*
* En caso de recibir un probador y una descripcion != NULL.
* Devuelve un mensaje por pantalla si la prueba fue exitosa o no
*/

void asegurar_probador(probador_t* probador, char* descripcion, bool caso);

/*
* En caso de recibir un probador != NULL
* Muestra por pantalla un mensaje de cuantas pruebas exitosas resultaron de
* todas las pruebas hechas, a lo largo de todos los tests.
*/

void mostrar_estadisticas_totales(probador_t* probador);

/*
* En caso de recibir un probador !=NULL
* Muestras las cantidad de pruebas hechas para un determinado set de pruebas para una funcion
* y la cantidad de pruebas exitosas
* Al final de la funcion las vuelve a poner en 0 para un nuevo set de pruebas 
*/

void mostrar_estadisticas_locales(probador_t* probador);

/*
* Destruye un probador creado
*/
void destruir_probador(probador_t* probador);

#endif /*__PROBADOR_H__ */
