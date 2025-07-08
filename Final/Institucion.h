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
    string correo;
    int yearderegistro;
    string tipoInst;
    string contrasena;
    string codigo;
    ListaEnlazada<Curso*> cursos;
    AVLTree<Profesor> profesores;
    ListaEnlazada<string> logsdeprofes;

public:
    Institucion();
    Institucion(const string& nombre, const string& descripcion, int year);

    void setNombre(const string& nom);
    void setDescripcion(const string& desc);
    void setYearDeRegistro(int y);
	void setCorreo(const string& correo);
	void setContrasena(const string& contrasena);
	void setTipoInst(const string& tipoInst);
	void setCodigo(const string& codigo);

    const string& getNombre() const;
    const string& getDescripcion() const;
    int getYearDeRegistro() const;
	const string& getCorreo() const;
	const string& getContrasena() const;
	const string& getTipoInst() const;
	const string& getCodigo() const;

    ListaEnlazada<Curso*>& getcursos();
    AVLTree<Profesor>& getprofesores();
    ListaEnlazada<string>& getlogsdeprofes();

    void mostrarInformacion();
    void mostrarEstadisticas();

    void agregarCurso(Curso* curso) {
        cursos.insertarAlFinal(curso);
    }
};