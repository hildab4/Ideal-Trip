#include <iostream>
#include <cstring>
#include "graph.h"
#include "hash.h"

using namespace std;

unsigned int myHash(const string s) {
	unsigned int acum = 0;
	for (unsigned int i = 0; i < s.size(); i++) {
		acum += (int) s[i];
	}
	return acum;
}

int main(int argc, char* argv[]) {

    Graph puntos;
    Quadratic <string, int> h1(11, string("empty"), myHash);
    vector<string> est {"México", "Querétaro", "San Luis Potosí", "Guanajuato", "Guerrero", "Oaxaca", "Jalisco"}; 
    h1.loadHash();

    puntos.loadGraphList("puntos.txt", 7, 7);

    cout << "Desplegar estados" << endl << "---------------------------" << endl;
    puntos.despliegaEstados(est);

    cout << endl << "Buscar ruta más corta entre dos estados" << endl << "---------------------------" << endl;
    cout << "México a Oaxaca" << endl;
    cout << "La ruta más corta es: " << endl << endl;
    vector<string> estadosPath = puntos.BFS(0, 5, est);
    cout << endl;

    cout << endl << "Consultar precios de todas las casetas" << endl << "---------------------------" << endl;
    h1.despliegaPrecios();

    cout << endl << "Consultar precios de casetas en mi ruta" << endl << "---------------------------" << endl;
    cout << "México a Oaxaca" << endl << endl;
    cout << "La ruta más corta es: " << endl << endl;
    vector<string> estadosPath1 = puntos.BFS(0, 3, est);
    vector<int> preciosPath = h1.precioPath(estadosPath1);
    cout << endl;
    int total = 0;
    for (int i = 0; i < estadosPath1.size(); i++) {
        cout << estadosPath1[i] << ": " << preciosPath[i] << endl;
        total = total + preciosPath[i];
        }
    cout << "\nEl total es de: " << total << endl;

    cout << endl << "Gracias por visitar Great Travel" << endl;
    cout << "-----------------------------" << endl;
}