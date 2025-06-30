#pragma once
#include <iostream>
#include "Profesor.h"
#include "Curso.h"
#include "Institucion.h"
#include "HashUtil.h"
#include "ListaEnlazada.h"
#include "Usuario.h"
#include "Estudiante.h"
#include "Profesor.h"
#include "Institucion.h"
#include "Administrador.h"
#include "UI.h"
using namespace std;

class Sistema {
private:
	UI disenio;
	Curso curso;
	Estudiante* estudiante = new Estudiante();
	Profesor* profesor = new Profesor();
	Institucion* institucion = new Institucion();
	ListaEnlazada<Curso> cursos;
	ListaEnlazada<Usuario> usuarios;
	ListaEnlazada<Profesor> profesores;
	ListaEnlazada<Estudiante> estudiantes;
	void menuInstitucion();
	void menuPrincipal();
	void registroEstudiante();
	void registroProfesor();
	void registroInstitucion();
	void registrarse();
	void iniciarSesion();
    void menuAdmin();
	bool validarCorreo(string& correo);
	bool validarContrasena(string& contrasena, string& correo);
	void inicializarDatos();
	void menuProfesor();
	void menuEstudiante();
	void cursosEstudiante();
	void perfilEstudiante();
	void saldoEstudiante();
	void cursosInscritos();
	void iniciarSesionUI();
	void mostrarCursosUI();
	void registroEstudianteUI();
	void registroUI();
	void inicioUI();
public:
	void iniciarPrograma();
};
