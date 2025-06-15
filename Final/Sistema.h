#pragma once
#include <iostream>
#include "Profesor.h"
#include "Curso.h"
#include "Institucion.h"
#include "HashUtil.h"
#include "ListaEnlazada.h"
using namespace std;

class Sistema {
private:
	ListaEnlazada<Curso> cursos;
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
public:
	void iniciarPrograma();
};
