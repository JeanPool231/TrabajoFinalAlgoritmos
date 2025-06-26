#pragma once
#include <iostream>
#include "ListaEnlazada.h";
#include "Nodo.h"
#include "Curso.h"
using namespace std;

class Estudiante {
private:
    string correo;
    string contrasena;
    string nombres;
    string apellidos;
    ListaEnlazada<Curso> cursosInscritos;
public:
    Estudiante();
    Estudiante(string correo, string contrasena, string nombres, string apellidos);
    ~Estudiante();

    // Getters
    string getCorreo();
    string getContrasena();
    string getNombres();
    string getApellidos();
    ListaEnlazada<Curso> getCursosInscritos();

    // Setters
    void setCorreo(string correo);
    void setContrasena(string contrasena);
    void setNombres(string nombres);
    void setApellidos(string apellidos);
    void agregarCurso(Curso curso);
};
