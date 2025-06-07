#pragma once
#ifndef NODOAVL_H
#define NODOAVL_H

template <typename T>
struct NodoAVL {
    T dato;
    NodoAVL<T>* izquierda;
    NodoAVL<T>* derecha;
    int altura;

    NodoAVL(T valor) : dato(valor), izquierda(nullptr), derecha(nullptr), altura(1) {}
};

#endif