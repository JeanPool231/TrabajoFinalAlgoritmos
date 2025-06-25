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
	void añadir_cursos(ListaEnlazada<Curso*>& curso);
	void eliminar_cursos(ListaEnlazada<Curso*>& curso);
	void ver_estudiantes(ListaEnlazada<Estudiante*>& estu);
	void añadir_estudiantes(ListaEnlazada<Estudiante*>& estu);
	void eliminar_estudiantes(ListaEnlazada<Estudiante*>& estu);
	void ver_profesores(AVLTree<Profesor*>& profe);
	void añadir_profesores(AVLTree<Profesor*>& profe);
	void eliminar_profesores(AVLTree<Profesor*>& profe);
	void ver_instituciones(AVLTree<Institucion*>& inst);
	void añadir_instituciones(AVLTree<Institucion*>& inst);
	void eliminar_instituciones(AVLTree<Institucion*>& inst);

	void menu_admin(ListaEnlazada<Curso*>& curso, ListaEnlazada<Estudiante*>& estu, AVLTree<Profesor*>& profe, AVLTree<Institucion*>& inst);
};
