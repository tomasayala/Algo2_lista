#include <stdlib.h>
#include "abb.h"

const int EXITO = 0;
const int ERROR = -1;
const int CLAVE_MAYOR = 1;
const int ELEMENTOS_IGUALES = 0;
const int CLAVE_MENOR = -1;
const size_t SIN_HIJOS = 0;
const size_t UN_HIJO = 1;
const size_t DOS_HIJOS = 2;
const int ARRAY_VACIO = 0;

/*
* Funcion privada
* Precondiciones: No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve un puntero al nodo con el elemento cargado si se pudo crear o un puntero a NULL si fallo
*/

nodo_abb_t* crear_nodo(void* elemento){
  nodo_abb_t* nuevo = calloc(1, sizeof(nodo_abb_t));
  if(nuevo)
    nuevo->elemento = elemento;
  return nuevo;
}


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
  if(!comparador)
    return NULL;
  abb_t* arbol = calloc(1,sizeof(abb_t));
  if(arbol != NULL){
    arbol->comparador = comparador;
    arbol->destructor = destructor;
  }
  return arbol;
}


bool arbol_vacio(abb_t* arbol){
  if(!arbol)
    return true;
  return arbol->nodo_raiz == NULL;
}


void* arbol_raiz(abb_t* arbol){
  if(!arbol || arbol_vacio(arbol))
    return NULL;
  return arbol->nodo_raiz->elemento;
}

abb_t* insertar_en_subarbol_derecho(abb_t* arbol, nodo_abb_t* padre, nodo_abb_t* nuevo);

/*
* Funcion privada
* No hay precondiciones sobre los parametros
*
*/

abb_t* insertar_en_subarbol_izquierdo (abb_t* arbol, nodo_abb_t* padre, nodo_abb_t* nuevo){
  if(padre->izquierda == NULL){
    padre->izquierda = nuevo;
    return arbol;
  }
  if( arbol->comparador( nuevo->elemento, padre->izquierda->elemento) == CLAVE_MENOR){
    return insertar_en_subarbol_izquierdo(arbol, padre->izquierda, nuevo);
  }
  return insertar_en_subarbol_derecho(arbol, padre->izquierda, nuevo);
}

/*
* Funcion privada
* Precondiciones: No hay precondiciones sobre los parametros
* Postcondiciones: Inserta el nuevo nodo en su hoja derecha correspondiente en el arbol
*/

abb_t* insertar_en_subarbol_derecho(abb_t* arbol, nodo_abb_t* padre, nodo_abb_t* nuevo){
  if(padre->derecha == NULL){
    padre->derecha = nuevo;
    return arbol;
  }
  if(arbol->comparador( nuevo->elemento, padre->derecha->elemento) == CLAVE_MENOR)
    return insertar_en_subarbol_izquierdo(arbol, padre->derecha, nuevo);
  return insertar_en_subarbol_derecho(arbol, padre->derecha, nuevo);
}


int arbol_insertar(abb_t* arbol, void* elemento){
  if(!arbol)
    return ERROR;
  nodo_abb_t* nuevo = crear_nodo(elemento);
  if (!nuevo)
    return ERROR;
  if(arbol_vacio(arbol)){
    arbol->nodo_raiz = nuevo;
    return EXITO;
  }
  if( arbol->comparador( elemento, arbol->nodo_raiz->elemento) == CLAVE_MENOR){
    arbol = insertar_en_subarbol_izquierdo(arbol, arbol->nodo_raiz, nuevo);
    return EXITO;
  }
  arbol = insertar_en_subarbol_derecho( arbol, arbol->nodo_raiz, nuevo);
  return EXITO;
}

/*
* Funcion privada
* Precondiciones: El elemento buscado de poder ser comparable con los elmentos de los nodos segun el comparador
* Postcondiciones: Devuelve NULL si el elemento no esta dentro del arbol o una puntero a donde se encuentra el elemento en el arbol.
*/

void* buscar_elemento(abb_comparador comparador, nodo_abb_t* actual, void* buscado){
  if(!actual)
    return NULL;
  int comparacion = comparador(buscado, actual->elemento);
  if(comparacion == ELEMENTOS_IGUALES)
    return actual->elemento;
  else if( comparacion == CLAVE_MENOR )
    return buscar_elemento(comparador, actual->izquierda, buscado);
  else
    return buscar_elemento( comparador, actual->derecha, buscado);
}


void* arbol_buscar(abb_t* arbol, void* elemento){
  if(!arbol)
    return NULL;
  void* buscado = buscar_elemento(arbol->comparador, arbol->nodo_raiz, elemento);
  return buscado;
}


/*
* Funcion privada
*
* Postcondiciones: Devuelve el nodo a borrar y se guarda una referencia al padre del nodo al que hay que borrar
*/

nodo_abb_t* buscar_nodo_a_borrar(abb_t* arbol, nodo_abb_t** padre_buscado, nodo_abb_t* buscado, void* elemento_buscado, nodo_abb_t* actual){
  if((!actual->izquierda && !actual->derecha) || !actual )
    return buscado;
  int comparacion = arbol->comparador( elemento_buscado, actual->elemento);
  if(actual->izquierda != NULL){
    if( arbol->comparador ( elemento_buscado, actual->izquierda->elemento) == ELEMENTOS_IGUALES){
      buscado = actual->izquierda;
      (*padre_buscado) = actual;
      return buscado;
    }
  }
  if(actual->derecha != NULL){
    if(arbol->comparador ( elemento_buscado, actual->derecha->elemento) == ELEMENTOS_IGUALES){
      buscado = actual->derecha;
      (*padre_buscado) = actual;
      return buscado;
    }
  }
  if(comparacion == CLAVE_MAYOR){
    return buscar_nodo_a_borrar(arbol, padre_buscado, buscado, elemento_buscado, actual->derecha);
  }
  return buscar_nodo_a_borrar(arbol, padre_buscado, buscado, elemento_buscado, actual->izquierda);
}

/*
* Funcion privada
* Precondiciones: No hay precondiciones sobre los parametros
* Postcondiciones: Libera la memoria que fue asignada al crear un nodo y devuelve un puntero a NULL
*/

nodo_abb_t* destruir_nodo(nodo_abb_t* objetivo, abb_liberar_elemento destructor){
  if(destructor != NULL)
    destructor(objetivo->elemento);
  free(objetivo);
  return NULL;
}

/*
* Funcion privada
* Precondiciones: No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve un bool que dice si el segundo puntero es el hijo derecho
                   del nodo padre.
*/

bool es_hijo_derecho(nodo_abb_t* padre, nodo_abb_t* hijo_derecho){
  return padre->derecha == hijo_derecho;
}

/*
* Funcion privada
* Precondiciones: No hay precondiciones sobre los parametros
* Postcondiciones: Devuelve el nodo hijo del nodo a borrar cargado correctamente en su nodo abuelo
                   en la posicion correcta.
*/

nodo_abb_t* adoptar_nieto( nodo_abb_t* abuelo, nodo_abb_t* a_borrar){
  bool a_borrar_es_hijo_derecho = es_hijo_derecho (abuelo, a_borrar);
  bool hijo_derecho_de_a_borrar_es_nulo = es_hijo_derecho(a_borrar, NULL);
  if(a_borrar_es_hijo_derecho && hijo_derecho_de_a_borrar_es_nulo){
    abuelo->derecha = a_borrar->izquierda;
  }
  else if(a_borrar_es_hijo_derecho && !hijo_derecho_de_a_borrar_es_nulo){
    abuelo->derecha = a_borrar->derecha;
  }
  else if(!a_borrar_es_hijo_derecho && hijo_derecho_de_a_borrar_es_nulo){
    abuelo->izquierda = a_borrar->izquierda;
  }
  else{
    abuelo->izquierda = a_borrar->derecha;
  }
  return abuelo;
}

/*
* Funcion privada
* Precondiciones: El nodo padre debe ser != NULL
* Postcondiciones: Devuelve la cantidad de hijos que tiene un nodo
*/

size_t cantidad_de_hijos(nodo_abb_t* padre){
  size_t cantidad_hijos = SIN_HIJOS;
  if(padre->izquierda != NULL)
    cantidad_hijos++;
  if(padre->derecha != NULL)
    cantidad_hijos++;
  return cantidad_hijos;
}

/*
*
*
*
*/
nodo_abb_t* buscar_mayor_de_los_menores(nodo_abb_t** actual){
  if((*actual)->derecha->derecha == NULL){
    return (*actual)->derecha;
  }
  *actual = (*actual)->derecha;
  return buscar_mayor_de_los_menores( actual);
}

/*
*
*
*
*/
void intercambiar_elementos(nodo_abb_t* nodo_1, nodo_abb_t* nodo_2){
  void* aux = nodo_1->elemento;
  nodo_1->elemento = nodo_2->elemento;
  nodo_2->elemento = aux;
}

/*
* Funcion privada
* No hay precondiciones
* Postcondiciones: Borra el nodo a borrar y deja
*/

void destruir_nodo_con_dos_hijos( abb_t* arbol, nodo_abb_t* padre_del_borrado, nodo_abb_t* a_borrar){
  if( a_borrar->izquierda->derecha == NULL){
    if(es_hijo_derecho (padre_del_borrado, a_borrar))
      padre_del_borrado->derecha = a_borrar->izquierda;
    else{
      padre_del_borrado->izquierda = a_borrar->izquierda;
    }
    a_borrar->izquierda->derecha = a_borrar->derecha;
    a_borrar = destruir_nodo(a_borrar, arbol->destructor);
    return;
  }
  nodo_abb_t* padre_del_mayor_de_los_menores = a_borrar->izquierda;
  nodo_abb_t* mayor_de_los_menores = buscar_mayor_de_los_menores( &padre_del_mayor_de_los_menores);
  intercambiar_elementos( mayor_de_los_menores, a_borrar);
  if(mayor_de_los_menores->izquierda != NULL){
    intercambiar_elementos( mayor_de_los_menores, mayor_de_los_menores->izquierda);
    mayor_de_los_menores->izquierda = destruir_nodo( mayor_de_los_menores->izquierda, arbol->destructor);
    return;
  }
  else
    padre_del_mayor_de_los_menores->derecha = destruir_nodo(padre_del_mayor_de_los_menores->derecha, arbol->destructor);
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones: Borra el nodo adecuado y deja el mayor de los menores en su lugar en el arbol
*/

abb_t* borrar_nodo_encontrado(abb_t* arbol, nodo_abb_t* padre_del_borrado, nodo_abb_t* a_borrar){
  size_t cantidad_hijos = cantidad_de_hijos(a_borrar);
  if( cantidad_hijos == SIN_HIJOS){
    if(es_hijo_derecho(padre_del_borrado, a_borrar))
      padre_del_borrado->derecha = NULL;
    else
      padre_del_borrado->izquierda = NULL;
    a_borrar = destruir_nodo(a_borrar, arbol->destructor);
    return arbol;
  }
  else if(cantidad_hijos == UN_HIJO){
    padre_del_borrado = adoptar_nieto(padre_del_borrado, a_borrar);
    a_borrar = destruir_nodo(a_borrar, arbol->destructor);
    return arbol;
  }
  else{
    destruir_nodo_con_dos_hijos( arbol, padre_del_borrado, a_borrar);
    return arbol;
  }
}

/*
* Funcion privada
*
*
*/

void borrar_raiz_con_dos_hijo(abb_t* arbol){
  nodo_abb_t* a_borrar = arbol->nodo_raiz;
  if( a_borrar->izquierda->derecha == NULL){
    arbol->nodo_raiz = a_borrar->izquierda;
    arbol->nodo_raiz->derecha = a_borrar->derecha;
    a_borrar = destruir_nodo(a_borrar, arbol->destructor);
    return;
  }
  else{
    nodo_abb_t* padre_del_mayor_de_los_menores = a_borrar->izquierda;
    nodo_abb_t* mayor_de_los_menores = buscar_mayor_de_los_menores( &padre_del_mayor_de_los_menores);
    intercambiar_elementos( arbol->nodo_raiz, mayor_de_los_menores);
    if(mayor_de_los_menores->izquierda != NULL){
      intercambiar_elementos( mayor_de_los_menores, mayor_de_los_menores->izquierda);
      mayor_de_los_menores->izquierda = destruir_nodo( mayor_de_los_menores->izquierda, arbol->destructor);
      return;
    }
    else
      padre_del_mayor_de_los_menores->derecha = destruir_nodo(mayor_de_los_menores, arbol->destructor);
  }
}


/*
* Funcion privada
*
*
*/

void borrar_raiz_con_un_hijo( abb_t* arbol){
  nodo_abb_t* aux = arbol->nodo_raiz;
  if( aux->derecha != NULL)
    arbol->nodo_raiz = aux->derecha;
  else{
    arbol->nodo_raiz = aux->izquierda;
  }
  aux = destruir_nodo( aux, arbol->destructor);
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones: Borra el nodo raiz
*/

void borrar_raiz( abb_t* arbol){
  size_t cantidad_hijos = cantidad_de_hijos(arbol->nodo_raiz);
  if( cantidad_hijos == SIN_HIJOS){
    arbol->nodo_raiz = destruir_nodo( arbol->nodo_raiz, arbol->destructor);
    return;
  }
  else if ( cantidad_hijos == UN_HIJO){
    borrar_raiz_con_un_hijo(arbol);
    return;
  }
  else{
    borrar_raiz_con_dos_hijo(arbol);
    return;
  }
}


int arbol_borrar(abb_t* arbol, void* elemento){
  if(!arbol || arbol_vacio(arbol))
    return ERROR;
  if(arbol->comparador(arbol->nodo_raiz->elemento, elemento) == ELEMENTOS_IGUALES){
    borrar_raiz(arbol);
    return EXITO;
  }
  nodo_abb_t* padre_del_borrado = NULL;
  nodo_abb_t* a_borrar = NULL;
  a_borrar = buscar_nodo_a_borrar ( arbol, &padre_del_borrado, a_borrar, elemento, arbol->nodo_raiz);
  if(a_borrar == NULL)
    return ERROR;
  borrar_nodo_encontrado(arbol, padre_del_borrado, a_borrar);
  return EXITO;
}

/*
* Funcion privada
*
*
*/

void llenar_array_en_inorden( nodo_abb_t* actual, void** array, int tamanio_array, int* posicion){
  if(!actual)
    return;
  llenar_array_en_inorden(actual->izquierda, array, tamanio_array, posicion);
  if(*posicion < tamanio_array){
    array[*posicion] = actual->elemento;
    (*posicion)++;
  }
  if(*posicion < tamanio_array)
    llenar_array_en_inorden(actual->derecha, array, tamanio_array, posicion);
}


int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
  if( !arbol || !array || tamanio_array < 0 || arbol_vacio(arbol))
    return ARRAY_VACIO;
  int elementos_insertados = ARRAY_VACIO;
  llenar_array_en_inorden( arbol->nodo_raiz, array, tamanio_array, &elementos_insertados);
  return elementos_insertados;
}

/*
* Funcion privada
*
*
*/

void llenar_array_en_preorden( nodo_abb_t* actual, void** array, int tamanio_array, int* posicion){
  if( !actual)
    return;
  if(*posicion < tamanio_array){
    array[*posicion] = actual->elemento;
    (*posicion)++;
  }
  if(*posicion < tamanio_array)
    llenar_array_en_preorden(actual->izquierda, array, tamanio_array, posicion);
  if(*posicion < tamanio_array)
    llenar_array_en_preorden(actual->derecha, array, tamanio_array, posicion);
}


int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
  if( !arbol || !array || tamanio_array < 0 || arbol_vacio(arbol))
    return ARRAY_VACIO;
  int elementos_insertados = ARRAY_VACIO;
  llenar_array_en_preorden( arbol->nodo_raiz, array, tamanio_array, &elementos_insertados);
  return elementos_insertados;
}

/*
* Funcion privada
* No hay precondiciones parametros
* Postcondiciones:
*/

void llenar_array_en_postorden( nodo_abb_t* actual, void** array, int tamanio_array, int* posicion){
  if(!actual)
    return;
  if(*posicion < tamanio_array)
    llenar_array_en_postorden(actual->izquierda, array, tamanio_array, posicion);
  if(*posicion < tamanio_array)
    llenar_array_en_postorden(actual->derecha, array, tamanio_array, posicion);
  if(*posicion < tamanio_array){
    array[*posicion] = actual->elemento;
    (*posicion)++;
  }
}


int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
  if( !arbol || !array || tamanio_array < 0 || arbol_vacio(arbol))
    return ARRAY_VACIO;
  int elementos_insertados = ARRAY_VACIO;
  llenar_array_en_postorden( arbol->nodo_raiz, array, tamanio_array, &elementos_insertados);
  return elementos_insertados;
}

/*
* Funcion privada
* Precondiciones: No hay precondiciones sobre los parametros
* Postcondiciones: Libera toda memoria de un nodo y sus subarboles izquierdos y derechos
*/
void liberar_nodos(nodo_abb_t* actual, abb_liberar_elemento destructor){
  if(!actual)
    return;
  liberar_nodos(actual->izquierda, destructor);
  liberar_nodos(actual->derecha, destructor);
  actual = destruir_nodo(actual, destructor);
}

void arbol_destruir(abb_t* arbol){
  if(!arbol)
    return;
  if( !arbol_vacio(arbol)){
    liberar_nodos(arbol->nodo_raiz, arbol->destructor);
  }
  free(arbol);
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones:
*/

void cada_elemento_en_inorden(nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, bool* termino){
  if(!actual || *termino)
    return;
  cada_elemento_en_inorden(actual->izquierda, funcion, extra, termino);
  if(!(*termino)){
    *termino = funcion(actual->elemento, extra);
    if(!(*termino))
      cada_elemento_en_inorden(actual->derecha, funcion, extra, termino);
  }
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones:
*/

void cada_elemento_en_preorden( nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, bool* termino){
  if(!actual || *termino)
    return;
  *termino = funcion( actual->elemento, extra);
  if(!(*termino)){
    cada_elemento_en_preorden( actual->izquierda, funcion, extra, termino);
    if(!(*termino))
      cada_elemento_en_preorden( actual->derecha, funcion, extra, termino);
  }
}

/*
* Funcion privada
* No hay precondiciones sobre los parametros
* Postcondiciones:
*/

void cada_elemento_en_posorden( nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, bool* termino){
  if(!actual || *termino)
    return;
  cada_elemento_en_posorden( actual->izquierda, funcion, extra, termino);
  if(!(*termino)){
    cada_elemento_en_posorden( actual->derecha, funcion, extra, termino);
    if(!(*termino))
      *termino = funcion( actual->elemento, extra);
  }
}


void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
  if( !arbol || recorrido < ABB_RECORRER_INORDEN || recorrido > ABB_RECORRER_POSTORDEN || !funcion)
    return;
  bool termino = false;
  if( recorrido == ABB_RECORRER_INORDEN){
    cada_elemento_en_inorden( arbol->nodo_raiz, funcion, extra, &termino);
  }
  else if( recorrido == ABB_RECORRER_PREORDEN){
    cada_elemento_en_preorden( arbol->nodo_raiz, funcion, extra, &termino);
  }
  else
    cada_elemento_en_posorden( arbol->nodo_raiz, funcion, extra, &termino);
}
