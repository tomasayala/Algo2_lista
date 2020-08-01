Arbol de Busqueda Binario
Tomas Ayala
Padron: 105336

Compilacion y ejecucion de las pruebas, en terminal:

  Este arbol contiene un Makefile que contiene las lineas de compilacion y de
ejecucion de las pruebas en valgrind, estas son:

    make abb y make valgrind respectivamente.

  En caso de desear ejecutar las pruebas sin valgrind, simplemente escriba
./abb y se ejecutaran las pruebas.

Archivos entregados y pruebas:

  Probador: probador.h y probador.c

  Se entrega tambien un tda probador que lleva la cuenta de cuantas pruebas se
ejecutan y ademas de cuantas de estas fueron exitosas. Tambien resalta en rojo
y en verde las pruebas las pruebas que fallaron y las que pasaron, respectiva-
mente. Tambien resalta en verde y en rojo si se pasaron todas las pruebas res-
pectivamene. Tambien marca con amarillo las pruebas ciertas pruebas que no se
pueden verificar con valores de un booleano o si es una prueba que puede llegar
a generar un segmentation fault o segmentation violation.

  El resto de los archivos entregados consisten del Makefile, y el abb con sus
respectivos .h y .c y el pdf con el enunciado.

Convenciones del ABB:

  Este ABB toma como siguiente convenciones que:
    1- Segun la funcion de comparacion que de el usuario, los elementos mayores
      se insertaran a la derecha y los menores a la izquierda.
    2- En caso de que se inserten valores repetidos en el arbol, estos se inser-
       taran como hijo derecho de dicho nodo repetido.
    3- En caso de que se quiera borrar un nodo con dos hijos, se buscara reem-
       plazar con el sucesor inorden ( el mayor de los menores).

Consideraciones para el usuario:

  *La funcion de comparacion es esencial para la creacion del abb y el arbol no
puede ser creado si esta ausente.
  *La funcion de liberar de elementos es necesario para el caso en que se quiera
utilizar el heap para crear y guardar los elementos. Esta funcion debe encar-
garse de liberar correctamente la memoria que fue asignada cuando se creo el
elemento insertado. De lo contrario, habra perdida de memoria cuando se ejecu
te el programa. Si se utilizaran elementos creados en el stack, entonce se puede
crear el arbol mandando NULL en el parametro del destructor. No habra perdida de
por el arbol.
  *Para evitar perdida de memoria, una vez que se crea el un arbol, se debe ase-
gurar que antes de la finalizacion del programa este sea destruido con la función
arbol_destruir. De lo contrario, habra perdida de memoria.

Desarrollo teorico:

  *Un ABB (Arbol Binario de Busqueda) es un tda del tipo Arbol, que es una co-
leccion de nodos en los que se distingue un nodo raiz del resto y cero o muchos
subarboles cada uno de ellos posee su raiz conectada mediatne un vertice al nodo
raiz. El nodo raiz de cada subarbol se denomina nodo hijo del nodo raiz.La can-
tidad de subarboles en el tda arbol puede ir desde 0 a k (con k perteneciente a
los numeros naturales). En el caso de los arboles binarios, es que el nodo raiz
solo estar conectado a dos subarboles, uno a su izquierda y otro a su derecha.
Dicho en otras palabras, los arboles binarios, dado un nodo, este puede solamen-
te no tener hijos, tener un solo hijo o tener dos hijos.
A direncia de los arboles binarios puros, en los ABB en estos existen una nocion
de orden a la hora de insertar elementos. Por lo general, los elemento tiene una
clave o una forma de discenir si un elemento es mayor o menor a otro y esto de-
termina, según el criterio de inserción, si el nuevo elemento se inserta en el
subarbol derecho o en el subarbol izquierdo. Esta noción de orden permite una
facilidad mayor a la hora de realizar busqueda, insertar y eleminar arboles den-
tro de arbol binario.

  *En el TDA, se encuentra la funcion de destruir debido a que este implementa-
de ABB utiliza memoria dinamica, de manera en que una vez que no se necesita mas
el arbol, ya sea porque cumplio su uso o porque esta a punto de finalizar el
programa, la memoria dinamica debe retornar al heap. Lo que hace la funcion es
liberar la memoria de todos los nodos, recorriendo y liberando el arbol en un
recorrido postorden. En el caso en que los elementos hayan sido asignados con
memoria dinamica, el destructor liberara asignada para dichos elementos.
En el caso de no tener la funcion de destruir el arbol, si se finaliza el progra
ma o si se invocara a la funcion dandole solo el arbol, habria una gran perdida
de memoria. En el primer caso, porque se finaliza el programa sin liberar la me-
moria. Y, en el segundo caso, se liberaria solo el puntero al nodo raiz y los
punteros a las funciones de comparación y destructor, no se liberaria el resto de
los nodos ni sus elementos, si se crearon con memoria dinamica.

  * En el peor de los casos, segun el orden o que elementos se inserten en el
ABB, este puede llegar a degenerar en un lista. Esto puede llegar a afectar la
complejidad de las operaciones, para los casos en los que un ABB este balanceado.
Por dicha razon se presenta una lista con las operaciones y sus complejidades en
un arbol balanceado y un arbol degenerado a en una lista, siempre analizando el
algoritmo con la formacion de evaluacion Big O:

Operacion           ABB balanceado          ABB degenarado en lista

Crear               O(1)                    O(1)
Vacio               O(1)                    O(1)
arbol_raiz          O(1)                    O(1)
Buscar              O(log n)                O(n)
Insertar            O(log n)                O(n)
Borrar              O(log n)                O(n)
Destruir            O(n)                    O(n)
Recorridos          O(n)                    O(n)
Iterador int        O(n)                    O(n)

Caso de crear, vacio y arbol_raiz
Estas funciones ejecutando instrucciones secuencialmente sin ninguna iteracion,
asumiendo que la funcion calloc se ejecuta con O(1). Por esa razon, en ambos
casos la complejidad es de O(1).

Caso de Buscar, Insertar, Borrar
  O(log n)

    Para este caso, debido a que el arbol esta balanceado y que se tiene la fun-
    ción de comparación. Cada vez que se quiera o un insertar o buscar o eliminar
    un nodo con su elemento, va a ser dentro de un subarbol derecho o un subarbol
    izquierdo. Por lo tanto, cada vez que se recorre arbol el problema se divide
    en dos debido a que se deja un subarbol entero de lado. El peor de los casos,
    para las operaciones son: En caso de buscar, que el nodo buscado no este, lo
    mismo que al borrar. Y para insertar, que el nodo que se quiera insertar va
    a ser siempre una hoja, por lo tanto siempre va a ir recorriendo nodos hasta
    encontrar su subarbol correcto.

  O(n)

    Sin embargo, para una lista degenerado, como todos los nodos, o casi todos
    los nodos se encuentran en un unico subarbol, tomando una forma semejante a
    una lista. Para buscar un nodo que se desea o que se quiera borrar se revisan
    todos o casi todos los nodos, semejante a una busqueda lineal, por lo tanto
    se obtiene una complejidad de O(n). En el caso de insertar, se revisa cada uno
    de los nodos hasta que se llega a la hoja y el nuevo nodo se inserta como
    hijo de la hoja encontrada.

Caso de Destruir, Recorridos e Iterador interno

  O(n)

    Para los casos de estas funciones, como se deben recorrer de una forma u otra
    todos los elementos del arbol, es indistinto si es un ABB balanceado o dege-
    nerado en una lista. Por lo tanto, el tiempo de ejecución de estas funciones,
    en el peor de los casos, dependra de la cantidad de nodos que han sido inser-
    tados en el arbol. 
