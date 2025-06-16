#pragma once
#include <string>
#include <vector>
#include "AVLTree.h"
#include "Curso.h"
using namespace std;

class Profesor {
private:
	string codigo, nombre, apellido, correo;
	char sexo, estadoCivil;
	int edad, tiempoEnCoursera, id, reputacion;
	string cursoAsignado;
public:
	Profesor();
	~Profesor();
	Profesor(string codigo, string nombre, string apellido, string correo,
		char sexo, char estadoCivil, int edad, int tiempoEnCoursera, int id, int reputacion);
	void setCodigo(string);
	void setNombre(string);
	void setApellido(string);
	void setCorreo(string);
	void setSexo(char);
	void setEstadoCivil(char);
	void setEdad(int);
	void setTiempoEnCoursera(int);
	void setId(int);
	void setReputacion(int);
	string getCodigo();
	string getNombre();
	string getApellido();
	string getCorreo();
	char getSexo();
	char getEstadoCivil();
	int getEdad();
	int getTiempoEnCoursera();
	int getId();
	int getReputacion();

	void asignarCurso(const string& nombreCurso) {
		cursoAsignado = nombreCurso;
	}
	void quitarCurso() {
		cursoAsignado = "";
	}
	string getCursoAsignado() const {
		return cursoAsignado;
	}
};