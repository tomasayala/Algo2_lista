README

Se encuentra en esta entre la entrega de los siguientes archivos:

        a) lista.c                       lista.h
        b) probador.c                    probador.h
        c) pruebas.c                     d) Makefile

Para compilar, correr y probar el archivo se incluye un Makefile con un las lineas de
compilacion ya cargadas. Para compilar el programa simple ejecute en la terminal una vez
que estan todos los archivos extraidos en la misma carpeta. Escriba en la terminal make lista,
(sin la coma) para compilar la lista con las pruebas y make valgrind para ejecutar las pruebas
de la lista en valgrind.

a) Lista.c y lista.h
    En este archivo se encuentra desarrollo los structs definidos en el archivo lista.h
y las primitivas y funciones privadas que utiliza el tda lista. Tambien se encuentra el
desarrollo de las funciones definidas en lista.h, que son las funciones a las cuales
el usuario invoca para su propia utilización de la lista. Contiene las funciones publicas
a las cuales el usuario tiene un acceso y que contiene los contratos para dichas funciones.

b) Probador.c y probador.h
    Estos archivos se encuentran implementados el tda probador que se utiliza el archivo de pruebas.
En el .h se encuentra declarada las funciones y el contrato de que llevara el tda y en el .c se encuentra
implementadas. Este tda muestra con colores las pruebas aprobadas, desaprobadas y lleva un conteo de pruebas
que se hacen para determinadas funciones y un conteo de todas las pruebas que se van aprobando.

c) Pruebas.c
    En este archivo se encuentra la implementacion de las pruebas de las lista. Alli se prueban varias casos
del funcionamiento de la lista que fue implementada en lista.c mediante pruebas de caja negra. Se evaluan la
funcionalidad de todas las funciones publicas que aparecen en lista.h. Tambien se ejecutan las pruebas mediante
el probador de manera en que se lleven en cuenta las pruebas que se estan llevando adelante.

d) Makefile
    Contiene los flags de compilacion y de ejecucion en valgrind de la implementacion de la lista. Esta diseñado
para que el usuario no tenga que tocar los flags de compilacion de la lista y de las lineas de ejecucion de valgrind.

    En esta implementación particular de lista a la hora de definir la lista se tuvo en cuenta se genero un struct que funcione
como un nodo y que es encuentra utlizado en el struct lista. Estos structs contienen los siguientes campos:
En el caso del nodo:
    - Un puntero a void en donde se almacena el elemento que el usuario desee que se encuentra en la lista.
    - Un puntero al cual seria el siguiente nodo en la lista.
En el caso del struct lista:
    - Dos punteros a nodos, un al primer elemento de la lista y otro al ultimo elemento de la lista. Estos fueron creados con el
      objetivo de facilitar la implementacion y el acceso a la informacion que requieren algunas funciones, como lista_ultimo, lista_primero
      lista_insertar, lista_borrar y otras funciones.
    - Un size_t que lleva la cuenta de cuantos nodos fueron insertados en la lista. Tambien sirve para facilitar el acceso a las funciones a cierta
      informacion y para funcionamiento de algunas funciones privadas como buscar_nodo_en_posicion.
    - Por ultimo, se declara un bool de si una lista alguna vez fue invocada por las funciones del tda cola. Sirve, sobre todo para los casos en los que
      se desee pasar una cola a lista_borrar


Segunda Seccion

 * Una lista es un conjunto de nodos enlazados (pueden ser simple o doblemente enlazados) de manera en que un nodo lleve a otro y donde en la lista
   alla un nodo que sea el principio y otro que sea el fin de la lista y que no hayan dos nodos que apunten a un mismo nodo en una lista simplemente
   enlazada y mas de dos nodos en una dos en doblemente enlazada. La diferencia entre nodos simplementes enlazados y doblemente enlazados es que el
   nodo simplemente enlazado guarda una referencia al nodo siguiente. Mientras que el nodo doblemente enlazado guarda una referencia al nodo al nodo
   anterior y al nodo siguiente.

  * Las caracteristica fundamental de una pila es que sigue la regla FILO para insertar y borrar los elementos que se insertan en la pila.
    FILO significa First In Last Out, de manera que el primer elemento que se inserta en la pila es el ultimo que se va a eliminar si se quiere
    vaciar la pila. Y la caracteristica fundamental de la cola es que FIFO, First In First Out, de manera que el primer elemento de la cola que
    se inserta es el primer que debe ser eleminado si se quiere vaciar la cola u eleminar un elemento.

  * El iterador, en el caso de la lista, es una forma de recorrer todos los elemento la lista. Su funcion es poder recorrer cada uno de los elementos
    de una lista, desde el principio hasta el punto que se desea y/o el final. Hay dos clases de iteradores, uno externo y otro interno.
    El iterador externo es un tda, que guarda una referencia de la lista creada y es implementada para el uso del usuario, de esta manera, el usuario
    del tda puede elegir con que estructura iterativa puede recorrer la lista y hasta que punto.
    Mientras, que el iterador interno, delega la forma de la forma y la implementacion de como iterar la lista a la lista en si. Por lo general, se
    pasa una funcion a la funcion con el iterador interno para utilizara los valores de la lista, para la funcionalidad que el usuario desee.
