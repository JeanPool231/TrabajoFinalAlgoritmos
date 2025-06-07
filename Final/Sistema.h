#pragma once
#include <iostream>
#include "Profesor.h"
using namespace std;

class Sistema {
private:
	AVLTree<Profesor> arbolProfesores;
	void menuPrincipal();
	void agregarProfesor();
public:
	void iniciarPrograma();
};

