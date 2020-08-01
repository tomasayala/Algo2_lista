#include <stdio.h>
#include "abb.h"
#include "probador.h"

const int TODO_OK = 0;
const int FALLO = -1;



typedef struct cosa {
	int clave;
	char contenido[10];
} cosa_t;

cosa_t* crear_cosa(int clave){
	cosa_t* c = (cosa_t*)malloc(sizeof(cosa_t));
	if(c)
		c->clave = clave;
	return c;
}

void destruir_cosa(cosa_t* c){
	if(c)
		free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){
	if(!elemento1 || !elemento2)
		return 0;
	if(((cosa_t*)elemento1)->clave>((cosa_t*)elemento2)->clave)
		return 1;
	if(((cosa_t*)elemento1)->clave<((cosa_t*)elemento2)->clave)
		return -1;
	return 0;
}

void destructor_de_cosas(void* elemento){
	if(!elemento)
		return;
	destruir_cosa((cosa_t*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
	extra=extra; //para que no se queje el compilador, gracias -Werror -Wall

	if(elemento)
		printf("%i ", ((cosa_t*)elemento)->clave);

	return false;
}

bool mostrar_hasta_5(void* elemento, void* extra){
	extra=extra; //para que no se queje el compilador, gracias -Werror -Wall

	if(elemento){
		printf("%i ", ((cosa_t*)elemento)->clave);
		if(((cosa_t*)elemento)->clave == 5)
			return true;
	}

	return false;
}

void pruebas_de_arbol_crear(probador_t* probador){
  printf("Pruebas de arbol crear y arbol vacio\n");
  abb_t* arbol = arbol_crear( comparar_cosas, destructor_de_cosas);
  abb_t* arbol_sin_destructor = arbol_crear( comparar_cosas, NULL);
  asegurar_probador( probador, "Se intenta un arbol con un comparador nulo y devuelve NULL", arbol_crear(NULL, destructor_de_cosas) == NULL);
  asegurar_probador( probador, "Se crea un arbol con un comparador valido y destructor nulo", arbol_sin_destructor != NULL);
  asegurar_probador( probador, "Cuando se crea el arbol esta vacio", arbol_vacio(arbol) == true);
  asegurar_probador( probador, "Se pasa un arbol nulo a arbol vacio y devuelve true", arbol_vacio(NULL) == true);
  avisar_probador( probador, "Se destruye un arbol nulo");
  arbol_destruir( NULL);
  avisar_probador( probador, "Se destruye un arbol vacio");
  arbol_destruir( arbol);
  arbol_destruir( arbol_sin_destructor);
  mostrar_estadisticas_locales(probador);
}

void pruebas_de_arbol_vacio_e_insertar(probador_t* probador){
  printf("Pruebas de arbol vacio e insertar y de arbol raiz\n");
  cosa_t* c1 = crear_cosa(1);
  abb_t* arbol = arbol_crear( comparar_cosas, destructor_de_cosas);
  asegurar_probador( probador, "Se intenta insertar insertar en un arbol nulo y devuelve error", arbol_insertar(NULL,c1) == FALLO);
  asegurar_probador( probador, "Se pide la raiz de un arbol vacio y devuelve NULL", arbol_raiz(NULL) == NULL);
  asegurar_probador( probador, "Se intenta insertar un elemento no nulo", arbol_insertar(arbol, c1) == TODO_OK && arbol_raiz(arbol) == c1);
  asegurar_probador( probador, "Se inserta un elemento NULL en el arbol", arbol_insertar (arbol, NULL) == TODO_OK);
  asegurar_probador( probador, "Se pasa un arbol no vacio a arbol_vacio y devuelve false", arbol_vacio(arbol) == false);
  avisar_probador( probador, "Se destruye un arbol no vacio");
  arbol_destruir( arbol);
  mostrar_estadisticas_locales(probador);
}

void pruebas_de_arbol_buscar( probador_t* probador){
  printf("Pruebas de arbol buscar\n");
  abb_t* arbol = arbol_crear( comparar_cosas, destructor_de_cosas);
  cosa_t* c1 = crear_cosa(1);
  cosa_t* c2= crear_cosa(2);
  cosa_t* c3= crear_cosa(3);
  cosa_t* c4= crear_cosa(4);
  asegurar_probador( probador, "Se pasa un arbol nulo y devuelve NULL", arbol_buscar(NULL, c1) == NULL);
  asegurar_probador( probador, "Se pasa un arbol vacio a arbol buscar y devuelve NULL", arbol_buscar(arbol, c1) == NULL);
  arbol_insertar( arbol, c2);
  asegurar_probador( probador, "Se pide buscar un elemento que no esta en el arbol", arbol_buscar( arbol, c1) == NULL);
  arbol_insertar( arbol, c1);
  arbol_insertar( arbol, c3);
  arbol_insertar( arbol, c4);
  asegurar_probador( probador, "Se pide buscar un elemento que esta en el arbol y devuelve ese elemento", arbol_buscar( arbol, c4) == c4);
  arbol_destruir(arbol);
  mostrar_estadisticas_locales(probador);
}

void pruebas_de_recorrido_inorden(probador_t* probador, int cantidad, cosa_t* elementos[10], abb_t* arbol){
  printf("Pruebas de recorrido inorden \n");
  asegurar_probador( probador, "Se pasa un arbol nulo y devuelve 0", arbol_recorrido_inorden(NULL,(void**) elementos, 10) == 0);
  asegurar_probador( probador, "Se pasa un array nulo y devuelve 0", arbol_recorrido_inorden(arbol, NULL, 10) == 0);
  asegurar_probador( probador, "Se pasa un tamaño negativo y devuelve 0", arbol_recorrido_inorden(arbol, (void**) elementos, -1) == 0);
  asegurar_probador( probador, "Se pasa un tamaño 0 y devuelve 0", arbol_recorrido_inorden(arbol, (void**)elementos, 0)==0);
  cantidad = arbol_recorrido_inorden(arbol, (void**) elementos, 10);
  avisar_probador(probador, "Se recorre un arbol inorden, deberia ser 1 2 3 4 5 7 9");
  for (size_t i = 0; i < cantidad; i++) {
    printf("%i ", elementos[i]->clave);
  }
  printf("\n");
}

void pruebas_de_recorridos_preorden( probador_t* probador, int cantidad, cosa_t* elementos[10], abb_t* arbol){
  printf("Pruebas de recorrido preorden \n");
  asegurar_probador( probador, "Se pasa un arbol nulo y devuelve 0", arbol_recorrido_preorden(NULL,(void**) elementos, 10) == 0);
  asegurar_probador( probador, "Se pasa un array nulo y devuelve 0", arbol_recorrido_preorden(arbol, NULL, 10) == 0);
  asegurar_probador( probador, "Se pasa un tamaño negativo y devuelve 0", arbol_recorrido_preorden(arbol, (void**) elementos, -1) == 0);
  asegurar_probador( probador, "Se pasa un tamaño 0 y devuelve 0", arbol_recorrido_preorden(arbol, (void**)elementos, 0)==0);
  cantidad = arbol_recorrido_preorden(arbol, (void**) elementos, 10);
  avisar_probador( probador, "Se recorre un arbol en preorden, deberia ser 4 2 1 3 7 5 9");
  for (size_t i = 0; i < cantidad; i++) {
    printf("%i ", elementos[i]->clave);
  }
  printf("\n");
}

void pruebas_de_recorrido_postorden(probador_t* probador, int cantidad, cosa_t* elementos[10], abb_t* arbol){
  printf("Pruebas de recorrido postorden\n");
  asegurar_probador( probador, "Se pasa un arbol nulo y devuelve 0", arbol_recorrido_postorden(NULL,(void**) elementos, 10) == 0);
  asegurar_probador( probador, "Se pasa un array nulo y devuelve 0", arbol_recorrido_postorden(arbol, NULL, 10) == 0);
  asegurar_probador( probador, "Se pasa un tamaño negativo y devuelve 0", arbol_recorrido_postorden(arbol, (void**) elementos, -1) == 0);
  asegurar_probador( probador, "Se pasa un tamaño 0 y devuelve 0", arbol_recorrido_postorden(arbol, (void**)elementos, 0)==0);
  cantidad = arbol_recorrido_postorden( arbol, (void**) elementos, 10);
  avisar_probador( probador, "Se recorre un arbol en postorden, deberia ser 1 3 2 5 9 7 4");
  for (size_t i = 0; i < cantidad; i++) {
    printf("%i ", elementos[i]->clave);
  }
  printf("\n");
}

void pruebas_de_recorridos(probador_t* probador){
  printf("Pruebas de arbol_recorrer\n");
  int cantidad = 0;
  cosa_t* elementos[10];
  abb_t* arbol = arbol_crear( comparar_cosas, destructor_de_cosas);
  printf("Pruebas de recorridos con arboles vacio\n");
  asegurar_probador( probador, "Se pasa un arbol vacio y devuelve 0, en preorden", arbol_recorrido_preorden(arbol, (void**) elementos, 10) == 0);
  asegurar_probador( probador, "Se pasa un arbol vacio y devuelve 0, en inorden", arbol_recorrido_inorden(arbol, (void**) elementos, 10) == 0);
  asegurar_probador( probador, "Se pasa un arbol vacio y devuelve 0, en postorden", arbol_recorrido_postorden(arbol, (void**) elementos, 10) == 0);
  arbol_insertar(arbol, crear_cosa(4));
  arbol_insertar(arbol, crear_cosa(2));
  arbol_insertar(arbol, crear_cosa(1));
  arbol_insertar(arbol, crear_cosa(3));
  arbol_insertar(arbol, crear_cosa(7));
  arbol_insertar(arbol, crear_cosa(9));
  arbol_insertar(arbol, crear_cosa(5));
  pruebas_de_recorrido_inorden( probador, cantidad, elementos, arbol);
  pruebas_de_recorridos_preorden( probador, cantidad, elementos, arbol);
  pruebas_de_recorrido_postorden( probador, cantidad, elementos, arbol);
  arbol_destruir(arbol);
  mostrar_estadisticas_locales(probador);
}

void pruebas_de_borrar_raiz(probador_t* probador){
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  cosa_t* c1 = crear_cosa(1);
  cosa_t* c2 = crear_cosa(2);
  cosa_t* c3 = crear_cosa(3);
  cosa_t* c4 = crear_cosa(4);
  cosa_t* c5 = crear_cosa(5);
  arbol_insertar(arbol, c4);
  asegurar_probador(probador, "Se pide borrar un elemento que no esta en el arbol devuelve FALLO", arbol_borrar(arbol, c1) == FALLO);
  asegurar_probador(probador, "Se borra la raiz y el arbol queda vacio", arbol_borrar(arbol,c4) == TODO_OK && arbol_vacio(arbol));
  arbol_insertar(arbol, c1);
  c4 = crear_cosa(4);
  arbol_insertar(arbol, c4);
  asegurar_probador(probador, "Se borra la raiz (1) que tiene un hijo y su unico hijo es ahora la raiz (4)", arbol_borrar(arbol,c1) == TODO_OK && arbol_raiz(arbol) == c4);
  arbol_insertar(arbol, c2);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c5);
  asegurar_probador(probador, "La raiz (4) tiene dos hijos y la nueva raiz es el mayor de los menores (3)", arbol_borrar(arbol,c4) == TODO_OK && arbol_raiz(arbol) == c3);
	arbol_destruir(arbol);
}

void pruebas_de_arbol_borrar(probador_t* probador){
  printf("Pruebas de arbol borrar\n");
	abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
  cosa_t* c1 = crear_cosa(1);
  cosa_t* c2 = crear_cosa(2);
  cosa_t* c3 = crear_cosa(3);
  cosa_t* c4 = crear_cosa(4);
  cosa_t* c5 = crear_cosa(5);
  cosa_t* c6 = crear_cosa(6);
  cosa_t* c7 = crear_cosa(7);
  asegurar_probador(probador, "Se pasa un arbol nulo a arbol borrar y devuelve FALLO", arbol_borrar(NULL,NULL) == FALLO);
  asegurar_probador(probador, "Se pasa un arbol vacio y devuelve FALLO", arbol_borrar(arbol,NULL) == FALLO);
  pruebas_de_borrar_raiz(probador);
  arbol_insertar(arbol, c4);
  arbol_insertar(arbol, c2);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c1);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c7);
  arbol_insertar(arbol, c5);
  asegurar_probador(probador, "Se pide borrar una hoja (7)", arbol_borrar(arbol,c7) == TODO_OK);
  asegurar_probador(probador, "Se pide borrar un nodo con hijo(6)", arbol_borrar(arbol, c6) == TODO_OK);
  asegurar_probador(probador, "Se pide borrar un nodo con dos hijos(2)", arbol_borrar(arbol, c2) == TODO_OK);
  arbol_destruir(arbol);
  mostrar_estadisticas_locales(probador);
}

void pruebas_de_con_cada_elemento(probador_t* probador){
	printf("Pruebas de iterador interno\n");
  abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);
	avisar_probador(probador, "Se pasa un arbol vacio y no tendria que imprimirse nada");
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
  arbol_insertar(arbol, crear_cosa(4));
  arbol_insertar(arbol, crear_cosa(2));
  arbol_insertar(arbol, crear_cosa(1));
  arbol_insertar(arbol, crear_cosa(3));
  arbol_insertar(arbol, crear_cosa(7));
  arbol_insertar(arbol, crear_cosa(9));
  arbol_insertar(arbol, crear_cosa(5));
	avisar_probador(probador, "Se pasa un arbol nulo, no tendria que imprimirse nada");
	abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
	avisar_probador(probador, "Se pasa dos recorridos invalidos, -1 y 3. No tendria que imprimirse nada");
	abb_con_cada_elemento(arbol, -1, mostrar_elemento, NULL);
	abb_con_cada_elemento(arbol, 3, mostrar_elemento, NULL);
	avisar_probador(probador, "Se pasa una funcion NULL y no tendria que imprimir nada");
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL);
	avisar_probador(probador, "Se recorre inorden todos los elementos  deberia imprimirse 1 2 3 4 5 7 9");
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
	printf("\n");
	avisar_probador(probador, "Muestra todos los elementos hasta el 5");
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
	printf("\n");
	avisar_probador(probador,"Muestra todos los elemento en preorden, deberia imprimirse 4 2 1 3 7 5 9");
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
	printf("\n");
	avisar_probador(probador, "Muestra todos los elementos hasta el 5");
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
	printf("\n");
	avisar_probador(probador, "Muestra todos los elementos en postorden, deberia imprimirse 1 3 2 5 9 7 4");
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
	printf("\n");
	avisar_probador(probador, "Muestra todos los elementos hasta el 5");
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
	printf("\n");
	arbol_destruir(arbol);
}

int main(){
  probador_t* probador = crear_probador();
  pruebas_de_arbol_crear(probador);
  pruebas_de_arbol_vacio_e_insertar(probador);
  pruebas_de_arbol_buscar(probador);
  pruebas_de_recorridos(probador);
  pruebas_de_arbol_borrar(probador);
  pruebas_de_con_cada_elemento(probador);
	mostrar_estadisticas_totales(probador);
  destruir_probador(probador);
  return 0;
}
