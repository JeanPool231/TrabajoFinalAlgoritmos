#pragma once
#include <string>
#include "AVLTree.h"
using namespace std;

class Profesor {
private:
	string codigo, nombre, apellido, correo;
	char sexo, estadoCivil;
	int edad, tiempoEnCoursera;
public:
	Profesor();
	~Profesor();
	Profesor(string codigo, string nombre, string apellido, string correo,
		char sexo, char estadoCivil, int edad, int tiempoEnCoursera);
	void setCodigo(string);
	void setNombre(string);
	void setApellido(string);
	void setCorreo(string);
	void setSexo(char);
	void setEstadoCivil(char);
	void setEdad(int);
	void setTiempoEnCoursera(int);
	string getCodigo() const;
	string getNombre() const;
	string getApellido() const;
	string getCorreo() const;
	char getSexo() const;
	char getEstadoCivil() const;
	int getEdad() const;
	int getTiempoEnCoursera() const;

};

