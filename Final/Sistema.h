#pragma once
#include <iostream>
#include "Profesor.h"
#include "Curso.h"
#include "HashUtil.h"
using namespace std;

class Sistema {
private:

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

