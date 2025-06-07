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
    string nombre, apellido, correo, codigo;
    char sexo, estadoCivil;
    int edad, tiempo;

    cout << "Codigo: "; cin >> codigo;
    cout << "Nombre: "; cin >> nombre;
    cout << "Apellido: "; cin >> apellido;
    cout << "Correo: "; cin >> correo;
    cout << "Sexo (M/F): "; cin >> sexo;
    cout << "Estado civil (S/C): "; cin >> estadoCivil;
    cout << "Edad: "; cin >> edad;
    cout << "Tiempo en Coursera (años): "; cin >> tiempo;

    Profesor nuevo(codigo, nombre, apellido, correo, sexo, estadoCivil, edad, tiempo);

    arbolProfesores.insertar(nuevo, [](Profesor& a, Profesor& b) {
        return a.getApellido() < b.getApellido();
        });
}

void Sistema::iniciarPrograma() {
	menuPrincipal();
}