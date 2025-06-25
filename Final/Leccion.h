#pragma once
#include <string>
using namespace std;

class Leccion {
private:
    string titulo;
    string contenido;
    int duracionMinutos;

public:
    Leccion();
    Leccion(string titulo, string contenido, int duracion);
    Leccion(string& titulo) : titulo(titulo), contenido(""), duracionMinutos(0) {}

    string& getTitulo();
    string& getContenido();
    int getDuracionMinutos();

    void setTitulo(string& nuevoTitulo);
    void setContenido(string& nuevoContenido);
    void setDuracionMinutos(int nuevaDuracion);
};
