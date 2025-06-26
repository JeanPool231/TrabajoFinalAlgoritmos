/*
#include <iostream>
#include "Sistema.h"

//#include <windows.h>
//#undef byte
using namespace std;

int main(){

	system("pause");
	return 0;
}
*/
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include "Sistema.h"
int main() {
	setlocale(LC_ALL, "");

	Sistema sistema;
	sistema.iniciarPrograma();
    return 0;
}

