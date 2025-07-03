#pragma once
#include <string>
#include "Curso.h"
#include "Profesor.h"
#include "ListaEnlazada.h"
#include "AVLTree.h"

using namespace std;

class Institucion {
private:
    string nombre;
    string descripcion;
    int yearderegistro;
    ListaEnlazada<Curso*> cursos;
    AVLTree<Profesor> profesores;
    ListaEnlazada<string> logsdeprofes;

public:
    Institucion();
    Institucion(const string& nombre, const string& descripcion, int year);

    void setNombre(const string& nom);
    void setDescripcion(const string& desc);
    void setYearDeRegistro(int y);

    const string& getNombre() const;
    const string& getDescripcion() const;
    int getYearDeRegistro() const;

    ListaEnlazada<Curso*>& getcursos();
    AVLTree<Profesor>& getprofesores();
    ListaEnlazada<string>& getlogsdeprofes();

    void mostrarInformacion();
    void mostrarEstadisticas();

    void agregarCurso(Curso* curso) {
        cursos.insertarAlFinal(curso);
    }
};