#ifndef __PROBADOR_H__
#define __PROBADOR_H__

#include <stdio.h>
#include <stdbool.h>

typedef struct probador probador_t;

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
*
*
*/

void asegurar_probador(probador_t* probador, char* descripcion, bool caso);

/*
*
*
*/

void mostrar_estadisticas_probador(probador_t* probador);

/*
*
*
*/
void destruir_probador(probador_t* probador);

#endif /*__PROBADOR_H__ */
