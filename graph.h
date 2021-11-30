#ifndef GRAPH_H
#define GRAPH_H

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
 
class Graph {
    private:
        int edgesList;
        int edgesMat;
        int nodes;
        vector<int> *adjList;
        int *adjMatrix;
        void addEdgeAdjList(int u, int v);
        void addEdgeAdjMatrix(int u, int v);
        void sortAdjList();
        void bfsHelper(int inicial, int meta, queue<int> &q, list<int> &visited, vector<vector<int>> &paths);
        vector<string> printPaths(vector<vector<int>> &paths, int inicial, int meta, vector<string> &est);
        string printVisited(list<int> visited);
        bool contains(list<int> visited, int data);

    public:
        Graph();
        Graph(int n);
        void loadGraphList(string file, int n, int m);
        string printAdjList();
        vector<string> BFS(int inicial, int meta, vector<string> &est);
        void despliegaEstados(const vector<string> &est);
};

Graph::Graph() {
    edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int> [nodes];
    adjMatrix = new int [nodes*nodes];
    for (int i = 0; i < nodes*nodes; i++) {
        adjMatrix[i] = 0;
    }
    edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

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

string Graph::printAdjList() {
    stringstream aux;
    sortAdjList();
    for (int i = 0; i < nodes; i++) {
        aux << "vertex " << i << " :";
        for (int j = 0; j < adjList[i].size(); j++) {
            aux << " " << adjList[i][j];
        }
        aux << " ";
    }
    return aux.str();
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i ++) {
        sort(adjList[i].begin(), adjList[i].end());
    }
}

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

string Graph::printVisited(list<int> visited) {
    stringstream aux;
    aux << "visited: ";
    while (!visited.empty()) {
        aux << visited.front() << " ";
        visited.pop_front();
    }
    return aux.str();
}

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

void Graph::despliegaEstados(const vector<string> &est) {
    for (int i = 0; i < est.size(); i++) {
        cout << i << ": " << est[i] << endl;
    }
}

#endif