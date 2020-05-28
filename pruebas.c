#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
#include "probador.h"

const int EXITO = 0;
const int FALLO = -1;

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas
                  de lista_crear y lista_destruir y lista_vacia. Tambien avisa cuando se
                  ejecta funciones con parametros que pueden generar segmentation fault
*/

void prueba_lista_crear(probador_t* probador){
  printf("Pruebas de lista crear y lista vacia y lista_destruir\n");
  avisar_probador(probador, "Se crea una lista");
  lista_t* lista = lista_crear();
  asegurar_probador(probador, "Se pasa una lista nula y devuelve true", lista_vacia(NULL) == true);
  asegurar_probador(probador, "lista_vacia recibe una lista vacia", lista_vacia(lista) == true );
  avisar_probador(probador, "Se destruye la lista vacia");
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                   de lista_insertar, lista_borrar y lista_vacia. Tambien avisa cuando se
                   ejecuta funciones con parametros que pueden generar la terminacion temprana
                   del programa por segmentation fault o violacion de segmento.
*/

void prueba_lista_insertar(probador_t* probador){
  char a = 'a';
  char b = 'b';
  printf("Pruebas de lista insertar y ultima prueba de lista_vacia y de lista_destruir\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador,"Se pasa una lista nula y elemento valido",lista_insertar(NULL,&a) == FALLO);
  asegurar_probador(probador,"Se inserta el primer elemento en una lista vacia", lista_insertar(lista,&a) == EXITO);// && lista->primero == lista->ultimo && lista->primero->elemento == &a);
  asegurar_probador(probador,"Se pasa una lista valida y un elemento nulo", lista_insertar(lista, NULL) == EXITO);
  asegurar_probador(probador,"Se pasa a lista_insertar una lista con un elemento y lo inserta al final", lista_insertar(lista,&b) == EXITO);//) && lista->ultimo->elemento == &b);
  asegurar_probador(probador,"Se pasa a lista_vacia una lista no vacia", lista_vacia(lista) == false);
  avisar_probador(probador,"Se destruye una lista no vacia");
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                   lista_insertar_en_posicion.
*/

void prueba_lista_insertar_en_posicion(probador_t* probador){
  char a = 'a';
  char b = 'b';
  char c = 'c';
  char d = 'd';
  printf("Pruebas de lista_insertar_en_posicion\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador,"Se pasa una lista nula y un elemento valido", lista_insertar_en_posicion(NULL,&a,1) == FALLO);
  asegurar_probador(probador,"Se pasa el primer elemento a una lista vacia en la posicion 0", lista_insertar_en_posicion(lista,&a,0) == EXITO); //&& lista->primero == lista->ultimo);
  asegurar_probador(probador,"Se pasa un elemento a una lista no vacia con una posicion mayor a la cantidad de elementos", lista_insertar_en_posicion(lista,&b,100) == EXITO); //&& lista->ultimo->elemento == &b);
  asegurar_probador(probador,"Se pasa un elemento en la posicion 0 a una lista no vacia",lista_insertar_en_posicion(lista,&c,0) == EXITO); //&& lista->primero->elemento == &c);
  asegurar_probador(probador,"Se pasa un elemento en la posicion 1 y lo inserta bien", lista_insertar_en_posicion(lista,&d,1) == EXITO && lista_elemento_en_posicion(lista,1) == &d); //&& lista->primero->siguiente->elemento == &d);
  asegurar_probador(probador,"Se pasa una lista valida y un elemento nulo", lista_insertar_en_posicion(lista,NULL,100) == EXITO);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_borrar
*/

void prueba_lista_borrar(probador_t* probador){
  char a = 'a';
  char b = 'b';
  printf("Pruebas de lista_borrar\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador, "Se pasa una lista nula", lista_borrar(NULL)==FALLO);
  asegurar_probador(probador, "Se pasa una lista vacia a lista borrar", lista_borrar(lista) == FALLO);
  lista_insertar(lista,&a);
  asegurar_probador(probador, "Se pasa una lista con un solo elemento", lista_borrar(lista) == EXITO && lista_vacia(lista)); //&& lista->primero == NULL && lista->ultimo == NULL);
  lista_insertar(lista,&a);
  lista_insertar(lista,&b);
  asegurar_probador(probador,"Se pasa una lista con mas de un elemento y lo borra bien", lista_borrar(lista) == EXITO); //&& lista->primero->siguiente == NULL);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                   prueba_lista_borrar_en_posicion
*/

void prueba_lista_borrar_en_posicion(probador_t* probador){
  char a = 'a';
  char b = 'b';
  char c = 'c';
  char d = 'd';
  char z = 'z';
  printf("Pruebas de lista_borrar_de_posicion\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador, "Se pasa una lista nula", lista_borrar_de_posicion(NULL,0) == FALLO);
  asegurar_probador(probador,"Se pasa una lista vacia", lista_borrar_de_posicion(lista,0) == FALLO);
  lista_insertar(lista,&a);
  lista_insertar(lista,&b);
  lista_insertar(lista,&c);
  lista_insertar(lista,&d);
  lista_insertar(lista,&z);
  asegurar_probador(probador,"Se pasa una posicion de 100 a una lista con 5 elementos", lista_borrar_de_posicion(lista,100) == EXITO); //&& lista->ultimo->elemento == &d);
  lista_insertar(lista,&z);
  asegurar_probador(probador,"Se pide borrar la posicion 1 de una lista de 5 elementos", lista_borrar_de_posicion(lista,1) == EXITO); //&& lista->primero->siguiente->elemento == &c);
  asegurar_probador(probador,"Se pide borrar la posicion 0 de una lista de 4 elementos", lista_borrar_de_posicion(lista,0) == EXITO); //&& lista->primero->elemento == &c);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                   lista_elemento_en_posicion
*/

void prueba_lista_elemento_en_posicion(probador_t* probador){
  char a = 'a';
  char b = 'b';
  char c = 'c';
  char d = 'd';
  char z = 'z';
  printf("Pruebas de lista_elemento_en_posicion\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador,"Se pasa una lista nula", lista_elemento_en_posicion(NULL,0) == NULL);
  asegurar_probador(probador,"Se pasa una lista vacia", lista_elemento_en_posicion(lista,0) == NULL);
  lista_insertar(lista,&a);
  lista_insertar(lista,&b);
  lista_insertar(lista,&c);
  lista_insertar(lista,&d);
  lista_insertar(lista,&z);
  asegurar_probador(probador,"Se pide la posicion 100 de una lista de 5 elementos", lista_elemento_en_posicion(lista,100) == NULL);
  asegurar_probador(probador,"Se pide el primer elemento de una lista de 5 elementos", lista_elemento_en_posicion(lista,0) == &a);
  asegurar_probador(probador,"Se pide el ultimo elemento de una lista de 5 elementos", lista_elemento_en_posicion(lista,4) == &z);
  asegurar_probador(probador,"Se pide la posicion 2 de una lista de 5 elementos", lista_elemento_en_posicion(lista,2)  == &c);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                   lista_ultimo
*/

void prueba_lista_ultimo(probador_t* probador){
  char a = 'a';
  char b = 'b';
  printf("Pruebas de lista_ultimo\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador,"Se pasa una lista nula", lista_ultimo(NULL) == NULL);
  asegurar_probador(probador,"Se pasa una lista vacia", lista_ultimo(lista) == NULL);
  lista_insertar(lista,&a);
  asegurar_probador(probador,"Se pasa una lista con unico elemento y devuelve ese elemento", lista_ultimo(lista) == &a);
  lista_insertar(lista,&b);
  asegurar_probador(probador,"Se pasa una lista con mas de un elemento y devuelve el ultimo", lista_ultimo(lista) == &b);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_elementos
*/

void prueba_lista_elementos(probador_t* probador){
  char a = 'a';
  char b = 'b';
  printf("Pruebas de lista_elementos\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador,"Se pasa una lista nula y devuelve 0", lista_elementos(NULL) == 0 );
  asegurar_probador(probador,"Se pasa una lista vacia y devuelve 0", lista_elementos(lista) == 0);
  lista_insertar(lista,&a);
  lista_insertar(lista,&b);
  asegurar_probador(probador,"Se pasa una lista con dos elementos y devuelve el numero correcto", lista_elementos(lista) == 2);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El puntero contador debe ser distinto de NULL
* Postcondiciones: Muestra por pantalla los elementos de la lista en orden
*/

void mostrar_elemento(void* elemento, void* contador){
  if(elemento && contador)
    printf("Elemento %i: %c \n", (*(int*)contador)++, *(char*)elemento);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas avisando y que se espera ver cuando se ejecuta las pruebas de
                   lista_con_cada_elemento
*/

void prueba_lista_con_cada_elemento(probador_t* probador){
  void (*funcion)(void*,void*) = mostrar_elemento;
  int contador = 0;
  char a = 'a';
  char b = 'b';
  char c = 'c';
  char d = 'd';
  printf("Pruebas de lista_con_cada_elemento\n");
  lista_t* lista = lista_crear();
  lista_insertar(lista,&a);
  lista_t* lista_vacia = lista_crear();
  avisar_probador(probador,"Se pasa una lista nula, no tendria que imprimerse nada");
  lista_con_cada_elemento(NULL,funcion,(void*)&contador);
  avisar_probador(probador,"Se pasa una funcion nula, no tendria que imprimerse nada");
  lista_con_cada_elemento(lista,NULL,(void*)&contador);
  avisar_probador(probador,"Se pasa un contexto nulo, no tendria que imprimerse nada");
  lista_con_cada_elemento(lista,funcion,NULL);
  avisar_probador(probador,"Se pasa una lista vacia, no tendria que imprimerse nada");
  lista_con_cada_elemento(lista_vacia, funcion, (void*)&contador);
  lista_insertar(lista,&b);
  lista_insertar(lista,&c);
  lista_insertar(lista,&d);
  avisar_probador(probador,"Se pasa una lista no vacia, tienen que imprimir los elementos a b c d");
  lista_con_cada_elemento(lista,funcion,(void*)&contador);
  lista_destruir(lista);
}
lista_destruir(lista_vacia);

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Ejecuta todas y muestra por pantalla todas las pruebas para la lista que se pasaron o fallaron
*/

void pruebas_de_lista(probador_t* probador){
  prueba_lista_crear(probador);
  prueba_lista_insertar(probador);
  prueba_lista_insertar_en_posicion(probador);
  prueba_lista_borrar(probador);
  prueba_lista_borrar_en_posicion(probador);
  prueba_lista_elemento_en_posicion(probador);
  prueba_lista_ultimo(probador);
  prueba_lista_con_cada_elemento(probador);
  printf("Fin de las pruebas de la lista\n\n");
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_apilar
*/

void pruebas_de_apilar(probador_t* probador){
  printf("Pruebas de lista apilar\n");
  int a = 0;
  int b = 1;
  lista_t* pila = lista_crear();
  asegurar_probador(probador,"Se intenta apilar en una pila nula", lista_apilar(NULL,&a) == FALLO);
  asegurar_probador(probador,"Se inserta el primer elemento en la pila", lista_apilar(pila,&a) == EXITO && lista_ultimo(pila) == lista_primero(pila) && lista_ultimo(pila) == &a);
  // Caja blanca  asegurar_probador(probador,"Se inserta el primer elemento en la pila", lista_apilar(pila,&a) == EXITO && lista->primero->elemento == lista->ultimo->elemento);
  asegurar_probador(probador,"Se otro elemento en la pila correctamente al final", lista_apilar(pila,&b) == EXITO && lista_ultimo(pila) == &b);
  asegurar_probador(probador,"Se intenta apilar un elemento nulo en una pila no nula", lista_apilar(pila,NULL) == EXITO);
  lista_destruir(pila);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_desapilar
*/

void pruebas_de_desapilar(probador_t* probador){
  printf("Pruebas de lista desapilar\n");
  int a = 0;
  int b = 1;
  int c = 2;
  lista_t* pila = lista_crear();
  asegurar_probador(probador,"Se intenta desapilar en una lista nula", lista_desapilar(NULL) == FALLO);
  asegurar_probador(probador,"Se intenta desapilar en una pila vacia", lista_desapilar(pila) == FALLO);
  lista_apilar(pila,&a);
  asegurar_probador(probador,"Se intenta desapilar una pila con un solo elemento", lista_desapilar(pila) == EXITO && lista_vacia(pila) == true);
  lista_apilar(pila,&b);
  lista_apilar(pila,&c);
  asegurar_probador(probador,"Se intenta desapilar una pila con mas de un elemento", lista_desapilar(pila) == EXITO && lista_elementos(pila) == 1);
  // Caja blanca asegurar_probador(probador,"Se intenta desapilar una pila con mas de un elemento", lista_desapilar(pila) == EXITO && lista->cantidad_elementos == 1 && lista->primero == lista->ultimo );
  lista_destruir(pila);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_tope
*/

void pruebas_de_lista_tope(probador_t* probador){
  printf("Pruebas de lista_tope\n");
  int a = 0;
  int b = 1;
  int c = 2;
  lista_t* pila = lista_crear();
  asegurar_probador(probador,"Se pasa una pila nula", lista_tope(NULL) == NULL);
  asegurar_probador(probador,"Se pasas una pila vacia", lista_tope(pila) == NULL);
  lista_apilar(pila,&a);
  asegurar_probador(probador,"Se pide el elemento tope de una pila con unico elemento", lista_tope(pila) == &a);
  // Caja blanca   asegurar_probador(probador,"Se pide el elemento tope de una pila con unico elemento", lista_tope(pila) == lista->ultimo->elemento && lista->ultimo->elemento == &a);
  lista_apilar(pila,&b);
  lista_apilar(pila,&c);
  asegurar_probador(probador,"Se pide el elemento tope de una pila de varios elementos", lista_tope(pila) == &c);
  lista_destruir(pila);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Ejecuta todas y muestra por pantalla todas las pruebas para la lista que se pasaron o fallaron
*/

void pruebas_de_pila(probador_t* probador){
  pruebas_de_apilar(probador);
  pruebas_de_desapilar(probador);
  pruebas_de_lista_tope(probador);
  printf("Fin de las pruebas de pila\n\n");
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_encolar
*/

void pruebas_encolar(probador_t* probador){
  int a = 0;
  int b = 1;
  //int c = 2;
  printf("Pruebas de lista_encolar\n");
  lista_t* cola = lista_crear();
  asegurar_probador(probador,"Se pasa una cola nula", lista_encolar(NULL,&a) == FALLO);
  asegurar_probador(probador,"Inserta correctamente el primer elemento de una cola vacia", lista_encolar(cola,&a) == EXITO && lista_primero(cola) == &a && lista_ultimo(cola) == &a);
  asegurar_probador(probador,"Se inserta correctamente un elemento en una cola no vacia", lista_encolar(cola,&b) == EXITO && lista_ultimo(cola) == &b);
  //asegurar_probador(probador,"Se pasa un elemento nulo", lista_encolar(cola,NULL) == EXITO);
  avisar_probador(probador,"Se destruye la cola");
  lista_destruir(cola);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_desencolar
*/

void pruebas_desencolar(probador_t* probador){
  printf("Pruebas de lista_desencolar\n");
  int a = 0;
  int b = 1;
  int c = 2;
  lista_t* cola = lista_crear();
  asegurar_probador(probador,"Se pasa una cola", lista_desencolar(NULL) == FALLO);
  asegurar_probador(probador,"Se pasa una cola vacia", lista_desencolar(cola) == FALLO);
  lista_encolar(cola,&a);
  asegurar_probador(probador,"Se pasa una cola con unico y despues queda vacia", lista_desencolar(cola) == EXITO && lista_vacia(cola));
  lista_encolar(cola,&a);
  lista_encolar(cola,&b);
  lista_encolar(cola,&c);
  asegurar_probador(probador,"Se pasa una cola con multiples elementos y desencola bien", lista_desencolar(cola) == EXITO && !lista_vacia(cola) && lista_primero(cola) == &b);
  lista_destruir(cola);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de lista_primero
*/

void pruebas_lista_primero(probador_t* probador){
  printf("Pruebas de lista_primero\n");
  int a = 0;
  int b = 1;
  int c = 2;
  lista_t* cola = lista_crear();
  asegurar_probador(probador,"Se pasa una cola nula", lista_primero(NULL) == NULL);
  asegurar_probador(probador,"Se pasa una cola vacia", lista_primero(cola) == NULL);
  lista_encolar(cola,&a);
  asegurar_probador(probador,"Se pasa una cola con un unico elemento", lista_primero(cola) == &a);
  lista_desencolar(cola);
  lista_encolar(cola,&c);
  lista_encolar(cola,&b);
  asegurar_probador(probador,"Se pasa una cola con multiples elementos", lista_primero(cola) == &c);
  lista_destruir(cola);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Ejecuta y muestra por pantalla todas las pruebas de la cola
*/

void pruebas_de_cola(probador_t* probador){
  pruebas_encolar(probador);
  pruebas_desencolar(probador);
  pruebas_lista_primero(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                   lista_iterador_crear
*/

void pruebas_iterador_crear(probador_t* probador){
  printf("Pruebas de lista_iterador_crear\n");
  lista_t* lista = lista_crear();
  asegurar_probador(probador,"Se pasa una lista nula y espera que devuelva NULL", lista_iterador_crear(NULL) == NULL);
  lista_iterador_t* it = lista_iterador_crear(lista);
  asegurar_probador(probador, "Se pasa una lista vacia y devuelve un puntero al iterador", it != NULL && lista_vacia(lista));
  avisar_probador(probador,"Se intenta destruir un itereador nulo");
  lista_iterador_destruir(NULL);
  avisar_probador(probador,"Se destruye un iterador de la lista");
  lista_iterador_destruir(it);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                   lista_iterador_tiene_siguiente
*/

void pruebas_iterador_tiene_siguiente(probador_t* probador){
  printf("Pruebas de lista_iterador_tiene_siguiente\n");
  int a = 0;
  lista_t* lista = lista_crear();
  lista_iterador_t* it = lista_iterador_crear(lista);
  asegurar_probador(probador,"Se pasa un iterador NULL y devuelve false", lista_iterador_tiene_siguiente(NULL) == false);
  asegurar_probador(probador,"Se pasa una iterador a una lista vacia y devuelve false", lista_iterador_tiene_siguiente(it) == false);
  lista_iterador_destruir(it);
  lista_insertar(lista,&a);
  it = lista_iterador_crear(lista);
  asegurar_probador(probador,"Se pasa iterador que apunta a una lista no vacia en la primera posicion", lista_iterador_tiene_siguiente(it) == true);
  lista_iterador_destruir(it);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Muestra mensajes por pantallas diciendo si se pasaron las pruebas de
                    lista_iterador_siguiente
*/

void pruebas_iterador_siguiente(probador_t* probador){
  printf("Pruebas de lista_iterador_siguiente\n");
  int a = 0;
  int b = 1;
  int c = 2;
  lista_t* lista = lista_crear();
  lista_iterador_t* it = lista_iterador_crear(lista);
  asegurar_probador(probador,"Se pasa un iterador nulo y devuelve NULL", lista_iterador_siguiente(NULL) == NULL);
  asegurar_probador(probador,"Se pasa un iterador que apunta a una lista vacia", lista_iterador_siguiente(it) == NULL);
  lista_iterador_destruir(it);
  lista_insertar(lista,&a);
  lista_insertar(lista,&b);
  lista_insertar(lista,&c);
  it = lista_iterador_crear(lista);
  asegurar_probador(probador,"Se itera ahora lista con tres elementos y se pide el primero", lista_iterador_siguiente(it) == &a);
  asegurar_probador(probador,"Se pide el siguiente elemento", lista_iterador_siguiente(it) == &b);
  asegurar_probador(probador,"Se pide el ultimo elemento", lista_iterador_siguiente(it) == &c);
  asegurar_probador(probador,"Se pide un nuevo siguiente y devuelve NULL porque ya no posee mas elementos la lista", lista_iterador_siguiente(it) == NULL);
  lista_iterador_destruir(it);
  lista_destruir(lista);
  mostrar_estadisticas_locales(probador);
}

/*
* Precondiciones: El probador debe ser creado con crear_probador
* Postcondiciones: Ejecuta y muestra el resultado de todas las pruebas para el iterador de la lista
*/

void pruebas_de_iterador(probador_t* probador){
  pruebas_iterador_crear(probador);
  pruebas_iterador_tiene_siguiente(probador);
  pruebas_iterador_siguiente(probador);
}

int main(){
  probador_t* probador = crear_probador();
  if(!probador){
    perror("No hay memoria suficiente para crear las pruebas");
    return -1;
  }

  printf("\t\t\t Pruebas de lista\n");
  pruebas_de_lista(probador);
  printf("\t\t\t Pruebas de pila\n");
  pruebas_de_pila(probador);
  printf("\t\t\t Pruebas de cola\n");
  pruebas_de_cola(probador);
  printf("\t\t\t Pruebas de iteradores externos\n");
  pruebas_de_iterador(probador);

  mostrar_estadisticas_totales(probador);

  destruir_probador(probador);

  return 0;
}
