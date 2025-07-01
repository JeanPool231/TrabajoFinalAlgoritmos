#include "Administrador.h"
#include <filesystem>
namespace fs = std::filesystem;

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

void Administrador::añadir_cursos(ListaEnlazada<Curso*>& curso)
{
	int opc;   
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
	string name = "cursosCreados/" + id + ".txt"; ofstream archivo(name, ios::app);
	if (archivo.is_open()) {
		archivo << "[" << nombre << "]" << endl;
		archivo << "id: " << id << endl;
		archivo << "categoria: " << categoria << endl;
		archivo << "descripcion: " << descripcion << endl;
		archivo << "duracion: " << duracionHoras << endl;
		archivo << "fecha: " << fechaCreacion << endl;
		archivo << endl;
		archivo << "[LECCIONES] " << numLecciones << endl;
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
	string name = "Usuarios/usuarios.txt";
	ifstream archivo(name);
	if (archivo.is_open())
	{
		string linea;
		while (getline(archivo, linea))
		{
			if (!linea.empty() && linea[0] == 'E')
			{
				cout << linea << endl;
				cout << endl;
			}
		}
	}
	_getch();
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
	string name1 = "Usuarios/usuarios.txt", name2 = "Usuarios/usuarios1.txt"; string correo, linea;
	cout << "Ingresar el correo del estudiante a eliminar: "; cin >> correo;
	estu.eliminarPrimero();
	ifstream archivo1(name1); ofstream archivo2(name2);
	while (getline(archivo1, linea))
	{
		if (linea.find(correo) == string::npos)
		{
			archivo2 << linea << endl;
		}
	}
	archivo1.close(); archivo2.close();
	remove(name1.c_str());
	rename(name2.c_str(), name1.c_str());
	cout << "Estudiante Eliminado";
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
void Administrador::añadir_profesores(AVLTree<Profesor*>& profe)
{
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
	string cod;
	cout << "Ingresar el codigo del profesor a eliminar: "; cin >> cod;
	string name = "profesoresGuardados/" + cod + ".txt";
	if (fs::exists(name))
	{
		fs::remove(name);
		cout << "Profesor Eliminado";
	}
	else {
		cout << "Ese profesor no existe" << endl;
	}
	_getch();
}

void Administrador::ver_instituciones(AVLTree<Institucion*>& inst)
{
	string name = "Usuarios/usuarios.txt";
	ifstream archivo(name);
	if (archivo.is_open())
	{
		string linea;
		while (getline(archivo, linea))
		{
			if (!linea.empty() && linea[0] == 'I')
			{
				cout << linea << endl;
				cout << endl;
			}
		}
	}
	_getch();
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
	string name1 = "Usuarios/usuarios.txt", name2 = "Usuarios/usuarios1.txt"; string correo, linea;
	cout << "Ingresar el correo de la institucion a eliminar: "; cin >> correo;
	ifstream archivo1(name1); ofstream archivo2(name2);
	while (getline(archivo1, linea))
	{
		if (linea.find(correo) == string::npos)
		{
			archivo2 << linea << endl;
		}
	}
	archivo1.close(); archivo2.close();
	remove(name1.c_str());
	rename(name2.c_str(), name1.c_str());
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
