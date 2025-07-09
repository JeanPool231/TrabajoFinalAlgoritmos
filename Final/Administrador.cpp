#include "Administrador.h"
#include <filesystem>
namespace fs = std::filesystem;

void posicion_color(int y, int x, string color)
{
	string codigoColor = "0";

	if (color == "negro")        codigoColor = "30";
	else if (color == "rojo")    codigoColor = "31";
	else if (color == "verde")   codigoColor = "32";
	else if (color == "amarillo")codigoColor = "33";
	else if (color == "azul")    codigoColor = "34";
	else if (color == "magenta") codigoColor = "35";
	else if (color == "cyan")    codigoColor = "36";
	else if (color == "blanco")  codigoColor = "37";
	else if (color == "brillante") codigoColor = "1";
	else if (color == "subrayado") codigoColor = "4";
	else if (color == "inverso") codigoColor = "7";

	std::cout << "\033[" << y << ";" << x << "H"
		<< "\033[" << codigoColor << "m";
}

void cuadro()
{
	posicion_color(1,5,"cyan"); cout << " -------------------------------------------------------------------------------------------------------- " << endl;
	for (int i = 0; i < 24; i++)
	{
		posicion_color(2+i, 5, "cyan"); cout << "|||                                                                                                    |||" << endl;
	}
	posicion_color(26, 5, "cyan"); cout << "  ------------------------------------------------------------------------------------------------------  " << endl;
	posicion_color(27, 5, "cyan"); cout << " |Presione cualquier tecla para continuar...                                                            | " << endl;
	posicion_color(28, 5, "cyan"); cout << "  ------------------------------------------------------------------------------------------------------  " << endl;
}

Administrador::Administrador() {}
//Administrador::~Administrador() {}

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
		int i = 0; system("cls"); cuadro();
		if (entry.path().extension() == ".txt")
		{
			ifstream archivo(entry.path());
			string linea;
			while (getline(archivo, linea))
			{
				posicion_color(10+i, 10, "blanco"); cout << linea << endl;
				i++;
			}
			_getch();
		}
	}
	_getch();
}
void Administrador::anadir_cursos(ListaEnlazada<Curso*>& curso)
{
	cuadro();
	int opc, num = 13;
	string nombre, id, categoria, descripcion, fechaCreacion, cod_profe, titulo;
	int duracionHoras, cantidadInscritos, numLecciones;
	double costo;
	posicion_color(3, 10, "blanco"); cout << "Ingrese nombre del curso a agregar: "; cin.ignore(); getline(cin, nombre);
	posicion_color(4, 10, "blanco"); cout << "Ingrese ID del curso a agregar: "; cin >> id;
	posicion_color(5, 10, "blanco"); cout << "Ingrese categoria del curso a agregar: "; cin.ignore(); getline(cin, categoria);
	posicion_color(6, 10, "blanco"); cout << "Ingrese descripcion del curso a agregar: "; cin.ignore(); getline(cin, descripcion);
	posicion_color(7, 10, "blanco"); cout << "Ingrese la fecha de la creacion del curso a agregar: "; cin >> fechaCreacion;
	posicion_color(8, 10, "blanco"); cout << "Ingrese duracion en horas del curso a agregar: "; cin >> duracionHoras;
	posicion_color(9, 10, "blanco"); cout << "Ingrese la cantidad de inscritos del curso a agregar: "; cin >> cantidadInscritos;
	posicion_color(10, 10, "blanco"); cout << "Ingrese el costo del curso a agregar: "; cin >> costo;
	posicion_color(11, 10, "blanco"); cout << "Ingrese el codigo del profesor del curso a agregar: "; cin >> cod_profe;
	posicion_color(12, 10, "blanco"); cout << "Ingrese el numero de lecciones del curso a agregar: "; cin >> numLecciones;
	Curso* c = new Curso(nombre, id, categoria, descripcion, fechaCreacion, duracionHoras, cantidadInscritos, numLecciones, costo, cod_profe);
	Leccion* leccion = new Leccion[numLecciones];
	for (int i = 0; i < numLecciones; i++)
	{
		posicion_color(13+i, 10, "blanco"); cout << "Ingresar titulo de la leccion " << i + 1 << ": "; cin >> titulo;
		leccion[i].setTitulo(titulo);
		num += 1;
	}
	posicion_color(num, 10, "blanco"); cout << "Donde quiere agregar el nuevo curso: Inicio(1) o Final (2): "; cin >> opc;
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
		posicion_color(num+1, 10, "blanco"); cout << "Error al abrir el archivo para guardar.\n";
	}
	posicion_color(num + 1, 10, "blanco"); cout << "Curso A" << char(241) << "adido";
	_getch();
}
void Administrador::eliminar_cursos(ListaEnlazada<Curso*>& curso)
{
	cuadro();
	int ID;
	posicion_color(3, 10, "blanco"); cout << "Ingresar ID del curso a eliminar: "; cin >> ID;
	string name = "cursosCreados/" + to_string(ID) + ".txt";
	curso.eliminarPrimero();
	if (fs::exists(name))
	{
		fs::remove(name);
		posicion_color(4, 10, "blanco"); cout << "Curso Eliminado";
	}
	else {
		posicion_color(4, 10, "blanco"); cout << "Ese curso no existe" << endl;
	}
	_getch();
}

void Administrador::ver_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	for (auto& entry : fs::directory_iterator("estudiantesCreados"))
	{
		int i = 0; system("cls"); cuadro();
		if (entry.path().extension() == ".txt")
		{
			ifstream archivo(entry.path());
			string linea;
			while (getline(archivo, linea))
			{
				posicion_color(10 + i, 10, "blanco"); cout << linea << endl;
				i++;
			}
			_getch();
		}
	}
	_getch();
}
void Administrador::anadir_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	cuadro();
	string correo, contrasena, nombre, apellido, codigo;
	posicion_color(3, 10, "blanco"); cout << "Ingresar correo del estudiante a agregar: "; cin >> correo;
	posicion_color(4, 10, "blanco"); cout << "Ingresar la contraseña del estudiante a agregar: "; cin >> contrasena;
	posicion_color(5, 10, "blanco"); cout << "Ingresar el nombre del estudiante a agregar: "; cin.ignore(); getline(cin, nombre);
	posicion_color(6, 10, "blanco"); cout << "Ingresar el apellido del estudiante a agregar: "; cin.ignore(); getline(cin, apellido);
	posicion_color(7, 10, "blanco"); cout << "Ingresar el codigo del estudiante a agregar: "; cin >> codigo;
	Estudiante* est = new Estudiante(correo, contrasena, nombre, apellido, codigo);
	cout << endl;
	Usuario estudiante = { 'E', correo, contrasena };
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
		posicion_color(8, 10, "blanco"); cout << "Error al abrir el archivo para guardar.\n";
	}
	posicion_color(9, 10, "blanco"); cout << "Estudiante a" << char(241) << "adido";
	_getch();
}
void Administrador::eliminar_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
	cuadro();
	string cod, correo;
	posicion_color(3, 10, "blanco"); cout << "Ingresar el codigo del estudiante a eliminar: "; cin >> cod;
	posicion_color(4, 10, "blanco"); cout << "Ingresar el correo del estudiante a eliminar: "; cin >> correo;
	string name = "estudiantesCreados/" + cod + ".txt";
	if (fs::exists(name))
	{
		fs::remove(name);
		posicion_color(5, 10, "blanco"); cout << "Estudiante Eliminado";
	}
	else {
		posicion_color(5, 10, "blanco"); cout << "Ese profesor no existe" << endl;
	}
	eliminar(correo);
	_getch();
}

void Administrador::ver_profesores(AVLTree<Profesor*>& profe)
{
	for (auto& entry : fs::directory_iterator("profesoresGuardados"))
	{
		int i = 0; system("cls"); cuadro();
		if (entry.path().extension() == ".txt")
		{
			ifstream archivo(entry.path());
			string linea;
			while (getline(archivo, linea))
			{
				posicion_color(10 + i, 10, "blanco"); cout << linea << endl;
				i++;
			}
			_getch();
		}
	}
	_getch();
}
void Administrador::anadir_profesores(AVLTree<Profesor*>& profe)
{
	cuadro();
	string codigo, contrasena, nombre, apellido, correo, id; int tiempoEnCoursera, reputacion;
	posicion_color(3, 10, "blanco"); cout << "Ingrese el codigo del profesor a agregar: "; cin >> codigo;
	posicion_color(4, 10, "blanco"); cout << "Ingrese el nombre del profesor a agregar: "; cin.ignore(); getline(cin, nombre);
	posicion_color(5, 10, "blanco"); cout << "Ingrese el apellido del profesor a agregar: "; cin.ignore(); getline(cin, nombre);
	posicion_color(6, 10, "blanco"); cout << "Ingrese el correo del profesor a agregar: "; cin >> correo;
	posicion_color(7, 10, "blanco"); cout << "Ingrese la contraseña del profesor a agregar: "; cin >> contrasena;
	posicion_color(8, 10, "blanco"); cout << "Ingrese el tiempo en Cursera del profesor a agregar: "; cin >> tiempoEnCoursera;
	posicion_color(9, 10, "blanco"); cout << "Ingrese el ID del profesor a agregar: "; cin >> id;
	posicion_color(10, 10, "blanco"); cout << "Ingrese la reputacion del profesor a agregar: "; cin >> reputacion;
	Profesor* pro = new Profesor(codigo, nombre, apellido, correo, tiempoEnCoursera, id, reputacion);
	cout << endl;
	auto cmp = [](Profesor*& a, Profesor*& b) { return a->getReputacion() < b->getReputacion(); };
	profe.insertar(pro, cmp);
	Usuario usprofe = { 'P', correo, contrasena };
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
		posicion_color(11, 10, "blanco"); cout << "Error al abrir el archivo para guardar.\n";
	}
	posicion_color(11, 10, "blanco"); cout << "Profesor A" << char(241) << "adido";
	_getch();
}
void Administrador::eliminar_profesores(AVLTree<Profesor*>& profe)
{
	cuadro();
	string cod, correo;
	posicion_color(3, 10, "blanco"); cout << "Ingresar el codigo del profesor a eliminar: "; cin >> cod;
	posicion_color(4, 10, "blanco"); cout << "Ingresar el correo del profesor a eliminar: "; cin >> correo;
	string name = "profesoresGuardados/" + cod + ".txt";
	if (fs::exists(name))
	{
		fs::remove(name);
		posicion_color(5, 10, "blanco"); cout << "Profesor Eliminado";
	}
	else {
		posicion_color(5, 10, "blanco"); cout << "Ese profesor no existe" << endl;
	}
	eliminar(correo);
	_getch();
}

void Administrador::ver_instituciones(AVLTree<Institucion*>& inst)
{
	for (auto& entry : fs::directory_iterator("Usuarios"))
	{
		int i = 0; system("cls"); cuadro();
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
					posicion_color(10 + i, 10, "blanco"); cout << linea << endl;
					i++;
				}
				_getch();
			}
		}
	}
	_getch();
}
void Administrador::anadir_instituciones(AVLTree<Institucion*>& inst)
{
	cuadro();
	string nombre, descripcion, correo, contrasena; int yearderegistro;
	posicion_color(3, 10, "blanco"); cout << "Ingrese el nombre de la institucion a agregar: "; cin.ignore(); getline(cin, nombre);
	posicion_color(4, 10, "blanco"); cout << "Ingrese la descripcion de la institucion a agregar: "; cin.ignore(); getline(cin, descripcion);
	posicion_color(5, 10, "blanco"); cout << "Ingrese el año de registro de la institucion a agregar: "; cin >> yearderegistro;
	posicion_color(6, 10, "blanco"); cout << "Ingrese el correo de la institucion a agregar: "; cin >> correo;
	posicion_color(7, 10, "blanco"); cout << "Ingrese la contraseña de la institucion a agregar: "; cin >> contrasena;
	Institucion* ins = new Institucion(nombre, descripcion, yearderegistro);
	auto cmp = [](Institucion*& a, Institucion*& b) { return a->getYearDeRegistro() < b->getYearDeRegistro(); };
	inst.insertar(ins, cmp);
	Usuario institucion = { 'I', correo, contrasena };
	guardar(institucion, descripcion);
	posicion_color(8, 10, "blanco"); cout << "Institucion A" << char(241) << "adida" << endl;
	_getch();

}
void Administrador::eliminar_instituciones(AVLTree<Institucion*>& inst)
{
	cuadro();
	string correo;
	posicion_color(3, 10, "blanco"); cout << "Ingresar el correo de la institucion a eliminar: "; cin >> correo;
	eliminar(correo);
	posicion_color(4, 10, "blanco"); cout << "Institucion eliminada";
	_getch();
}

void Administrador::menu_admin(ListaEnlazada<Curso*>& curso, ListaEnlazada<Estudiante*>& estu, AVLTree<Profesor*>& profe, AVLTree<Institucion*>& inst)
{
	int opc; bool ciclo = true;
	do {
		system("cls");
		posicion_color(5, 30, "azul"); cout << "####   ####   ##  ##  ####   ####   ####   ####   #### " << endl;
		posicion_color(6, 30, "azul"); cout << "##    ##  ##  ##  ##  ## ## ##     ##     ##  ## ##  ##" << endl;
		posicion_color(7, 30, "azul"); cout << "##    ##  ##  ##  ##  ####   ###   ####   ####   ######" << endl;
		posicion_color(8, 30, "azul"); cout << "##    ##  ##  ##  ##  ## ##     ## ##     ## ##  ##  ##" << endl;
		posicion_color(9, 30, "azul"); cout << "####   ####    ####   ##  ## ####   ####  ##  ## ##  ##" << endl;
		posicion_color(10, 30, "brillante"); cout << "                 (Modo Administrador)                  " << endl;

		posicion_color(12, 26, "cyan"); cout << " ------------------------------------------------------------ " << endl;
		posicion_color(13, 26, "cyan"); cout << "|  Administrar Cursos      |      Administrar Estudiantes    |" << endl;
		posicion_color(14, 26, "cyan"); cout << "|   1. Ver Cursos          |       4. Ver Estudiantes        |" << endl;
		posicion_color(15, 26, "cyan"); cout << "|   2. A" << char(241) << "adir Cursos       |       5. A" << char(241) << "adir Estudiantes     |" << endl;
		posicion_color(16, 26, "cyan"); cout << "|   3. Eliminar Cursos     |       6. Eliminar Estudiantes   |" << endl;
		posicion_color(17, 26, "cyan"); cout << "|------------------------------------------------------------|" << endl;
		posicion_color(18, 26, "cyan"); cout << "|  Administrar Profesores  |     Administrar Instituciones   |" << endl;
		posicion_color(19, 26, "cyan"); cout << "|   7. Ver Profesores      |      10. Ver Instituciones      |" << endl;
		posicion_color(20, 26, "cyan"); cout << "|   8. A" << char(241) << "adir Profesores   |      11. A" << char(241) << "adir Instituciones   |" << endl;
		posicion_color(21, 26, "cyan"); cout << "|   9. Eliminar Profesores |      12. Eliminar Instituciones |" << endl;
		posicion_color(22, 26, "cyan"); cout << "|------------------------------------------------------------|" << endl;
		posicion_color(23, 26, "cyan"); cout << "||||||||||||||||||||||||   0. Salir   ||||||||||||||||||||||||" << endl;
		posicion_color(24, 26, "cyan"); cout << "|------------------------------------------------------------|" << endl;
		posicion_color(25, 26, "cyan"); cout << "|                                                            |" << endl;
		posicion_color(26, 26, "cyan"); cout << " ------------------------------------------------------------ " << endl;

		posicion_color(25, 28, "blanco"); cout << "Ingrese una opci" << char(243) << "n: "; cin >> opc;
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
