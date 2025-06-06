#include "Sistema.h"
#include <iostream>
#include <conio.h>
using namespace std;

void Sistema::menuPrincipal() {
	cout << "Coursera\n";
	cout << "1. Iniciar sesion\n";
	cout << "2. Registrarte\n";
	cout << "3. Acceder a los cursos(sin iniciar sesion)\n";
	cout << "4. Salir\n";
	//_getch();
}

void Sistema::agregarProfesor() {
	//debuggeando
	string nombre, apellido;
	Profesor profesor;

	cout << "Ingrese su nombre: "; cin >> nombre;
	cout << "Ingrese su apellido: "; cin >> apellido;
	profesor.setNombre(nombre);
	profesor.setApellido(apellido);
}

void Sistema::iniciarPrograma() {
	menuPrincipal();
}