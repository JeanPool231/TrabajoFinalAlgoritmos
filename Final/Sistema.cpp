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
#include <iostream>

void limpiarZona(int filaInicio, int columnaInicio, int alto, int ancho) {
    for (int i = 0; i < alto; ++i) {
        cout << "\033[" << (filaInicio + i) << ";" << columnaInicio << "H";
        cout << string(ancho, ' ');
    }
}

string leerPassword() {
    string password;
    char c;

    while (true) {
        c = _getch(); // lee carácter sin mostrarlo
        if (c == 13) break; // Enter
        else if (c == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // Borra el * anterior
            }
        }
        else {
            password += c;
            cout << '*';
        }
    }

    return password;
}

void imprimirConFondo(string texto, string colorFondo) {
    string fondo;

    if (colorFondo == "negro")      fondo = "40";
    else if (colorFondo == "rojo")  fondo = "41";
    else if (colorFondo == "verde") fondo = "42";
    else if (colorFondo == "amarillo") fondo = "43";
    else if (colorFondo == "azul")  fondo = "44";
    else if (colorFondo == "magenta") fondo = "45";
    else if (colorFondo == "cyan")  fondo = "46";
    else if (colorFondo == "blanco")fondo = "47";
    else fondo = "40"; // fondo negro por defecto

    std::cout << "\033[37;" << fondo << "m" // texto blanco + fondo
        << texto
        << "\033[0m"; // restaura color y fondo
}

void sombrearZonaRect(int filaInicio, int columnaInicio, int alto, int ancho, string colorFondo) {
    std::string fondo;

    if (colorFondo == "negro")      fondo = "40";
    else if (colorFondo == "rojo")  fondo = "41";
    else if (colorFondo == "verde") fondo = "42";
    else if (colorFondo == "amarillo") fondo = "43";
    else if (colorFondo == "azul")  fondo = "44";
    else if (colorFondo == "magenta") fondo = "45";
    else if (colorFondo == "cyan")  fondo = "46";
    else if (colorFondo == "blanco")fondo = "47";
    else fondo = "40"; // fondo negro por defecto

    for (int i = 0; i < alto; ++i) {
        std::cout << "\033[" << (filaInicio + i) << ";" << columnaInicio << "H";
        std::cout << "\033[0;" << fondo << "m" << std::string(ancho, ' ') << "\033[0m";
    }
}

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
Profesor* leerProfesor(string ruta) {
    ifstream archivo(ruta);
    Profesor* profesor = new Profesor();
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << ruta << '\n';
        system("pause");
        return profesor;
    }
    string linea;
    int i = 1;
    while (getline(archivo, linea)) {
        if (i == 1) {
            profesor->setCodigo(linea);
        }
        else if (i == 2) {
            profesor->setNombre(linea);
        }
        else if (i == 3) {
            profesor->setApellido(linea);
        }
        else if (i == 4) {
            profesor->setCorreo(linea);
        }
        else if (i == 5) {
            profesor->setTiempoEnCoursera(stoi(linea));
        }
        else if (i == 6) {
            profesor->setId(linea);
        }
        else if (i == 7) {
            profesor->setReputacion(stoi(linea));
        }
        i++;
    }

    archivo.close();
    return profesor;

}
void guardarEstudiante(Estudiante nuevoEstudiante) {
    string nombre = nuevoEstudiante.getCorreo();
    string ruta = "Usuarios/" + nombre + ".txt";

    ofstream archivo(ruta);
    if (archivo.is_open()) {
        archivo << 'E' << '\n';
        archivo << nuevoEstudiante.getCorreo() << '\n';
        archivo << nuevoEstudiante.getContrasena() << '\n';
        archivo << nuevoEstudiante.getCodigo() << '\n';
        archivo.close();
    }
    else {
        cout << "Error al crear el archivo para el usuario.\n";
    }
    nombre = nuevoEstudiante.getCodigo();
    ruta = "estudiantesCreados/" + nombre + ".txt";

    ofstream archivo2(ruta);
    if (archivo2.is_open()) {
        archivo2 << nuevoEstudiante.getNombres() << '\n';
        archivo2 << nuevoEstudiante.getApellidos() << '\n';
        archivo2 << nuevoEstudiante.getCorreo() << '\n';
        archivo2.close();
    }
    else {
        cout << "Error al crear el archivo para el usuario.\n";
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
        inicioUI();
        moverCursor(24,5);
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
    } while (opcion != 5);
}


void Sistema::menuInstitucion() {

    Institucion inst("UPC", "Educacion universitaria", 2018);

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
    do {
        system("cls");
        estudianteUI();
        moverCursor(24, 5);
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            //seleccionar Curso
            cursosEstudiante();
            break;
        case 2:
            //Buscar Cursos
            cursosInscritos();
            break;
        case 3:
            //perfil
            perfilEstudiante();
            break;
        case 4:
            break;
        case 5:
            break;
        default:
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
    verPerfilUI();
    moverCursor(9, 81);
    cout << estudiante->getNombres();
    moverCursor(12, 81);
    cout << estudiante->getApellidos();
    moverCursor(15, 81);
    cout << estudiante->getCorreo();
    string s;
    moverCursor(24, 5);
    cin >> s;

    system("cls");
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
    registroUI();
    char tipoUsuario;
    string waza;
    do {
		moverCursor(24, 71);
		cin >> waza;
		for (char& c : waza) c = tolower(c); // validacion 
        if (waza == "estudiante") tipoUsuario = 'E';
        else if (waza == "profesor") tipoUsuario = 'P';
        else if (waza == "institucion") tipoUsuario = 'I';
        else if (waza == "volver") tipoUsuario = 'V';
        else tipoUsuario = 'O';
		switch (tipoUsuario) {
		case 'E':
			registroEstudiante();
			menuEstudiante();
            return;
			break;
		case 'P':
			registroProfesor();
			menuProfesor();
            return;
			break;
		case 'I':
			registroInstitucion();
			menuInstitucion();
            return;
			break;
        case 'V':
            break;
        case 'O' :
            moverCursor(23, 65);
            cout << "Input invalido";
		}
    } while (waza != "volver");
}
/// <summary>
/// 
/// /
/// /
/// /
/// /
/// /
/// /
/// /
/// 
/// 
/// 
/// 
/// 
/// 
/// 
/// /////////////
/// 
/// /
/// /
/// 
/// </summary>
void Sistema::registroEstudiante() {
    string correo, contrasena, nombres, apellidos;
    string contrasena2;
    string codigo;
    registroEstudianteUI();
    moverCursor(7, 62);
    cin.ignore();

    getline(cin, nombres);
    moverCursor(10, 62);
    getline(cin, apellidos);

    moverCursor(13, 62);
    cin >> correo;

    moverCursor(16, 62);
    cin >> contrasena;

    moverCursor(20, 62);
    cin >> contrasena2;

    estudiante->setNombres(nombres);
    estudiante->setApellidos(apellidos);
    estudiante->setContrasena(contrasena);
    estudiante->setCorreo(correo);
    codigo = HashUtil::generarHash(nombres + to_string(rand() % 10000));
    estudiante->setCodigo(codigo);
    guardarEstudiante(*estudiante);
    
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
    //leer los cursos
    string ruta = "cursosCreados/cursoHash.txt";
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "error hijito\n";
        system("pause");
    }
    string linea;
    while (getline(archivo, linea)) {
        string ruta2 = "cursosCreados/" + linea + ".txt";
        Curso* curso = leerCurso(ruta2);
        cursos.insertarAlFinal(*curso);
    }
    //leer a los profes
	string rutaProfes("profesoresCreados/profesoresHash.txt");
	ifstream archivoProfes(rutaProfes);
	while (getline(archivoProfes, linea)) {
		string rutaHash = "profesoresCreados/" + linea + ".txt";
		Profesor* profesor = leerProfesor(rutaHash);
		profesores.insertarAlFinal(*profesor);
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
            cout << "Falta papu\n";
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

	cout << "\033[?25l";
    disenio.cuadro_dividido(120, 28);
    disenio.tituloIniciarSesion(3, 45);
    disenio.cuadroDobleLineas(10, 55, 30, 5);
    disenio.tituloEmail(8, 55);
    disenio.cuadroDobleLineas(20, 55, 30, 5);
    disenio.tituloPassword(18, 55);
    moverCursor(6, 2);
    cout << "- Escriba volver para";
    moverCursor(7, 2);
    cout << "volver al menu principal";

	cout << "\033[?25h"; 
}
void Sistema::inicioUI() {
	cout << "\033[?25l"; // eliminar cursor
    disenio.cuadro_dividido(120, 28);
    moverCursorColor(0, 0, "azul");
    disenio.tituloCoursera(3, 33);
    moverCursor(3, 85);
    cout << "Iniciar Sesion";
    moverCursor(3, 105);
    cout << "Registrarte";
    resetColor();
    moverCursor(8, 2);
    cout << "1. Iniciar Sesion";
    moverCursor(10, 2);
    cout << "2. Registrarse";
    moverCursor(12, 2);
    cout << "Navegacion:";
    moverCursor(14, 2);
    cout << "3. Derecha";
    moverCursor(16, 2);
    cout << "4. Izquierda";
    moverCursor(18, 2);
    cout << "5. Salir";
	cout << "\033[?25h"; // mostrar cursor luego de eliminar cursor
    for (int i = 0, j = 0; i < 4; i++) {
        disenio.cuadroRedondo(8, i + 33 + j, 20, 7);
        j += 20;
    }
    for (int i = 0, j = 0; i < 4; i++) {
        disenio.cuadroRedondo(16, i + 33 + j, 20, 7);
        j += 20;
    }
    for (int i = 0, j = 0; i < 4; i++) {
        disenio.cuadroRedondo(24, i + 68 + j, 3, 3);
        j += 2;
    }
    moverCursor(25, 69);
    imprimirConFondo("1", "verde");
    moverCursor(25, 72);
    cout << "2";
    moverCursor(25, 75);
    cout << "3";
    moverCursor(25, 78);
    cout << "4";
    mostrarCursosUI();
}

void Sistema::estudianteUI() {
    //metodo para imprimir solo el primer nombre del usuario
    string nom = estudiante->getNombres(), nombre = "";
    for (int i = 0; i < nom.size(); i++) {
        if (nom[i] == ' ') break;
        nombre += nom[i];
    }
	cout << "\033[?25l"; 
    disenio.cuadro_dividido(120, 28);
    moverCursorColor(0, 0, "azul");
    disenio.tituloCoursera(3, 33);
    moverCursor(3, 95);
    cout << "Bienvenido " << nombre;
    resetColor();
    moverCursor(8, 2);
    cout << "1. Seleccionar Curso";
    moverCursor(10, 2);
    cout << "2. Buscar Cursos";
    moverCursor(12, 2);
    cout << "3. Perfil";
    moverCursor(14, 2);
    cout << "Navegacion:";
    moverCursor(16, 2);
    cout << "3. Derecha";
    moverCursor(18, 2);
    cout << "4. Izquierda";
    moverCursor(20, 2);
    cout << "5. Cerrar Sesion";
	cout << "\033[?25h";

    for (int i = 0, j = 0; i < 4; i++) {
        disenio.cuadroRedondo(8, i + 33 + j, 20, 7);
        j += 20;
    }
    for (int i = 0, j = 0; i < 4; i++) {
        disenio.cuadroRedondo(16, i + 33 + j, 20, 7);
        j += 20;
    }
    for (int i = 0, j = 0; i < 4; i++) {
        disenio.cuadroRedondo(24, i + 68 + j, 3, 3);
        j += 2;
    }
    moverCursor(25, 69);
    imprimirConFondo("1", "verde");
    moverCursor(25, 72);
    cout << "2";
    moverCursor(25, 75);
    cout << "3";
    moverCursor(25, 78);
    cout << "4";
    mostrarCursosUI();
}
void Sistema::iniciarSesion() {
    system("cls");
    iniciarSesionUI();
    string correo, contrasena;
    do {
        moverCursor(12, 57);
        cin >> correo;
        if (correo == "volver") return;
        if (!validarCorreo(correo)) {
            moverCursorColor(16, 57, "rojo");
            cout << "Correo no encontrado!, escriba volver para ir el menu principal";
            resetColor();
            moverCursor(12, 57);
            limpiarZona(12, 57, 25);
        }
    } while (!validarCorreo(correo));
    limpiarZona(16, 57, 63);
    do {
        moverCursor(22, 57);
        contrasena = leerPassword();
        if (contrasena == "volver") return;
        if (!validarContrasena(contrasena, correo)) {
            moverCursorColor(26, 57, "rojo");
            cout << "Contrasena incorrecta!, escriba volver para ir al menu principal";
            resetColor();
            moverCursor(22, 57);
            limpiarZona(22, 57, 25);
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
    int i = 1;
    string subRuta, linea2;
    if (tipo == "E") {
                    
        ifstream archivo2(ruta);
        while (getline(archivo2, linea)) {
            if (i == 4) {
                subRuta = "estudiantesCreados/" + linea + ".txt";
                ifstream sub_ruta(subRuta);
                int j = 1;
                estudiante->setCodigo(linea);
                while (getline(sub_ruta, linea2)) {
                   //cout << linea2 << ": linea\n";
                    if (j == 1) {
                        estudiante->setNombres(linea2);
                    }
                    else if (j == 2) {
                        estudiante->setApellidos(linea2);
                    }
                    else if (j == 3) {
                        estudiante->setCorreo(linea2);
                    }
                    j++;
                }
                break;
            }
            i++;
        }
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
void limpiarCursosCuadros() {
    int a = 9, b = 0;
    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            a += 8;
            b = 0;
        }
        for (int j = 0; j < 4; j++) {
            limpiarZona(a, 34 + b, 4, 18);
            b += 21;
        }
    }
}
void Sistema::mostrarCursosUI() {
    Nodo<Curso>* actual = cursos.obtenerCabeza();
    int i = 1;
    int a = 9, b = 34;
    moverCursorColor(0, 0, "subrayado");
    while (actual != nullptr) {
        Curso& auxCurso = actual->dato;
        string nombre = auxCurso.getNombre();
        string p1 = "";
        string p2 = "";
        if (nombre.size() > 18) {
			p1 = nombre.substr(0, 18);
            p2 = nombre.substr(18);
        }
        else {
            p1 = nombre;
        }
        moverCursor(a, b); 
        cout << p1;
        moverCursor(a + 1, b);
        cout << p2;
        b += 21;
        actual = actual->siguiente;
        i++;
        if (i == 5) {
            a += 8;
            b = 34;
        }
        else if (i == 9) break;
    }
    resetColor();
    //system("pause");
    //limpiarCursosCuadros();
}
void Sistema::registroUI() {
    system("cls");
    disenio.cuadro_dividido(120, 28);
    disenio.tituloElegirPerfil(3, 51);
    disenio.cuadroPosicional(7, 35, 20, 12);
    disenio.cuadroPosicional(7, 65, 20, 12);
    disenio.cuadroPosicional(7, 95, 20, 12);
    disenio.cuadroDobleLineas(23, 60, 31, 4);
    disenio.logoProfesor(8, 66);
    disenio.logoEstudiante(9, 36);
    disenio.logoInstitucion(9, 97);
    moverCursor(19, 40);
    cout << "Estudiante";
    moverCursor(19, 71);
    cout << "Profesor";
    moverCursor(19, 99);
    cout << "Institucion";
}
void Sistema::registroEstudianteUI() {
    system("cls");
    disenio.cuadro_dividido(120, 28);
    disenio.tituloRegistroEstudiante(2, 33);
    disenio.tituloNombre(6, 38);
    disenio.tituloApellido(9, 38);
    disenio.tituloEmail(12, 38);
    disenio.tituloPassword(15, 38);
    disenio.tituloConfirmar(18, 38);

    disenio.cuadroDobleLineas(6, 60, 50, 3);
    disenio.cuadroDobleLineas(9, 60, 50, 3);
    disenio.cuadroDobleLineas(12, 60, 50, 3);
    disenio.cuadroDobleLineas(15, 60, 50, 3);
    disenio.cuadroDobleLineas(19, 60, 50, 3);
}

void Sistema::bienvenidoUI() {
	cout << "\033[?25l"; // eliminar cursor
    disenio.cuadro(120, 28);
    disenio.tituloBienvenido(7, 21);
    disenio.barraCargaConCuadro(17, 37, 50, 50);
	cout << "\033[?25h"; 

}

void Sistema::verPerfilUI() {
    disenio.cuadro_dividido(120, 28);
    disenio.tituloTuPerfil(3, 30);

    disenio.cuadroPosicional(6, 33, 20, 12);
    disenio.logoEstudiante(8, 34);
    
    disenio.tituloNombre(8, 65);
    disenio.tituloApellido(11, 65);
    disenio.tituloEmail(14, 65);
    disenio.cuadroRedondo(8, 80, 30, 3);
    disenio.cuadroRedondo(11, 80, 30, 3);
    disenio.cuadroRedondo(14, 80, 30, 3);
    disenio.cuadroRedondo(17, 80, 30, 3);
}

void Sistema::verCursoSeleccionadoUI(Curso curso) {
    disenio.cuadro_dividido(120, 28);
}

void Sistema::iniciarPrograma() {
    inicializarDatos();
    bienvenidoUI();
    menuPrincipal();    
}
