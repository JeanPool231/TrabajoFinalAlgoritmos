#pragma once

#include "Institucion.h"
#include "Profesor.h"
#include "Curso.h"
#include "AVLTree.h"
#include "ListaEnlazada.h"

class AdministrarInstituciones {
public:
    void guardarInstitucionEnArchivo(Institucion* institucion);
    Institucion* leerInstitucionDesdeArchivo(string ruta);
    void registrarInstitucion(Institucion* institucion);

    void generarTokenRegistro(string hashInstitucion);
    bool validarYEliminarToken(string token);
    string obtenerInstitucionDesdeToken(string token);
};

void guardarprofenelarchivo(Profesor prof);

void agregarprofesor2(Institucion& inst);

void mostrarhistorial2(const ListaEnlazada<string>& logs);

void quitarprofesor2(Institucion& inst);

void asignarcursoalprofe2(Institucion& inst);

void desvincularcursoalprofe2(Institucion& inst);
