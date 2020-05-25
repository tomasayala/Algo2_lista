#include <stdio.h>
#include "probador.h"

typedef struct probador{
  size_t pruebas_totales;
  size_t pruebas_exitosas;
}probador_t;



probador_t* crear_probador(){
  return calloc(1, sizeof(probador_t));
}

void avisar_probador(probador_t* probador, char* aviso){
  if(!probador || !aviso)
    return;
  probador->pruebas_exitosas++;
  probador->pruebas_totales++;
  printf(" Aviso: %s\n", aviso);
}

void asegurar_probador(probador_t* probador, char* descripcion, bool caso){
  if(!probador || !descripcion)
    return;
  if(caso)
    probador->pruebas_exitosas++;
  probador->pruebas_totales++;
  printf("PRUEBA: %s %s\n",descripcion, caso ? "EXITO":"FALLO" );
}

void mostrar_estadisticas_probador(probador_t* probador){
  if(!probador)
    return;
  printf("Pruebas exitosas %zu de %zu\n",probador->pruebas_exitosas, probador->pruebas_totales);
}

void destruir_probador(probador_t* probador){
  free(probador);
}
