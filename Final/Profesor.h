#pragma once
#include <string>
#include <vector>
#include "AVLTree.h"
#include "Curso.h"
#include "ListaEnlazada.h"
using namespace std;

class Profesor {
private:
	string codigo_institucion, nombre, apellido, correo;
	string id;
	int tiempoEnCoursera, reputacion;
	string cursoAsignado;
	ListaEnlazada<Curso*> cursosCreados;
	vector<string> cursosAsignados;
public:
	Profesor();
	~Profesor();
	Profesor(string codigo_institucion, string nombre, string apellido, string correo,
		int tiempoEnCoursera, string id, int reputacion);
	void setCodigo(string);
	void setNombre(string);
	void setApellido(string);
	void setCorreo(string);
	void setTiempoEnCoursera(int);
	void setId(string);
	void setReputacion(int);
	string getCodigo();
	string getNombre();
	string getApellido();
	string getCorreo();
	int getTiempoEnCoursera();
	string getId();
	int getReputacion();

	void agregarCurso(const string& nombreCurso) {
		cursosAsignados.push_back(nombreCurso);
	}

	void quitarCurso(const string& nombreCurso) {
		cursosAsignados.erase(
			remove_if(cursosAsignados.begin(), cursosAsignados.end(),
				[&](const string& curso) {
					return curso == nombreCurso;
				}),
			cursosAsignados.end());
	}

	vector<string>& getCursosAsignados() {
		return cursosAsignados;
	}

	void setCursosAsignados(const vector<string>& cursos) {
		cursosAsignados = cursos;
	}
};