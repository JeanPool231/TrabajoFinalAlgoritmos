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
#include "ListaDobleCircular.h"
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
	ListaDobleCircular<ListaEnlazada<Curso>> bloques;
	ListaEnlazada<Leccion> lecciones;
	void menuPrincipal();
	void registroEstudiante();
	void registroProfesor();
	void registroInstitucion();
	void registrarse();
	void iniciarSesion();
    void menuAdmin();

	void menuInstitucion();

	void gestionProfesoresUI();
	void agregarProfesorUI();
	void quitarProfesorUI();
	void desvincularCursoUI();
	void asignarCursoUI();

	void verInformacionInstitucionUI();
	void verProfesoresInstitucionUI();
	void mostrarcursos();
	void menuVerInformacion();
	void menuInstitucionUI();
	void historialLogsUI();
	void buscarProfesorUI();
	//
	void verEstadisticasUI();
	void verCursosUI();
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
	void seleccionarCurso();
	void iniciarSesionUI();
	void mostrarCursosUI();
	void registroEstudianteUI();
	void registroInstitucionUI();
	void registroUI();
	void inicioUI();
	void bienvenidoUI();
	void estudianteUI();
	void verPerfilUI();
	void buscarCursos();
	void cursoSeleccionado(Curso);
	void verCursoSeleccionadoUI(Curso);

	void buscarCursosUI();
	void buscarCursosUI2(bool, int, vector<Curso>&);
	void cursosEstudianteUI();
	void mostrarBloque8(ListaEnlazada<Curso>);
	void registroProfesorUI();

	void menuProfesorUI();
	void crearCursoUI();
	void gestionleccionesUI();
	void nuevaLeccionUI();

public:
	void iniciarPrograma();
};
