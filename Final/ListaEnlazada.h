#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include <functional>
#include "Nodo.h"

using namespace std;

template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;

public:
    ListaEnlazada();
    ~ListaEnlazada();

    void insertarAlInicio(T& dato);
    void insertarAlFinal(T dato);
    bool estaVacia();
    void eliminarPrimero();
    void limpiar();
    Nodo<T>* obtenerCabeza();

    bool eliminarSi(function<bool(T)> condicion);
    void recorrer(function<void(T)> accion);
};

template <typename T>
ListaEnlazada<T>::ListaEnlazada() : cabeza(nullptr) {}

template <typename T>
ListaEnlazada<T>::~ListaEnlazada() {
    //limpiar();
}

template <typename T>
void ListaEnlazada<T>::insertarAlInicio(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

template <typename T>
void ListaEnlazada<T>::insertarAlFinal(T dato) {
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
    while (cabeza != nullptr) {
        eliminarPrimero();
    }
}

template <typename T>
Nodo<T>* ListaEnlazada<T>::obtenerCabeza() {
    return cabeza;
}

template <typename T>
bool ListaEnlazada<T>::eliminarSi(function<bool(T)> condicion) {
    Nodo<T>* actual = cabeza;
    Nodo<T>* anterior = nullptr;

    while (actual != nullptr) {
        if (condicion(actual->dato)) {
            if (anterior == nullptr) {
                cabeza = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}


template <typename T>
void ListaEnlazada<T>::recorrer(function<void(T)> accion) {
    Nodo<T>* actual = cabeza;
    while (actual != nullptr) {
        accion(actual->dato);
        actual = actual->siguiente;
    }
}

#endif
