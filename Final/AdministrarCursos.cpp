#include "AdministrarCursos.h"
#include <vector>
using namespace std;
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
        cout << "-" << auxCurso.getNombre() << '\n';
        actual = actual->siguiente;
        i++;
    }
}
void AdministrarCurso::ImprimirNombreCursosIndices() {
    Nodo<Curso>* actual = cursos.obtenerCabeza();
    int i = 1;
    while (actual != nullptr) {
        Curso& auxCurso = actual->dato;
        cout << i << ". " << auxCurso.getNombre() << '\n';
        actual = actual->siguiente;
        i++;
    }
}
void AdministrarCurso::verDetallesCursos(int indice) {
    Nodo<Curso>* actual = cursos.obtenerCabeza();
    int i = 1;
    while (actual != nullptr) {
        Curso& auxCurso = actual->dato;
        if (i == indice) {
            cout << "Nombre: " << auxCurso.getNombre() << '\n';
            cout << "Cantidad de lecciones: " << auxCurso.getNumLecciones() << '\n';
            cout << "Categoria: " << auxCurso.getCategoria() << '\n';
            //cout << "Costo del Curso: " << auxCurso.getCosto() << '\n';
            break;
        }
        actual = actual->siguiente;
        i++;
    }
}
Curso AdministrarCurso::InscribirseACurso(int indice) {
    Nodo<Curso>* actual = cursos.obtenerCabeza();
    int i = 1;
    while (actual != nullptr) {
        Curso& auxCurso = actual->dato;
        if (indice == i) {
            return actual->dato;
        }
        actual = actual->siguiente;
        i++;
    }
}
