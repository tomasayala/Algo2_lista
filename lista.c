#include <stdio.h>
#include "lista.h"

void liberar_nodo (nodo_t* nodo){
  free(nodo);
}

lista_t* lista_crear(){
  lista_t* lista = calloc (1, sizeof (lista_t));
  return lista;
}

bool lista_vacia ( lista_t* lista){
  if(!lista)
    return true;
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
    lista->ultimo = nuevo;
    lista->cantidad_elementos++;
    return OK;
  }
  lista->ultimo.siguiente = nuevo;
  lista->ultimo = nuevo;
  lista->cantidad_elementos++;
  return TODO_OK;
}


int lista_insertar_en_posicion ( lista_t* lista, void* elemento, size_t posicion){
  if(!lista || !elemento)
    return ERROR;
  if (posicion >= lista->cantidad_elementos)
    return lista_insertar(lista,elemento);
  nodo_t* nuevo = calloc (1, sizeof(nodo_t));
  if(!nuevo)
    return ERROR;
  size_t posicion_actual = 0;
  nodo_t* actual = lista->primero;
  while (posicion_actual != posicion-2) {
    actual = actual->siguiente;
    posicion_actual++;
  }
  nuevo->siguiente = actual->siguiente;
  actual->siguiente = nuevo;
  lista->cantidad_elementos++;
  return TODO_OK;
}

int lista_borrar(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return ERROR;
  if(lista->cantidad_elementos == 1){
    liberar_nodo(lista->primero);
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->cantidad_elementos--;
    return TODO_OK;
  }
  nodo_t* aux = lista->primero;
  while (aux->siguiente != lista->ultimo){
    aux = aux->siguiente;
  }
  aux->siguiente = NULL;
  liberar_nodo(lista->ultimo);
  lista->ultimo = aux;
  return TODO_OK;
}


int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  if(!lista)
    return ERROR;
  if(posicion >= lista->cantidad_elementos)
    return lista_borrar(lista);
  nodo_t* aux = lista->primero;
  size_t posicion_actual = 0;
  while( posicion_actual != posicion -2){
    aux = aux->siguiente;
    posicion_actual++;
  }
  nodo_t* a_eliminar = aux->siguiente;
  aux->siguiente = a_eliminar->siguiente;
  liberar_nodo(a_eleminar);
  return TODO_OK;
}

void* lista_elemento_en_posicion (lista_t* lista, size_t posicion){
  if(!lista || (posicion >= lista->cantidad_elementos) )
    return NULL;
  if( posicion == lista->cantidad_elementos--)
    return lista->ultimo.elemento;
  nodo_t* aux = lista->primero;
  size_t posicion = 0;
  while (posicion_actual != posicion--){
    aux = aux->siguiente;
    posicion_actual++;
  }
  return aux->elemento;
}

void* lista_ultimo(lista_t* lista){
  if(!lista|| lista_vacia(lista) )
    return NULL;
  return lista->ultimo.elemento;
}

size_t lista_elementos (lista_t* lista){
  if(!lista)
    return 0;
  return lista->cantidad_elementos;
}

int lista_apilar(lista_t* lista, void* elemento){
  if(!lista || !elemento)
    return ERROR;
    //Fijarte de armar mas primitivas
}

void lista_destruir(lista_t* lista){
  if (!lista)
    return;
  nodo_t* aux = lista->primero;
  while (lista->cantidad_elementos > 0){
    lista->primero = aux->siguiente;
    liberar_nodo(aux);
    aux = lista->primero;
  }
  free(lista);
}
