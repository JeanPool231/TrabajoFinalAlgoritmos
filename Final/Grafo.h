#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Grafo {
public:
    class Nodo {
    public:
        T dato;
        vector< Arco* > arcos;

        Nodo(T valor) {
            dato = valor;
        }
    };

    class Arco {
    public:
        Nodo* origen;
        Nodo* destino;

        Arco(Nodo* o, Nodo* d) {
            origen = o;
            destino = d;
        }
    };

    vector< Nodo* > nodos;

    Grafo() {
    }

    ~Grafo() {
    }

    Nodo* agregarNodo(T valor) {
        Nodo* n = new Nodo(valor);
        nodos.push_back(n);
        return n;
    }

    void agregarArco(Nodo* origen, Nodo* destino) {
        Arco* a = new Arco(origen, destino);
        origen->arcos.push_back(a);
    }

    void imprimir() {
        for (int i = 0; i < nodos.size(); i = i + 1) {
            Nodo* n = nodos[i];
            cout << "Nodo " << n->dato << ":\n";
            for (int j = 0; j < n->arcos.size(); j = j + 1) {
                Arco* a = n->arcos[j];
                cout << "  -> (destino: " << a->destino->dato << '\n';
            }
        }
    }
};
