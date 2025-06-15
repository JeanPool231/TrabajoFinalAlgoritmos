#pragma once
#include <string>
#include "ListaEnlazada.h"
#include "Profesor.h"

class Institucion {
private:
    std::string nombre;
    std::string direccion;
    ListaEnlazada<Profesor> profesores;

public:
    Institucion();
    Institucion(std::string nombre, std::string direccion);

    void setNombre(std::string);
    void setDireccion(std::string);
    std::string getNombre();
    std::string getDireccion();

    void agregarProfesor(const Profesor&);
    ListaEnlazada<Profesor>& getProfesores();
};