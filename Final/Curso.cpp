#include "Curso.h"

Curso::Curso() 
	: nombre("") {
}

Curso::~Curso() {}

Curso::Curso(string nombre) {
	this->nombre = nombre;
}