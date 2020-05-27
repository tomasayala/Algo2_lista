#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
#include "probador.h"

void pruebas_de_lista(probador_t* probador){

  char a = 'a';
  char b = 'b';
  char c = 'c';
  /*
  char d = 'd';
  char z = 'z';
*/
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
  //Pruebas de lista_insertar y ultima prueba de lista_vacia
  {
    printf("Pruebas de lista insertar y ultima prueba de lista_vacia y de lista_destruir\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador,"Se pasa una lista nula y elemento valido",lista_insertar(NULL,&a) == ERROR);
    asegurar_probador(probador,"Se pasa una lista valida y un elemento nulo", lista_insertar(NULL,&a) == ERROR);
    asegurar_probador(probador,"Se inserta el primer elemento en una lista vacia", lista_insertar(lista,&a) == TODO_OK && lista->primero == lista->ultimo && lista->primero->elemento == &a);
    asegurar_probador(probador,"Se pasa a lista_vacia una lista no vacia", lista_vacia(lista) == false);
    asegurar_probador(probador,"Se pasa a lista_insertar una lista con un elemento y lo inserta al final", lista_insertar(lista,&b) == TODO_OK && (char*) lista->ultimo->elemento == &b);
    //asegurar_probador()
    avisar_probador(probador,"Se destruye una lista no vacia");
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }
  //Pruebas de lista insertar en posicion
  {
    printf("Pruebas de lista_insertar_en_posicion\n");
    lista_t* lista = lista_crear();
    asegurar_probador(probador,"Se pasa una lista nula y un elemento valido", lista_insertar_en_posicion(NULL,&a,1) == ERROR);
    asegurar_probador(probador,"Se pasa una lista valida y un elemento nulo", lista_insertar_en_posicion(lista,NULL,1) == ERROR);
    asegurar_probador(probador,"Se pasa el primer elemento a una lista vacia en la posicion 0", lista_insertar_en_posicion(lista,&a,0) == TODO_OK && lista->primero == lista->ultimo);
    asegurar_probador(probador,"Se pasa un elemento a una lista no vacia con una posicion mayor a la cantidad de elementos", lista_insertar_en_posicion(lista,&b,100) == TODO_OK && (char*) lista->ultimo->elemento == &b);
    asegurar_probador(probador,"Se pasa un elemento en la posicion 0 a una lista no vacia",lista_insertar_en_posicion(lista,&c,0) == TODO_OK && (char*) lista->primero->elemento == &c);
    //asegurar_probador(probador,"Se pasa un elemento en la posicion 1 y lo inserta bien", lista_insertar_en_posicion(lista,&d,1) == TODO_OK && (char) lista->primero->siguiente->elemento == d);
    lista_destruir(lista);
    mostrar_estadisticas_locales(probador);
    printf("\n");
  }
  //
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
