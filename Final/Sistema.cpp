#include "Sistema.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <conio.h>
#include "AdministrarCursos.h"
#include <vector>
#include <clocale>
using namespace std;


Curso* leerCursoDesdeArchivo(string ruta) {
    ifstream archivo(ruta);
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


Profesor* leerprofesor(const string& ruta) {
    try {
        ifstream archivo(ruta);

        string linea, codigo, nombre, apellido, correo, curso_asignado;
        char sexo = ' ', estadoCivil = ' ';
        int edad = 0, tiempoEnCoursera = 0, id = 0, reputacion = 0;

        while (getline(archivo, linea)) {
            linea.erase(0, linea.find_first_not_of(" \t\r\n"));
            linea.erase(linea.find_last_not_of(" \t\r\n") + 1);
            if (linea.empty()) continue;

            if (linea.rfind("codigo:", 0) == 0) codigo = linea.substr(7);
            else if (linea.rfind("nombre:", 0) == 0) nombre = linea.substr(7);
            else if (linea.rfind("apellido:", 0) == 0) apellido = linea.substr(9);
            else if (linea.rfind("correo:", 0) == 0) correo = linea.substr(7);
            //else if (linea.rfind("sexo:", 0) == 0 && linea.length() > 6) sexo = linea[6];
            //else if (linea.rfind("estado_civil:", 0) == 0 && linea.length() > 14) estadoCivil = linea[14];
            //else if (linea.rfind("edad:", 0) == 0) {
            //    string val = linea.substr(5);
            //    if (!val.empty()) edad = stoi(val);
            //}
            else if (linea.rfind("tiempo_en_coursera:", 0) == 0) {
                string val = linea.substr(21);
                if (!val.empty()) tiempoEnCoursera = stoi(val);
            }
            else if (linea.rfind("id:", 0) == 0) {
                string val = linea.substr(3);
                if (!val.empty()) id = stoi(val);
            }
            else if (linea.rfind("reputacion:", 0) == 0) {
                string val = linea.substr(11);
                if (!val.empty()) reputacion = stoi(val);
            }
            else if (linea.rfind("curso_asignado:", 0) == 0) {
                if (linea.length() > 16) {
                    curso_asignado = linea.substr(16);
                    curso_asignado.erase(0, curso_asignado.find_first_not_of(" "));
                }
                else {
                    curso_asignado = ""; //b dnt
                }
            }
        }

        archivo.close();

        if (codigo.empty() || nombre.empty()) {
            return nullptr;
        }

        Profesor* prof = new Profesor(codigo, nombre, apellido, correo,
            tiempoEnCoursera, id, reputacion);
        if (!curso_asignado.empty())
            prof->asignarCurso(curso_asignado);

        return prof;
    }
    catch (const exception& e) {
        return nullptr;
    }
}

void guardarUsuario(Usuario usuario) {
    ofstream archivo("Usuarios/usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << usuario.tipoUsuario << " " << usuario.correo << " " << usuario.contrasena << endl;
        archivo.close();
    }
    else {
        cout << "Error al abrir el archivo para guardar.\n";
    }
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


void Sistema::menuInstitucion() {

    Institucion inst("UPC", "Educacion universitaria", 2018);

    fs::create_directory("logs");

    for (const auto& entry : fs::directory_iterator("profesoresGuardados")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            if (fs::file_size(entry.path()) == 0) continue;

            Profesor* prof = leerprofesor(entry.path().string());
            if (prof != nullptr) {
                inst.agregarprofesor(*prof);
                delete prof;
            }
        }
    }

    for (auto entry : fs::directory_iterator("cursosCreados")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            Curso* curso = leerCursoDesdeArchivo(entry.path().string());
            if (curso != nullptr) {
                inst.agregarcurso(curso); 
            }
        }
    }

    // test
    Profesor p1("P1", "Cain", "Mohammed", "cain@upc.edu.pe", 5, 101, 95);
    Profesor p2("P2", "Beniju", "Ballestin", "beniju@upc.edu.pe", 3, 102, 88);
    inst.agregarprofesor(p1);
    inst.agregarprofesor(p2);

    int opc;
    do {
        cout << "\nInstitucion\n";
        cout << "1. Ver informacion de la institucion\n";
        cout << "2. Gestionar profesores\n";
        cout << "3. Ver cursos publicados\n";
        cout << "4. Ver estadisticas\n";
        cout << "5. Salir\n";
        cout << "\n";
        cout << "Ingrese una opcion: ";
        cin >> opc;
        cin.ignore();

        switch (opc) {
        case 1:
            inst.verinformacion();
            break;

        case 2: {
            inst.menugestiondeprofes();
            break;
        }

        case 3:
            inst.vercursos();
            break;

        case 4: {
            inst.verestadisticas();
            break;
        }

        case 5:
            cout << "Saliendo .,...\n";
            break;

        default:
            cout << "opcion no valida\n";
        }

    } while (opc != 5);
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
            perfilEstudiante();
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
void Sistema::perfilEstudiante() {
    system("cls");
    cout << "Perfil\n";
    cout << "1. Nombres: " << estudiante->getNombres() << '\n';
    cout << "2. Apellidos: " << estudiante->getApellidos() << '\n';
    cout << "3. Correo: " << estudiante->getCorreo() << '\n';
    system("pause");
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

    bool encontrado = false;
    Nodo<Usuario>* actual = usuarios.obtenerCabeza();
    Usuario& u = actual->dato;
    while (actual != nullptr) {
        u = actual->dato;
        actual = actual->siguiente;
        if (u.correo == correo && u.contrasena == contrasena) {
            encontrado = true;
            break;
        }
    }
    if (encontrado) {
        switch (u.tipoUsuario) {
        case 'E': menuEstudiante(); break;
        case 'P': menuProfesor(); break;
        case 'I':  break;
        }
    }
    else {
        cout << "Correo o contraseña incorrectos.\n";
    }

    system("pause");
    system("cls");
}

void Sistema::registrarse() {
    system("cls");
    char tipoUsuario;
    cout << "Ingrese si es Estudiante(E), Profesor(P) o Institucion(I): "; cin >> tipoUsuario;
    switch (tipoUsuario) {
    case 'E':
        registroEstudiante();
        menuEstudiante();
        break;
    case 'P':
        registroProfesor();
        menuProfesor();
        break;
    case 'I':
        registroInstitucion();
        menuInstitucion();
        break;
    }
}

void Sistema::registroEstudiante() {
    system("cls");
    string correo, contrasena, nombres, apellidos;
    cout << "Ingrese el correo: "; cin >> correo;
    cout << "Ingrese la contrasena: "; cin >> contrasena;
    cin.ignore();
    cout << "Ingrese sus Nombres: ";
    getline(cin, nombres);
    cout << "Ingrese sus apellidos: ";
    getline(cin, apellidos);
    cout << "Se ha registrado correctamente\n";
    estudiante->setNombres(nombres);
    estudiante->setApellidos(apellidos);
    estudiante->setContrasena(contrasena);
    estudiante->setCorreo(correo);
    Usuario nuevoUsuario = { 'E', correo, contrasena };
    guardarUsuario(nuevoUsuario);
    system("pause");
    system("cls");
}

void Sistema::registroProfesor() {
    system("cls");
	string codigo, nombre, apellido, correo;
	char sexo, estadoCivil;
    int edad, tiempoEnCoursera, id, reputacion;
    string contrasena;
    cout << "Ingrese el codigo de la institucion: ";
    cin >> codigo;
    cout << "Ingrese el correo: "; cin >> correo;
    cout << "Ingrese la contrasena: "; cin >> contrasena;
    cin.ignore();
    cout << "Ingrese sus Nombres: ";
    getline(cin, nombre);
    cout << "Ingrese sus apellidos: ";
    getline(cin, apellido);
    //cout << "Ingrese su genero (M : masculino, F : femenino): "; cin >> sexo;
    cout << "Se ha registrado correctamente profesor\n";
    profesor->setApellido(apellido);
    profesor->setCodigo(codigo);
    profesor->setCorreo(correo);
    //profesor.setEdad(edad);
    //profesor.setId(id);
    profesor->setNombre(nombre);
    //profesor.setSexo(sexo);
    Usuario nuevoUsuario = { 'P', correo, contrasena };
    guardarUsuario(nuevoUsuario);

    system("pause");
    system("cls");
}

void Sistema::registroInstitucion() {
    system("cls");
    //string correo, contrasena, nombres, apellidos;
    //cout << "Ingrese el correo: "; cin >> correo;
    //cout << "Ingrese la contrasena: "; cin >> contrasena;
    //cout << "Ingrese sus Nombres: ";
    //getline(cin, nombres);
    //cout << "Ingrese sus apellidos: ";
    //getline(cin, apellidos);
    cout << "Se ha registrado los datos \n Por favor espere a que el admin apruebe su registro\n";
    system("pause");
    system("cls");
}
void Sistema::inicializarDatos() {
    string carpeta = "cursosCreados/";

    for (auto entry : fs::directory_iterator(carpeta)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            Curso* curso = leerCursoDesdeArchivo(entry.path().string());
            cursos.insertarAlFinal(*curso);
        }
    }
    
    ifstream archivo("Usuarios/usuarios.txt");
    if (archivo.is_open()) {
        Usuario usuario;
        while (archivo >> usuario.tipoUsuario >> usuario.correo >> usuario.contrasena) {
            usuarios.insertarAlFinal(usuario);
        }
        archivo.close();
    }
    else {
        cout << "No se pudo abrir el archivo de usuarios.\n";
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
    menuProfesor();
    //menuEstudiante();
    //menuInstitucion();

}
