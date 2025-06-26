#include "Estudiante.h"

Estudiante::Estudiante() {
    correo = "";
    contrasena = "";
    nombres = "";
    apellidos = "";
}

Estudiante::Estudiante(string correo, string contrasena, string nombres, string apellidos) {
    this->correo = correo;
    this->contrasena = contrasena;
    this->nombres = nombres;
    this->apellidos = apellidos;
}

Estudiante::~Estudiante() {
}

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
void Estudiante::agregarCurso(Curso curso) {
    cursosInscritos.insertarAlFinal(curso);
}
ListaEnlazada<Curso> Estudiante::getCursosInscritos() {
    return cursosInscritos;
}
