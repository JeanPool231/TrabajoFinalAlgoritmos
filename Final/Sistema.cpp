#include "Sistema.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <fstream>
#include <ostream>
using namespace std; 

Curso* cargarcursodesdeeltxt(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "error a" << ruta << endl;
        return nullptr;
    }

    string linea, nombre, id, categoria, descripcion, duracion, fecha;

    getline(archivo, linea); 
    if (!linea.empty() && linea.front() == '[' && linea.back() == ']')
        nombre = linea.substr(1, linea.size() - 2);

    while (getline(archivo, linea)) {
        if (linea.rfind("id:", 0) == 0) id = linea.substr(4);
        else if (linea.rfind("categoria:", 0) == 0) categoria = linea.substr(10);
        else if (linea.rfind("descripcion:", 0) == 0) descripcion = linea.substr(12);
        else if (linea.rfind("duracion:", 0) == 0) duracion = linea.substr(9);
        else if (linea.rfind("fecha:", 0) == 0) fecha = linea.substr(7);
        else if (linea == "[LECCIONES]") break;
    }

    Curso* curso = new Curso();
    curso->setNombre(nombre);
    curso->setId(id);
    curso->setCategoria(categoria);
    curso->setDescripcion(descripcion);
    curso->setFechaCreacion(fecha);
    curso->setduracionentexto(duracion); 
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

void Sistema::menuInstitucion() {
    Institucion inst("UPC", "Educacion universitaria", 2015);

    Curso* cursoDesdeTxt = cargarcursodesdeeltxt("cursosCreados/845632255.txt");
    if (cursoDesdeTxt != nullptr) {
        inst.agregarcurso(cursoDesdeTxt);
    }


   // TEST son profes de prueba pre establecidos
    Profesor p1("P1", "Cain", "Mohammed", "cain@upc.edu.pe", 'M', 'S', 40, 5, 101, 95);
    Profesor p2("P2", "Rosa", "Melano", "rosa@upc.edu.pe", 'F', 'C', 35, 3, 102, 88);
    inst.agregarprofesor(p1);
    inst.agregarprofesor(p2);



    int opc;
    do {
        cout << "\nInstitucion\n";
        cout << "1. Ver Profesores\n";
        cout << "2. Agregar/Quitar\n";
        cout << "3. Ver cursos publicados\n";
        cout << "4. Ver Estadisticas\n";
        cout << "5. Salir\n";
        cout << "\n";
        cout << "Ingrese una opcion: ";
        cin >> opc;
        cin.ignore();

        switch (opc) {
        case 1:
            inst.verinformacion();
            inst.verprofesores();
            break;

        case 2: {
            int sub;
            cout << "\nGestion de profes\n";
            cout << "1. Agregar Profesor\n";
            cout << "2. Quitar Profesor\n";
            cout << "3. Volver\n";
            cout << "Ingrese opcion: ";
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                string codigo, nombre, apellido, correo;
                char sexo, estadocivil;
                int edad, tiempoencoursera, id, reputacion;

                cout << "Código: "; cin >> codigo;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Apellido: "; getline(cin, apellido);
                cout << "Correo: "; getline(cin, correo);
                cout << "Sexo: "; cin >> sexo;
                cout << "Estado civil: "; cin >> estadocivil;
                cout << "Edad: "; cin >> edad;
                cout << "Tiempo en Coursera: "; cin >> tiempoencoursera;
                cout << "ID: "; cin >> id;
                cout << "Reputacion (0-100): "; cin >> reputacion;
                cin.ignore();

                Profesor nuevo(codigo, nombre, apellido, correo, sexo, estadocivil, edad, tiempoencoursera, id, reputacion);
                inst.agregarprofesor(nuevo);
                cout << "Profesor agregado correctamente.\n";
            }
            else if (sub == 2) {
                cout << "fal\n";
            }
            break;
        }

        case 3:
            inst.vercursos();
            break;

        case 4: {
            int sub;
            cout << "\nEstadisticas\n";
            cout << "1. Cantidad de cursos\n";
            cout << "2. Total de inscritos\n";
            cout << "3. Volver\n";
            cout << "Ingrese opción: ";
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                cout << "Cantidad de cursos: " << inst.getcursos().size() << "\n";
            }
            else if (sub == 2) {
                inst.verestadisticas();
            }
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

void Sistema::iniciarPrograma() {
	//menuPrincipal();
    //menuProfesor(); //toy testeando mano, es pa q veas
    menuInstitucion(); 
}

