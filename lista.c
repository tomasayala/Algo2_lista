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
  return lista->cantidad_elementos == 0;
}

nodo_t crear_nodo(void* elemento){
  nodo_t nuevo = calloc(1, sizeof(nodo_t));
  if(!nuevo)
    return NULL;
  nuevo->elemento = elemento;
  return nuevo;
}

lista_t* apilar( lista_t* lista, nodo_t* nuevo ){
  lista->ultimo.siguiente = nuevo;
  lista->ultimo = nuevo;
  lista->cantidad_elementos++;
  return lista;
}

lista_t* insertar_primer_elemento(lista_t* lista, nodo_t* nuevo){
  lista->primero = nuevo;
  lista->ultimo = nuevo;
  lista->cantidad_elementos++;
  return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
  if(!lista || !elemento){
    return ERROR;
  }
  nodo_t* nuevo = crear_nodo(elemento);
  if(!nuevo)
    return ERROR;
  if (lista_vacia(lista){
    lista = insertar_primer_elemento(lista, nuevo);
    return TODO_OK;
  }
  lista = apilar(lista,nuevo);
  return TODO_OK;
}

nodo_t* buscar_nodo_en_posicion_deseada(lista_t* lista, size_t posicion_deseada){
  nodo_t* deseado = lista->primero;
  size_t posicion_actual = 0;
  while (posicion_actual != posicion_deseada) {
    actual = actual->siguiente;
    posicion_actual++;
  }
  return deseado;
}

int lista_insertar_en_posicion ( lista_t* lista, void* elemento, size_t posicion){
  if(!lista || !elemento)
    return ERROR;
  if (posicion >= lista->cantidad_elementos)
    return lista_insertar(lista,elemento);
  nodo_t* nuevo = calloc (1, sizeof(nodo_t));
  if(!nuevo)
    return ERROR;
  if(posicion == 0)
    return insertar_primera_posicion(lista,nuevo);
  if(posicion == 1)
    nodo_t* actual = buscar_nodo_en_posicion_deseada(lista, posicion--);
  else
    nodo_t* actual = buscar_nodo_en_posicion_deseada(lista, posicion-2);
  nuevo->siguiente = actual->siguiente;
  actual->siguiente = nuevo;
  lista->cantidad_elementos++;
  return TODO_OK;
}

int desapilar (lista_t* lista){
  nodo_t* aux = lista->primero;
  nodo_t* aux = buscar_nodo_en_posicion_deseada(lista, lista->cantidad_elementos - 2);
  aux->siguiente = NULL;
  liberar_nodo(lista->ultimo);
  lista->ultimo = aux;
  return TODO_OK;
}

int lista_borrar(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return ERROR;
  if(lista->cantidad_elementos == 1){
    //Se vacia la lista
    liberar_nodo(lista->primero);
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->cantidad_elementos--;
    return TODO_OK;
  }
  return desapilar(lista);
}


int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  if(!lista)
    return ERROR;
  if(posicion >= lista->cantidad_elementos)
    return lista_borrar(lista);
  nodo_t* aux;
  if(posicion == 1)
    aux = buscar_nodo_en_posicion_deseada(lista, posicion--);
  else
    aux = buscar_nodo_en_posicion_deseada(lista,posicion -2);
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









lista_iterador_t* lista_iterador_crear(lista_t* lista){
  if(!lista)
    return NULL;
  lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t) );
  if(!iterador)
    return NULL;
  iterador->lista = lista;
  return iterador;
}
