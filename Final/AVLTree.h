#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "NodoAVL.h"
#include <algorithm>
#include <functional>

template <typename T>
class AVLTree {
private:
    NodoAVL<T>* raiz;

    int altura(NodoAVL<T>* nodo) {
        return nodo ? nodo->altura : 0;
    }

    int obtenerBalance(NodoAVL<T>* nodo) {
        return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
    }

    void actualizarAltura(NodoAVL<T>* nodo) {
        nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
    }

    NodoAVL<T>* rotarDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->izquierda;
        NodoAVL<T>* T2 = x->derecha;
        x->derecha = y;
        y->izquierda = T2;
        actualizarAltura(y);
        actualizarAltura(x);
        return x;
    }

    NodoAVL<T>* rotarIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->derecha;
        NodoAVL<T>* T2 = y->izquierda;
        y->izquierda = x;
        x->derecha = T2;
        actualizarAltura(x);
        actualizarAltura(y);
        return y;
    }

    NodoAVL<T>* insertarNodo(NodoAVL<T>* nodo, T dato, std::function<bool(const T&, const T&)> cmp) {
        if (!nodo) return new NodoAVL<T>(dato);

        if (cmp(dato, nodo->dato))
            nodo->izquierda = insertarNodo(nodo->izquierda, dato, cmp);
        else
            nodo->derecha = insertarNodo(nodo->derecha, dato, cmp);

        actualizarAltura(nodo);

        int balance = obtenerBalance(nodo);

        if (balance > 1 && cmp(dato, nodo->izquierda->dato)) return rotarDerecha(nodo);
        if (balance < -1 && !cmp(dato, nodo->derecha->dato)) return rotarIzquierda(nodo);
        if (balance > 1 && !cmp(dato, nodo->izquierda->dato)) {
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && cmp(dato, nodo->derecha->dato)) {
            nodo->derecha = rotarDerecha(nodo->derecha);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    void inOrden(NodoAVL<T>* nodo, std::function<void(const T&)> f) {
        if (nodo) {
            inOrden(nodo->izquierda, f);
            f(nodo->dato);
            inOrden(nodo->derecha, f);
        }
    }

public:
    AVLTree() : raiz(nullptr) {}

    void insertar(T dato, std::function<bool(const T&, const T&)> cmp) {
        raiz = insertarNodo(raiz, dato, cmp);
    }

    void recorrerInOrden(std::function<void(const T&)> f) {
        inOrden(raiz, f);
    }
};

#endif