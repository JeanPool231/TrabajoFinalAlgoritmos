#pragma once
#include <string>
#include <fstream>
#include "Leccion.h"
#include "ListaEnlazada.h"

using namespace std;

class Curso {
private:
    string nombre;
    string id;
    string categoria;
    string descripcion;
    string fechaCreacion; //aprovechando q vamos a usar lo del tiempo maybe
    //double costo;
    int duracionHoras;
    int cantidadInscritos;
    int numLecciones;
    string duracionentexto;
    ListaEnlazada<Leccion*> lecciones;


public:
    Curso();
    Curso(string& nombre, string id, string& categoria, string& descripcion, string fechaCreacion,
        int duracionHoras, int cantidadInscritos, int numLecciones);
    ~Curso();

    // Getters
    string getNombre();
    string getId();
    string getCategoria();
    string getDescripcion();
    string getFechaCreacion();
    int getDuracionHoras();
    int getCantidadInscritos();
    int getNumLecciones();
    string getduracionentexto() const;
    //double getCosto();
    // Setters
    ListaEnlazada<Leccion*>& getLecciones();
    void setId(string);
    void setNombre(string);
    void setCategoria(string);
    void setDescripcion(string);
    void setDuracionHoras(int);
    void setFechaCreacion(string);
    void setCantidadInscritos(int);
    void setNumLecciones(int);
    void setduracionentexto(const string&);
    //void setCosto(double costo);

    // Quizas quzias algo como para gestionar lecciones
    void agregarLeccion(Leccion* leccion);

    void guardarLeccionesEnArchivo(const string& ruta);
    void cargarLeccionesDesdeArchivo(const string& ruta);

    //e


    void eliminarLeccion(string tituloLeccion);

    Leccion* obtenerLeccionActual();
    void siguienteLeccion();
    void anteriorLeccion();

    int contarLeccionesRecursivo();

    void aumentarInscritos();
    void reducirInscritos();
};


