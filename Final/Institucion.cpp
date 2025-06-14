#include "Institucion.h"
#include <iostream>

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

void Institucion::verinformacion() {
    cout << "Nombre: " << nombre << "\n";
    cout << "Descripcion: " << descripcion << "\n";
    cout << "Se registro en: " << yearderegistro << "\n";
}

void Institucion::verprofesores() {
    cout << "\nProfesores Afiliados:\n";
    profesores.recorrerInOrden([](Profesor& p) {
        cout << "- " << p.getNombre() << " " << p.getApellido()
            << " | Codigo: " << p.getCodigo()
            << " | Correo: " << p.getCorreo()
            << " | Sexo: " << p.getSexo()
            << " | Estado civil: " << p.getEstadoCivil()
            << " | Edad: " << p.getEdad()
            << " | Tiempo en Coursera: " << p.getTiempoEnCoursera()
            << " edad | ID: " << p.getId()
            << " | Reputacion: " << p.getReputacion() << "\n";
        });
}


void Institucion::vercursos() {
    cout << "\nCursos Publicados:\n";
    int i = 1;
    for (auto curso : cursos) {
        cout << i++ << ". " << curso->getNombre()
            << " | ID: " << curso->getId()
            << " | Categoria: " << curso->getCategoria()
            << " | Duracion: " << curso->getduracionentexto()
            << " | Fecha: " << curso->getFechaCreacion() << "\n"
            << "   Descripcion: " << curso->getDescripcion() << "\n";
    }
}



void Institucion::verestadisticas() {
    cout << "\nEstadisticas del usuario\n";
    cout << "Cantidad de cursos: " << cursos.size() << "\n";

    int total = 0;
    for (auto c : cursos) {
        total += c->getCantidadInscritos();
    }
    cout << "Total de inscritos: " << total << "\n";

    cout << "\n";
}
