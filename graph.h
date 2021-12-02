/*
 * Great Travel
 * 
 * Hilda Beltrán Acosta
 * A01251916
 *
 * graph.h
*/

#ifndef GRAPH_H
#define GRAPH_H

//Se incluyen las librerías necesarias
#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

/*
 * Dentro de esta clase Graph se definen los atributos privados del objeto, 
 * así como funciones necesarias para los métodos públicos. Los métodos incluyen 
 * loadGraphList que es la función encargada de cargar los datos al grafo desde el
 * archivo csv. El método despliegaEstados muestra la lista de estados disponibles
 * junto con su índice. Mientras que BFS muestra la ruta más corta de un estado a otro.
*/
class Graph {
    private:
        int edgesList;
        int edgesMat;
        int nodes;
        vector<int> *adjList;
        int *adjMatrix;
        void addEdgeAdjList(int u, int v);
        void sortAdjList();
        // Lo manda a llamar el método de BFS
        void bfsHelper(int inicial, int meta, queue<int> &q, list<int> &visited, vector<vector<int>> &paths);
        // Lo manda a llamar el método de BFS
        vector<string> printPaths(vector<vector<int>> &paths, int inicial, int meta, vector<string> &est);
        // Lo manda a llamar el método de BFS
        string printVisited(list<int> visited);
        // Lo manda a llamar el método de BFS
        bool contains(list<int> visited, int data);

    public:
        // Constructor por default
        Graph();
        // Sobrecarga del constructor por default
        Graph(int n);
        void loadGraphList(string file, int n, int m);
        vector<string> BFS(int inicial, int meta, vector<string> &est);
        string despliegaEstados(const vector<string> &est);
};

// Constructor por default
Graph::Graph() {
    edgesList = edgesMat = 0;
}

// Sobrecarga del constructor por default
Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int> [nodes];
    adjMatrix = new int [nodes*nodes];
    for (int i = 0; i < nodes*nodes; i++) {
        adjMatrix[i] = 0;
    }
    edgesList = edgesMat = 0;
}

/*
 * La función addEdgeAdjList carga las conexiones a la lista de adyacencia,
 * es decir la relación entre los datos que recibe (u, v).
 * 
 * @param int, int
 * @return 
*/ 
void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

/*
 * La función loadGraphList lee un archivo csv para interpretar las conexiones
 * y mandarlos a la función addEdgeAdjList.
 * 
 * @param string, int, int
 * @return 
*/ 
void Graph::loadGraphList(string file, int n, int m) {
    adjList = new vector<int> [n];
    nodes = n;

    string line;
    ifstream lee(file);
    int u, v;
    if (lee.is_open()) {
        while (getline(lee, line)) {
            u = stoi(line.substr(1,1));
            v = stoi(line.substr(4,1));
            addEdgeAdjList(u, v);
        }
        lee.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

/*
 * La función recibe los datos del punto inicial y el punto meta para poder
 * obtener la ruta más corta entre ambos puntos. Regresa un vector de strings
 * con los nombres de los estados por los que tiene que pasar.
 * 
 * @param int, int, vector<string>&
 * @return vector<string>
*/ 
vector<string> Graph::BFS(int inicial, int meta, vector<string> &est) {
    stringstream aux;
    queue<int> q;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(0));
    q.push(inicial);
    bfsHelper(inicial, meta, q, visited, paths);
    vector<string> pathEst = printPaths(paths, inicial, meta, est);
    return pathEst;
}

/*
 * Dentro de esta función se recorre el grafo desde el punto inicial hasta encontrar
 * el punto meta; los estados por los que va pasando se guardan para ser utilizados
 * posteriormente. En este caso solo nos interesa la estructura donde se almacena path,
 * ya que solo queremos mostrar el camino más corto.
 * 
 * @param int, int, queue<int>&, list<int>&, vector<vector<int>>&
 * @return 
*/ 
void Graph::bfsHelper(int inicial, int meta, queue<int> &q, list<int> &visited, vector<vector<int>> &paths) {
    stringstream aux;
    if (inicial == meta) {
        printVisited(visited);
    }
    else if (q.empty()) {
        aux << " node not found";
    }
    else {
        inicial = q.front();
        q.pop();
        visited.push_back(inicial);
        for (int i = 0; i < adjList[inicial].size(); i++) {
            if (!contains(visited, adjList[inicial][i])) {
                q.push(adjList[inicial][i]);
                paths[adjList[inicial][i]].push_back(inicial);
            }
        }
        bfsHelper(inicial, meta, q, visited, paths);
    }
}

/*
 * Toma los estados que pueden ser visitados para llegar al punto meta.
 * (No es la ruta más corta).
 * 
 * @param list<int>
 * @return string
*/ 
string Graph::printVisited(list<int> visited) {
    stringstream aux;
    aux << "visited: ";
    while (!visited.empty()) {
        aux << visited.front() << " ";
        visited.pop_front();
    }
    return aux.str();
}

/*
 * La función contains se encarga de revisar si el punto buscado se
 * encuentra en el grafo. Regresa un valor de verdadero o falso.
 * 
 * @param list<int>, int
 * @return bool
*/ 
bool Graph::contains(list<int> visited, int data) {
    list<int>::iterator it;
    it = find(visited.begin(), visited.end(), data);
    if (it != visited.end()) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * Guarda los estados del camino más corto y los regresa en un vector
 * de strings.
 * 
 * @param vector<vector<int>>&, int, int, vector<string>&
 * @return vector<string>
*/ 
vector<string> Graph::printPaths(vector<vector<int>> &paths, int inicial, int meta, vector<string> &estados) {
    stringstream aux;
    int node = paths[meta][0];
    stack<int> reverse;
    vector<string> pathEstado;
    reverse.push(meta);
    while (node != inicial) {
        reverse.push(node);
        node = paths[node][0];
    }
    reverse.push(inicial);
    while (!reverse.empty()) {
        string estado = estados[reverse.top()];
        cout << estado << endl;
        pathEstado.push_back(estado);
        reverse.pop();
    }
    return pathEstado; 
}

/*
 * Recibe un vector con los nombres de los estados disponibles y los imprime
 * junto con el índice que será utilizado para identificarlos.
 * 
 * @param const vector<string>&
 * @return 
*/ 
string Graph::despliegaEstados(const vector<string> &est) {
    stringstream aux;
    for (int i = 0; i < est.size(); i++) {
        aux << i << ": " << est[i] << "\n";
    }
    return aux.str();
}

#endif