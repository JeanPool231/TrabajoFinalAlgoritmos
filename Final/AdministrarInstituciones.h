#pragma once

#include "Institucion.h"
#include "Profesor.h"
#include "Curso.h"
#include "AVLTree.h"
#include "ListaEnlazada.h"

void guardarprofenelarchivo(Profesor prof);

void agregarprofesor2(Institucion& inst);

void mostrarhistorial2(const ListaEnlazada<string>& logs);

void quitarprofesor2(Institucion& inst);

void asignarcursoalprofe2(Institucion& inst);

void desvincularcursoalprofe2(Institucion& inst);
