#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
#include "probador.h"

void pruebas_de_lista(probador_t* probador){

  char a = 'a';
  char b = 'b';
  /*
  char c = 'c';
  char d = 'd';
  char z = 'z';
*/
  // Prueba de lista crear y lista vacia
  {
    printf("Pruebas de lista crear y lista vacia\n");
    avisar_probador(probador, "Se crea una lista");
    lista_t* lista = lista_crear();
    asegurar_probador(probador, "Se pasa una lista nula", lista_vacia(NULL) == false);
    asegurar_probador(probador, "lista_vacia recibe una lista vacia", lista_vacia(lista) == true );
    avisar_probador(probador, "Se destruye la lista vacia");
    lista_destruir(lista);
    printf("\n");
  }
  //Pruebas de lista_insertar y ultima prueba de lista_vacia
  {
    printf("Pruebas de lista insertar\n");
    avisar_probador(probador, "Se crea una lista");
    lista_t* lista = lista_crear();
    asegurar_probador(probador,"Se pasa una lista nula y elemento valido",lista_insertar(NULL,&a) == ERROR);
    asegurar_probador(probador,"Se pasa una lista valida y un elemento nulo", lista_insertar(NULL,&a) == ERROR);
    asegurar_probador(probador,"Se inserta el primer elemento en una lista vacia", lista_insertar(lista,&a) == TODO_OK && lista->primero == lista->ultimo);
    asegurar_probador(probador,"Se pasa a lista_vacia una lista no vacia", lista_vacia(lista) == false);
    asegurar_probador(probador,"Se pasa a lista_insertar una lista con un elemento y lo inserta al final", lista_insertar(lista,&b) == TODO_OK && (char*) lista->ultimo->elemento == &b);
    asegurar_probador()
  }
}

int main(){
  probador_t* probador = crear_probador();

  pruebas_de_lista(probador);
  /*
  pruebas_de_pila(probador);
  pruebas_de_cola(probador);
  pruebas_de_iterador(probador);
  */
  mostrar_estadisticas_probador(probador);

  destruir_probador(probador);

  return 0;
}
