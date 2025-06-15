#pragma once
#include "ListaEnlazada.h"
#include "Profesor.h"

class AdministrarProfesores {
private:
    ListaEnlazada<Profesor> profesores;

public:
    AdministrarProfesores();
    void agregarProfesor(const Profesor&);
    void listarProfesores();
    Profesor* buscarPorCodigo(const std::string&);
};