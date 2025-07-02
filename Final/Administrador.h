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

void guardar(Usuario usuario); //listo
void ver_cursos(ListaEnlazada<Curso*>& curso); //listo
void añadir_cursos(ListaEnlazada<Curso*>& curso); //listo
void eliminar_cursos(ListaEnlazada<Curso*>& curso); //listo
void ver_estudiantes(ListaEnlazada<Estudiante*>& estu); //listo
void añadir_estudiantes(ListaEnlazada<Estudiante*>& estu); //listo
void eliminar_estudiantes(ListaEnlazada<Estudiante*>& estu);
void ver_profesores(AVLTree<Profesor*>& profe); //listo
void añadir_profesores(AVLTree<Profesor*>& profe); //listo
void eliminar_profesores(AVLTree<Profesor*>& profe); //listo
void ver_instituciones(AVLTree<Institucion*>& inst); //listo
void añadir_instituciones(AVLTree<Institucion*>& inst); //listo
void eliminar_instituciones(AVLTree<Institucion*>& inst);

void menu_admin(ListaEnlazada<Curso*>& curso, ListaEnlazada<Estudiante*>& estu, AVLTree<Profesor*>& profe, AVLTree<Institucion*>& inst);
};
