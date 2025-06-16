#pragma once
#include <iostream>
#include "Profesor.h"
#include "Curso.h"
#include "Institucion.h"
#include "HashUtil.h"
#include "ListaEnlazada.h"
#include "Usuario.h"
#include "Administrador.h"
using namespace std;

class Sistema {
private:
	ListaEnlazada<Curso> cursos;
	ListaEnlazada<Usuario> usuarios;
	void menuInstitucion();
	void menuPrincipal();
	void registroEstudiante();
	void registroProfesor();
	void registroInstitucion();
	void registrarse();
	void iniciarSesion();
	void menuAdmin();
	bool validarCorreo();
	void inicializarDatos();
	void menuProfesor();
	void menuEstudiante();
	void cursosEstudiante();
public:
	void iniciarPrograma();
};
