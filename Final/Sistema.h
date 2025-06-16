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

using namespace std;

class Sistema {
private:
	Estudiante* estudiante = new Estudiante();
	Profesor* profesor = new Profesor();
	Institucion* institucion = new Institucion();
	ListaEnlazada<Curso> cursos;
	ListaEnlazada<Usuario> usuarios;
	void menuInstitucion();
	void menuPrincipal();
	void registroEstudiante();
	void registroProfesor();
	void registroInstitucion();
	void registrarse();
	void iniciarSesion();
	bool validarCorreo();
	void inicializarDatos();
	void menuProfesor();
	void menuEstudiante();
	void cursosEstudiante();
	void perfilEstudiante();
public:
	void iniciarPrograma();
};
