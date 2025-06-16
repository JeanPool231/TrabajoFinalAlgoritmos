#pragma once
#include <string>
#include <vector>
#include "Curso.h"
#include "Profesor.h"
#include "AVLTree.h"

using namespace std;

class Institucion {
private:
    string nombre;
    string descripcion;
    int yearderegistro;

    vector<Curso*> cursos;
    AVLTree<Profesor> profesores;

public:
    Institucion(string nombre, string descripcion, int yearderegistro);

    string getnombre();
    string getdescripcion();
    int getyear();
    vector<Curso*>& getcursos() {
        return cursos;
    }


    void quitarprofes();
    void asignarcursosalprofe();

    void desvincularprofes();
    void guardarprofenearchivo(Profesor prof);
    void agregarprofe(); 

    void agregarcurso(Curso* curso);
    void agregarprofesor(Profesor prof);
    void quitarprofesor(int id);
    void menugestiondeprofes(); 
    void verinformacion();
    //void verprofesores();
    void vercursos();
    void verestadisticas();
    
};
