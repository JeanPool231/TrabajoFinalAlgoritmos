#pragma once
#include <string>
using namespace std;

class Curso {
private:
    string nombre;
    //Categoria categoria;
    //int numLecciones;
    //ListaCircular<Leccion*> lecciones;
public:
    Curso();
	~Curso();
    Curso(string nombre);
};

