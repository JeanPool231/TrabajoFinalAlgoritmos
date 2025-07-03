#include "Institucion.h"
#include <iostream>
using namespace std;

Institucion::Institucion() : nombre(""), descripcion(""), yearderegistro(0) {}

Institucion::Institucion(const string& nombre, const string& descripcion, int year)
    : nombre(nombre), descripcion(descripcion), yearderegistro(year) {}

void Institucion::setNombre(const string& nom) { nombre = nom; }
void Institucion::setDescripcion(const string& desc) { descripcion = desc; }
void Institucion::setYearDeRegistro(int y) { yearderegistro = y; }

const string& Institucion::getNombre() const { return nombre; }
const string& Institucion::getDescripcion() const { return descripcion; }
int Institucion::getYearDeRegistro() const { return yearderegistro; }

ListaEnlazada<Curso*>& Institucion::getcursos() { return cursos; }
AVLTree<Profesor>& Institucion::getprofesores() { return profesores; }
ListaEnlazada<string>& Institucion::getlogsdeprofes() { return logsdeprofes; }

void Institucion::mostrarInformacion() {
    cout << "\nInfo insti\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Se registro en coursera en : " << yearderegistro << endl;

    cout << "\nCursos\n";
    if (cursos.estaVacia()) {
        cout << "No hay\n";
    }
    else {
        int i = 1;
        cursos.recorrer([&](Curso* curso) {
            cout << i++ << ". " << curso->getNombre() << " | "
                << "Categoría: " << curso->getCategoria() << " | "
                << "Fecha: " << curso->getFechaCreacion() << "\n";
            });
    }

    cout << "\nProfes\n";
    if (profesores.estaVacio()) {
        cout << "No hay\n";
    }
    else {
        profesores.recorrerInOrden([](Profesor& p) {
            cout << "\nCodigo: " << p.getCodigo()
                << "\nNombre: " << p.getNombre() << " " << p.getApellido()
                << "\nCorreo: " << p.getCorreo();

            const auto& cursos = p.getCursosAsignados();
            if (cursos.empty()) {
                cout << "\nCurso Asignado: No asignado";
            }
            else {
                cout << "\nCursos Asignados: ";
                for (const string& curso : cursos) {
                    cout << curso << "; ";
                }
            }

            cout << endl;
            });
    }
}

void Institucion::mostrarEstadisticas() {
    int contador = 0;
    cursos.recorrer([&](Curso* c) { contador++; });
    cout << "\nEstadisticas\n";
    cout << "Cantidad total de cursos: " << contador << "\n";
}