#include "Profesor.h"

Profesor::Profesor()
	: codigo(" "), nombre(" "), apellido(" "), correo(" "),
	sexo(' '), estadoCivil(' '), edad(0), tiempoEnCoursera(0), id(0), reputacion(0){}

Profesor::~Profesor(){}

Profesor::Profesor(string codigo, string nombre, string apellido, string correo,
	char sexo, char estadoCivil, int edad, int tiempoEnCoursera, int id, int reputacion) {

	this->codigo = codigo;
	this->nombre = nombre;
	this->apellido = apellido;
	this->correo = correo;
	this->sexo = sexo;
	this->estadoCivil = estadoCivil;
	this->edad = edad;
	this->tiempoEnCoursera = tiempoEnCoursera;
	this->id = id;
	this->reputacion = reputacion;
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
int Profesor::getId() { return id; }
int Profesor::getReputacion() { return reputacion; }


// Setters

void Profesor::setNombre(string nombre) {this->nombre = nombre;}
void Profesor::setCodigo(string codigo) {this->codigo = codigo;}
void Profesor::setApellido(string apellido) {this->apellido = apellido;}
void Profesor::setCorreo(string correo) {this->correo = correo;}
void Profesor::setSexo(char sexo) {this->sexo = sexo;}
void Profesor::setEstadoCivil(char estadoCivil) {this->estadoCivil = estadoCivil;}
void Profesor::setEdad(int edad) {this->edad = edad;}
void Profesor::setTiempoEnCoursera(int tiempoEnCoursera) {this->tiempoEnCoursera = tiempoEnCoursera;}
void Profesor::setId(int id) {this->id = id;}
void Profesor::setReputacion(int reputacion) {this->reputacion = reputacion;}