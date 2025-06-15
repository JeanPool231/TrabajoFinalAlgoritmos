#ifndef COLA_H
#define COLA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* fondo;
    int tam;

public:
    Cola();
    ~Cola();

    bool estaVacia();
    int tamanio();

    void encolar(T& dato);
    void desencolar();

    T& frenteElemento();
};


template <typename T>
Cola<T>::Cola() : frente(nullptr), fondo(nullptr), tam(0) {}

template <typename T>
Cola<T>::~Cola() {
    //while (!estaVacia()) {
        //desencolar();
    //}
}

template <typename T>
bool Cola<T>::estaVacia() {
    return tam == 0;
}

template <typename T>
int Cola<T>::tamanio() {
    return tam;
}

template <typename T>
void Cola<T>::encolar(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    if (estaVacia()) {
        frente = fondo = nuevo;
    }
    else {
        fondo->siguiente = nuevo;
        fondo = nuevo;
    }
    ++tam;
}

template <typename T>
void Cola<T>::desencolar() {
    if (estaVacia()) return;

    Nodo<T>* temp = frente;
    frente = frente->siguiente;
    delete temp;

    if (frente == nullptr) fondo = nullptr;
    --tam;
}

template <typename T>
T& Cola<T>::frenteElemento() {
    return frente->dato;
}

#endif
