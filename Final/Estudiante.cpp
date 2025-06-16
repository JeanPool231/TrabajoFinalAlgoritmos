#include "Estudiante.h"

// Constructor por defecto
Estudiante::Estudiante() {
    correo = "";
    contrasena = "";
    nombres = "";
    apellidos = "";
}

// Constructor con parámetros
Estudiante::Estudiante(string correo, string contrasena, string nombres, string apellidos) {
    this->correo = correo;
    this->contrasena = contrasena;
    this->nombres = nombres;
    this->apellidos = apellidos;
}

// Destructor
Estudiante::~Estudiante() {
    // Por ahora vacío
}

// Getters
string Estudiante::getCorreo() {
    return correo;
}

string Estudiante::getContrasena() {
    return contrasena;
}

string Estudiante::getNombres() {
    return nombres;
}

string Estudiante::getApellidos() {
    return apellidos;
}

// Setters
void Estudiante::setCorreo(string correo) {
    this->correo = correo;
}

void Estudiante::setContrasena(string contrasena) {
    this->contrasena = contrasena;
}

void Estudiante::setNombres(string nombres) {
    this->nombres = nombres;
}

void Estudiante::setApellidos(string apellidos) {
    this->apellidos = apellidos;
}
