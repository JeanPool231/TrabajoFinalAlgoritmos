#include <io.h>
#include <fcntl.h>
#include <iostream>
#include "Sistema.h"
int main() {
	setlocale(LC_ALL, "");
	cout << "\033[?25l"; // eliminar cursos
	cout << "\033[?25h"; // mostrar cursor luego de eliminar cursor
	Sistema sistema;
	sistema.iniciarPrograma();
    return 0;
}

