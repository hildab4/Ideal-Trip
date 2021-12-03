# TC1031-Integral-B

# Correcciones
* -> Se agrega el grafo y la búsqueda de información en el grafo.
* -> Se agrega lectura de archivos, y la consulta de datos en las estructuras.
* -> Se agrega la complejidad temporal de las funciones.

# Programa para obtener la ruta más corta de un estado a otro
Los datos se encuentran en el archivo puntos.txt, con estos se cargan los datos al grafo; el usuario indica en el menú inicial la opción a seleccionar por medio de un número, antes mostrado cuando se despliega el menú. Dependiendo de la opción el programa llama a las funciones necesarias para poder llevar a cabo el proceso requerido por el usuario.

# SICT0302B - Toma de decisiones

## Usa grafos para hacer análisis de información
* La información se carga al grafo por medio de la función loadGraphList, la cual crea una lista de adyacencia para almacenar los datos.

## Usa un algoritmo de búsqueda en grafos adecuado para resolver un problema
* Por medio de la función BFS, que utiliza también a la función de bfsHelper, se recorre el grafo para buscar la ruta más corta de un punto inicial a uno final, los cuales son indicados por el usuario en el menú.

## Usa un algoritmo de hashing adecuado para resolver un problema
* En el Hash se almacenan los datos como Llave, Valor del estado (como llave) y el costo de la caseta (como valor), de esta manera cuando se hace el recorrido se busca el dato por medio de la llave para poder sumar los costos de cada estado por el que pasa.

# SICT0303B - Implementa acciones científicas

## Implementa mecanismos para consultar información de las estructuras correctos
* Los mecanismos de consulta para las distintas estructuras dentro del proyecto son los siguientes:
* graph.h -> BFS junto con bfsHelper permiten desplegar la ruta más corta de un estado a otro, los cuales son ingresados por el usuario; esta ruta más corta es agregada a un string por medio de la función printPaths.
* hash.h -> get permite conocer el valor por medio de una llave proporcionada por el usuario en el menú; toString permite imprimir el hash para conocer los datos que se encuentran almacenados.

## Implementa mecanismos de lectura de archivos correctos
* Graph.h implementa un mecanismo de lectura de archivos para almacenar la información en el grafo, el archivo de donde se toma la información es puntos.txt; se usa la librería fstream que permite la lectura y escritura de archivos, el mismo algoritmo se encarga de cerrar el archivo cuando la lectura es terminada.

# SICT0301B - Evalúa los componentes

## Presenta Casos de Prueba correctos y completos para todas las funciones y procedimientos del programa
* El main funciona al elegir la opción para la operación deseada; desplegar estados solo los imprime en la consola con el índice indicado, mientras que la opción de buscar la ruta más corta entre dos estados, recibe dos datos, ambos son índices de la salida y la partida. La opción de consultar precios de todas las casetas solo imprime el estado y el costo de la caseta; por último, la opción de consultar precios de casetas en mi ruta muestra la ruta más rápida y los precios de cada caseta, al final muestra el total de casetas para esta ruta.
* En el archivo pruebas.cpp se encuentran casos de prueba completos para utilizar todas las funciones y procedimientos del programa; para utilizarlo hay que copiar el código en el archivo main.cpp y correr el programa, los datos se muestran en la consola.

## Hace un análisis de complejidad correcto y completo para todo el programa y sus componentes
* loadGraphList -> El algoritmo lee un archivo y el tiempo que tarda en completar la lectura depende de la cantidad de líneas en el archivo; por lo tanto la complejidad temporal es de O(n) para el peor de los casos.
* BFS -> El algoritmo recorre los nodos y los bordes de la lista de adyacencia, debido a que debe de recorrer todos en el peor de los casos, la complejidad temporal es de O(n+b). Donde n es la cantidad de nodos y b es la cantidad de bordes.
* loadHash -> El algoritmo obtiene el índice para la llave, pero en caso de alguna colisión se tendrá que buscar otra posición; por lo que la complejidad temporal es de O(n) para el peor de los casos.
* get -> El algoritmo obtiene el índice para la llave, pero en caso de alguna colisión se tendrá que recorrer toda la tabla hasta encontrar el valor; por lo que la complejidad temporal es de O(n) para el peor de los casos.