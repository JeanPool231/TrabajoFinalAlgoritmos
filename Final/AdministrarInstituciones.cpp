#include "AdministrarInstituciones.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

AdministrarInstitucion::AdministrarInstitucion() {}
AdministrarInstitucion::~AdministrarInstitucion() {}

string obtenerFechaHoraActual1() {
    time_t ahora = time(0);
    tm tiempo;
    localtime_s(&tiempo, &ahora);

    stringstream ss;
    ss << (tiempo.tm_mday < 10 ? "0" : "") << tiempo.tm_mday << "/"
        << (tiempo.tm_mon + 1 < 10 ? "0" : "") << tiempo.tm_mon + 1 << "/"
        << (tiempo.tm_year + 1900) << " "
        << (tiempo.tm_hour < 10 ? "0" : "") << tiempo.tm_hour << ":"
        << (tiempo.tm_min < 10 ? "0" : "") << tiempo.tm_min << ":"
        << (tiempo.tm_sec < 10 ? "0" : "") << tiempo.tm_sec;

    return ss.str();
}
void AdministrarInstitucion::guardarprofenelarchivo(Profesor prof) {
    ofstream archivo("profesoresGuardados/" + prof.getCodigo() + ".txt");
    archivo << "codigo: " << prof.getCodigo() << "\n";
    archivo << "nombre: " << prof.getNombre() << "\n";
    archivo << "apellido: " << prof.getApellido() << "\n";
    archivo << "correo: " << prof.getCorreo() << "\n";
    archivo << "curso_asignado: ";
    if (!prof.getCursosAsignados().empty())
        archivo << prof.getCursosAsignados()[0] << "\n";
    else
        archivo << "0\n";
    archivo.close();

    ofstream plano("profesoresCreados/" + prof.getCodigo() + ".txt");
    plano << prof.getCodigo() << "\n"
        << prof.getNombre() << "\n"
        << prof.getApellido() << "\n"
        << prof.getCorreo() << "\n0\n0\n";

    if (!prof.getCursosAsignados().empty()) {
        string cursosConcat;
        for (const string& c : prof.getCursosAsignados()) cursosConcat += c + ";";
        cursosConcat.pop_back();
        plano << cursosConcat << "\n";
    }
    else plano << "0\n";
    plano.close();
}

bool AdministrarInstitucion::quitarprofesor2(Institucion& inst, int idx, string& mensaje) {
    auto& arbol = inst.getprofesores();
    ListaEnlazada<Profesor> lista;
    arbol.recorrerInOrden([&](Profesor& p) { lista.insertarAlFinal(p); });

    Nodo<Profesor>* actual = lista.obtenerCabeza();
    for (int i = 0; actual && i < idx; ++i) actual = actual->siguiente;
    if (!actual) return false;

    Profesor objetivo = actual->dato;

        fs::remove("profesoresGuardados/" + objetivo.getCodigo() + ".txt");
        fs::remove("profesoresCreados/" + objetivo.getCodigo() + ".txt");

    AVLTree<Profesor> nuevo;
    arbol.recorrerInOrden([&](Profesor& p) {
        if (p.getCodigo() != objetivo.getCodigo()) {
            nuevo.insertar(p, [](Profesor& a, Profesor& b) {
                return a.getCodigo() < b.getCodigo();
                });
        }
        });
    inst.getprofesores() = nuevo;
    mensaje = "Eliminado: " + objetivo.getNombre() + " " + objetivo.getApellido();

    string log = mensaje + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(log);
    ofstream archivo("logs/logsProfesores.txt", ios::app);
    archivo << log << "\n";
    archivo.close();
    return true;
}

void AdministrarInstitucion::agregarprofesor2(Institucion& inst, const string& codigo, const string& nombre,
    const string& apellido, const string& correo, int tiempo, int id,
    int reputacion, const string& cursoAsignado) {
    Profesor nuevo(codigo, nombre, apellido, correo, tiempo, to_string(id), reputacion);
    if (!cursoAsignado.empty()) nuevo.agregarCurso(cursoAsignado);
    inst.getprofesores().insertar(nuevo, [](Profesor& a, Profesor& b) {
        return a.getCodigo() < b.getCodigo();
        });
    guardarprofenelarchivo(nuevo);
   
    string log = "Agregado: " + nombre + " " + apellido + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(log);
    ofstream archivo("logs/logsProfesores.txt", ios::app);
    archivo << log << "\n";
    archivo.close();

}

ListaEnlazada<Profesor> AdministrarInstitucion::obtenerListaProfes(Institucion& inst) {
    ListaEnlazada<Profesor> lista;
    inst.getprofesores().recorrerInOrden([&](Profesor& p) {
        lista.insertarAlFinal(p);
        });
    return lista;
}

ListaEnlazada<Profesor*> AdministrarInstitucion::obtenerProfesoresSinCurso(Institucion& inst) {
    ListaEnlazada<Profesor*> lista;
    inst.getprofesores().recorrerInOrden([&](Profesor& p) {
        if (p.getCursosAsignados().empty()) lista.insertarAlFinal(&p);
        });
    return lista;
}

ListaEnlazada<Profesor*> AdministrarInstitucion::obtenerProfesoresConCurso(Institucion& inst) {
    ListaEnlazada<Profesor*> lista;
    inst.getprofesores().recorrerInOrden([&](Profesor& p) {
        if (!p.getCursosAsignados().empty()) lista.insertarAlFinal(&p);
        });
    return lista;
}

ListaEnlazada<Curso*> AdministrarInstitucion::obtenerCursosLibres(Institucion& inst) {
    ListaEnlazada<Curso*> libres;
    Nodo<Curso*>* nodo = inst.getcursos().obtenerCabeza();

    while (nodo != nullptr) {
        Curso* c = nodo->dato;
        bool ocupado = false;
        string nombre = c->getNombre();

        inst.getprofesores().recorrerInOrden([&](Profesor& p) {
            for (const string& asignado : p.getCursosAsignados()) {
                if (asignado == nombre) {
                    ocupado = true;
                    break;
                }
            }
            });

        if (!ocupado) libres.insertarAlFinal(c);

        nodo = nodo->siguiente;
    }

    return libres;
}

bool AdministrarInstitucion::asignarCursoAProfesor(Institucion& inst, int idxProfe, int idxCurso, string& mensaje) {
    ListaEnlazada<Profesor*> profes = obtenerProfesoresSinCurso(inst);
    ListaEnlazada<Curso*> cursos = obtenerCursosLibres(inst);
    Nodo<Profesor*>* pNode = profes.obtenerCabeza();
    Nodo<Curso*>* cNode = cursos.obtenerCabeza();
    for (int i = 0; i < idxProfe && pNode; ++i) pNode = pNode->siguiente;
    for (int i = 0; i < idxCurso && cNode; ++i) cNode = cNode->siguiente;
    if (!pNode || !cNode) return false;

    Profesor* profe = pNode->dato;
    string nombreCurso = cNode->dato->getNombre();

    profe->agregarCurso(nombreCurso);
    guardarprofenelarchivo(*profe);
    cout << "Curso asignado.";
    string log = "Asignado: " + profe->getNombre() + " → " + nombreCurso + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(log);
    ofstream archivo("logs/logsProfesores.txt", ios::app);
    archivo << log << "\n";
    archivo.close();
    return true;
}

bool AdministrarInstitucion::desvincularCursoDeProfesor(Institucion& inst, int idxProfe, string cursoAEliminar, string& mensaje) {
    ListaEnlazada<Profesor*> profes = obtenerProfesoresConCurso(inst);
    Nodo<Profesor*>* nodo = profes.obtenerCabeza();
    for (int i = 0; i < idxProfe && nodo; ++i) nodo = nodo->siguiente;
    if (!nodo) return false;

    Profesor* profe = nodo->dato;
    profe->quitarCurso(cursoAEliminar);
    guardarprofenelarchivo(*profe);
    string log = "Desvinculado: " + profe->getNombre() + " ← " + cursoAEliminar + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(log);
    ofstream archivo("logs/logsProfesores.txt", ios::app);
    archivo << log << "\n";
    archivo.close();

    cout << "Curso desvinculado.";
    return true;
}

void AdministrarInstitucion::mostrarLogsPorFiltro(const string& filtro, const string& valor, ListaEnlazada<string>& resultado) {
    ifstream archivo("logsp/logsProfesores.txt");
    string linea;
    while (getline(archivo, linea)) {
        if (filtro == "fecha" && linea.find(valor) != string::npos) resultado.insertarAlFinal(linea);
        else if (filtro == "accion" && linea.find(valor) != string::npos) resultado.insertarAlFinal(linea);
        else if (filtro == "todo") resultado.insertarAlFinal(linea);
    }
}

void AdministrarInstitucion::obtenerResumenCursos(Institucion& inst, ListaEnlazada<string>& resumen) {
    Nodo<Curso*>* nodo = inst.getcursos().obtenerCabeza();

    while (nodo != nullptr) {
        Curso* curso = nodo->dato;
        string profe = "No asignado";

        inst.getprofesores().recorrerInOrden([&](Profesor& p) {
            for (const string& c : p.getCursosAsignados()) {
                if (c == curso->getNombre()) {
                    profe = p.getNombre();
                    break;
                }
            }
            });

        resumen.insertarAlFinal(curso->getNombre() + " | Profesor: " + profe);
        nodo = nodo->siguiente;
    }
}

void AdministrarInstitucion::obtenerResumenProfesores(Institucion& inst, ListaEnlazada<string>& resumen) {
    inst.getprofesores().recorrerInOrden([&](Profesor& p) {
        resumen.insertarAlFinal(p.getCodigo() + " - " + p.getNombre() + " " + p.getApellido());
        });
}

void AdministrarInstitucion::obtenerListadoCursosConProfesor(Institucion& inst, ListaEnlazada<string>& listado) {
    Nodo<Curso*>* nodo = inst.getcursos().obtenerCabeza();

    while (nodo != nullptr) {
        Curso* curso = nodo->dato;
        string profe = "No asignado";

        inst.getprofesores().recorrerInOrden([&](Profesor& p) {
            for (const string& c : p.getCursosAsignados()) {
                if (c == curso->getNombre()) {
                    profe = p.getNombre();
                    break;
                }
            }
            });

        listado.insertarAlFinal("Curso: " + curso->getNombre() + " | Profesor: " + profe);
        nodo = nodo->siguiente;
    }
}

size_t AdministrarInstitucion::contarCursos(Institucion& inst) {
    size_t count = 0;
    Nodo<Curso*>* nodo = inst.getcursos().obtenerCabeza();
    while (nodo != nullptr) {
        count++;
        nodo = nodo->siguiente;
    }
    return count;
}