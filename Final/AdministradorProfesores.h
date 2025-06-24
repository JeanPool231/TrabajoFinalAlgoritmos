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
    HashTabla<string> hashCorreos;
    TEMPListaEnlazada<string> logs;

public:
    AdministradorProfesores();

    void cargarProfesoresDesdeArchivos();
    void agregarProfesorInteractivo(vector<Curso*>& cursosDisponibles);
    void asignarCursoAProfesor(vector<Curso*>& cursosDisponibles);
    void desvincularCurso();


    void cargarCursosDesdeCarpeta(string ruta, vector<Curso*>& cursosRef);
    void mostrarCursos(const vector<Curso*>& cursosRef);
    void eliminarCursoPorId(vector<Curso*>& cursosRef, string id);
    void guardarCursoEnArchivo(Curso* curso);
    void mostrarLogs();
    void mostrarProfesoresEnOrden();

    // extra
    ArbolBB<Profesor>& getArbol();
    TEMPListaEnlazada<string>& getLogs();
};

#endif
