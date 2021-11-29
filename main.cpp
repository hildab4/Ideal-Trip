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
    h1.loadHash();


    /*h1.loadHash();

    cout << h1.toString() << endl;

    cout << h1.get("México") << endl;

    puntos.loadGraphList("puntos.txt", 7, 7);

    cout << puntos.printAdjList() << endl;

    cout << puntos.BFS(0, 4) << endl;*/

    while(true) {
        cout << "------------------------------------------" << endl << "Bienvenido a Great Travel" << endl << endl;
        cout << endl << "Seleccione la opción de la operación que desea llevar a cabo" <<
        endl << endl << "\t 1: Desplegar estados" << endl << "\t 2: Buscar ruta más corta entre dos estados" << endl <<
        "\t 3: Consultar precios de todas las casetas" << endl <<
        "\t 4: Consultar precios de casetas en mi ruta" << endl << "\t 5: Exit" << endl;

        int opc;
        cin >> opc;
        cout << endl;

        if (opc == 1) {
            cout << "Desplegar estados" << endl << "---------------------------" << endl;
            h1.despliegaEstados();
        }
        else if (opc == 2) {
            cout << "Buscar ruta más corta entre dos estados" << endl << "---------------------------" << endl;
            puntos.loadGraphList("puntos.txt", 7, 7);
            cout << "Salida: ";
            int s; cin >> s; cout << endl;
            cout << "Destino: ";
            int d; cin >> d; cout << endl;
            puntos.BFS(s, d);
        }
        else if (opc == 3) {
            cout << "Consultar precios de todas las casetas" << endl << "---------------------------" << endl;
            h1.despliegaPrecios();
        }
        else if (opc == 4) {
            cout << "Consultar precios de casetas en mi ruta" << endl << "---------------------------" << endl;
            //Pendiente
        }
        else if (opc == 5) {
            cout << "Gracias por visitar Great Travel" << endl;
            cout << "-----------------------------" << endl;
            exit(1);
        }
    }

    // El BFS se usa para la ruta más corta
} 