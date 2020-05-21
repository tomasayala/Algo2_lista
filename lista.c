#include <stdio.h>
#include "lista.h"


lista_t* lista_crear(){
  lista_t* lista = calloc (1, sizeof (lista_t));
  return lista;
}

bool lista_vacia ( lista_t* lista){
  return lista->cantidad_elementos > 0;
}
