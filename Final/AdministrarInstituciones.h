#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Profesor.h"
#include "Curso.h"
#include "Institucion.h"
#include "ListaEnlazada.h"
using namespace std;

class AdministrarInstitucion {
public:
    AdministrarInstitucion();
    ~AdministrarInstitucion();

    void guardarprofenelarchivo(Profesor prof);
    bool desvincularCursoDeProfesor(Institucion& inst, int idxProfe, string cursoAEliminar, string& mensaje);

    void agregarprofesor2(Institucion& inst, const string& codigo, const string& nombre,
        const string& apellido, const string& correo, int tiempoEnCoursera, int id,
        int reputacion, const string& cursoAsignado);

    bool quitarprofesor2(Institucion& inst, int indexAEliminar, string& mensajeConfirmacion);
    ListaEnlazada<Profesor> obtenerListaProfes(Institucion& inst);

    ListaEnlazada<Profesor*> obtenerProfesoresSinCurso(Institucion& inst);
    ListaEnlazada<Curso*> obtenerCursosLibres(Institucion& inst);
    bool asignarCursoAProfesor(Institucion& inst, int idxProfe, int idxCurso, string& logMensaje);

    ListaEnlazada<Profesor*> obtenerProfesoresConCurso(Institucion& inst);

    void mostrarLogsPorFiltro(const string& filtro, const string& valor, ListaEnlazada<string>& resultado);

    void obtenerResumenCursos(Institucion& inst, ListaEnlazada<string>& resumen);
    void obtenerResumenProfesores(Institucion& inst, ListaEnlazada<string>& resumen);
    size_t contarCursos(Institucion& inst);
    void obtenerListadoCursosConProfesor(Institucion& inst, ListaEnlazada<string>& listado);
    Profesor* buscarProfesorPorID(Institucion& inst, const string& id);
};
