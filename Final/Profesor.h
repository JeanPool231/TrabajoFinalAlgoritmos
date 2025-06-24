#pragma once
#include <string>
#include <vector>
#include "AVLTree.h"
#include "Curso.h"
#include "ListaEnlazada.h"
using namespace std;

class Profesor {
private:
	string codigo, nombre, apellido, correo;
	char sexo, estadoCivil;
	int edad, tiempoEnCoursera, id, reputacion;
	string cursoAsignado;
	ListaEnlazada<Curso*> cursosCreados;
public:
	Profesor();
	~Profesor();
	Profesor(string codigo, string nombre, string apellido, string correo,
		int tiempoEnCoursera, int id, int reputacion);
	void setCodigo(string);
	void setNombre(string);
	void setApellido(string);
	void setCorreo(string);
	void setTiempoEnCoursera(int);
	void setId(int);
	void setReputacion(int);
	string getCodigo();
	string getNombre();
	string getApellido();
	string getCorreo();
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

	void agregarCurso(Curso* c) {
		cursosCreados.insertarAlFinal(c);
	}
	ListaEnlazada<Curso*>& getCursosCreados() {
		return cursosCreados;
	}

};