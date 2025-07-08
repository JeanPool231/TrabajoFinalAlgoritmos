#include "Administrador.h"
#include <filesystem>
namespace fs = std::filesystem;

Administrador::Administrador() {}
//Administrador::~Administrador() {}

void Administrador::guardar(Usuario usuario, string id) {
}

void Administrador::eliminar(string correo)
{

}

void Administrador::ver_cursos(ListaEnlazada<Curso*>& curso)
{
}
void Administrador::anadir_cursos(ListaEnlazada<Curso*>& curso)
{
}
void Administrador::eliminar_cursos(ListaEnlazada<Curso*>& curso)
{
}

void Administrador::ver_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
}
void Administrador::anadir_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
}
void Administrador::eliminar_estudiantes(ListaEnlazada<Estudiante*>& estu)
{
}

void Administrador::ver_profesores(AVLTree<Profesor*>& profe)
{
}
void Administrador::anadir_profesores(AVLTree<Profesor*>& profe)
{
}
void Administrador::eliminar_profesores(AVLTree<Profesor*>& profe)
{
}

void Administrador::ver_instituciones(AVLTree<Institucion*>& inst)
{
}
void Administrador::anadir_instituciones(AVLTree<Institucion*>& inst)
{
}
void Administrador::eliminar_instituciones(AVLTree<Institucion*>& inst)
{
}

void Administrador::menu_admin(ListaEnlazada<Curso*>& curso, ListaEnlazada<Estudiante*>& estu, AVLTree<Profesor*>& profe, AVLTree<Institucion*>& inst)
{
}
