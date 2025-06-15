#ifndef NODO_H
#define NODO_H

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;
    Nodo(const T& d) : dato(d), siguiente(nullptr), anterior(nullptr){}
};

#endif
