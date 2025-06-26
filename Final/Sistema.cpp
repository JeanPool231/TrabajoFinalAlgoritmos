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
#include <algorithm>
#include "CursoUtils.h"
using namespace std;


void moverCursor(int fila, int columna) {
    cout << "\033[" << fila << ";" << columna << "H";
}
void resetColor() {
    cout << "\033[0m";
}
void moverCursorColor(int fila, int columna, string color) {
    string codigoColor = "0"; 

    if (color == "negro")        codigoColor = "30";
    else if (color == "rojo")    codigoColor = "31";
    else if (color == "verde")   codigoColor = "32";
    else if (color == "amarillo")codigoColor = "33";
    else if (color == "azul")    codigoColor = "34";
    else if (color == "magenta") codigoColor = "35";
    else if (color == "cyan")    codigoColor = "36";
    else if (color == "blanco")  codigoColor = "37";
    else if (color == "brillante") codigoColor = "1";
    else if (color == "subrayado") codigoColor = "4";
    else if (color == "inverso") codigoColor = "7";

    std::cout << "\033[" << fila << ";" << columna << "H"
        << "\033[" << codigoColor << "m";
}
void limpiarZona(int fila, int columnaInicio, int cantidad) {
    moverCursor(fila, columnaInicio);
    cout << string(cantidad, ' ');
    moverCursor(fila, columnaInicio);
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
void guardarEstudiante(Estudiante nuevoEstudiante) {
    string nombre = nuevoEstudiante.getCorreo();
    string ruta = "Usuarios/" + nombre + ".txt";

    ofstream archivo(ruta);
    if (archivo.is_open()) {
        archivo << 'E' << '\n';
        archivo << nuevoEstudiante.getCorreo() << '\n';
        archivo << nuevoEstudiante.getContrasena() << '\n';
        archivo.close();
    }
    else {
        cout << "Error al crear el archivo para el usuario.\n";
    }
}
void guardarProfesor(Profesor profesor) {

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
    do {
        system("cls");
        //iniciarSesionUI();
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
    } while (true);
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
void saldoEstudiante() {

}
void Sistema::menuEstudiante() {
    int opcion;
    system("cls");
    do {
        system("cls");
        cout << "Menu estudiante\n";
        cout << "1. Ver Cursos\n";
        cout << "2. Ver Tus Cursos\n";
        cout << "3. Perfil\n";
        cout << "4. Saldo\n";
        cout << "5. Cerrar Sesion\n";
        cout << "Opcino: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cursosEstudiante();
            break;
        case 2:
            cursosInscritos();
            system("pause");
            break;
        case 3:
            perfilEstudiante();
            break;
        case 4:
            //saldoEstudiante();
            break;
        case 5:
            break;
        default:
            cout << "Opcion invalida, ingrese una opcion valida\n";
            break;
        }
    } while (opcion != 5);
}
void Sistema::cursosInscritos() {
    ListaEnlazada<Curso> inscritos = estudiante->getCursosInscritos();
    Nodo<Curso>* actual = inscritos.obtenerCabeza();
    cout << "Tus cursos Inscritos son: \n";
    int i = 1;
    while (actual != nullptr) {
        Curso& auxCurso = actual->dato;
        cout << i << ". ";
        cout << auxCurso.getNombre() << '\n';
        actual = actual->siguiente;
        i++;
    }
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
    int opcion, indice;
    system("cls");
    cout << "Los Cursos disponibles son: \n";
    AdministrarCurso auxCursos = cursos;
    Curso nuevoCurso;
    do {
        system("cls");
		auxCursos.ImprimirNombreCursos();
		cout << "Opciones: \n";
		cout << "1. Ver detalles de un curso\n";
		cout << "2. Inscribirse a un curso\n";
		cout << "3. Ver cursos ordenados por nombre\n";
		cout << "4. Ver cursos ordenados por costo\n";
        cout << "5. Volver\n";
        cout << "Opcion : "; cin >> opcion;
        system("cls");
        switch (opcion) {
        case 1:
            auxCursos.ImprimirNombreCursosIndices();
            cout << "\nIngrese el indice del curso a ver detalles: ";
            cin >> indice;
            auxCursos.verDetallesCursos(indice);
            system("pause");
            break;
        case 2:
            auxCursos.ImprimirNombreCursosIndices();
            cout << "\nSeleccione el indice del curso a inscribirse: "; cin >> indice;
            nuevoCurso = auxCursos.InscribirseACurso(indice);
            estudiante->agregarCurso(nuevoCurso);
            cout << "Se ha inscrito correctamente al curso de " << nuevoCurso.getNombre() << "!\n";
            system("pause");
            break;
        case 3:
            auxCursos.mostrarCursosOrdenados([](Curso a, Curso b) {
                string aux = a.getNombre();
                string aux2 = b.getNombre();
                char c1 = aux[0];
                char c2 = aux2[0];
                return toupper(c1) < toupper(c2);
                });
            system("pause");
            break;
        case 4:
            auxCursos.mostrarCursosOrdenados([](Curso a, Curso b) {
                return a.getCosto() < b.getCosto();
                });
            system("pause");
            break;
        case 5:
            break;
        default:
            cout << "Ingrese a una opcion valida\n";
            break;
        }
    } while (opcion != 5);
}
bool Sistema::validarCorreo(string& correo) {
    string ar = "Usuarios/" + correo + ".txt";
    ifstream archivo(ar);
    if (!archivo) {
        return false;
    }
    return true;
}
bool Sistema::validarContrasena(string& contrasena, string& correo) {
    string ruta = "Usuarios/" + correo + ".txt";
    ifstream archivo(ruta);
    string linea;
    int lineaActual = 0;
    bool si = false;
    while (getline(archivo, linea)) {
        lineaActual++;
        if (lineaActual == 3) {
            archivo.close();
            if (linea == contrasena) {
                si = true;
                break;
            }
        }
    }
    return si;
}

void Sistema::menuAdmin() {
    ListaEnlazada<Curso*> curso;
    ListaEnlazada<Estudiante*> estu;
    AVLTree<Profesor*> profe;
    AVLTree<Institucion*> inst;
    Administrador* admin = new Administrador();
    admin->menu_admin(curso, estu, profe, inst);
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
    //guardarUsuario(nuevoUsuario);
    guardarEstudiante(*estudiante);
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
        cout << "2. Ver cursos existentes" << endl;
        cout << "3. Eliminar curso" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
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
                cout << "1. Añadir una leccion al curso" << endl;
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
                }

            } while (subop != 2);

            cursos.insertarAlFinal(nuevoCurso);

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

        else if (opcion == 2) {
            cout << "\n--- CURSOS EXISTENTES ---\n";
            for (auto entry : fs::directory_iterator("cursosCreados")) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    Curso* curso = leerCursoDesdeArchivo(entry.path().string());
                    if (curso != nullptr) {
                        cout << "ID: " << curso->getId() << "\n";
                        cout << "Nombre: " << curso->getNombre() << "\n";
                        cout << "Categoria: " << curso->getCategoria() << "\n";
                        cout << "Descripcion: " << curso->getDescripcion() << "\n";
                        cout << "Duracion: " << curso->getDuracionHoras() << " horas\n";
                        cout << "Fecha: " << curso->getFechaCreacion() << "\n";
                        cout << "-----------------------------\n";
                        delete curso;
                    }
                }
            }
        }

        else if (opcion == 3) {
            cout << "\n--- ELIMINAR CURSO ---\n";
            cout << "Ingrese el ID del curso a eliminar: ";
            string idEliminar;
            getline(cin, idEliminar);

            string ruta = "cursosCreados/" + idEliminar + ".txt";
            if (fs::exists(ruta)) {
                fs::remove(ruta);
                cout << "Archivo eliminado correctamente.\n";
            }
            else {
                cout << "No se encontró el archivo.\n";
            }

            bool eliminado = cursos.eliminarSi([&](Curso c) {
                return c.getId() == idEliminar;
                });

            if (eliminado) {
                cout << "Curso eliminado de la lista en memoria.\n";
            }
            else {
                cout << "Curso no encontrado en la lista.\n";
            }
        }

    } while (opcion != 4);
}

void Sistema::iniciarSesionUI() {

	cout << "\033[?25l"; // eliminar cursos
    disenio.cuadro(120, 28);
    disenio.tituloIniciarSesion(3, 30);
    disenio.cuadroDobleLineas(10, 40, 30, 5);
    disenio.tituloEmail(8, 40);
    disenio.cuadroDobleLineas(20, 40, 30, 5);
    disenio.tituloPassword(18, 40);
	cout << "\033[?25h"; // mostrar cursor luego de eliminar cursor
}
void Sistema::iniciarPrograma() {
    inicializarDatos();
    menuPrincipal();    
}
void Sistema::iniciarSesion() {
    system("cls");
    iniciarSesionUI();
    string correo, contrasena;
    do {
        moverCursor(12, 42);
        cin >> correo;
        if (correo == "volver") return;
        if (!validarCorreo(correo)) {
            moverCursorColor(16, 42, "rojo");
            cout << "Correo no encontrado!, escriba volver para ir el menu principal";
            resetColor();
            moverCursor(12, 42);
            limpiarZona(12, 42, 25);
        }
    } while (!validarCorreo(correo));
    limpiarZona(16, 42, 70);
    do {
        moverCursor(22, 42);
        cin >> contrasena;
        if (contrasena == "volver") return;
        if (!validarContrasena(contrasena, correo)) {
            moverCursorColor(26, 42, "rojo");
            cout << "Contrasena incorrecta!, escriba volver para ir al menu principal";
            resetColor();
            moverCursor(22, 42);
            limpiarZona(22, 42, 25);
        }
    } while (!validarContrasena(contrasena, correo));
    
    string ruta = "Usuarios/" + correo + ".txt";
    ifstream archivo(ruta);
    string linea;
    string tipo;
    while (getline(archivo, linea)) {
        tipo = linea;
        break;
    }
    if (tipo == "E") {
        menuEstudiante();
    }
    else if (tipo == "P") {
        menuProfesor();
    }
    else if (tipo == "I") {
        
    }
    else {

    }
}
