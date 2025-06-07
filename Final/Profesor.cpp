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

string Profesor::getNombre() { return nombre; }
string Profesor::getCodigo() { return codigo; }
string Profesor::getApellido() { return apellido; }
string Profesor::getCorreo() { return correo; }
char Profesor::getSexo() { return sexo; }
char Profesor::getEstadoCivil() { return estadoCivil; }
int Profesor::getEdad() { return edad; }
int Profesor::getTiempoEnCoursera() { return tiempoEnCoursera; }


// Setters

void Profesor::setNombre(string nombre) {this->nombre = nombre;}
void Profesor::setCodigo(string codigo) {this->codigo = codigo;}
void Profesor::setApellido(string apellido) {this->apellido = apellido;}
void Profesor::setCorreo(string correo) {this->correo = correo;}
void Profesor::setSexo(char sexo) {this->sexo = sexo;}
void Profesor::setEstadoCivil(char estadoCivil) {this->estadoCivil = estadoCivil;}
void Profesor::setEdad(int edad) {this->edad = edad;}
void Profesor::setTiempoEnCoursera(int tiempoEnCoursera) {this->tiempoEnCoursera = tiempoEnCoursera;}