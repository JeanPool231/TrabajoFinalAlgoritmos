#pragma once
#include <string>
using namespace std;

class Profesor {
private:
	string codigo, nombre, apellido, correo;
	char sexo, estadoCivil;
	int edad, tiempoEnCoursera;
public:
	Profesor();
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
	string getCodigo();
	string getNombre();
	string getApellido();
	string getCorreo();
	char getSexo();
	char getEstadoCivil();
	int getEdad();
	int getTiempoEnCoursera();
};

