#include "AdministrarCursos.h"

AdministrarCurso::AdministrarCurso() {}

AdministrarCurso::AdministrarCurso(ListaEnlazada<Curso> cursos) {
    this->cursos = cursos;
}

AdministrarCurso::~AdministrarCurso() {}

void AdministrarCurso::ImprimirNombreCursos() {
    Nodo<Curso>* actual = cursos.obtenerCabeza();
    int i = 1;
    while (actual != nullptr) {
        Curso& auxCurso = actual->dato;
        cout << i << ". " << auxCurso.getNombre() << '\n';
        actual = actual->siguiente;
        i++;
    }
}

