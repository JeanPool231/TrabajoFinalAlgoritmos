#include "Estudiante.h"

Estudiante::Estudiante() {
    correo = "";
    contrasena = "";
    nombres = "";
    apellidos = "";
    codigo = "";
    saldo = 0;
}

Estudiante::Estudiante(string correo, string contrasena, string nombres, string apellidos, string codigo) {
    this->correo = correo;
    this->contrasena = contrasena;
    this->nombres = nombres;
    this->apellidos = apellidos;
    this->codigo = codigo;
    this->saldo = 0;
}


Estudiante::~Estudiante() {
}

string Estudiante::getCorreo() {
    return correo;
}
string Estudiante::getCodigo() {
    return codigo;
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
double Estudiante::getSaldo() {
    return saldo;
}
void Estudiante::setCorreo(string correo) {
    this->correo = correo;
}
void Estudiante::setSaldo(double saldo) {
    this->saldo = saldo;
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
void Estudiante::setCodigo(string codigo) {
    this->codigo = codigo;
}
ListaEnlazada<Curso> Estudiante::getCursosInscritos() {
    return cursosInscritos;
}
