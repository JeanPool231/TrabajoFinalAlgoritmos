#pragma once
#include "ListaEnlazada.h"
#include "ListaCircularSimple.h"
#include "AVLTree.h"
#include "Profesor.h"
#include "Curso.h"
#include <conio.h>
using namespace std;

class Administrador
{
public:
	Administrador();
	~Administrador();

	void ver_cursos(ListaEnlazada<Curso*>& curso);
	void añadir_cursos(ListaEnlazada<Curso*>& curso);
	void eliminar_cursos(ListaEnlazada<Curso*>& curso);
	void ver_estudiantes();
	void añadir_estudiantes();
	void eliminar_estudiantes();
	void ver_profesores(AVLTree<Profesor*>& profe);
	void añadir_profesores(AVLTree<Profesor*>& profe);
	void eliminar_profesores(AVLTree<Profesor*>& profe);
	void ver_instituciones();
	void añadir_instituciones();
	void eliminar_instituciones();

	void menu_admin(ListaEnlazada<Curso*>& curso, AVLTree<Profesor*>& profe);
};