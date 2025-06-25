#include "CursoUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>

Curso* leerCursoDesdeArchivo(std::string ruta) {
    std::ifstream archivo(ruta);
    Curso* curso = new Curso();

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << ruta << std::endl;
        return nullptr;
    }

    std::string linea;
    bool leyendoLecciones = false;
    bool nombreYaLeido = false;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        linea.erase(0, linea.find_first_not_of(" \t\r\n"));
        linea.erase(linea.find_last_not_of(" \t\r\n") + 1);

        if (!leyendoLecciones) {
            if (!nombreYaLeido && linea.front() == '[' && linea.back() == ']') {
                std::string nombre = linea.substr(1, linea.size() - 2);
                curso->setNombre(nombre);
                nombreYaLeido = true;
            }
            else if (linea == "[LECCIONES]") {
                leyendoLecciones = true;
            }
            else if (linea.rfind("id:", 0) == 0) {
                curso->setId(linea.substr(3));
            }
            else if (linea.rfind("categoria:", 0) == 0) {
                curso->setCategoria(linea.substr(9));
            }
            else if (linea.rfind("descripcion:", 0) == 0) {
                curso->setDescripcion(linea.substr(11));
            }
            else if (linea.rfind("duracion:", 0) == 0) {
                std::string dur = linea.substr(8);
                int horas = 0;
                for (char c : dur) {
                    if (isdigit(c)) horas = horas * 10 + (c - '0');
                    else break;
                }
                curso->setDuracionHoras(horas);
            }
            else if (linea.rfind("fecha:", 0) == 0) {
                curso->setFechaCreacion(linea.substr(6));
            }
        }
        else {
            if (linea.rfind("- ", 0) == 0) {
                std::string titulo = linea.substr(2);
                Leccion* lec = new Leccion(titulo, "", 0);
                curso->getLecciones().insertarAlFinal(lec);
            }
        }
    }

    archivo.close();
    return curso;
}
