#ifndef ADMINISTRADORPROFESORES_H
#define ADMINISTRADORPROFESORES_H

#include <string>
#include "Profesor.h"
#include "Curso.h"
#include "HashTabla.h"
#include "ArbolBB.h"
#include "TEMPlistaEnlazada.h"

using namespace std;

class AdministradorProfesores {
private:
    ArbolBB<Profesor> arbolProfesores;
    HashTabla<string> hashCorreos; // Solo almacena correos por ahora
    TEMPListaEnlazada<string> logs;

public:
    AdministradorProfesores();

    void cargarProfesoresDesdeArchivos();
    void guardarProfesor(const Profesor& prof);

    void agregarProfesorInteractivo(vector<Curso*>& cursosDisponibles);
    void eliminarProfesor();
    void asignarCursoAProfesor(vector<Curso*>& cursosDisponibles);
    void desvincularCurso();

    void mostrarLogs();
    void mostrarProfesoresEnOrden();

    // extra
    ArbolBB<Profesor>& getArbol();
    TEMPListaEnlazada<string>& getLogs();
};

#endif
