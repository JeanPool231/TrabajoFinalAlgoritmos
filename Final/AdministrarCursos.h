#pragma once
#include "Curso.h"
#include "Nodo.h"
#include "ListaEnlazada.h"
#include <iostream>
using namespace std;

class AdministrarCurso {
private:
    ListaEnlazada<Curso> cursos;
public:
    AdministrarCurso();
    AdministrarCurso(ListaEnlazada<Curso> cursos);
    ~AdministrarCurso();

    void ImprimirNombreCursos();
    void ImprimirNombreCursosIndices();
    void verDetallesCursos(int indice);

    Curso InscribirseACurso(int indice);

	template<typename Cmp>
	void mostrarCursosOrdenados(Cmp comparador) {
		vector<Curso> ordenado;
		Nodo<Curso>* actual = cursos.obtenerCabeza();

		while (actual != nullptr) {
			ordenado.push_back(actual->dato);
			actual = actual->siguiente;
		}

		function<void(int, int)> mergeSort = [&](int izquierda, int derecha) {
			if (izquierda >= derecha) return;

			int medio = (izquierda + derecha) / 2;
			mergeSort(izquierda, medio);
			mergeSort(medio + 1, derecha);

			vector<Curso> temp;
			int i = izquierda, j = medio + 1;

			while (i <= medio && j <= derecha) {
				if (comparador(ordenado[i], ordenado[j]))
					temp.push_back(ordenado[i++]);
				else
					temp.push_back(ordenado[j++]);
			}

			while (i <= medio) temp.push_back(ordenado[i++]);
			while (j <= derecha) temp.push_back(ordenado[j++]);

			for (int k = 0; k < temp.size(); ++k)
				ordenado[izquierda + k] = temp[k];
			};

		mergeSort(0, ordenado.size() - 1);
		int k = 1;
		for (Curso& c : ordenado) {
			cout << (k++) <<". " << c.getNombre() << '\n';
		}
	}

};
