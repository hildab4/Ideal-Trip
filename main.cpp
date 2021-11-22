#include <iostream>
#include <cstring>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {

    Graph puntos;

    puntos.loadGraphList("puntos.txt", 5, 5);

    puntos.loadGraphMat("puntos.txt", 5, 5);

    cout << puntos.printAdjList() << endl;

    cout << puntos.DFS(0, 3) << endl;

    cout << puntos.BFS(4, 3) << endl;
}