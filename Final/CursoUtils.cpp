#include "CursoUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
Curso* leerCurso(string ruta) {
    ifstream archivo(ruta);
    Curso* curso = new Curso();
    vector<Leccion> lecciones;
    Leccion* leccion = new Leccion();
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << ruta << '\n';
        system("pause");
        return curso;
    }
    string linea; 
    int i = 1;
    while (getline(archivo, linea)) {
        if (i == 1) {
            curso->setNombre(linea);
        }
        else if (i == 2) {
            curso->setId(linea);
        }
        else if (i == 3) {
            curso->setCategoria(linea);
        }
        else if (i == 4) {
            curso->setDescripcion(linea);
        }
        else if (i == 5) {
            curso->setDuracionHoras(stoi(linea));
        }
        else if (i == 6) {
            curso->setFechaCreacion(linea);
        }
        else if (i >= 7) {
            Leccion* leccion = new Leccion();
            leccion->setTitulo(linea);
            curso->agregarLeccion(leccion);
        }
        i++;
    }

    archivo.close();
    return curso;
}
