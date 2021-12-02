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

    // Prueba función 1
    string esperada = "0: México\n1: Querétaro\n2: San Luis Potosí\n3: Guanajuato\n4: Guerrero\n5: Oaxaca\n6: Jalisco";
    cout << "Desplegar estados" << endl << "---------------------------" << endl;
    cout << "\n" <<"1.- esperada " << esperada << "\n 1.- programa " << puntos.despliegaEstados(est) << "\n";
	cout <<	(!esperada.compare(puntos.despliegaEstados(est)) ? "success\n" : "fail\n");

    // Prueba función 2
    vector<string> esperada2 {"México", "Guerrero", "Oaxaca"};
    cout << endl << "Buscar ruta más corta entre dos estados" << endl << "---------------------------" << endl;
    cout << "México a Oaxaca" << endl;
    cout << "La ruta más corta es: " << endl << endl;
    vector<string> estadosPath = puntos.BFS(0, 5, est);
    cout << "\n" <<"2.- esperada " << esperada2[0] << endl << esperada2[1] << endl << esperada2[2] << endl << 
    "\n 2.- programa " << estadosPath[0] << endl << estadosPath[1] << endl << estadosPath[2] << "\n";
	if (esperada2 == estadosPath) { 
        cout << "success\n";
    } 
    else{ cout << "fail\n";}
    cout << endl;

    // Prueba función 3
    cout << endl << "Consultar precios de todas las casetas" << endl << "---------------------------" << endl;
    cout << h1.despliegaPrecios();

    // Prueba función 4
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