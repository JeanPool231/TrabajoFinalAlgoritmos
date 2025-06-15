#pragma once
#include <iostream>
#include "Profesor.h"
#include "Curso.h"
#include "HashUtil.h"
#include "ListaEnlazada.h"
using namespace std;

class Sistema {
private:
	ListaEnlazada<Curso> cursos;
	void menuPrincipal();
	void registroEstudiante();
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
