#include "Institucion.h"
using namespace std;

Institucion::Institucion() {}

Institucion::Institucion(string nombre, string direccion) {
    this->nombre = nombre;
    this->direccion = direccion;
}

void Institucion::setNombre(string nombre) {this->nombre = nombre;}

void Institucion::setDireccion(string direccion) {this->direccion = direccion;}

string Institucion::getNombre() {return nombre;}

string Institucion::getDireccion() {return direccion;}

void Institucion::agregarProfesor(const Profesor& profe) {
    profesores.insertarAlFinal(profe);
}

ListaEnlazada<Profesor>& Institucion::getProfesores() {return profesores;}