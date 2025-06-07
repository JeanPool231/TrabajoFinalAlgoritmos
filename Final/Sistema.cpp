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
	



void Sistema::menuAdminDebug() {
cout << "Profesores\n";
	cout << "1. Agregar profesor\n";
	cout << "2. Modificar profesor\n";
	cout << "3. Eliminar profesor\n";
	//_getch();
}

void Sistema::menuDebug() {
	cout << "Aca se suponen que estan los cursos en el carrusel\n\n";
	cout << "\033[3;14H |Curso 1|"; cout << "\033[3;29H |Curso 2|";
	cout << "\033[5;4H1 [Siguiente]\n"; cout << "\033[5;36H2 [Anterior]\n"; 
	cout << "\033[6;19H3 [Seleccionar]\n";
	//_getch();

}


void Sistema::iniciarPrograma() {
	
	//menuPrincipal();
	
	switch (admin){
		case true: menuAdminDebug(); break;
		case false: menuDebug(); break;
	}
}