#include "Profesor.h"

Profesor::Profesor()
	: codigo(" "), nombre(" "), apellido(" "), correo(" "),
	sexo(' '), estadoCivil(' '), edad(0), tiempoEnCoursera(0) {}

Profesor::~Profesor(){}

Profesor::Profesor(string codigo, string nombre, string apellido, string correo,
	char sexo, char estadoCivil, int edad, int tiempoEnCoursera) {

	this->codigo = codigo;
	this->nombre = nombre;
	this->apellido = apellido;
	this->correo = correo;
	this->sexo = sexo;
	this->estadoCivil = estadoCivil;
	this->edad = edad;
	this->tiempoEnCoursera = tiempoEnCoursera;
}

// Getters

string Profesor::getCodigo() {
	return this->codigo;
}

string Profesor::getNombre() {
	return this->nombre;
}

string Profesor::getCorreo() {
	return this->correo;
}

char Profesor::getSexo() {
	return this->sexo;
}

char Profesor::getEstadoCivil() {
	return this->estadoCivil;
}

string Profesor::getApellido() {
	return this->apellido;
}

int Profesor::getEdad() {
	return this->edad;
}

int Profesor::getTiempoEnCoursera() {
	return this->tiempoEnCoursera;
}

// Setters

void Profesor::setNombre(string nombre) {
	this->nombre = nombre;
}

void Profesor::setCodigo(string codigo) {
	this->codigo = codigo;
}

void Profesor::setApellido(string apellido) {
	this->apellido = apellido;
}

void Profesor::setCorreo(string correo) {
	this->correo = correo;
}

void Profesor::setSexo(char sexo) {
	this->sexo = sexo;
}

void Profesor::setEstadoCivil(char estadoCivil) {
	this->estadoCivil = estadoCivil;
}

void Profesor::setEdad(int edad) {
	this->edad = edad;
}

void Profesor::setTiempoEnCoursera(int tiempoEnCoursera) {
	this->tiempoEnCoursera = tiempoEnCoursera;
}