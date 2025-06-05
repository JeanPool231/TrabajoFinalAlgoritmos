#ifndef LISTACIRCULARSIMPLE_H
#define LISTACIRCULARSIMPLE_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaCircularSimple {
private:
    Nodo<T>* ultimo;
    int tam;

public:
    ListaCircularSimple();
    ~ListaCircularSimple();

    bool estaVacia();
    int tamanio();

    void insertarInicio(T& dato);
    void insertarFinal(T& dato);

    void eliminarInicio();
    void eliminarFinal();

};


template <typename T>
ListaCircularSimple<T>::ListaCircularSimple() : ultimo(nullptr), tam(0) {}

template <typename T>
ListaCircularSimple<T>::~ListaCircularSimple() {
    while (!estaVacia()) {
        eliminarInicio();
    }
}

template <typename T>
bool ListaCircularSimple<T>::estaVacia() {
    return tam == 0;
}

template <typename T>
int ListaCircularSimple<T>::tamanio() {
    return tam;
}

template <typename T>
void ListaCircularSimple<T>::insertarInicio(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (estaVacia()) {
        nuevo->siguiente = nuevo;
        ultimo = nuevo;
    }
    else {
        nuevo->siguiente = ultimo->siguiente;
        ultimo->siguiente = nuevo;
    }
    ++tam;
}

template <typename T>
void ListaCircularSimple<T>::insertarFinal(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (estaVacia()) {
        nuevo->siguiente = nuevo;
        ultimo = nuevo;
    }
    else {
        nuevo->siguiente = ultimo->siguiente;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    ++tam;
}

template <typename T>
void ListaCircularSimple<T>::eliminarInicio() {
    if (estaVacia()) return;

    Nodo<T>* primero = ultimo->siguiente;
    if (ultimo == primero) {
        delete primero;
        ultimo = nullptr;
    }
    else {
        ultimo->siguiente = primero->siguiente;
        delete primero;
    }
    --tam;
}

template <typename T>
void ListaCircularSimple<T>::eliminarFinal() {
    if (estaVacia()) return;

    Nodo<T>* actual = ultimo->siguiente;
    if (actual == ultimo) {
        delete ultimo;
        ultimo = nullptr;
    }
    else {
        while (actual->siguiente != ultimo) {
            actual = actual->siguiente;
        }
        actual->siguiente = ultimo->siguiente;
        delete ultimo;
        ultimo = actual;
    }
    --tam;
}


#endif
