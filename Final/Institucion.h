#pragma once
#include <string>
#include <vector>
#include "Curso.h"
#include "Profesor.h"
#include "AVLTree.h"
#include "ListaEnlazada.h"

using namespace std;

class Institucion {
private:
    ListaEnlazada<string> logs;
    vector<Curso*> cursos;
    AVLTree<Profesor> profesores;

    string nombre;
    string descripcion;
    int yearderegistro;

public:
    Institucion() {
        nombre = "";
        descripcion = "";
        yearderegistro = 0;
    }
    Institucion(string nombre, string descripcion, int yearderegistro);

    string getnombre();
    string getdescripcion();
    int getyear();

	string getNombre() { return nombre; }
	string getDescripcion() { return descripcion; }
	int getYearRegistro() { return yearderegistro; }


    vector<Curso*>& getcursos() {
        return cursos;
    }

    AVLTree<Profesor>& getprofesores() { 
        return profesores;
    }

    ListaEnlazada<string>& getlogsdeprofes() { 
        return logs; 
    }

    void agregarcurso(Curso* curso);

    void agregarprofesor(Profesor prof); 

    void quitarprofesor(int id);

    void guardarprofenearchivo(Profesor prof); //admininsti
    
    ///////////////////////////////////////////

    void verinformacion();

    void menugestiondeprofes();

    void verhistorial(); //admininsti

    void agregarprofe(); //admininsti

    void quitarprofes(); //admininsti

    void asignarcursosalprofe(); //admininsti

    void desvincularprofes(); //admininsti

    void vercursos();

    void verestadisticas();
    
};
