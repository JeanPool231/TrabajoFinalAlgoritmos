#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include "Nodo.h"

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    void insertarAlInicio(T& dato);
    void insertarAlFinal(T& dato);
    bool estaVacia();
    void eliminarPrimero();
    void limpiar();
    Nodo<T>* obtenerCabeza();
};


template <typename T>
ListaEnlazada<T>::ListaEnlazada() : cabeza(nullptr) {}

template <typename T>
ListaEnlazada<T>::~ListaEnlazada() {
    limpiar();
}

template <typename T>
void ListaEnlazada<T>::insertarAlInicio(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void ListaEnlazada<T>::insertarAlFinal(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (!cabeza) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}


template <typename T>
bool ListaEnlazada<T>::estaVacia() {
    return cabeza == nullptr;
}

template <typename T>
void ListaEnlazada<T>::eliminarPrimero() {
    if (cabeza) {
        Nodo<T>* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

template <typename T>
void ListaEnlazada<T>::limpiar() {
    while (!estaVacia()) {
        eliminarPrimero();
    }
}
template <typename T>
Nodo<T>* ListaEnlazada<T>::obtenerCabeza() {
    return cabeza;
}
#endif
