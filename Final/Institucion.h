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
    string nombre;
    string descripcion;
    int yearderegistro;
    ListaEnlazada<string> logs;
    vector<Curso*> cursos;
    AVLTree<Profesor> profesores;

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
    vector<Curso*>& getcursos() {
        return cursos;
    }

    // void mostrarprofes();

    void quitarprofes();
    void asignarcursosalprofe();

    void desvincularprofes();
    void guardarprofenearchivo(Profesor prof);
    void agregarprofe(); 


    void verhistorial();

    void agregarcurso(Curso* curso);
    void agregarprofesor(Profesor prof); //
    void quitarprofesor(int id);
    void menugestiondeprofes(); 
    void verinformacion();
    //void verprofesores();
    void vercursos();
    void verestadisticas();
    
};
