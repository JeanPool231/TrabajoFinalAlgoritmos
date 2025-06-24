#include "AdministradorProfesores.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "CursoUtils.h"
using namespace std;
namespace fs = std::filesystem;


void AdministradorProfesores::mostrarLogs() {
    logs.recorrer([](string msg) {
        cout << "[LOG] " << msg << endl;
        });
}

void AdministradorProfesores::mostrarProfesoresEnOrden() {
    cout << "(Reutilizado para mostrar cursos ordenados por nombre)" << endl;
    arbolProfesores.enOrden();
}

ArbolBB<Profesor>& AdministradorProfesores::getArbol() {
    return arbolProfesores;
}

TEMPListaEnlazada<string>& AdministradorProfesores::getLogs() {
    return logs;
}




// NUEVO: Gestionar cursos desde este "administrador de profesores"
void AdministradorProfesores::cargarCursosDesdeCarpeta(string ruta, vector<Curso*>& cursosRef) {
    for (auto entry : fs::directory_iterator(ruta)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            Curso* curso = leerCursoDesdeArchivo(entry.path().string());
            cursosRef.push_back(curso);
            logs.insertarAlFinal("Curso cargado: " + curso->getNombre());
        }
    }
}

void AdministradorProfesores::mostrarCursos(const vector<Curso*>& cursosRef) {
    for (Curso* c : cursosRef) {
        cout << "Curso: " << c->getNombre() << " | Categoria: " << c->getCategoria() << endl;
    }
}

void AdministradorProfesores::eliminarCursoPorId(vector<Curso*>& cursosRef, string id) {
    bool eliminado = false;
    for (auto it = cursosRef.begin(); it != cursosRef.end(); ++it) {
        if ((*it)->getId() == id) {
            delete* it;
            cursosRef.erase(it);
            eliminado = true;
            logs.insertarAlFinal("Curso eliminado con ID: " + id);
            break;
        }
    }
    if (eliminado) {
        string ruta = "cursosCreados/" + id + ".txt";
        fs::remove(ruta);
    }
}

void AdministradorProfesores::guardarCursoEnArchivo(Curso* curso) {
    string archivoNombre = "cursosCreados/" + curso->getId() + ".txt";
    ofstream archivo(archivoNombre);
    if (archivo.is_open()) {
        archivo << "[" << curso->getNombre() << "]\n";
        archivo << "id: " << curso->getId() << "\n";
        archivo << "categoria: " << curso->getCategoria() << "\n";
        archivo << "descripcion: " << curso->getDescripcion() << "\n";
        archivo << "duracion: " << curso->getDuracionHoras() << " horas\n";
        archivo << "fecha: " << curso->getFechaCreacion() << "\n";
        archivo << "\n[LECCIONES]\n";

        Nodo<Leccion*>* actual = curso->getLecciones().obtenerCabeza();
        while (actual) {
            archivo << "- " << actual->dato->getTitulo() << "\n";
            actual = actual->siguiente;
        }

        archivo.close();
        logs.insertarAlFinal("Curso guardado: " + curso->getNombre());
    }
    else {
        cerr << "Error al guardar el curso." << endl;
    }
}