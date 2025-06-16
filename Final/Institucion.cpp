#include "Institucion.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <regex>
#include <fstream>
#include <filesystem>

Institucion::Institucion(string nombre, string descripcion, int yearderegistro)
    : nombre(nombre), descripcion(descripcion), yearderegistro(yearderegistro) {}

string Institucion::getnombre() { return nombre; }
string Institucion::getdescripcion() { return descripcion; }
int Institucion::getyear() { return yearderegistro; }

void Institucion::agregarcurso(Curso* curso) {
    cursos.push_back(curso);
}

void Institucion::agregarprofesor(Profesor prof) {
    profesores.insertar(prof, [](Profesor& a, Profesor& b) {
        return a.getId() < b.getId();
        });
}

void Institucion::quitarprofesor(int id) {
    cout << "\n";
}

void Institucion::verinformacion() {
    cout << "\nInformacion de la institucion\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Se registro en: " << yearderegistro << endl;

    //lista de los cursos
    cout << "\nCursos \n";
    if (cursos.empty()) {
        cout << "no se encontraron cursos registrados\n";
    }
    else {
        vector<Curso*> ordenados = cursos;
        sort(ordenados.begin(), ordenados.end(), [](Curso* a, Curso* b) {
            return a->getNombre() < b->getNombre();
            });

        int i = 1;
        for (auto curso : ordenados) {
            cout << i++ << ". " << curso->getNombre()
                << " | Categoría: " << curso->getCategoria()
                << " | Fecha: " << curso->getFechaCreacion()
                << " | Descripción: " << curso->getDescripcion() << endl;
        }
    }

    // lista de profes
    cout << "\nProfesores\n";
    if (profesores.estaVacio()) {
        cout << "no hay ningun profesor registrado\n";
    }
    else {
        profesores.recorrerInOrden([](Profesor& p) {
            cout << "\n- Codigo: " << p.getCodigo()
                << "\n  Nombre: " << p.getNombre() << " " << p.getApellido()
                << "\n  Correo: " << p.getCorreo()
           /*     << "\n  Sexo: " << p.getSexo()
                << "\n  Estado Civil: " << p.getEstadoCivil()
                << "\n  Edad: " << p.getEdad()*/
                << "\n  Años en coursera: " << p.getTiempoEnCoursera()
                << "\n  ID: " << p.getId()
                << "\n  Reputacion: " << p.getReputacion()
                << "\n  Curso asignado: "
                << (p.getCursoAsignado().empty() ? "no asignado" : p.getCursoAsignado())
                << endl;
            });
    }
}


void Institucion::menugestiondeprofes() {
    int subop;
    do {
        cout << "\nGestion de profesores\n";
        cout << "1. Agregar profesor\n";
        cout << "2. Quitar profesor\n";
        cout << "3. Asignar un curso a un profesor existente\n";
        cout << "4. Desvincular al profesor de su curso\n";
        cout << "5. Volver\n";
        cout << "Ingrese una opcion ";
        cin >> subop;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (subop) {
        case 1: agregarprofe(); break;
        case 2: quitarprofes(); break;
        case 3: asignarcursosalprofe(); break;
        case 4: desvincularprofes(); break;
        case 5: break;
        default: cout << "opcion no valida\n"; break;
        }
    } while (subop != 5);
}

void Institucion::guardarprofenearchivo(Profesor prof) {
    namespace fs = std::filesystem;
    fs::create_directory("profesoresGuardados");
    string ruta = "profesoresGuardados/" + prof.getCodigo() + ".txt";
    ofstream archivo(ruta);
    if (!archivo.is_open()) return;

    archivo << "codigo: " << prof.getCodigo() << "\n";
    archivo << "nombre: " << prof.getNombre() << "\n";
    archivo << "apellido: " << prof.getApellido() << "\n";
    archivo << "correo: " << prof.getCorreo() << "\n";
 /*   archivo << "sexo: " << prof.getSexo() << "\n";
    archivo << "estado_civil: " << prof.getEstadoCivil() << "\n";
    archivo << "edad: " << prof.getEdad() << "\n";*/
    archivo << "tiempo_en_coursera: " << prof.getTiempoEnCoursera() << "\n";
    archivo << "id: " << prof.getId() << "\n";
    archivo << "reputacion: " << prof.getReputacion() << "\n";
    archivo << "curso_asignado: " << prof.getCursoAsignado() << "\n";
    archivo.close();
}
void Institucion::agregarprofe() {
    string codigo, nombre, apellido, correo, cursoSeleccionado;
    char sexo, estadoCivil;
    int edad, tiempoEnCoursera, id, reputacion;

    cout << "Ingrese datos del profesor:\n";
    cout << "Codigo: "; getline(cin, codigo);
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Apellido: "; getline(cin, apellido);

    do {
        cout << "Correo : ";
        getline(cin, correo);
        if (!regex_match(correo, regex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$"))) {
            cout << "Ese @ medio dudoso ingrese otro uno que si exista\n";
        }
    } while (!regex_match(correo, regex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$")));

    do {
        cout << "Sexo (M/F): ";
        cin >> sexo;
        sexo = toupper(sexo);
        cin.ignore();
        if (sexo != 'M' && sexo != 'F') {
            cout << "No conozco el sexo '" << sexo << "' , ingrese uno valido.\n";
        }
    } while (sexo != 'M' && sexo != 'F');

    do {
        cout << "Estado civil (S/C): ";
        cin >> estadoCivil;
        estadoCivil = toupper(estadoCivil);
        cin.ignore();
        if (estadoCivil != 'S' && estadoCivil != 'C') {
            cout << "incorrecto ingrese uno valido\n";
        }
    } while (estadoCivil != 'S' && estadoCivil != 'C');

    do {
        cout << "Edad: ";
        cin >> edad;
        cin.ignore();
        if (edad < 25) {
            cout << "Tiene que tener mas de 25\n";
        }
    } while (edad < 25);

    cout << "Años en Coursera: "; cin >> tiempoEnCoursera; cin.ignore();
    cout << "ID: "; cin >> id; cin.ignore();
    cout << "Reputacion (0/100): "; cin >> reputacion; cin.ignore();

    vector<Curso*> disponibles;
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

    guardarprofenearchivo(nuevo);
    cout << "Profesor agregado correctamente '" << cursoSeleccionado << "'\n";
}


void Institucion::quitarprofes() {
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

    string codigo = todos[opcion - 1].getCodigo();

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
}

void Institucion::asignarcursosalprofe() {
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
    cout << "Curso asignado.\n";
}

void Institucion::desvincularprofes() {
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
    cout << "Curso desvinculado\n";
}

void Institucion::vercursos() {
    if (cursos.empty()) {
        cout << "\n(No hay cursos registrados)\n";
        return;
    }

    vector<Curso*> ordenados = cursos;
    sort(ordenados.begin(), ordenados.end(), [](Curso* a, Curso* b) {
        return a->getNombre() < b->getNombre();
        });

    cout << "\nCursos publicados :\n";
    int i = 1;
    for (auto curso : ordenados) {
        string profesorAsignado = "(sin ningun profesor asignado)";

        profesores.recorrerInOrden([&](Profesor& p) {
            if (p.getCursoAsignado() == curso->getNombre()) {
                profesorAsignado = p.getNombre() + " " + p.getApellido();
            }
            });

        cout << i++ << ". " << curso->getNombre() << " | "
            << curso->getCategoria() << " | "
            << curso->getDescripcion() << "\n    "
            << "Duracion: " << curso->getDuracionHoras() << " horas"
            << " | Fecha: " << curso->getFechaCreacion() << "\n    "
            << "Profesor: " << profesorAsignado << "\n";
    }
}

void Institucion::verestadisticas() {
    cout << "\nEstadisticas\n";
    cout << "Cantidad total de cursos: " << cursos.size() << "\n";
}
