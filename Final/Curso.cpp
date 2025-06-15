#include "Curso.h"
#include <iostream>

Curso::Curso()
    : nombre(""), id(""), categoria(""), descripcion(""), fechaCreacion(""),
    duracionHoras(0), cantidadInscritos(0), numLecciones(0) {
}

Curso::~Curso() {
}

Curso::Curso(string& nombre, string id, string& categoria, string& descripcion, string fechaCreacion,
    int duracionHoras, int cantidadInscritos, int numLecciones) {

    this->nombre = nombre;
    this->id = id;
    this->categoria = categoria;
    this->descripcion = descripcion;
    this->duracionHoras = duracionHoras;
    this->cantidadInscritos = cantidadInscritos;
    this->numLecciones = numLecciones;
}

string Curso::getNombre() { return nombre; }
string Curso::getId() { return id; }
string Curso::getCategoria() { return categoria; }
string Curso::getDescripcion() { return descripcion; }
string Curso::getFechaCreacion() { return fechaCreacion; }
int Curso::getDuracionHoras() { return duracionHoras; }
int Curso::getCantidadInscritos() { return cantidadInscritos; }
int Curso::getNumLecciones() { return numLecciones; }
string Curso::getduracionentexto() const {
    return duracionentexto;
}

ListaEnlazada<Leccion*>& Curso::getLecciones() { return lecciones; }

void Curso::setNombre(string nombre) { this->nombre = nombre; }
void Curso::setId(string id) { this->id = id; }
void Curso::setCategoria(string categoria) { this->categoria = categoria; }
void Curso::setDescripcion(string descripcion) { this->descripcion = descripcion; }
void Curso::setFechaCreacion(string fechaCreacion) { this->fechaCreacion = fechaCreacion; }
void Curso::setDuracionHoras(int duracionHoras) { this->duracionHoras = duracionHoras; }
void Curso::setCantidadInscritos(int cantidadInscritos) { this->cantidadInscritos = cantidadInscritos; }
void Curso::setNumLecciones(int numLecciones) { this->numLecciones = numLecciones; }
void Curso::setduracionentexto(const string& d) {
    duracionentexto = d;
}

void Curso::agregarLeccion(Leccion* leccion) {
    lecciones.insertarAlFinal(leccion);
    numLecciones++;
}

void Curso::guardarLeccionesEnArchivo(const string& ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para guardar lecciones." << endl;
        return;
    }

    Nodo<Leccion*>* actual = lecciones.obtenerCabeza();
    while (actual != nullptr) {
        archivo << actual->dato->getTitulo() << "|"
            << actual->dato->getContenido() << "|"
            << actual->dato->getDuracionMinutos() << "\n";
        actual = actual->siguiente;
    }

    archivo.close();
}

void Curso::cargarLeccionesDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para cargar lecciones." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        size_t pos1 = linea.find("|");
        size_t pos2 = linea.find("|", pos1 + 1);

        string titulo = linea.substr(0, pos1);
        string contenido = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        int duracion = stoi(linea.substr(pos2 + 1));

        Leccion* lec = new Leccion(titulo, contenido, duracion);
        agregarLeccion(lec);
    }

    archivo.close();
}

void Curso::eliminarLeccion(string tituloLeccion) {
}

Leccion* Curso::obtenerLeccionActual() {
    return nullptr;
}

void Curso::siguienteLeccion() {
}

void Curso::anteriorLeccion() {
}

int Curso::contarLeccionesRecursivo() {
    return 0;
}

void Curso::aumentarInscritos() {
    cantidadInscritos++;
}

void Curso::reducirInscritos() {
    if (cantidadInscritos > 0) cantidadInscritos--;
}

