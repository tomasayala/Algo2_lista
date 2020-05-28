#include <stdlib.h>
#include "lista.h"
//Operaciones generales

#define ERROR -1
#define TODO_OK 0


typedef struct nodo{
  void* elemento;
  struct nodo* siguiente;
}nodo_t;

struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t cantidad_elementos;
};

struct lista_iterador{
    lista_t* lista;
    nodo_t* indice;
};


void liberar_nodo (nodo_t* nodo){
  free(nodo);
  nodo = NULL;
}

lista_t* vaciar_lista(lista_t* lista){
  liberar_nodo(lista->primero);
  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->cantidad_elementos = 0;
  return lista;
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

nodo_t* crear_nodo(void* elemento){
  nodo_t* nuevo = calloc(1, sizeof(nodo_t));
  if(!nuevo)
    return NULL;
  nuevo->elemento = elemento;
  return nuevo;
}


nodo_t* buscar_nodo_en_posicion(lista_t* lista, nodo_t* primer_nodo, size_t posicion_deseada){
  nodo_t* deseado = primer_nodo;
  size_t posicion_actual = 0;
  while (posicion_actual != posicion_deseada) {
    deseado = deseado->siguiente;
    posicion_actual++;
  }
  return deseado;
}

//Operaciones de lista

lista_t* insertar_primera_posicion (lista_t* lista, nodo_t* nuevo){
  nuevo->siguiente = lista->primero;
  lista->primero = nuevo;
  lista->cantidad_elementos++;
  return lista;
}

lista_t* insertar_al_final( lista_t* lista, nodo_t* nuevo ){
  lista->ultimo->siguiente = nuevo;
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
  if (lista_vacia(lista)){
    lista = insertar_primer_elemento(lista, nuevo);
    return TODO_OK;
  }
  lista = insertar_al_final(lista,nuevo);
  return TODO_OK;
}


int lista_insertar_en_posicion ( lista_t* lista, void* elemento, size_t posicion){
  if(!lista || !elemento)
    return ERROR;
  if (posicion >= lista->cantidad_elementos)
    return lista_insertar(lista,elemento);
  nodo_t* nuevo = crear_nodo(elemento);
  if(!nuevo)
    return ERROR;
  if(posicion == 0){
    lista = insertar_primera_posicion(lista,nuevo);
    return TODO_OK;
  }
  nodo_t* actual = buscar_nodo_en_posicion(lista, lista->primero, posicion-1);
  nuevo->siguiente = actual->siguiente;
  actual->siguiente = nuevo;
  lista->cantidad_elementos++;
  return TODO_OK;
}

lista_t* desapilar (lista_t* lista){
  nodo_t* penultimo = buscar_nodo_en_posicion(lista, lista->primero, lista->cantidad_elementos - 2);
  penultimo->siguiente = NULL;
  liberar_nodo(lista->ultimo);
  lista->ultimo = penultimo;
  lista->cantidad_elementos--;
  return lista;
}

int lista_borrar(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return ERROR;
  if(lista->cantidad_elementos == 1){
    lista = vaciar_lista(lista);
    return TODO_OK;
  }
  lista = desapilar(lista);
  return TODO_OK;
}

void lista_destruir(lista_t* lista){
  if (!lista)
    return;
  int borrado = lista_borrar(lista);
  while ( !lista_vacia(lista) && borrado == TODO_OK){
    borrado = lista_borrar(lista);
  }
  free(lista);
}

lista_t* borrar_primera_posicion(lista_t* lista){
  nodo_t* a_eleminar = lista->primero;
  lista->primero = (nodo_t*) lista->primero->siguiente;
  liberar_nodo(a_eleminar);
  lista->cantidad_elementos--;
  return lista;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
  if(!lista)
    return ERROR;
  if(posicion >= lista->cantidad_elementos)
    return lista_borrar(lista);
  if(posicion == 0){
    lista = borrar_primera_posicion(lista);
    return TODO_OK;
  }
  nodo_t* aux =  buscar_nodo_en_posicion(lista, lista->primero, posicion -1);
  nodo_t* a_eliminar = aux->siguiente;
  aux->siguiente = a_eliminar->siguiente;
  liberar_nodo(a_eliminar);
  lista->cantidad_elementos--;
  return TODO_OK;
}

void* lista_elemento_en_posicion (lista_t* lista, size_t posicion){
  if(!lista || (posicion >= lista->cantidad_elementos) )
    return NULL;
  if( posicion == lista->cantidad_elementos-1)
    return lista->ultimo->elemento;
  if (posicion == 0)
    return lista->primero->elemento;
  nodo_t* deseado = buscar_nodo_en_posicion(lista, lista->primero, posicion);
  return deseado->elemento;
}

void* lista_ultimo(lista_t* lista){
  if(!lista|| lista_vacia(lista) )
    return NULL;
  return lista->ultimo->elemento;
}

size_t lista_elementos (lista_t* lista){
  if(!lista)
    return 0;
  return lista->cantidad_elementos;
}
//Operaciones para la pila


int lista_apilar(lista_t* lista, void* elemento){
  if(!lista || !elemento)
    return ERROR;
  nodo_t* nuevo = crear_nodo(elemento);
  if(!nuevo)
    return ERROR;
  if(lista_vacia(lista)){
    lista = insertar_primer_elemento(lista,nuevo);
    return TODO_OK;
  }
  lista = insertar_al_final(lista,nuevo);
  return TODO_OK;
}

int lista_desapilar(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return ERROR;
  if(lista->cantidad_elementos == 1){
    lista = vaciar_lista(lista);
    return TODO_OK;
  }
  lista = desapilar(lista);
  return TODO_OK;
}

void* lista_tope (lista_t* lista){
  if(!lista || lista_vacia(lista))
    return NULL;
  return lista->ultimo->elemento;
}


//Operaciones para colas

lista_t* encolar(lista_t* lista, nodo_t* nuevo){
  nuevo->siguiente = lista->ultimo;
  lista->ultimo = nuevo;
  lista->cantidad_elementos++;
  return lista;
}

int lista_encolar (lista_t* lista, void* elemento){
  if(!lista || !elemento)
    return ERROR;
  nodo_t* nuevo = crear_nodo(elemento);
  if(!nuevo)
    return ERROR;
  if(lista_vacia(lista)){
    lista = insertar_primer_elemento(lista, nuevo);
    return TODO_OK;
  }
  lista = encolar(lista, nuevo);
  return TODO_OK;
}

lista_t* desencolar(lista_t* lista){
  nodo_t* aux = buscar_nodo_en_posicion(lista, lista->ultimo, lista->cantidad_elementos -2);
  liberar_nodo(lista->primero);
  lista->primero = aux;
  lista->cantidad_elementos--;
  return lista;
}

int lista_desencolar(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return ERROR;
  if(lista->cantidad_elementos == 1){
    lista = vaciar_lista(lista);
    return TODO_OK;
  }
  lista = desencolar(lista);
  return TODO_OK;
}

void* lista_primero(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return NULL;
  return lista->primero->elemento;
}

//Operaciones lista iterador




lista_iterador_t* lista_iterador_crear(lista_t* lista){
  if(!lista)
    return NULL;
  lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t) );
  if(!iterador)
    return NULL;
  iterador->lista = lista;
  iterador->indice = lista->primero;
  return iterador;
}

bool lista_iterador_tiene_siguiente (lista_iterador_t* iterador){
  if(!iterador || lista_vacia(iterador->lista))
    return false;
  return iterador->indice !=NULL;
}

void* lista_iterador_siguiente(lista_iterador_t* iterador){
  if(!iterador || !lista_iterador_tiene_siguiente(iterador))
    return NULL;
  void* elemento_actual = iterador->indice->elemento;
  iterador->indice = iterador->indice->siguiente;
  return elemento_actual;
}

void lista_iterador_destruir (lista_iterador_t* iterador){
  if(!iterador)
    return;
  free(iterador);
}

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*, void*), void* contexto){
  if(!lista || !funcion || !contexto || lista_vacia(lista))
    return;
  nodo_t* indice = lista->primero;
  void* actual = lista->primero->elemento;
  while(indice != NULL){
    funcion (actual,contexto);
    indice=indice->siguiente;
    if(indice)
    actual = indice->elemento;
  }
}
