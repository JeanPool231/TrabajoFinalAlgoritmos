#include "Administrador.h"

Administrador::Administrador() {}
Administrador::~Administrador() {}

void Administrador::guardar(Usuario usuario) {
	ofstream archivo("Usuarios/usuarios.txt", ios::app);
	if (archivo.is_open()) {
		archivo << usuario.tipoUsuario << " " << usuario.correo << " " << usuario.contrasena << endl;
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo para guardar.\n";
	}
}

void Administrador::ver_cursos(ListaEnlazada<Curso*>& curso)
{
	ifstream archivo("cursosCreados/654633245.txt");
	if (archivo.is_open())
	{
		string linea;
		while (getline(archivo, linea))
		{
			cout << linea << endl;
		}
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo para cargar.\n";
	}
	_getch();
}
void Administrador::añadir_cursos(ListaEnlazada<Curso*>& curso)
{
	int opc; ofstream archivo("cursosCreados/654633245.txt", ios::app);
	string nombre, id, categoria, descripcion, fechaCreacion;
	int duracionHoras, cantidadInscritos,numLecciones;
	cout << "Ingrese nombre del curso a agregar: "; cin >> nombre;
	cout << "Ingrese ID del curso a agregar: "; cin >> id;
	cout << "Ingrese categoria del curso a agregar: "; cin >> categoria;
	cout << "Ingrese descripcion del curso a agregar: "; cin >> descripcion;
	cout << "Ingrese la fecha de la creacion del curso a agregar: "; cin >> fechaCreacion;
	cout << "Ingrese duracion en horas del curso a agregar: "; cin >> duracionHoras;
	cout << "Ingrese la cantidad de inscritos del curso a agregar: "; cin >> cantidadInscritos;
	cout << "Ingrese el numero de lecciones del curso a agregar: "; cin >> numLecciones;
	Curso* c = new Curso(nombre, id, categoria, descripcion, fechaCreacion, duracionHoras, cantidadInscritos, numLecciones);
	cout << endl;
	cout << "Donde quiere agregar el nuevo curso: Inicio(1) o Final (2): "; cin >> opc;
	if (opc == 1)
	{
		curso.insertarAlInicio(c);
	}
	else {
		curso.insertarAlFinal(c);
	}
	if (archivo.is_open()) {
		archivo << "[" << nombre << "]" << endl;
		archivo << "id: " << id << endl;
		archivo << "categoria: " << categoria << endl;
		archivo << "descripcion: " << descripcion << endl;
		archivo << "duracion: " << duracionHoras << endl;
		archivo << "fecha: " << fechaCreacion << endl;
		archivo << endl;
		archivo << "[LECCIONES]" << endl;
		archivo << numLecciones << endl;
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo para guardar.\n";
	}
	cout << "Curso Añadido";
	_getch();
}
void Administrador::eliminar_cursos(ListaEnlazada<Curso*>& curso)
{
	curso.eliminarPrimero();
	cout << "Curso Eliminado";
	_getch();
}
void Administrador::ver_estudiantes(ListaEnlazada<Estudiante*>& estu)
{

}
void Administrador::añadir_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	string correo, contraseña, nombre, apellido;
	cout << "Ingresar correo del estudiante a agregar: "; cin >> correo;
	cout << "Ingresar la contraseña del estudiante a agregar: "; cin >> contraseña;
	cout << "Ingresar el nombre del estudiante a agregar: "; cin >> nombre;
	cout << "Ingresar el apellido del estudiante a agregar: "; cin >> apellido;
	Estudiante* est = new Estudiante(correo, contraseña, nombre, apellido);
	cout << endl;
	Usuario estudiante = { 'E', correo, contraseña };
	guardar(estudiante);
	cout << "Estudiante Añadido";
	_getch();
}
void Administrador::eliminar_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	estu.eliminarPrimero();
	cout << "Estudiante Eliminado";
	_getch();
}
void Administrador::ver_profesores(AVLTree<Profesor*>& profe)
{
	ifstream archivo("profesoresGuardados/P12.txt");
	if (archivo.is_open())
	{
		string linea;
		while (getline(archivo, linea))
		{
			cout << linea << endl;
		}
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo para cargar.\n";
	}
	_getch();
}
void Administrador::añadir_profesores(AVLTree<Profesor*>& profe)
{
	ofstream archivo("profesoresGuardados/P12.txt", ios::app);
	string codigo, contraseña, nombre, apellido, correo; int tiempoEnCoursera, id, reputacion;
	cout << "Ingrese el codigo del profesor a añadir: "; cin >> codigo;
	cout << "Ingrese el nombre del profesor a añadir: "; cin >> nombre;
	cout << "Ingrese el apellido del profesor a añadir: "; cin >> apellido;
	cout << "Ingrese el correo del profesor a añadir: "; cin >> correo;
	cout << "Ingrese la contraseña del profesor a añadir: "; cin >> contraseña;
	cout << "Ingrese el tiempo en Cursera del profesor a añadir: "; cin >> tiempoEnCoursera;
	cout << "Ingrese el ID del profesor a añadir: "; cin >> id;
	cout << "Ingrese la reputacion del profesor a añadir: "; cin >> reputacion;
	Profesor* pro = new Profesor(codigo, nombre, apellido, correo, tiempoEnCoursera, id, reputacion);
	cout << endl;
	auto cmp = [](Profesor*& a, Profesor*& b) { return a->getReputacion() < b->getReputacion(); };
	profe.insertar(pro, cmp);
	Usuario usprofe = { 'P', correo, contraseña };
	guardar(usprofe);
	if (archivo.is_open()) {
		archivo << "codigo: " << codigo << endl;
		archivo << "nombre: " << nombre << endl;
		archivo << "apellido: " << apellido << endl;
		archivo << "correo: " << correo << endl;
		archivo << "tiempo_en_cursera: " << tiempoEnCoursera << endl;
		archivo << "id: " << id << endl;
		archivo << "reputacion: " << reputacion << endl;
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo para guardar.\n";
	}
	cout << "Profesor Añadido";
	_getch();
}
void Administrador::eliminar_profesores(AVLTree<Profesor*>& profe)
{

}
void Administrador::ver_instituciones(AVLTree<Institucion*>& inst)
{

}
void Administrador::añadir_instituciones(AVLTree<Institucion*>& inst)
{
	string nombre, descripcion, correo, contraseña; int yearderegistro;
	cout << "Ingrese el nombre de la institucion a añadir: "; cin >> nombre;
	cout << "Ingrese la descripcion de la institucion a añadir: "; cin >> descripcion;
	cout << "Ingrese el año de registro de la institucion a añadir: "; cin >> yearderegistro;
	cout << "Ingrese el correo de la institucion a añadir: "; cin >> correo;
	cout << "Ingrese la contraseña de la institucion a añadir: "; cin >> contraseña;
	Institucion* ins = new Institucion(nombre, descripcion, yearderegistro);
	auto cmp = [](Institucion*& a, Institucion*& b) { return a->getyear() < b->getyear(); };
	inst.insertar(ins, cmp);
	Usuario institucion = { 'I', correo, contraseña };
	guardar(institucion);
	cout << "Institucion Añadida";
	_getch();
}
void Administrador::eliminar_instituciones(AVLTree<Institucion*>& inst)
{

}

void Administrador::menu_admin(ListaEnlazada<Curso*>& curso, ListaEnlazada<Estudiante*>& estu, AVLTree<Profesor*>& profe, AVLTree<Institucion*>& inst)
{
	int opc; bool ciclo = true;
	do {
		system("cls");
		cout << "MENU" << endl;
		cout << "Administrar Cursos" << endl;
		cout << " 1. Ver Cursos" << endl;
		cout << " 2. Añadir Cursos" << endl;
		cout << " 3. Eliminar Cursos" << endl;
		cout << "Administrar Estudiantes" << endl;
		cout << " 4. Ver Estudiantes" << endl;
		cout << " 5. Añadir Estudiantes" << endl;
		cout << " 6. Eliminar Estudiantes" << endl;
		cout << "Administrar Profesores" << endl;
		cout << " 7. Ver Profesores" << endl;
		cout << " 8. Añadir Profesores" << endl;
		cout << " 9. Eliminar Profesores" << endl;
		cout << "Administrar Instituciones" << endl;
		cout << " 10. Ver Instituciones" << endl;
		cout << " 11. Añadir Instituciones" << endl;
		cout << " 12. Eliminar Instituciones" << endl;
		cout << endl;
		cout << "Salir (Cualquier otra opcion)" << endl;
		cout << endl;
		cout << "Ingrese una opcion: "; cin >> opc;
		system("cls");
		switch (opc)
		{
		case 1: ver_cursos(curso);
			break;
		case 2: añadir_cursos(curso);
			break;
		case 3: eliminar_cursos(curso);
			break;
		case 4: ver_estudiantes(estu);
			break;
		case 5: añadir_estudiantes(estu);
			break;
		case 6: eliminar_estudiantes(estu);
			break;
		case 7: ver_profesores(profe);
			break;
		case 8: añadir_profesores(profe);
			break;
		case 9: eliminar_profesores(profe);
			break;
		case 10: ver_instituciones(inst);
			break;
		case 11: añadir_instituciones(inst);
			break;
		case 12: eliminar_instituciones(inst);
			break;
		default:
			ciclo = false;
			break;
		}

	} while (ciclo == true);
}
