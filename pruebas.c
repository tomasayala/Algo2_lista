#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
#include "probador.h"

const int EXITO = 0;
const int FALLO = -1;

void pruebas_de_lista(probador_t* probador){

  char a = 'a';
  char b = 'b';
  char c = 'c';
  char d = 'd';
  char z = 'z';
  // Prueba de lista crear y lista vacia
  {
    printf("Pruebas de lista crear y lista vacia y lista_destruir\n");
    avisar_probador(probador, "Se crea una lista");
    lista_t* lista = lista_crear();
    asegurar_probador(probador, "Se pasa una lista nula", lista_vacia(NULL) == false);
    asegurar_probador(probador, "lista_vacia recibe una lista vacia", lista_vacia(lista) == true );
    avisar_probador(probador, "Se destruye la lista vacia");
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }
  //Pruebas de lista_insertar y ultima prueba de lista_vacia y lista_destruir
  {
    printf("Pruebas de lista insertar y ultima prueba de lista_vacia y de lista_destruir\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador,"Se pasa una lista nula y elemento valido",lista_insertar(NULL,&a) == FALLO);
    asegurar_probador(probador,"Se pasa una lista valida y un elemento nulo", lista_insertar(NULL,&a) == FALLO);
    asegurar_probador(probador,"Se inserta el primer elemento en una lista vacia", lista_insertar(lista,&a) == EXITO && lista->primero == lista->ultimo && lista->primero->elemento == &a);
    asegurar_probador(probador,"Se pasa a lista_vacia una lista no vacia", lista_vacia(lista) == false);
    asegurar_probador(probador,"Se pasa a lista_insertar una lista con un elemento y lo inserta al final", lista_insertar(lista,&b) == EXITO && lista->ultimo->elemento == &b);
    avisar_probador(probador,"Se destruye una lista no vacia");
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }
  //Pruebas de lista insertar en posicion
  {
    printf("Pruebas de lista_insertar_en_posicion\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador,"Se pasa una lista nula y un elemento valido", lista_insertar_en_posicion(NULL,&a,1) == FALLO);
    asegurar_probador(probador,"Se pasa una lista valida y un elemento nulo", lista_insertar_en_posicion(lista,NULL,1) == FALLO);
    asegurar_probador(probador,"Se pasa el primer elemento a una lista vacia en la posicion 0", lista_insertar_en_posicion(lista,&a,0) == EXITO && lista->primero == lista->ultimo);
    asegurar_probador(probador,"Se pasa un elemento a una lista no vacia con una posicion mayor a la cantidad de elementos", lista_insertar_en_posicion(lista,&b,100) == EXITO && lista->ultimo->elemento == &b);
    asegurar_probador(probador,"Se pasa un elemento en la posicion 0 a una lista no vacia",lista_insertar_en_posicion(lista,&c,0) == EXITO && lista->primero->elemento == &c);
    asegurar_probador(probador,"Se pasa un elemento en la posicion 1 y lo inserta bien", lista_insertar_en_posicion(lista,&d,1) == EXITO && lista->primero->siguiente->elemento == &d);
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }
  //Pruebas de lista_borrar
  {
    printf("Pruebas de lista_borrar\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador, "Se pasa una lista nula", lista_borrar(NULL)==FALLO);
    asegurar_probador(probador, "Se pasa una lista vacia a lista borrar", lista_borrar(lista) == FALLO);
    lista_insertar(lista,&a);
    asegurar_probador(probador, "Se pasa una lista con un solo elemento", lista_borrar(lista) == EXITO && lista->primero == NULL && lista->ultimo == NULL);
    lista_insertar(lista,&a);
    lista_insertar(lista,&b);
    asegurar_probador(probador,"Se pasa una lista con mas de un elemento y lo borra bien", lista_borrar(lista) == EXITO && lista->primero->siguiente == NULL);
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }
  // Pruebas de lista_borrar_de_posicion
  {
    printf("Pruebas de lista_borrar_de_posicion\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador, "Se pasa una lista nula", lista_borrar_de_posicion(NULL,0) == FALLO);
    asegurar_probador(probador,"Se pasa una lista vacia", lista_borrar_de_posicion(lista,0) == FALLO);
    lista_insertar(lista,&a);
    lista_insertar(lista,&b);
    lista_insertar(lista,&c);
    lista_insertar(lista,&d);
    lista_insertar(lista,&z);
    asegurar_probador(probador,"Se pasa una posicion de 100 a una lista con 5 elementos", lista_borrar_de_posicion(lista,100) == EXITO && lista->ultimo->elemento == &d);
    lista_insertar(lista,&z);
    asegurar_probador(probador,"Se pide borrar la posicion 1 de una lista de 5 elementos", lista_borrar_de_posicion(lista,1) == EXITO && lista->primero->siguiente->elemento == &c);
    asegurar_probador(probador,"Se pide borrar la posicion 0 de una lista de 4 elementos", lista_borrar_de_posicion(lista,0) == EXITO && lista->primero->elemento == &c);
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }

  //Pruebas de lista_elemento_en_posicion

  {
    printf("Pruebas de lista_elemento_en_posicion\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador,"Se pasa una lista nula", lista_elemento_en_posicion(NULL,0) == NULL);
    asegurar_probador(probador,"Se pasa una lista vacia", lista_elemento_en_posicion(lista,0) == NULL);
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
    printf("\n");
  }
  //Pruebas de lista_ultimo
  {
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
    printf("\n");
  }
  //Pruebas de lista_elementos
  {
    printf("Pruebas de lista_elementos\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador,"Se pasa una lista nula y devuelve 0", lista_elementos(NULL) == 0 );
    asegurar_probador(probador,"Se pasa una lista vacia y devuelve 0", lista_elementos(lista) == 0);
    lista_insertar(lista,&a);
    lista_insertar(lista,&b);
    asegurar_probador(probador,"Se pasa una lista con dos elementos y devuelve el numero correcto", lista_elementos(lista) == lista->cantidad_elementos);
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }
  printf("Fin de las pruebas de la lista\n");
}

int main(){
  probador_t* probador = crear_probador();

  pruebas_de_lista(probador);
  /*
  pruebas_de_pila(probador);
  pruebas_de_cola(probador);
  pruebas_de_iterador(probador);
  */
  mostrar_estadisticas_totales(probador);

  destruir_probador(probador);

  return 0;
}
