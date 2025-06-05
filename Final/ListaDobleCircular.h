#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaDobleCircular {
private:
    Nodo<T>* cabeza;
    int tam;

public:
    ListaDobleCircular();
    ~ListaDobleCircular();

    bool estaVacia();
    int tamanio();

    void insertarInicio(T& dato);
    void insertarFinal(T& dato);

    void eliminarInicio();
    void eliminarFinal();

};


template <typename T>
ListaDobleCircular<T>::ListaDobleCircular() : cabeza(nullptr), tam(0) {}

template <typename T>
ListaDobleCircular<T>::~ListaDobleCircular() {
    while (!estaVacia()) {
        eliminarInicio();
    }
}

template <typename T>
bool ListaDobleCircular<T>::estaVacia() {
    return tam == 0;
}

template <typename T>
int ListaDobleCircular<T>::tamanio() {
    return tam;
}

template <typename T>
void ListaDobleCircular<T>::insertarInicio(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (estaVacia()) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        cabeza = nuevo;
    }
    else {
        Nodo<T>* cola = cabeza->anterior;

        nuevo->siguiente = cabeza;
        nuevo->anterior = cola;

        cabeza->anterior = nuevo;
        cola->siguiente = nuevo;

        cabeza = nuevo;
    }
    ++tam;
}

template <typename T>
void ListaDobleCircular<T>::insertarFinal(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (estaVacia()) {
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
        cabeza = nuevo;
    }
    else {
        Nodo<T>* cola = cabeza->anterior;

        nuevo->siguiente = cabeza;
        nuevo->anterior = cola;

        cola->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
    ++tam;
}

template <typename T>
void ListaDobleCircular<T>::eliminarInicio() {
    if (estaVacia()) return;

    if (tam == 1) {
        delete cabeza;
        cabeza = nullptr;
    }
    else {
        Nodo<T>* cola = cabeza->anterior;
        Nodo<T>* temp = cabeza;

        cabeza = cabeza->siguiente;
        cabeza->anterior = cola;
        cola->siguiente = cabeza;

        delete temp;
    }
    --tam;
}

template <typename T>
void ListaDobleCircular<T>::eliminarFinal() {
    if (estaVacia()) return;

    if (tam == 1) {
        delete cabeza;
        cabeza = nullptr;
    }
    else {
        Nodo<T>* cola = cabeza->anterior;
        Nodo<T>* nuevoCola = cola->anterior;

        nuevoCola->siguiente = cabeza;
        cabeza->anterior = nuevoCola;

        delete cola;
    }
    --tam;
}

#endif
