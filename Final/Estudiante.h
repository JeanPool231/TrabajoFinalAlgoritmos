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
    string codigo;
    double saldo;
    ListaEnlazada<Curso> cursosInscritos;
public:
    Estudiante();
    Estudiante(string correo, string contrasena, string nombres, string apellidos, string codigo);
    ~Estudiante();

    // Getters
    string getCorreo();
    string getContrasena();
    string getNombres();
    string getApellidos();
    string getCodigo();
    double getSaldo();
    ListaEnlazada<Curso> getCursosInscritos();

    // Setters
    void setCorreo(string correo);
    void setContrasena(string contrasena);
    void setNombres(string nombres);
    void setApellidos(string apellidos);
    void agregarCurso(Curso curso);
    void setCodigo(string codigo);
    void setSaldo(double saldo);
};
