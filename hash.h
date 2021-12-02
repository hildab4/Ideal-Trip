/*
 * Great Travel
 * 
 * Hilda Beltrán Acosta
 * A01251916
 *
 * hash.h
*/
#ifndef HASH_H
#define HASH_H

//Se incluyen las librerías necesarias
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
 * Dentro de esta clase Quadratic se definen los atributos privados del objeto, 
 * así como funciones necesarias para los métodos públicos. Los métodos incluyen 
 * loadHash que es la función encargada de cargar los datos al hash ingresados 
 * manualmente en el programa. El método despliegaPrecios muestra la lista de estados 
 * disponibles junto con el precio de la caseta. El método put regresa un valor 
 * booleano para definir si se agregó correctamente. Mientras que get regresa el valor 
 * por medio de una llave.
*/
template <class Key, class Value>
class Quadratic {
    private:
		unsigned int (*func) (const Key);
		unsigned int size;
		unsigned int count;
		Key *keys;
		Key initialValue;
		Value *values;
		long indexOf(const Key) const;
		vector<int> precios;

    public: 
		// Constructor
        Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
		~Quadratic();
		string despliegaPrecios() const; 
        bool put(Key, Value);
		Value get(const Key);
        void loadHash();
		vector<int> precioPath(vector<string> &est);
};

/*
 * La función llama al método put para insertar datos al hash, estos con
 * llave y valor.
 * 
 * @param 
 * @return 
*/ 
template <class Key, class Value>
void Quadratic<Key, Value>::loadHash() {
    put(string("México"), 100);
	put(string("Querétaro"), 150);
	put(string("San Luis Potosí"), 96);
	put(string("Guanajuato"), 75);
	put(string("Guerrero"), 145);
	put(string("Oaxaca"), 153);
	put(string("Jalisco"), 169);
}

// Constructor
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int s, Key init, unsigned int (*f) (const Key)) {
	size = s;
	keys = new Key[size];
	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	values = new Value[size];
	for (int i = 0; i < s; i++) {
		values[i] = 0;
	}
	func = f;
	count = 0;
}

// Destructor
template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete [] keys;
	keys = 0;
	delete [] values;
	values = 0;
	size = 0;
	func = 0;
	count = 0;
}

/*
 * La función indexOf regresa el índice en el que se encontrará
 * el dato ingresado por medio de la llave.
 * 
 * @param const Key
 * @return long
*/ 
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;
	start = i = func(k) % size;
	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + 1) % size;
	}
	while (start != i);
	return -1;
} 

/*
 * La función llama al método indexOf para calcular la posición en la 
 * que se va a insertar los datos, llave y valor.
 * 
 * @param Key, Value
 * @return bool
*/ 
template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i, start;
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return true;
	}
	start = i = func(k) % size;
	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			return true;
		}
		count++;
		i = (i + (count*count)) % size;
	}
	while (start != i);
	return false;
}

/*
 * La función busca el valor por medio de la llave ingresada por el usuario.
 * Para esto recurre a la función indexOf para encontrar la posición.
 * 
 * @param const Key
 * @return Value
*/ 
template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
	unsigned int i, start;
	long pos;
	pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
	return -1;
}

/*
 * La función recorre el hash por medio de un ciclo for e imprime
 * en la consola el estado con el precio de la caseta correspondiente.
 * 
 * @param 
 * @return 
*/ 
template <class Key, class Value>
string Quadratic<Key, Value>::despliegaPrecios() const {
	stringstream aux;
	for (int i = 0; i < size; i++){
		if (keys[i] != initialValue){
		  aux << keys[i] << ": " << values[i] << "\n";
		}
	}
	return aux.str();
}

/*
 * Dentro del ciclo for se recorre el vector de los estados en el 
 * camino, el cual se va recorriendo y se llama a la función get con
 * cada elemento del vector. De esta manera se busca el valor por medio
 * de la llave, y este valor se ingresa al vector que regresa la función.
 * 
 * @param vector<string>&
 * @return vector<int> 
*/ 
template <class Key, class Value>
vector<int> Quadratic<Key, Value>::precioPath(vector<string> &est) {
	for (int i = 0; i < est.size(); i++) {
		int p = get(est[i]);
		precios.push_back(p);
	}
	return precios;
}

#endif