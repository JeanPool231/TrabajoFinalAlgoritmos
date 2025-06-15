#include "AdministrarProfesores.h"
#include <iostream>
using namespace std;

AdministrarProfesores::AdministrarProfesores() {}

void AdministrarProfesores::agregarProfesor(const Profesor& profe) {
    profesores.insertarAlFinal(profe);
}

void AdministrarProfesores::listarProfesores() {
    Nodo<Profesor>* actual = profesores.obtenerCabeza();
    while (actual != nullptr) {
        Profesor& p = actual->dato;
        cout << "Codigo: " << p.getCodigo() << ", Nombre: " << p.getNombre() << " " << p.getApellido() << endl;
        actual = actual->siguiente;
    }
}

Profesor* AdministrarProfesores::buscarPorCodigo(const std::string& codigo) {
    Nodo<Profesor>* actual = profesores.obtenerCabeza();
    while (actual != nullptr) {
        if (actual->dato.getCodigo() == codigo) {
            return &(actual->dato);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}