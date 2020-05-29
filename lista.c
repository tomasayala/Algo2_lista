#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

const int ERROR = -1;
const int TODO_OK = 0;
const size_t PRIMERA_POSICION = 0;
const size_t LISTA_VACIA = 0;
const size_t UNICO_ELEMENTO = 1;

typedef struct nodo{
  void* elemento;
  struct nodo* siguiente;
}nodo_t;

struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t cantidad_elementos;
    bool es_cola;
};

struct lista_iterador{
    lista_t* lista;
    nodo_t* indice;
};

/*
*  Funcion privada
*  Recibe un nodo con memoria dinamica asignada
*  Y devuelve ese mismo puntero asignado a NULL
*/

void liberar_nodo (nodo_t* nodo){
  free(nodo);
  nodo = NULL;
}

/*
* Funcion privada
* Recibe una lista con un unico elemento cargado
* Devuelve una lista sin ningun elemento
*/

lista_t* vaciar_lista(lista_t* lista){
  liberar_nodo(lista->primero);
  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->cantidad_elementos = LISTA_VACIA;
  return lista;
}

/*
* Funcion publica
* Devuelve un puntero a una lista en el heap o NULL
*/

lista_t* lista_crear(){
  lista_t* lista = calloc (1, sizeof (lista_t));
  lista->es_cola = false;
  return lista;
}

/*
* Funcion publica
* Precondiciones: El puntero de la lista tiene que ser distinto de NULL
* Postcondiciones: Devuelve un bool si la lista esta vacia
*/

bool lista_vacia ( lista_t* lista){
  if(!lista)
    return true;
  return lista->cantidad_elementos == LISTA_VACIA;
}

/*
* Funcion privada
* Recibe un puntero a un elemento
* Devuelve un nodo una direccion a un nodo en el heap o un puntero a NULL
*/

nodo_t* crear_nodo(void* elemento){
  nodo_t* nuevo = calloc(1, sizeof(nodo_t));
  if(!nuevo)
    return NULL;
  nuevo->elemento = elemento;
  return nuevo;
}

/*
* Funcion privada
* No hay Precondiciones sobre los parametros
* Postcondiciones: Devuelve un nodo en la posicion buscada
*/

nodo_t* buscar_nodo_en_posicion(lista_t* lista, nodo_t* primer_nodo, size_t posicion_deseada){
  nodo_t* deseado = primer_nodo;
  size_t posicion_actual = PRIMERA_POSICION;
  while (posicion_actual != posicion_deseada) {
    deseado = deseado->siguiente;
    posicion_actual++;
  }
  return deseado;
}

/*
* Funcion privada
* Precondiciones: no hay Precondiciones sobre los parametros
* Postcondiciones: Devuelve un lista con un nuevo nodo insertado en la primera primera posicion
*/

lista_t* insertar_primera_posicion (lista_t* lista, nodo_t* nuevo){
  nuevo->siguiente = lista->primero;
  lista->primero = nuevo;
  lista->cantidad_elementos++;
  return lista;
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve una lista con un nuevo nodo insertado al final
*/

lista_t* insertar_al_final( lista_t* lista, nodo_t* nuevo ){
  lista->ultimo->siguiente = nuevo;
  lista->ultimo = nuevo;
  lista->cantidad_elementos++;
  return lista;
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve una lista con un unico elemento cargado y todos los punteros en sus respectivos lugares
*/

lista_t* insertar_primer_elemento(lista_t* lista, nodo_t* nuevo){
  lista->primero = nuevo;
  lista->ultimo = nuevo;
  lista->cantidad_elementos++;
  return lista;
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada con la funcion de lista_crear
* Postcondiciones: Devuelve una lista con el elemento cargado al final de la lista
*/

int lista_insertar(lista_t* lista, void* elemento){
  if(!lista || lista->es_cola ){
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

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada con la funcon lista_crear
* Postcondiciones: Devuelve una lista con el elemento insertado en la posicion deseada de la lista
*/

int lista_insertar_en_posicion ( lista_t* lista, void* elemento, size_t posicion){
  if(!lista || lista->es_cola)
    return ERROR;
  if (posicion >= lista->cantidad_elementos)
    return lista_insertar(lista,elemento);
  nodo_t* nuevo = crear_nodo(elemento);
  if(!nuevo)
    return ERROR;
  if(posicion == PRIMERA_POSICION){
    lista = insertar_primera_posicion(lista,nuevo);
    return TODO_OK;
  }
  nodo_t* actual = buscar_nodo_en_posicion(lista, lista->primero, posicion-1);
  nuevo->siguiente = actual->siguiente;
  actual->siguiente = nuevo;
  lista->cantidad_elementos++;
  return TODO_OK;
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones: Saca el ultimo elemento de una lista y disminuye la cantidad de elementos de la lista
*/

lista_t* desapilar (lista_t* lista){
  nodo_t* penultimo = buscar_nodo_en_posicion(lista, lista->primero, lista->cantidad_elementos - 2);
  penultimo->siguiente = NULL;
  liberar_nodo(lista->ultimo);
  lista->ultimo = penultimo;
  lista->cantidad_elementos--;
  return lista;
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada con lista_crear y los elementos insertados con lista_insertar o lista_insertar_en_posicion
* Postcondiciones: Devuelve una lista con el ultimo elemento
*/

int lista_borrar(lista_t* lista){
  if(!lista || lista_vacia(lista) || lista->es_cola)
    return ERROR;
  if(lista->cantidad_elementos == UNICO_ELEMENTO){
    lista = vaciar_lista(lista);
    return TODO_OK;
  }
  lista = desapilar(lista);
  return TODO_OK;
}

/*
* Funcion privado
* No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve una lista habiendo borrado el primer nodo de la lista
*/

lista_t* borrar_primera_posicion(lista_t* lista){
  nodo_t* a_eleminar = lista->primero;
  lista->primero = (nodo_t*) lista->primero->siguiente;
  liberar_nodo(a_eleminar);
  lista->cantidad_elementos--;
  return lista;
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada con lista_crear y los elementos insertados con lista_insertar o lista_insertar_en_posicion
* Postcondiciones: Devuelve si se pudo borrar el elemento en la posicion deseada o no
*/

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

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada con lista_crear
* Postcondiciones: Devuelve un puntero a la posicion deseada
*/

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

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creado con lista_crear
* Postcondiciones: Devuelve el ultimo elemento que se inserto en la lista
*/

void* lista_ultimo(lista_t* lista){
  if(!lista|| lista_vacia(lista) )
    return NULL;
  return lista->ultimo->elemento;
}

/*
* Funcion publica
* Precondiciones: La lista de haber sido creado con lista_crear
* Postcondiciones: Devuelve la cantidad de elementos de la lista
*/

size_t lista_elementos (lista_t* lista){
  if(!lista)
    return 0;
  return lista->cantidad_elementos;
}

/*
* Funcion publica
* Precondiciones: La pila debe haber sido creada con lista_crear
* Postcondiciones: Devuelve un elemento insertado en el tope de la pila
*/

int lista_apilar(lista_t* lista, void* elemento){
  if(!lista)
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

/*
* Funcion publica
* Precondiciones: La pila debe haber sido creada con lista_crear
* Postcondiciones: Devuelve un numero diciendo si pudo borrar el ultimo elemento de la pila
*/

int lista_desapilar(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return ERROR;
  if(lista->cantidad_elementos == UNICO_ELEMENTO){
    lista = vaciar_lista(lista);
    return TODO_OK;
  }
  lista = desapilar(lista);
  return TODO_OK;
}

/*
* Funcion publica
* Precondiciones: La pila debe estar creada con lista_crear
* Postcondiciones: Devuelve un puntero al ultimo elemento  o NULL
*/

void* lista_tope (lista_t* lista){
  if(!lista || lista_vacia(lista))
    return NULL;
  return lista->ultimo->elemento;
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve una lista con el nuevo nodo al final de la cola apuntando al siguiente nodo de la cola
*/

lista_t* encolar(lista_t* lista, nodo_t* nuevo){
  nuevo->siguiente = lista->ultimo;
  lista->ultimo = nuevo;
  lista->cantidad_elementos++;
  lista->es_cola = true;
  return lista;
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido lista_crear
* Postcondiciones: Devuelve un numero diciendo si pudo encolarse o no
*/

int lista_encolar (lista_t* lista, void* elemento){
  if(!lista)
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

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve una cola habiendo desencolado el primer elemento de la cola
*/

lista_t* desencolar(lista_t* lista){
  nodo_t* aux = buscar_nodo_en_posicion(lista, lista->ultimo, lista->cantidad_elementos -2);
  liberar_nodo(lista->primero);
  lista->primero = aux;
  lista->cantidad_elementos--;
  return lista;
}

/*
* Funcion publica
* Precondiciones: La cola debe haber sido lista_crear y haber insertado los elementos con lista_encolar
* Postcondiciones: Devuelve un numero si pudo desencolar o no el primer elemento de la cola
*/

int lista_desencolar(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return ERROR;
  if(lista->cantidad_elementos == UNICO_ELEMENTO){
    lista = vaciar_lista(lista);
    return TODO_OK;
  }
  lista = desencolar(lista);
  return TODO_OK;
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada con lista_crear
* Postcondiciones: Devuelve un puntero al primer elemento de una lista
*/

void* lista_primero(lista_t* lista){
  if(!lista || lista_vacia(lista))
    return NULL;
  return lista->primero->elemento;
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creado con lista_crear
* Postcondiciones: Se libera la memoria de la lista y de los nodos
*/

void lista_destruir(lista_t* lista){
  if (!lista)
    return;
  int (*funcion_borradora) (lista_t*) = lista->es_cola ? lista_desencolar : lista_borrar;
  int borrado = funcion_borradora(lista);
  while ( !lista_vacia(lista) && borrado == TODO_OK){
    borrado = funcion_borradora(lista);
  }
  free(lista);
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada con lista_crear
* Postcondiciones: Devuelve un puntero a un iterador de la lista valido o NULL
*/

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

/*
* Funcion publica
* Precondiciones: El iterador debe haber sido con lista_iterador_crear
* Postcondiciones: Devuelve un bool si el indice apunta a un nodo valido o a NULL
*/

bool lista_iterador_tiene_siguiente (lista_iterador_t* iterador){
  if(!iterador || lista_vacia(iterador->lista))
    return false;
  return iterador->indice !=NULL;
}

/*
* Funcion publica
* Precondiciones: El iterador debe haber sido creado con lista_iterador_crear
* Postcondiciones: Devuelve un puntero a elemento que estaba en la posicion indice
*/

void* lista_iterador_siguiente(lista_iterador_t* iterador){
  if(!iterador || !lista_iterador_tiene_siguiente(iterador))
    return NULL;
  void* elemento_actual = iterador->indice->elemento;
  iterador->indice = iterador->indice->siguiente;
  return elemento_actual;
}

/*
* Funcion publica
* Precondiciones: El iterador debe haber sido creado con lista_iterador_crear
* Postcondiciones: Se libera la memoria que habia sido asignada en lista_iterador_crear
*/

void lista_iterador_destruir (lista_iterador_t* iterador){
  if(!iterador)
    return;
  free(iterador);
}

/*
* Funcion publica
* Precondiciones: La lista debe haber sido creada lista_crear y debe ser una lista o una pila
* Postcondiciones: Ejecuta la funcion pasada como parametro con cada uno de los elementos de la lista
*/

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
