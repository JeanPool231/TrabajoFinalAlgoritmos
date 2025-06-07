#include "Sistema.h"
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

void Sistema::menuPrincipal() {
	int opcion;
	cout << "Coursera\n";
	cout << "1. Iniciar sesion\n";
	cout << "2. Registrarte\n";
	cout << "3. Acceder a los cursos(sin iniciar sesion)\n";
	cout << "4. Salir\n";
	cout << "Opcion: ";
	cin >> opcion;
	switch (opcion) {
	case 1:
		iniciarSesion();
		break;
	case 2:
		registrarse();
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}
bool Sistema::validarCorreo() {
	return false;
}
void Sistema::iniciarSesion() {
	string correo, contrasena;
	cout << "Ingrese el correo: ";
	cin >> correo;
	cout << "Ingrese la contrasena: ";
	cin >> contrasena;
}
void Sistema::registrarse() {
	system("cls");
	char tipoUsuario;
	cout << "Ingrese si es Estudiante(E), Profesor(P) o Institucion(I): "; cin >> tipo;
	switch (tipo) {
	case 'E':
		registroEstudiante();
		break;
	case 'P':
		break;
	case 'I':
		break;
	}
}
void Sistema::registroEstudiante() {
	system("cls");
	string correo, contrasena, nombres, apellidos;
	cout << "Ingrese el correo: "; cin >> correo;
	cout << "Ingrese la contrasena: "; cin >> contrasena;
	cout << "Ingrese sus Nombres: ";
	getline(cin, nombres);
	cout << "Ingrese sus apellidos: ";
	getline(cin, apellidos);
	cout << "Se ha registrado correctamente\n";
	system("pause");
	system("cls");
}
void Sistema::inicializarDatos() {
	
}
void Sistema::iniciarPrograma() {
	menuPrincipal();
}