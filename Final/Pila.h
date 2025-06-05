#ifndef PILA_H
#define PILA_H

#include "Nodo.h"
#include <iostream>

template <typename T>
class Pila {
private:
    Nodo<T>* cima;
    int tam;

public:
    Pila();
    ~Pila();

    bool estaVacia();
    int tamanio();

    void apilar(T& dato);
    void desapilar();

    T& cimaElemento();
};


template <typename T>
Pila<T>::Pila() : cima(nullptr), tam(0) {}

template <typename T>
Pila<T>::~Pila() {
    while (!estaVacia()) {
        desapilar();
    }
}

template <typename T>
bool Pila<T>::estaVacia() {
    return tam == 0;
}

template <typename T>
int Pila<T>::tamanio() {
    return tam;
}

template <typename T>
void Pila<T>::apilar(T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);
    nuevo->siguiente = cima;
    cima = nuevo;
    ++tam;
}

template <typename T>
void Pila<T>::desapilar() {
    if (estaVacia()) return;

    Nodo<T>* temp = cima;
    cima = cima->siguiente;
    delete temp;
    --tam;
}

template <typename T>
T& Pila<T>::cimaElemento() {
    return cima->dato;
}

#endif
