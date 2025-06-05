#ifndef LISTADOBLEENLAZADA_H
#define LISTADOBLEENLAZADA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class ListaDobleEnlazada {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tam;

public:
    ListaDobleEnlazada();
    ~ListaDobleEnlazada();

    bool estaVacia();
    int tamanio();

    void insertarInicio(T& dato);
    void insertarFinal(T& dato);

    void eliminarInicio();
    void eliminarFinal();

};


template <typename T>
ListaDobleEnlazada<T>::ListaDobleEnlazada() : cabeza(nullptr), cola(nullptr), tam(0) {}

template <typename T>
ListaDobleEnlazada<T>::~ListaDobleEnlazada() {
    while (!estaVacia()) {
        eliminarInicio();
    }
}

template <typename T>
bool ListaDobleEnlazada<T>::estaVacia() {
    return tam == 0;
}

template <typename T>
int ListaDobleEnlazada<T>::tamanio() {
    return tam;
}

template <typename T>
void ListaDobleEnlazada<T>::insertarInicio(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (estaVacia()) {
        cabeza = cola = nuevo;
    }
    else {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }
    ++tam;
}

template <typename T>
void ListaDobleEnlazada<T>::insertarFinal(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (estaVacia()) {
        cabeza = cola = nuevo;
    }
    else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
    ++tam;
}

template <typename T>
void ListaDobleEnlazada<T>::eliminarInicio() {
    if (estaVacia()) return;
    Nodo<T>* temp = cabeza;
    if (cabeza == cola) {
        cabeza = cola = nullptr;
    }
    else {
        cabeza = cabeza->siguiente;
        cabeza->anterior = nullptr;
    }
    delete temp;
    --tam;
}

template <typename T>
void ListaDobleEnlazada<T>::eliminarFinal() {
    if (estaVacia()) return;
    Nodo<T>* temp = cola;
    if (cabeza == cola) {
        cabeza = cola = nullptr;
    }
    else {
        cola = cola->anterior;
        cola->siguiente = nullptr;
    }
    delete temp;
    --tam;
}

#endif
