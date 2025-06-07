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

string Profesor::getNombre() const { return nombre; }
string Profesor::getCodigo() const { return codigo; }
string Profesor::getApellido() const { return apellido; }
string Profesor::getCorreo() const { return correo; }
char Profesor::getSexo() const { return sexo; }
char Profesor::getEstadoCivil() const { return estadoCivil; }
int Profesor::getEdad() const { return edad; }
int Profesor::getTiempoEnCoursera() const { return tiempoEnCoursera; }


// Setters

void Profesor::setNombre(string nombre) {this->nombre = nombre;}
void Profesor::setCodigo(string codigo) {this->codigo = codigo;}
void Profesor::setApellido(string apellido) {this->apellido = apellido;}
void Profesor::setCorreo(string correo) {this->correo = correo;}
void Profesor::setSexo(char sexo) {this->sexo = sexo;}
void Profesor::setEstadoCivil(char estadoCivil) {this->estadoCivil = estadoCivil;}
void Profesor::setEdad(int edad) {this->edad = edad;}
void Profesor::setTiempoEnCoursera(int tiempoEnCoursera) {this->tiempoEnCoursera = tiempoEnCoursera;}