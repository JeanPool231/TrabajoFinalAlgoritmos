#include "Institucion.h"
#include "AdministrarInstituciones.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <regex>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <sstream>
namespace fs = std::filesystem;

Institucion::Institucion(string nombre, string descripcion, int yearderegistro)
    : nombre(nombre), descripcion(descripcion), yearderegistro(yearderegistro) {}

string Institucion::getnombre() { return nombre; }
string Institucion::getdescripcion() { return descripcion; }
int Institucion::getyear() { return yearderegistro; }

void Institucion::agregarcurso(Curso* curso) {
    cursos.push_back(curso);
}

void Institucion::agregarprofesor(Profesor prof) {
    profesores.insertar(prof, [](Profesor& a, Profesor& b) {
        return a.getId() < b.getId();
        });
}

void Institucion::quitarprofesor(int id) {
    cout << "\n";
}

void Institucion::guardarprofenearchivo(Profesor prof) {
    guardarprofenelarchivo(prof);
}

void Institucion::verinformacion() {
    cout << "\nInformacion de la institucion\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Se registro en: " << yearderegistro << endl;

    //lista de los cursos
    cout << "\nCursos \n";
    if (cursos.empty()) {
        cout << "no se encontraron cursos registrados\n";
    }
    else {
        vector<Curso*> ordenados = cursos;
        sort(ordenados.begin(), ordenados.end(), [](Curso* a, Curso* b) {
            return a->getNombre() < b->getNombre();
            });

        int i = 1;
        for (auto curso : ordenados) {
            cout << i++ << ". " << curso->getNombre()
                << " | Categoria: " << curso->getCategoria()
                << " | Fecha: " << curso->getFechaCreacion()
                << " | Descripcion: " << curso->getDescripcion() << endl;
        }
    }

    // lista de profes
    cout << "\nProfesores\n";
    if (profesores.estaVacio()) {
        cout << "no hay ningun profesor registrado\n";
    }
    else {
        profesores.recorrerInOrden([](Profesor& p) {
            cout << "\n- Codigo: " << p.getCodigo()
                << "\n  Nombre: " << p.getNombre() << " " << p.getApellido()
                << "\n  Correo: " << p.getCorreo()
                << "\n  Años en coursera: " << p.getTiempoEnCoursera()
                << "\n  ID: " << p.getId()
                << "\n  Reputacion: " << p.getReputacion()
                << "\n  Curso asignado: "
                << (p.getCursoAsignado().empty() ? "no asignado" : p.getCursoAsignado())
                << endl;
            });
    }
}


void Institucion::menugestiondeprofes() {
    int subop;
    do {
        cout << "\nGestion de profesores\n";
        cout << "1. Agregar profesor\n";
        cout << "2. Quitar profesor\n";
        cout << "3. Asignar un curso a un profesor existente\n";
        cout << "4. Desvincular al profesor de su curso\n";
        cout << "5. Logs de cambios\n";
        cout << "6. Volver\n";
        cout << "Ingrese una opcion ";
        cin >> subop;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (subop) {
        case 1: agregarprofe(); break;
        case 2: quitarprofes(); break;
        case 3: asignarcursosalprofe(); break;
        case 4: desvincularprofes(); break;
        case 5: verhistorial(); break; //lista
        case 6: break;
        default: cout << "opcion no valida\n"; break;
        }
    } while (subop != 6);
}

void Institucion::verhistorial() {
    mostrarhistorial2(logs);
}


void Institucion::agregarprofe() {
    agregarprofesor2(*this);
}


void Institucion::quitarprofes() {
    quitarprofesor2(*this);
}

void Institucion::asignarcursosalprofe() {
    asignarcursoalprofe2(*this);
}

void Institucion::desvincularprofes() {
    desvincularcursoalprofe2(*this);
}

void Institucion::vercursos() {
    if (cursos.empty()) {
        cout << "\nNo hay ningun curso\n";
        return;
    }

    vector<Curso*> ordenados = cursos;
    sort(ordenados.begin(), ordenados.end(), [](Curso* a, Curso* b) {
        return a->getNombre() < b->getNombre();
        });

    cout << "\nCursos publicados :\n";
    int i = 1;
    for (auto curso : ordenados) {
        string profesorAsignado = "no hay profesor asignado a este curso ";

        profesores.recorrerInOrden([&](Profesor& p) {
            if (p.getCursoAsignado() == curso->getNombre()) {
                profesorAsignado = p.getNombre() + " " + p.getApellido();
            }
            });

        cout << i++ << ". " << curso->getNombre() << " | "
            << curso->getCategoria() << " | "
            << curso->getDescripcion() << "\n    "
            << "Duracion: " << curso->getDuracionHoras() << " horas"
            << " | Fecha: " << curso->getFechaCreacion() << "\n    "
            << "Profesor: " << profesorAsignado << "\n";
    }
}

void Institucion::verestadisticas() {
    cout << "\nEstadisticas\n";
    cout << "Cantidad total de cursos: " << cursos.size() << "\n";
}
