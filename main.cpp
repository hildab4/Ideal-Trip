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

    Graph puntos; // Se crea el objeto de la clase Graph
    Quadratic <string, int> h1(11, string("empty"), myHash); // Se crea el objeto de la clase Quadratic
    // Vector con los estados disponibles
    vector<string> est {"México", "Querétaro", "San Luis Potosí", "Guanajuato", "Guerrero", "Oaxaca", "Jalisco"}; 
    h1.loadHash(); // LLena el hash con los datos correspondientes
    puntos.loadGraphList("puntos.txt", 7, 7); // Lee el archivo y genera la lista de adyacencia

    // Muestra el menú y va a seguir hasta que el usuario ingrese la opción 5
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
            cout << puntos.despliegaEstados(est) << endl;
        }
        // En esta opción el usuario ingresa el índice de salida y destino correspondiente al estado.
        else if (opc == 2) {
            cout << "Buscar ruta más corta entre dos estados" << endl << "---------------------------" << endl;
            cout << "Salida: ";
            int s; cin >> s; cout << endl;
            cout << "Destino: ";
            int d; cin >> d; cout << endl;
            cout << "La ruta más corta es: " << endl << endl;
            vector<string> estadosPath = puntos.BFS(s, d, est);
            cout << endl;
        }
        else if (opc == 3) {
            cout << "Consultar precios de todas las casetas" << endl << "---------------------------" << endl;
            cout << h1.despliegaPrecios();
        }
        // En esta opción el usuario ingresa el índice de salida y destino correspondiente al estado.
        else if (opc == 4) {
            cout << "Consultar precios de casetas en mi ruta" << endl << "---------------------------" << endl;
            cout << "Salida: ";
            int s; cin >> s; cout << endl;
            cout << "Destino: ";
            int d; cin >> d; cout << endl;
            cout << "La ruta más corta es: " << endl << endl;
            vector<string> estadosPath = puntos.BFS(s, d, est);
            vector<int> preciosPath = h1.precioPath(estadosPath);
            cout << endl;
            int total = 0;
            for (int i = 0; i < estadosPath.size(); i++) {
                cout << estadosPath[i] << ": " << preciosPath[i] << endl;
                total = total + preciosPath[i];
            }
            cout << "\nEl total es de: " << total << endl;

        }
        else if (opc == 5) {
            cout << "Gracias por visitar Great Travel" << endl;
            cout << "-----------------------------" << endl;
            exit(1);
        }
    }
}