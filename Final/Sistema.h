#pragma once
#include <iostream>
#include "Profesor.h"
#include "Curso.h"
#include "HashUtil.h"
#include "Institucion.h"
using namespace std;

class Sistema {
private:
	void menuInstitucion();
	void menuPrincipal();
	void registroEstudiante();
	void registrarse();
	void iniciarSesion();
	bool validarCorreo();
	void inicializarDatos();
	void menuProfesor();
public:
	void iniciarPrograma();
};

