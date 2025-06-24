#include "AdministradorProfesores.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <sstream>
using namespace std;
namespace fs = filesystem;

AdministradorProfesores::AdministradorProfesores()
    : arbolProfesores([](Profesor p) {}, [](Profesor a, Profesor b) { return a.getCodigo() < b.getCodigo(); }) {}

void AdministradorProfesores::cargarProfesoresDesdeArchivos() {
    fs::create_directory("profesoresGuardados");
    for (auto& entry : fs::directory_iterator("profesoresGuardados")) {
        if (entry.path().extension() != ".txt") continue;

        ifstream archivo(entry.path());
        if (!archivo.is_open()) continue;

        string codigo, nombre, apellido, correo, cursoAsignado;
        int tiempo, id, reputacion;
        string linea;
        while (getline(archivo, linea)) {
            if (linea.find("codigo:") != string::npos) codigo = linea.substr(8);
            else if (linea.find("nombre:") != string::npos) nombre = linea.substr(8);
            else if (linea.find("apellido:") != string::npos) apellido = linea.substr(10);
            else if (linea.find("correo:") != string::npos) correo = linea.substr(8);
            else if (linea.find("tiempo_en_coursera:") != string::npos) tiempo = stoi(linea.substr(22));
            else if (linea.find("id:") != string::npos) id = stoi(linea.substr(4));
            else if (linea.find("reputacion:") != string::npos) reputacion = stoi(linea.substr(13));
            else if (linea.find("curso_asignado:") != string::npos) cursoAsignado = linea.substr(17);
        }
        Profesor prof(codigo, nombre, apellido, correo, tiempo, id, reputacion);
        prof.asignarCurso(cursoAsignado);

        arbolProfesores.insertar(prof);
        hashCorreos.insert(correo);
    }
}

void AdministradorProfesores::guardarProfesor(Profesor& prof) {
    fs::create_directory("profesoresGuardados");
    string ruta = "profesoresGuardados/" + prof.getCodigo() + ".txt";
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivo << "codigo: " << prof.getCodigo() << "\n";
    archivo << "nombre: " << prof.getNombre() << "\n";
    archivo << "apellido: " << prof.getApellido() << "\n";
    archivo << "correo: " << prof.getCorreo() << "\n";
    archivo << "tiempo_en_coursera: " << prof.getTiempoEnCoursera() << "\n";
    archivo << "id: " << prof.getId() << "\n";
    archivo << "reputacion: " << prof.getReputacion() << "\n";
    archivo << "curso_asignado: " << prof.getCursoAsignado() << "\n";
}

void AdministradorProfesores::agregarProfesorInteractivo(vector<Curso*>& cursosDisponibles) {
    string codigo, nombre, apellido, correo;
    int tiempo, id, reputacion;

    cout << "Codigo: "; getline(cin, codigo);
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Apellido: "; getline(cin, apellido);
    do {
        cout << "Correo: "; getline(cin, correo);
        if (!regex_match(correo, regex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$"))) {
            cout << "Correo inválido, intente de nuevo.\n";
        }
    } while (!regex_match(correo, regex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$")));

    cout << "Años en Coursera: "; cin >> tiempo; cin.ignore();
    cout << "ID: "; cin >> id; cin.ignore();
    cout << "Reputacion: "; cin >> reputacion; cin.ignore();

    cout << "\nCursos disponibles:\n";
    for (int i = 0; i < cursosDisponibles.size(); ++i) {
        cout << i + 1 << ". " << cursosDisponibles[i]->getNombre() << "\n";
    }
    cout << "0. No asignar curso\n";
    int opc;
    cout << "Seleccione: ";
    cin >> opc; cin.ignore();

    string curso = "";
    if (opc > 0 && opc <= cursosDisponibles.size()) {
        curso = cursosDisponibles[opc - 1]->getNombre();
    }

    Profesor nuevo(codigo, nombre, apellido, correo, tiempo, id, reputacion);
    nuevo.asignarCurso(curso);
    arbolProfesores.insertar(nuevo);
    hashCorreos.insert(correo);
    guardarProfesor(nuevo);

    string log = "Agregado: " + nombre + " " + apellido;
    logs.insertarAlFinal(log);
}

void AdministradorProfesores::mostrarLogs() {
    logs.recorrer([](string mensaje) {
        cout << "- " << mensaje << "\n";
        });
}

void AdministradorProfesores::mostrarProfesoresEnOrden() {
    arbolProfesores.enOrden();
}

ArbolBB<Profesor>& AdministradorProfesores::getArbol() {
    return arbolProfesores;
}

TEMPListaEnlazada<string>& AdministradorProfesores::getLogs() {
    return logs;
}
