#include "Administrador.h"
#include <filesystem>
namespace fs = std::filesystem;

Administrador::Administrador() {}
Administrador::~Administrador() {}

void Administrador::guardar(Usuario usuario, string id) {
	string name = "Usuarios/" + usuario.correo + ".txt"; ofstream archivo(name, ios::app);
	if (archivo.is_open()) {
		archivo << usuario.tipoUsuario << endl;
		archivo << usuario.correo << endl;
		archivo << usuario.contrasena << endl;
		archivo << id << endl;
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo para guardar.\n";
	}
}

void Administrador::eliminar(string correo)
{
	string name = "Usuarios/" + correo + ".txt";
	if (fs::exists(name))
	{
		fs::remove(name);
	}
	else {
		cout << "Ese usuario no existe" << endl;
	}
}

void Administrador::ver_cursos(ListaEnlazada<Curso*>& curso)
{
	for (auto& entry : fs::directory_iterator("cursosCreados"))
	{
		if (entry.path().extension() == ".txt")
		{
			ifstream archivo(entry.path());
			string linea;
			while (getline(archivo, linea))
			{
				cout << linea << endl;
			}
		}
		cout << endl;
	}
	_getch();
}
void Administrador::anadir_cursos(ListaEnlazada<Curso*>& curso)
{
	int opc;
	string nombre, id, categoria, descripcion, fechaCreacion, cod_profe, titulo;
	int duracionHoras, cantidadInscritos, numLecciones;
	double costo;
	cout << "Ingrese nombre del curso a agregar: "; cin >> nombre;
	cout << "Ingrese ID del curso a agregar: "; cin >> id;
	cout << "Ingrese categoria del curso a agregar: "; cin >> categoria;
	cout << "Ingrese descripcion del curso a agregar: "; cin >> descripcion;
	cout << "Ingrese la fecha de la creacion del curso a agregar: "; cin >> fechaCreacion;
	cout << "Ingrese duracion en horas del curso a agregar: "; cin >> duracionHoras;
	cout << "Ingrese la cantidad de inscritos del curso a agregar: "; cin >> cantidadInscritos;
	cout << "Ingrese el costo del curso a agregar: "; cin >> costo;
	cout << "Ingrese el codigo del profesor del curso a agregar: "; cin >> cod_profe;
	cout << "Ingrese el numero de lecciones del curso a agregar: "; cin >> numLecciones;
	Curso* c = new Curso(nombre, id, categoria, descripcion, fechaCreacion, duracionHoras, cantidadInscritos, numLecciones, costo, cod_profe);
	Leccion* leccion = new Leccion[numLecciones];
	for (int i = 0; i < numLecciones; i++)
	{
		cout << "Ingresar titulo de la leccion " << i + 1 << ": "; cin >> titulo;
		leccion[i].setTitulo(titulo);
	}
	cout << endl;
	cout << "Donde quiere agregar el nuevo curso: Inicio(1) o Final (2): "; cin >> opc;
	if (opc == 1)
	{
		curso.insertarAlInicio(c);
	}
	else {
		curso.insertarAlFinal(c);
	}
	string name = "cursosCreados/" + id + ".txt"; ofstream archivo(name, ios::app);
	if (archivo.is_open()) {
		archivo << nombre << endl;
		archivo << id << endl;
		archivo << categoria << endl;
		archivo << descripcion << endl;
		archivo << duracionHoras << endl;
		archivo << fechaCreacion << endl;
		for (int i = 0; i < numLecciones; i++)
		{
			archivo << leccion[i].getTitulo() << endl;
		}
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
	int ID;
	cout << "Ingresar ID del curso a eliminar: "; cin >> ID;
	string name = "cursosCreados/" + to_string(ID) + ".txt";
	curso.eliminarPrimero();
	if (fs::exists(name))
	{
		fs::remove(name);
		cout << "Curso Eliminado";
	}
	else {
		cout << "Ese curso no existe" << endl;
	}
	_getch();
}

void Administrador::ver_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	for (auto& entry : fs::directory_iterator("estudiantesCreados"))
	{
		if (entry.path().extension() == ".txt")
		{
			ifstream archivo(entry.path());
			string linea;
			while (getline(archivo, linea))
			{
				cout << linea << endl;
			}
			cout << endl;
		}
	}
	_getch();
}
void Administrador::anadir_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	string correo, contraseña, nombre, apellido, codigo;
	cout << "Ingresar correo del estudiante a agregar: "; cin >> correo;
	cout << "Ingresar la contraseña del estudiante a agregar: "; cin >> contraseña;
	cout << "Ingresar el nombre del estudiante a agregar: "; cin >> nombre;
	cout << "Ingresar el apellido del estudiante a agregar: "; cin >> apellido;
	cout << "Ingresar el codigo del estudiante a agregar: "; cin >> codigo;
	Estudiante* est = new Estudiante(correo, contraseña, nombre, apellido, codigo);
	cout << endl;
	Usuario estudiante = { 'E', correo, contraseña };
	guardar(estudiante, codigo);
	string name = "estudiantesCreados/" + codigo + ".txt";
	ofstream archivo(name, ios::app);
	if (archivo.is_open()) {
		archivo << nombre << endl;
		archivo << apellido << endl;
		archivo << correo << endl;
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo para guardar.\n";
	}
	cout << "Estudiante añadido";
	_getch();
}
void Administrador::eliminar_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	string cod, correo;
	cout << "Ingresar el codigo del estudiante a eliminar: "; cin >> cod;
	cout << "Ingresar el correo del estudiante a eliminar: "; cin >> correo;
	string name = "estudiantesCreados/" + cod + ".txt";
	if (fs::exists(name))
	{
		fs::remove(name);
		cout << "Estudiante Eliminado";
	}
	else {
		cout << "Ese profesor no existe" << endl;
	}
	eliminar(correo);
	_getch();
}

void Administrador::ver_profesores(AVLTree<Profesor*>& profe)
{
	for (auto& entry : fs::directory_iterator("profesoresGuardados"))
	{
		if (entry.path().extension() == ".txt")
		{
			ifstream archivo(entry.path());
			string linea;
			while (getline(archivo, linea))
			{
				cout << linea << endl;
			}
			cout << endl;
		}
	}
	_getch();
}
void Administrador::anadir_profesores(AVLTree<Profesor*>& profe)
{
	string codigo, contraseña, nombre, apellido, correo, id; int tiempoEnCoursera, reputacion;
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
	guardar(usprofe, codigo);
	string name = "profesoresGuardados/" + codigo + ".txt";
	ofstream archivo(name, ios::app);
	if (archivo.is_open()) {
		archivo << "codigo: " << codigo << endl;
		archivo << "nombre: " << nombre << endl;
		archivo << "apellido: " << apellido << endl;
		archivo << "correo: " << correo << endl;
		archivo << "tiempo_en_cursera: " << tiempoEnCoursera << endl;
		archivo << "id: " << id << endl;
		archivo << "reputacion: " << reputacion << endl;
		archivo << "curso_asignado:" << endl;
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
	string cod, correo;
	cout << "Ingresar el codigo del profesor a eliminar: "; cin >> cod;
	cout << "Ingresar el correo del profesor a eliminar: "; cin >> correo;
	string name = "profesoresGuardados/" + cod + ".txt";
	if (fs::exists(name))
	{
		fs::remove(name);
		cout << "Profesor Eliminado";
	}
	else {
		cout << "Ese profesor no existe" << endl;
	}
	eliminar(correo);
	_getch();
}

void Administrador::ver_instituciones(AVLTree<Institucion*>& inst)
{
	for (auto& entry : fs::directory_iterator("Usuarios"))
	{
		ifstream archivo(entry.path());
		string linea1;
		if (getline(archivo, linea1))
		{
			if (linea1 == "I")
			{
				cout << linea1 << endl;
				string linea;
				while (getline(archivo, linea))
				{
					cout << linea << endl;
				}
				cout << endl;
			}
		}
	}
	_getch();
}
void Administrador::anadir_instituciones(AVLTree<Institucion*>& inst)
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
	guardar(institucion, descripcion);
	cout << "Institucion Añadida" << endl;
	_getch();
}
void Administrador::eliminar_instituciones(AVLTree<Institucion*>& inst)
{
	string correo;
	cout << "Ingresar el correo de la institucion a eliminar: "; cin >> correo;
	eliminar(correo);
	cout << "Institucion eliminada";
	_getch();
}

void Administrador::menu_admin(ListaEnlazada<Curso*>& curso, ListaEnlazada<Estudiante*>& estu, AVLTree<Profesor*>& profe, AVLTree<Institucion*>& inst)
{
	int opc; bool ciclo = true;
	do {
		system("cls");
		cout << "MENU" << endl;
		cout << "Administrar Cursos" << endl;
		cout << " 1. Ver Cursos" << endl;
		cout << " 2. Anadir Cursos" << endl;
		cout << " 3. Eliminar Cursos" << endl;
		cout << "Administrar Estudiantes" << endl;
		cout << " 4. Ver Estudiantes" << endl;
		cout << " 5. Anadir Estudiantes" << endl;
		cout << " 6. Eliminar Estudiantes" << endl;
		cout << "Administrar Profesores" << endl;
		cout << " 7. Ver Profesores" << endl;
		cout << " 8. Anadir Profesores" << endl;
		cout << " 9. Eliminar Profesores" << endl;
		cout << "Administrar Instituciones" << endl;
		cout << " 10. Ver Instituciones" << endl;
		cout << " 11. Anadir Instituciones" << endl;
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
		case 2: anadir_cursos(curso);
			break;
		case 3: eliminar_cursos(curso);
			break;
		case 4: ver_estudiantes(estu);
			break;
		case 5: anadir_estudiantes(estu);
			break;
		case 6: eliminar_estudiantes(estu);
			break;
		case 7: ver_profesores(profe);
			break;
		case 8: anadir_profesores(profe);
			break;
		case 9: eliminar_profesores(profe);
			break;
		case 10: ver_instituciones(inst);
			break;
		case 11: anadir_instituciones(inst);
			break;
		case 12: eliminar_instituciones(inst);
			break;
		default:
			ciclo = false;
			break;
		}

	} while (ciclo == true);
}
