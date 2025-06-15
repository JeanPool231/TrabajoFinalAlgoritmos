#pragma once

template <typename T>
class NodoBinario {
public:
    T dato;
    NodoBinario<T>* izquierda;
    NodoBinario<T>* derecha;

    NodoBinario(const T& d) : dato(d), izquierda(nullptr), derecha(nullptr) {}
};



template <typename T>
class ArbolBinario {
private:
    NodoBinario<T>* raiz;

    void insertar(NodoBinario<T>*& nodo, const T& dato);
    void inOrden(NodoBinario<T>* nodo, void (*mostrar)(const T&));
    NodoBinario<T>* buscar(NodoBinario<T>* nodo, const T& dato);

public:
    ArbolBinario();
    void insertar(const T& dato);
    void recorrerInOrden(void (*mostrar)(const T&));
    T* buscar(const T& dato);
};



template <typename T>
ArbolBinario<T>::ArbolBinario() {
    raiz = nullptr;
}

template <typename T>
void ArbolBinario<T>::insertar(NodoBinario<T>*& nodo, const T& dato) {
    if (nodo == nullptr) {
        nodo = new NodoBinario<T>(dato);
    }
    else if (dato < nodo->dato) {
        insertar(nodo->izquierda, dato);
    }
    else {
        insertar(nodo->derecha, dato);
    }
}

template <typename T>
void ArbolBinario<T>::insertar(const T& dato) {
    insertar(raiz, dato);
}

template <typename T>
void ArbolBinario<T>::inOrden(NodoBinario<T>* nodo, void (*mostrar)(const T&)) {
    if (nodo == nullptr) return;
    inOrden(nodo->izquierda, mostrar);
    mostrar(nodo->dato);
    inOrden(nodo->derecha, mostrar);
}

template <typename T>
void ArbolBinario<T>::recorrerInOrden(void (*mostrar)(const T&)) {
    inOrden(raiz, mostrar);
}

template <typename T>
NodoBinario<T>* ArbolBinario<T>::buscar(NodoBinario<T>* nodo, const T& dato) {
    if (nodo == nullptr) return nullptr;
    if (dato == nodo->dato) return nodo;
    if (dato < nodo->dato) return buscar(nodo->izquierda, dato);
    return buscar(nodo->derecha, dato);
}

template <typename T>
T* ArbolBinario<T>::buscar(const T& dato) {
    NodoBinario<T>* nodo = buscar(raiz, dato);
    return nodo ? &nodo->dato : nullptr;
}