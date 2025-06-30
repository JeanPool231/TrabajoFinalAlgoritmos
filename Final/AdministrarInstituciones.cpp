#include "AdministrarInstituciones.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include "HashUtil.h"
using namespace std;
namespace fs = std::filesystem;

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

string limpiarespacio(const string& str) {
    string limpio = str;
    limpio.erase(remove_if(limpio.begin(), limpio.end(), ::isspace), limpio.end());
    return limpio;
}

void guardarprofenelarchivo(Profesor prof) {

    fs::create_directory("profesoresGuardados");

    string codigoLimpio = limpiarespacio(prof.getCodigo());
    string ruta = "profesoresGuardados/" + codigoLimpio + ".txt";

    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        return;
    }

    archivo << "codigo: " << prof.getCodigo() << "\n";
    archivo << "nombre: " << prof.getNombre() << "\n";
    archivo << "apellido: " << prof.getApellido() << "\n";
    archivo << "correo: " << prof.getCorreo() << "\n";
    archivo << "tiempo_en_coursera: " << prof.getTiempoEnCoursera() << "\n";
    archivo << "id: " << prof.getId() << "\n";
    archivo << "reputacion: " << prof.getReputacion() << "\n";
    archivo << "curso_asignado: " << prof.getCursoAsignado() << "\n";
    archivo.close();
}


void guardarProfesor(Profesor profesor) {
    filesystem::create_directory("profesoresCreados");

    string ruta = "profesoresCreados/" + profesor.getCodigo() + ".txt";
    ofstream archivo(ruta);

    if (archivo.is_open()) {
        archivo << profesor.getCodigo() << "\n";
        archivo << profesor.getNombre() << "\n";
        archivo << profesor.getApellido() << "\n";
        archivo << profesor.getCorreo() << "\n";
        archivo << profesor.getTiempoEnCoursera() << "\n";
        archivo << profesor.getId() << "\n";
        archivo << profesor.getReputacion() << "\n";
        archivo.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para escritura.\n";
    }
}

void agregarprofesor2(Institucion& inst) {

    vector<Curso*>& cursos = inst.getcursos(); 
    AVLTree<Profesor>& profesores = inst.getprofesores();
    vector<Curso*> disponibles;


    string codigo = "", nombre, apellido, correo, cursoSeleccionado;
    int tiempoEnCoursera = 0, id = 0, reputacion = 0;

    cout << "Ingrese datos del profesor:\n";
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Apellido: "; getline(cin, apellido);
    cout << "Correo: "; getline(cin, correo);
    codigo = HashUtil::generarHash(nombre + to_string(rand() % 10000));
    cout << '\n';
    cout << codigo << '\n';
    system("pause");
    cin.ignore();

    for (auto c : cursos) {
        bool ocupado = false;
        profesores.recorrerInOrden([&](Profesor& p) {
            if (p.getCursoAsignado() == c->getNombre()) ocupado = true;
            });
        if (!ocupado) {
            disponibles.push_back(c);
        }
    }

    cout << "\nCursos\n";
    if (disponibles.empty()) {
        cout << "no hay cursos disponibles para asignarle a un profesor\n";
        cursoSeleccionado = "";
    }
    else {
        cout << "0. No asignar ningun curso\n";
        for (size_t j = 0; j < disponibles.size(); ++j) {
            cout << j + 1 << ". " << disponibles[j]->getNombre() << "\n";
        }

        int opcionCurso;
        cout << "Ingrese el numero del indice para asignarle un curso: ";
        cin >> opcionCurso; cin.ignore();

        if (opcionCurso == 0) {
            cursoSeleccionado = "";
        }
        else if (opcionCurso < 1 || opcionCurso > disponibles.size()) {
            cout << "opcion invalida\n";
            return;
        }
        else {
            cursoSeleccionado = disponibles[opcionCurso - 1]->getNombre();
        }
    }


    Profesor nuevo(codigo, nombre, apellido, correo,
        tiempoEnCoursera, id, reputacion);
    nuevo.asignarCurso(cursoSeleccionado);

    profesores.insertar(nuevo, [](Profesor& a, Profesor& b) {
        return a.getCodigo() < b.getCodigo();
        });
    guardarProfesor(nuevo);
    guardarprofenelarchivo(nuevo);


    string mensaje = "Agregado: " + nombre + " " + apellido + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(mensaje);

    ofstream archivoLogs("logs/logsProfesores.txt", ios::app);
    archivoLogs << mensaje << "\n";
    archivoLogs.close();


}

void mostrarhistorial2(const ListaEnlazada<string>& logs) {
    
    
    string ruta = "logs/logsProfesores.txt";
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "\nno hay ningun log\n";
        return;
    }

    vector<string> logsTotales;
    string linea;
    while (getline(archivo, linea)) {
        logsTotales.push_back(linea);
    }
    archivo.close();

    if (logsTotales.empty()) {
        cout << "\nNo hay ningun dato en el log que mostrar\n";
        return;
    }

    int opcion;
    do {
        cout << "\nHistorial\n";
        cout << "1. Ver todos los logs\n";
        cout << "2. Filtrar por la fecha\n";
        cout << "3. Filtrar por cualquier accion\n";
        cout << "4. Volver al menu anterior\n";
        cout << "Ponga su opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            for (const string& l : logsTotales) {
                cout << "- " << l << "\n";
            }
        }
        else if (opcion == 2) {
            cout << "Ingrese la fecha (Dia/Mes/Año) (no letras): "; //bug letras 
            string fecha;
            getline(cin, fecha);

            bool encontrado = false;
            for (const string& l : logsTotales) {
                if (l.find(fecha) != string::npos) {
                    cout << "- " << l << "\n";
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << "Error, ejemplo : 26/05/2026\n";
            }
        }
        else if (opcion == 3) {
            cout << "Ingrese la accion : ";
            string palabra;
            getline(cin, palabra);

            bool encontrado = false;
            for (const string& l : logsTotales) {
                if (l.find(palabra) != string::npos) {
                    cout << "- " << l << "\n";
                    encontrado = true;
                }
            }
            if (!encontrado) {
                cout << "Error, ejemplos : Agregado, Eliminado, Curso Asignado, Curso desvinculado\n";
            }
        }
        else if (opcion != 4) {
            cout << "erorr\n";
        }

    } while (opcion != 4);
}


void quitarprofesor2(Institucion& inst) {
    vector<Curso*>& cursos = inst.getcursos();
    AVLTree<Profesor>& profesores = inst.getprofesores();
    vector<Profesor> todos;

    profesores.recorrerInOrden([&](Profesor& p) {
        todos.push_back(p);
        });

    if (todos.empty()) {
        cout << "No hay profesores para eliminar.\n";
        return;
    }

    cout << "\nLista de los profesores:\n";
    for (size_t i = 0; i < todos.size(); ++i) {
        cout << i + 1 << ". " << todos[i].getCodigo() << " | " << todos[i].getNombre();
        if (!todos[i].getCursoAsignado().empty())
            cout << " (Curso: " << todos[i].getCursoAsignado() << ")";
        cout << endl;
    }

    int opcion;
    cout << "Ingrese el indice del profesor a eliminar: ";
    cin >> opcion; cin.ignore();

    if (opcion < 1 || opcion > todos.size()) {
        cout << "opcion incorrecta\n";
        return;
    }

    string codigo = limpiarespacio(todos[opcion - 1].getCodigo());
    fs::remove("profesoresGuardados/" + codigo + ".txt");


    AVLTree<Profesor> nuevoArbol;
    profesores.recorrerInOrden([&](Profesor& p) {
        if (p.getCodigo() != codigo) {
            nuevoArbol.insertar(p, [](Profesor& a, Profesor& b) {
                return a.getCodigo() < b.getCodigo();
                });
        }
        });
    profesores = nuevoArbol;

    cout << "Profesor eliminado \n";

    string mensaje = "Eliminado: " + todos[opcion - 1].getNombre() + " " + todos[opcion - 1].getApellido() + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(mensaje);

    ofstream archivoLogs("logs/logsProfesores.txt", ios::app);
    archivoLogs << mensaje << "\n";
    archivoLogs.close();

}

void asignarcursoalprofe2(Institucion& inst) {
    vector<Curso*>& cursos = inst.getcursos();
    AVLTree<Profesor>& profesores = inst.getprofesores();
    vector<Profesor*> sinCurso;


    profesores.recorrerInOrden([&](Profesor& p) {
        if (p.getCursoAsignado().empty()) sinCurso.push_back(&p);
        });

    if (sinCurso.empty()) {
        cout << "Todos los profesores tienen un curso asignado\n";
        return;
    }

    cout << "\nProfesores sin algun curso asignado:\n";
    for (size_t i = 0; i < sinCurso.size(); ++i) {
        cout << i + 1 << ". " << sinCurso[i]->getCodigo() << " | " << sinCurso[i]->getNombre() << endl;
    }

    int opcionprof;
    cout << "Ingrese el indice del profesor: ";
    cin >> opcionprof; cin.ignore();
    if (opcionprof < 1 || opcionprof > sinCurso.size()) {
        cout << "opcion invalida\n";
        return;
    }

    vector<Curso*> libres;
    for (auto c : cursos) {
        bool ocupado = false;
        profesores.recorrerInOrden([&](Profesor& p) {
            if (p.getCursoAsignado() == c->getNombre()) ocupado = true;
            });
        if (!ocupado) libres.push_back(c);
    }

    if (libres.empty()) {
        cout << "no hay cursos disponibles\n";
        return;
    }

    cout << "\nCursos disponibles:\n";
    for (size_t i = 0; i < libres.size(); ++i) {
        cout << i + 1 << ". " << libres[i]->getNombre() << endl;
    }

    int opcionCurso;
    cout << "Seleccione el numero de curso: ";
    cin >> opcionCurso; cin.ignore();
    if (opcionCurso < 1 || opcionCurso > libres.size()) {
        cout << "opcion invalida\n";
        return;
    }

    sinCurso[opcionprof - 1]->asignarCurso(libres[opcionCurso - 1]->getNombre());
    guardarprofenelarchivo(*sinCurso[opcionprof - 1]);
    cout << "Curso asignado.\n";

    string mensaje = "Curso asignado: " + sinCurso[opcionprof - 1]->getNombre() + " → " + libres[opcionCurso - 1]->getNombre() + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(mensaje);

    ofstream archivoLogs("logs/logsProfesores.txt", ios::app);
    archivoLogs << mensaje << "\n";
    archivoLogs.close();


}

void desvincularcursoalprofe2(Institucion& inst) {
    vector<Curso*>& cursos = inst.getcursos();
    AVLTree<Profesor>& profesores = inst.getprofesores();
    vector<Profesor*> conCurso;
    profesores.recorrerInOrden([&](Profesor& p) {
        if (!p.getCursoAsignado().empty()) conCurso.push_back(&p);
        });

    if (conCurso.empty()) {
        cout << "Ningun profesor tiene algun curso asignado\n";
        return;
    }

    cout << "\nLista de profes con curso:\n";
    for (size_t i = 0; i < conCurso.size(); ++i) {
        cout << i + 1 << ". " << conCurso[i]->getCodigo() << " | " << conCurso[i]->getNombre()
            << " (" << conCurso[i]->getCursoAsignado() << ")\n";
    }

    int opcion;
    cout << "Seleccione un profesor a desvincular: ";
    cin >> opcion; cin.ignore();
    if (opcion < 1 || opcion > conCurso.size()) {
        cout << "opcion incorrecta\n";
        return;
    }

    conCurso[opcion - 1]->quitarCurso();
    guardarprofenelarchivo(*conCurso[opcion - 1]);
    cout << "Curso desvinculado\n";

    string mensaje = "Curso desvinculado: " + conCurso[opcion - 1]->getNombre() + " | " + obtenerFechaHoraActual1();
    inst.getlogsdeprofes().insertarAlFinal(mensaje);

    ofstream archivoLogs("logs/logsProfesores.txt", ios::app);
    archivoLogs << mensaje << "\n";
    archivoLogs.close();
}
