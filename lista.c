#include <stdio.h>
#include "lista.h"


lista_t* lista_crear(){
  lista_t* lista = calloc (1, sizeof (lista_t));
  return lista;
}

bool lista_vacia ( lista_t* lista){
  return lista->cantidad_elementos > 0;
}


int lista_insertar(lista_t* lista, void* elemento){
  if(!lista || !elemento){
    return ERROR;
  }
  nodo_t nuevo = calloc(1, sizeof(nodo_t));
  if(!nuevo)
    return ERROR;
  nuevo->elemento = elemento;
  if (lista_vacia(lista){
    lista->primero = nuevo;
    lista->ctual = nuevo;
    lista->ultimo = nuevo;
    return OK;
  }
  lista->ultimo.siguiente = nuevo;
  return TODO_OK;
}
