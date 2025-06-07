#pragma once
#include <iostream>
#include "Profesor.h"
using namespace std;

class Sistema {
private:

	void menuPrincipal();
	void registroEstudiante();
	void registrarse();
	void iniciarSesion();
	bool validarCorreo();
	void inicializarDatos();
	bool admin = false;
	void menuAdminDebug();
	void menuDebug();
public:
	void iniciarPrograma();
};

