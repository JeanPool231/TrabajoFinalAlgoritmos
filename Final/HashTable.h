#include <iostream>
#include <vector>

using namespace std;


template <class K, class V>
class TablaHash {
private:
    class Nodo {
    public:
        K clave;
        V valor;
        Nodo* siguiente;
        Nodo(K k, V v) {
            clave = k;
            valor = v;
            siguiente = 0;
        }
    };

    vector< Nodo* > cubetas;
    int numCubetas;
    int tamanoActual;

    int obtenerIndiceCubeta(K clave) {
        size_t hashValue = hash<K>()(clave);
        return (int)(hashValue % numCubetas);
    }

public:
    TablaHash(int cantidadCubetas = 10) {
        numCubetas = cantidadCubetas;
        cubetas = vector< Nodo* >(numCubetas);
        for (int i = 0; i < numCubetas; i = i + 1) cubetas[i] = 0;
        tamanoActual = 0;
    }

    ~TablaHash() {
        for (int i = 0; i < numCubetas; i = i + 1) {
            Nodo* actual = cubetas[i];
            while (actual != 0) {
                Nodo* sig = actual->siguiente;
                delete actual;
                actual = sig;
            }
        }
    }

    void insertar(K clave, V valor) {
        int idx = obtenerIndiceCubeta(clave);
        Nodo* actual = cubetas[idx];
        while (actual != 0) {
            if (actual->clave == clave) {
                actual->valor = valor;
                return;
            }
            actual = actual->siguiente;
        }
        Nodo* nuevo = new Nodo(clave, valor);
        nuevo->siguiente = cubetas[idx];
        cubetas[idx] = nuevo;
        tamanoActual = tamanoActual + 1;
    }

    void eliminar(K clave) {
        int idx = obtenerIndiceCubeta(clave);
        Nodo* actual = cubetas[idx];
        Nodo* ant = 0;
        while (actual != 0) {
            if (actual->clave == clave) {
                if (ant == 0) cubetas[idx] = actual->siguiente;
                else ant->siguiente = actual->siguiente;
                delete actual;
                tamanoActual = tamanoActual - 1;
                return;
            }
            ant = actual;
            actual = actual->siguiente;
        }
    }

    bool contiene(K clave) {
        int idx = obtenerIndiceCubeta(clave);
        Nodo* actual = cubetas[idx];
        while (actual != 0) {
            if (actual->clave == clave) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    V obtener(K clave) {
        int idx = obtenerIndiceCubeta(clave);
        Nodo* actual = cubetas[idx];
        while (actual != 0) {
            if (actual->clave == clave) return actual->valor;
            actual = actual->siguiente;
        }
        return V();
    }

    int tamano() {
        return tamanoActual;
    }
};