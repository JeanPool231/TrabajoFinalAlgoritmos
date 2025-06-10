#include "Leccion.h"

Leccion::Leccion() : duracionMinutos(0) {}

Leccion::Leccion(string& titulo, string& contenido, int duracionMinutos) :
	duracionMinutos(duracionMinutos), titulo(titulo), contenido(contenido)  {}

string& Leccion::getTitulo() { return titulo; }

string& Leccion::getContenido() { return contenido; }

int Leccion::getDuracionMinutos() { return duracionMinutos; }

void Leccion::setTitulo(string& nuevoTitulo) { titulo = nuevoTitulo; }

void Leccion::setContenido(string& nuevoContenido) { titulo = nuevoContenido; }

void Leccion::setDuracionMinutos(int nuevaDuracion) { titulo = nuevaDuracion; }