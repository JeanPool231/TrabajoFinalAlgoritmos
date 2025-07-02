#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <functional>
using namespace std;

template <typename T>
class NodoLista {
public:
    T dato;
    NodoLista* sig;
    NodoLista(T val) : dato(val), sig(nullptr) {}
};

template <typename T>
class TEMPListaEnlazada {
private:
    NodoLista<T>* cabeza;

public:
    TEMPListaEnlazada() : cabeza(nullptr) {}

    void insertarAlFinal(T val) {
        NodoLista<T>* nuevo = new NodoLista<T>(val);
        if (!cabeza) {
            cabeza = nuevo;
        }
        else {
            NodoLista<T>* temp = cabeza;
            while (temp->sig) temp = temp->sig;
            temp->sig = nuevo;
        }
    }

    void recorrer(function<void(T)> procesar) const {
        NodoLista<T>* temp = cabeza;
        while (temp) {
            procesar(temp->dato);
            temp = temp->sig;
        }
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

#endif