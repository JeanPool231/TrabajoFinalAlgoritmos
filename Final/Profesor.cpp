#include "Profesor.h"

Profesor::Profesor()
	: codigo_institucion(" "), nombre(" "), apellido(" "), correo(" "),
	tiempoEnCoursera(0), id(0), reputacion(0){}

Profesor::~Profesor(){}

Profesor::Profesor(string codigo, string nombre, string apellido, string correo,
	int tiempoEnCoursera, int id, int reputacion) {

	this->codigo_institucion = codigo;
	this->nombre = nombre;
	this->apellido = apellido;
	this->correo = correo;
	this->tiempoEnCoursera = tiempoEnCoursera;
	this->id = id;
	this->reputacion = reputacion;
}

// Getters

string Profesor::getNombre() { return nombre; }
string Profesor::getCodigo() { return codigo_institucion; }
string Profesor::getApellido() { return apellido; }
string Profesor::getCorreo() { return correo; }
int Profesor::getTiempoEnCoursera() { return tiempoEnCoursera; }
int Profesor::getId() { return id; }
int Profesor::getReputacion() { return reputacion; }


// Setters

void Profesor::setNombre(string nombre) {this->nombre = nombre;}
void Profesor::setCodigo(string codigo) {this->codigo_institucion = codigo;}
void Profesor::setApellido(string apellido) {this->apellido = apellido;}
void Profesor::setCorreo(string correo) {this->correo = correo;}
void Profesor::setTiempoEnCoursera(int tiempoEnCoursera) {this->tiempoEnCoursera = tiempoEnCoursera;}
void Profesor::setId(int id) {this->id = id;}
void Profesor::setReputacion(int reputacion) {this->reputacion = reputacion;}