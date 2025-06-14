﻿#include "Sistema.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <conio.h>
#include "AdministrarCursos.h"
#include <vector>
namespace fs = std::filesystem;
using namespace std;
//test 2 pa q no suban a master
Curso* leerCursoDesdeArchivo(string pathArchivo) {
    ifstream archivo(pathArchivo);
    string linea;
    Curso* curso = new Curso();

    bool leyendoLecciones = false;
    bool nombreYaLeido = false;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        
        linea.erase(0, linea.find_first_not_of(" \t\r\n"));
        linea.erase(linea.find_last_not_of(" \t\r\n") + 1);

        if (!leyendoLecciones) {
            if (!nombreYaLeido && linea.front() == '[' && linea.back() == ']') {
                string nombre = linea.substr(1, linea.size() - 2);
                curso->setNombre(nombre);
                nombreYaLeido = true;
            }
            else if (linea == "[LECCIONES]") {
                leyendoLecciones = true;
            }
            else if (linea.rfind("id:", 0) == 0) {
                string valor = linea.substr(3);
                valor.erase(0, valor.find_first_not_of(" "));
                curso->setId(valor);
            }
            else if (linea.rfind("categoria:", 0) == 0) {
                string valor = linea.substr(9);
                valor.erase(0, valor.find_first_not_of(" "));
                curso->setCategoria(valor);
            }
            else if (linea.rfind("descripcion:", 0) == 0) {
                string valor = linea.substr(11);
                valor.erase(0, valor.find_first_not_of(" "));
                curso->setDescripcion(valor);
            }
            else if (linea.rfind("duracion:", 0) == 0) {
                string valor = linea.substr(8);

                string numeroHoras = "";
                for (char c : valor) {
                    if (isdigit(c)) {
                        numeroHoras += c;
                    }
                    else {
                        break;
                    }
                }

                if (!numeroHoras.empty()) {
                    int horas = stoi(numeroHoras);
                    curso->setDuracionHoras(horas);
                }
                else {
                    curso->setDuracionHoras(0);
                }
            }
            else if (linea.rfind("fecha:", 0) == 0) {
                string valor = linea.substr(6);
                valor.erase(0, valor.find_first_not_of(" "));
                curso->setFechaCreacion(valor);
            }
        }
        else {
            if (linea.rfind("- ", 0) == 0) {
                string leccionTitulo = linea.substr(2);
                string contenidoVacio = "";
                int duracionPorDefecto = 0;

                Leccion* lec = new Leccion(leccionTitulo, contenidoVacio, duracionPorDefecto);
                curso->getLecciones().insertarAlFinal(lec);
            }
        }
    }

    archivo.close();
    return curso;
}

string obtenerFechaHoraActual() {
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

void Sistema::menuPrincipal() {
    int opcion;
    cout << "Coursera\n";
    cout << "1. Iniciar sesion\n";
    cout << "2. Registrarte\n";
    cout << "3. Acceder a los cursos(sin iniciar sesion)\n";
    cout << "4. Salir\n";
    cout << "Opcion: ";
    cin >> opcion;
    switch (opcion) {
    case 1:
        iniciarSesion();
        break;
    case 2:
        registrarse();
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
}
void Sistema::menuEstudiante() {
    int opcion;
    system("cls");
    do {
        system("cls");
        cout << "Menu estudiante\n";
        cout << "1. Ver Cursos\n";
        cout << "2. Ver Perfil\n";
        cout << "3. Saldo\n";
        cout << "4. Cerrar Sesion\n";
        cout << "Opcino: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cursosEstudiante();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
        }
    } while (opcion != 4);
}
void Sistema::cursosEstudiante() {
    system("cls");
    cout << "Los Cursos disponibles son: \n";
    AdministrarCurso auxCursos = cursos;
    auxCursos.ImprimirNombreCursos();
    system("pause");
}
bool Sistema::validarCorreo() {
    return false;
}

void Sistema::iniciarSesion() {
    string correo, contrasena;
    cout << "Ingrese el correo: ";
    cin >> correo;
    cout << "Ingrese la contrasena: ";
    cin >> contrasena;
}

void Sistema::registrarse() {
    system("cls");
    char tipoUsuario;
    cout << "Ingrese si es Estudiante(E), Profesor(P) o Institucion(I): "; cin >> tipoUsuario;
    switch (tipoUsuario) {
    case 'E':
        registroEstudiante();
        break;
    case 'P':
        break;
    case 'I':
        break;
    }
}

void Sistema::registroEstudiante() {
    system("cls");
    string correo, contrasena, nombres, apellidos;
    cout << "Ingrese el correo: "; cin >> correo;
    cout << "Ingrese la contrasena: "; cin >> contrasena;
    cout << "Ingrese sus Nombres: ";
    getline(cin, nombres);
    cout << "Ingrese sus apellidos: ";
    getline(cin, apellidos);
    cout << "Se ha registrado correctamente\n";
    system("pause");
    system("cls");
}
void Sistema::inicializarDatos() {
    string carpeta = "cursosCreados/";

    for (auto& entry : fs::directory_iterator(carpeta)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            Curso* curso = leerCursoDesdeArchivo(entry.path().string());
            cursos.insertarAlFinal(*curso);
        }
    }
}

void Sistema::menuProfesor() {
    int opcion;
    do {
        cout << "\n===== MENU PROFESOR =====" << endl;
        cout << "1. Crear curso" << endl;
        cout << "2. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            // Crear curso
            string nombre, categoria, descripcion;
            int duracion;

            cout << "\n--- CREAR CURSO ---" << endl;
            cout << "Nombre del curso: ";
            getline(cin, nombre);

            cout << "Categoria: ";
            getline(cin, categoria);

            cout << "Descripcion: ";
            getline(cin, descripcion);

            cout << "Duracion (en horas): ";
            cin >> duracion;
            cin.ignore();

            string id = HashUtil::generarHash(nombre + to_string(rand() % 10000));

            Curso nuevoCurso;
            nuevoCurso.setNombre(nombre);
            nuevoCurso.setCategoria(categoria);
            nuevoCurso.setDescripcion(descripcion);
            nuevoCurso.setDuracionHoras(duracion);
            nuevoCurso.setFechaCreacion(obtenerFechaHoraActual());
            nuevoCurso.setId(id);

            int subop;
            do {
                cout << "\n--- GESTION DE LECCIONES ---" << endl;
                cout << "1. A�adir una leccion al curso" << endl;
                cout << "2. Salir y guardar curso" << endl;
                cout << "Opcion: ";
                cin >> subop;
                cin.ignore();

                if (subop == 1) {
                    string titulo, contenido;
                    int duracionMin;

                    cout << "Titulo de la leccion: ";
                    getline(cin, titulo);

                    cout << "Contenido de la leccion: ";
                    getline(cin, contenido);

                    cout << "Duracion de la leccion (en minutos): ";
                    cin >> duracionMin;
                    cin.ignore();

                    Leccion* nueva = new Leccion(titulo, contenido, duracionMin);
                    nuevoCurso.agregarLeccion(nueva);
                    cursos.insertarAlFinal(nuevoCurso);
                }

            } while (subop != 2);

            string archivoNombre = "cursosCreados/" + id + ".txt";
            ofstream archivo(archivoNombre);
            if (archivo.is_open()) {
                archivo << "[" << nombre << "]\n";
                archivo << "id: " << id << "\n";
                archivo << "categoria: " << categoria << "\n";
                archivo << "descripcion: " << descripcion << "\n";
                archivo << "duracion: " << duracion << " horas\n";
                archivo << "fecha: " << nuevoCurso.getFechaCreacion() << "\n";
                archivo << "\n[LECCIONES]\n";

                Nodo<Leccion*>* actual = nuevoCurso.getLecciones().obtenerCabeza();
                while (actual) {
                    archivo << "- " << actual->dato->getTitulo() << "\n";
                    actual = actual->siguiente;
                }

                archivo.close();
                cout << "Curso guardado en " << archivoNombre << endl;
            }
            else {
                cerr << "Error al guardar el curso." << endl;
            }
        }

    } while (opcion != 2);
}


void Sistema::iniciarPrograma() {
    inicializarDatos();
    //menuPrincipal();    
    //menuProfesor();
    menuEstudiante();
}
