#include "Sistema.h"
#include <iostream>
#include <conio.h>
using namespace std;

//void Sistema::menuPrincipal() {
//	cout << "Coursera\n";
//	cout << "1. Iniciar sesion\n";
//	cout << "2. Registrarte\n";
//	cout << "3. Acceder a los cursos(sin iniciar sesion)\n";
//	cout << "4. Salir\n";
//	//_getch();
//}

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