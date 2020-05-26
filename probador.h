#ifndef __PROBADOR_H__
#define __PROBADOR_H__

#include <stdio.h>
#include <stdbool.h>

typedef struct probador{
  size_t pruebas_totales;
  size_t pruebas_exitosas;
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
* todas las pruebas hechas.
*/

void mostrar_estadisticas_probador(probador_t* probador);

/*
* Destruye un probador creado
*/
void destruir_probador(probador_t* probador);

#endif /*__PROBADOR_H__ */
