#pragma once
#include <iostream>
using namespace std;

class Estudiante {
private:
    string correo;
    string contrasena;
    string nombres;
    string apellidos;

public:
    Estudiante();
    Estudiante(string correo, string contrasena, string nombres, string apellidos);
    ~Estudiante();

    // Getters
    string getCorreo();
    string getContrasena();
    string getNombres();
    string getApellidos();

    // Setters
    void setCorreo(string correo);
    void setContrasena(string contrasena);
    void setNombres(string nombres);
    void setApellidos(string apellidos);
};
