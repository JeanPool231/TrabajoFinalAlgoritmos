#pragma once
#include <iostream>
using namespace std;

class Sistema {
private:
	void menuPrincipal();
	void registroEstudiante();
	void registrarse();
	void iniciarSesion();
	bool validarCorreo();
	void inicializarDatos();
public:
	void iniciarPrograma();
};

