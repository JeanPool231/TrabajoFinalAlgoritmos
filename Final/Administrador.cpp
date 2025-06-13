#include "Administrador.h" //Esto es mio


Administrador::Administrador() {}
Administrador::~Administrador() {}

void Administrador::ver_cursos(ListaEnlazada<Curso*>& curso)
{

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
	cout << "Curso Añadido";
	_getch();
}
void Administrador::eliminar_cursos(ListaEnlazada<Curso*>& curso)
{
	curso.eliminarPrimero();
	cout << "Curso Eliminado";
	_getch();
}
void Administrador::ver_estudiantes()
{

}
void Administrador::añadir_estudiantes()
{

}
void Administrador::eliminar_estudiantes()
{

}
void Administrador::ver_profesores(AVLTree<Profesor*>& profe)
{

}
void Administrador::añadir_profesores(AVLTree<Profesor*>& profe)
{
	
}
void Administrador::eliminar_profesores(AVLTree<Profesor*>& profe)
{

}
void Administrador::ver_instituciones()
{

}
void Administrador::añadir_instituciones()
{

}
void Administrador::eliminar_instituciones()
{

}

void Administrador::menu_admin(ListaEnlazada<Curso*>& curso, AVLTree<Profesor*>& profe)
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
		case 4: ver_estudiantes();
			break;
		case 5: añadir_estudiantes();
			break;
		case 6: eliminar_estudiantes();
			break;
		case 7: ver_profesores(profe);
			break;
		case 8: añadir_profesores(profe);
			break;
		case 9: eliminar_profesores(profe);
			break;
		case 10: ver_instituciones();
			break;
		case 11: añadir_instituciones();
			break;
		case 12: eliminar_instituciones();
			break;
		default:
			ciclo = false;
			break;
		}

	} while (ciclo == true);
}