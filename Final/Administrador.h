#pragma once
#include "ListaEnlazada.h"
#include "ListaCircularSimple.h"
#include "AVLTree.h"
#include "Estudiante.h"
#include "Profesor.h"
#include "Institucion.h"
#include "Usuario.h"
#include <conio.h>
using namespace std;

class Administrador
{
public:
	Administrador();
	~Administrador();

	void guardar(Usuario usuario);
	void ver_cursos(ListaEnlazada<Curso*>& curso);
	void anadir_cursos(ListaEnlazada<Curso*>& curso);
	void eliminar_cursos(ListaEnlazada<Curso*>& curso);
	void ver_estudiantes(ListaEnlazada<Estudiante*>& estu);
	void anadir_estudiantes(ListaEnlazada<Estudiante*>& estu);
	void eliminar_estudiantes(ListaEnlazada<Estudiante*>& estu);
	void ver_profesores(AVLTree<Profesor*>& profe);
	void anadir_profesores(AVLTree<Profesor*>& profe);
	void eliminar_profesores(AVLTree<Profesor*>& profe);
	void ver_instituciones(AVLTree<Institucion*>& inst);
	void anadir_instituciones(AVLTree<Institucion*>& inst);
	void eliminar_instituciones(AVLTree<Institucion*>& inst);

	void menu_admin(ListaEnlazada<Curso*>& curso, ListaEnlazada<Estudiante*>& estu, AVLTree<Profesor*>& profe, AVLTree<Institucion*>& inst);
};
