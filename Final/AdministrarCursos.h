#pragma once
#include "Curso.h"
#include "Nodo.h"
#include "ListaEnlazada.h"
#include <iostream>
using namespace std;

class AdministrarCurso {
private:
    ListaEnlazada<Curso> cursos;
public:
    AdministrarCurso();
    AdministrarCurso(ListaEnlazada<Curso> cursos);
    ~AdministrarCurso();

    void ImprimirNombreCursos();
};
