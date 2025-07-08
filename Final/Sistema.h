#pragma once
#include <iostream>
#include "Profesor.h"
#include "Curso.h"
#include "Institucion.h"
#include "HashUtil.h"
#include "ListaEnlazada.h"
#include "ListaDobleEnlazada.h"
#include "Usuario.h"
#include "Estudiante.h"
#include "Profesor.h"
#include "Institucion.h"
#include "Administrador.h"
#include "UI.h"
#include "AdministrarInstituciones.h"
using namespace std;

class Sistema {
private:
	UI disenio;
	Curso curso;
	Estudiante* estudiante = new Estudiante();
	Profesor* profesor = new Profesor();
	Institucion* institucion = new Institucion();
	ListaEnlazada<Curso> cursos;
	ListaEnlazada<Usuario> usuarios;
	ListaEnlazada<Profesor> profesores;
	ListaEnlazada<Estudiante> estudiantes;

	void menuPrincipal();
	void registroEstudiante();
	void registroProfesor();
	void registroInstitucion();
	void registrarse();
	void iniciarSesion();
    void menuAdmin();
	void menuInstitucion();
	void gestionProfesoresUI();
	void verInformacionUI();
	void verEstadisticasUI();
	void verCursosUI();
	void historialLogsUI();
	void cargarprofesBETA(Institucion* institucion);
	//
	bool validarCorreo(string& correo);
	bool validarContrasena(string& contrasena, string& correo);
	void inicializarDatos();
	void menuProfesor();
	void menuEstudiante();
	void cursosEstudiante();
	void perfilEstudiante();
	//void saldoEstudiante();
	void cursosInscritos();
	void iniciarSesionUI();
	void mostrarCursosUI();
	void registroEstudianteUI();
	void registroUI();
	void inicioUI();
	void bienvenidoUI();
	void estudianteUI();
	void verPerfilUI();
	void verCursoSeleccionadoUI(Curso);

public:
	void iniciarPrograma();
};
