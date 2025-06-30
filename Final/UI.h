#pragma once
#include <iostream>
#include <io.h>
#include <fcntl.h>
using namespace std;
class UI {
private:
    void moverCursor(int fila, int columna) {
        std::wcout << L"\033[" << fila << L";" << columna << L"H";
    }
public:

    void cuadro(int ancho, int alto) {
        if (ancho < 2 || alto < 2) return; // mínimo necesario para formar un cuadro

        _setmode(_fileno(stdout), _O_U16TEXT);

        wchar_t horizontal = L'═';
        wchar_t vertical = L'║';
        wchar_t esquina_sup_izq = L'╔';
        wchar_t esquina_sup_der = L'╗';
        wchar_t esquina_inf_izq = L'╚';
        wchar_t esquina_inf_der = L'╝';

        // Línea superior
        std::wcout << esquina_sup_izq;
        for (int i = 0; i < ancho - 2; ++i)
            std::wcout << horizontal;
        std::wcout << esquina_sup_der << std::endl;

        // Líneas intermedias
        for (int i = 0; i < alto - 2; ++i) {
            std::wcout << vertical;
            for (int j = 0; j < ancho - 2; ++j)
                std::wcout << L' ';
            std::wcout << vertical << std::endl;
        }

        // Línea inferior
        std::wcout << esquina_inf_izq;
        for (int i = 0; i < ancho - 2; ++i)
            std::wcout << horizontal;
        std::wcout << esquina_inf_der << std::endl;

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloOpcion(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila, columna);
        std::wcout << L"╔═╗┌─┐┌─┐┬┌─┐┌┐┌\n";
        moverCursor(fila + 1, columna);
        std::wcout << L"║ ║├─┘│  ││ ││││\n";
        moverCursor(fila + 2, columna);
        std::wcout << L"╚═╝┴  └─┘┴└─┘┘└┘\n";

        _setmode(_fileno(stdout), _O_TEXT);
    }

    void cuadro_dividido(int ancho, int alto) {
        if (ancho < 2 || alto < 2) return; // mínimo necesario para formar un cuadro

        _setmode(_fileno(stdout), _O_U16TEXT);

        wchar_t horizontal = L'═';
        wchar_t vertical = L'║';
        wchar_t esquina_sup_izq = L'╔';
        wchar_t esquina_sup_der = L'╗';
        wchar_t esquina_inf_izq = L'╚';
        wchar_t esquina_inf_der = L'╝';
        wchar_t abajo = L'╦';
        wchar_t arriba = L'╩';
        // Línea superior
        std::wcout << esquina_sup_izq;
        for (int i = 0; i < ancho - 2; ++i)
            if (i == 25) std::wcout << abajo;
            else std::wcout << horizontal;
        std::wcout << esquina_sup_der << std::endl;

        // Líneas intermedias
        for (int i = 0; i < alto - 2; ++i) {
            std::wcout << vertical;
            for (int j = 0; j < ancho - 2; ++j)
                if (j == 25) {
                    std::wcout << vertical;
                }
                else std::wcout << L' ';
            std::wcout << vertical << std::endl;
        }

        // Línea inferior
        std::wcout << esquina_inf_izq;
        for (int i = 0; i < ancho - 2; ++i)
            if (i == 25)std::wcout << arriba;
            else std::wcout << horizontal;
        std::wcout << esquina_inf_der << std::endl;
        cuadroDobleLineas(23, 4, 20, 4);
        moverCursor(22, 4);
        wcout << L"Input:";
        //tituloOpcion(20, 4);
        
        moverCursor(2, 2);
        wcout << L"MENU DE";
        moverCursor(3, 2);
        wcout << L"OPCIONES";
        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloIniciarSesion(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT); // Activar UTF-16

        moverCursor(fila, columna);
        std::wcout << L" ▀█▀ █▀█ ▀█▀ █▀▀ ▀█▀ █▀█ █▀▄   █▀▀ █▀▀ █▀▀ ▀█▀ █▀█ █▀█\n";
        moverCursor(fila + 1, columna);
        std::wcout << L"  █  █ █  █  █    █  █▀█ █▀▄   ▀▀█ █▀▀ ▀▀█  █  █ █ █ █\n";
        moverCursor(fila + 2, columna);
        std::wcout << L" ▀▀▀ ▀ ▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀ ▀ ▀ ▀   ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀ ▀\n";

        _setmode(_fileno(stdout), _O_TEXT); // Restaurar modo normal
    }
    void cuadroPosicional(int fila, int columna, int ancho, int alto) {
        if (ancho < 2 || alto < 2) return;

        _setmode(_fileno(stdout), _O_U16TEXT);

        wchar_t horizontal = L'═';
        wchar_t vertical = L'║';
        wchar_t esquina_sup_izq = L'╔';
        wchar_t esquina_sup_der = L'╗';
        wchar_t esquina_inf_izq = L'╚';
        wchar_t esquina_inf_der = L'╝';

        // Línea superior
        moverCursor(fila, columna);
        std::wcout << esquina_sup_izq;
        for (int i = 0; i < ancho - 2; ++i)
            std::wcout << horizontal;
        std::wcout << esquina_sup_der;

        // Líneas intermedias
        for (int i = 1; i < alto - 1; ++i) {
            moverCursor(fila + i, columna);
            std::wcout << vertical;
            for (int j = 0; j < ancho - 2; ++j)
                std::wcout << L' ';
            std::wcout << vertical;
        }

        // Línea inferior
        moverCursor(fila + alto - 1, columna);
        std::wcout << esquina_inf_izq;
        for (int i = 0; i < ancho - 2; ++i)
            std::wcout << horizontal;
        std::wcout << esquina_inf_der;

        _setmode(_fileno(stdout), _O_TEXT);
    }

    void cuadroDobleLineas(int fila, int columna, int ancho, int alto) {
        if (ancho < 2 || alto < 2) return;

        _setmode(_fileno(stdout), _O_U16TEXT);

        wchar_t horizontal = L'─';
        wchar_t vertical = L'│';
        wchar_t esquina_sup_izq = L'┌';
        wchar_t esquina_sup_der = L'┐';
        wchar_t esquina_inf_izq = L'└';
        wchar_t esquina_inf_der = L'┘';

        for (int y = 0; y < alto; ++y) {
            moverCursor(fila + y, columna);
            for (int x = 0; x < ancho; ++x) {
                if (y == 0 && x == 0) std::wcout << esquina_sup_izq;
                else if (y == 0 && x == ancho - 1) std::wcout << esquina_sup_der;
                else if (y == alto - 1 && x == 0) std::wcout << esquina_inf_izq;
                else if (y == alto - 1 && x == ancho - 1) std::wcout << esquina_inf_der;
                else if (y == 0 || y == alto - 1) std::wcout << horizontal;
                else if (x == 0 || x == ancho - 1) std::wcout << vertical;
                else std::wcout << L' ';
            }
        }

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloEmail(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila, columna);
        std::wcout << L"┏┓     •┓\n";
        moverCursor(fila + 1, columna);
        std::wcout << L"┣ ┏┳┓┏┓┓┃\n";
        moverCursor(fila + 2, columna);
        std::wcout << L"┗┛┛┗┗┗┻┗┗\n";

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloPassword(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila, columna);
        std::wcout << L"┏┓                \n";
        moverCursor(fila + 1, columna);
        std::wcout << L"┃ ┏┓┏┓╋┏┓┏┓┏┏┓┏┓┏┓\n";
        moverCursor(fila + 2, columna);
        std::wcout << L"┗┛┗┛┛┗┗┛ ┗┻┛┗ ┛┗┗┻\n";

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloCoursera(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila, columna);
        std::wcout << L" █▀▀ █▀█ █ █ █▀▄ █▀▀ █▀▀ █▀▄ █▀█\n";
        moverCursor(fila + 1, columna);
        std::wcout << L" █   █ █ █ █ █▀▄ ▀▀█ █▀▀ █▀▄ █▀█\n";
        moverCursor(fila + 2, columna);
        std::wcout << L" ▀▀▀ ▀▀▀ ▀▀▀ ▀ ▀ ▀▀▀ ▀▀▀ ▀ ▀ ▀ ▀\n";

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloElegirPerfil(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila, columna);
        std::wcout << L"░█▀▀░█░░░█▀▀░█▀▀░▀█▀░█▀▄░░░█▀█░█▀▀░█▀▄░█▀▀░▀█▀░█░░\n";
        moverCursor(fila + 1, columna);
        std::wcout << L"░█▀▀░█░░░█▀▀░█░█░░█░░█▀▄░░░█▀▀░█▀▀░█▀▄░█▀▀░░█░░█░░\n";
        moverCursor(fila + 2, columna);
        std::wcout << L"░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░▀░▀░░░▀░░░▀▀▀░▀░▀░▀░░░▀▀▀░▀▀▀\n";

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void logoProfesor(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila++, columna); std::wcout << L"  ██████████████  \n";
        moverCursor(fila++, columna); std::wcout << L"     ████████     \n";
        moverCursor(fila++, columna); std::wcout << L"    ██      ██    \n";
        moverCursor(fila++, columna); std::wcout << L"    ██████  ██    \n";
        moverCursor(fila++, columna); std::wcout << L"   ██ ██████  █   \n";
        moverCursor(fila++, columna); std::wcout << L"    ██ ████ ██    \n";
        moverCursor(fila++, columna); std::wcout << L"      ██  ██      \n";
        moverCursor(fila++, columna); std::wcout << L"   █████████████  \n";
        moverCursor(fila++, columna); std::wcout << L" █     ████     ██\n";
        moverCursor(fila++, columna); std::wcout << L"██████████████████\n";

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void logoEstudiante(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila++, columna); std::wcout << L"     ████████     \n";
        moverCursor(fila++, columna); std::wcout << L"    ██      ██    \n";
        moverCursor(fila++, columna); std::wcout << L"    ██████  ██    \n";
        moverCursor(fila++, columna); std::wcout << L"   ██ ██████  █   \n";
        moverCursor(fila++, columna); std::wcout << L"    ██ ████ ██    \n";
        moverCursor(fila++, columna); std::wcout << L"      ██  ██      \n";
        moverCursor(fila++, columna); std::wcout << L"   █████████████  \n";
        moverCursor(fila++, columna); std::wcout << L" █              ██\n";
        moverCursor(fila++, columna); std::wcout << L"██████████████████\n";

        _setmode(_fileno(stdout), _O_TEXT);
    }
    void logoInstitucion(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila++, columna); std::wcout << L"       ██       \n";
        moverCursor(fila++, columna); std::wcout << L"    ████████    \n";
        moverCursor(fila++, columna); std::wcout << L"  ████████████  \n";
        moverCursor(fila++, columna); std::wcout << L"  ████████████  \n";
        moverCursor(fila++, columna); std::wcout << L"   ██  ██  ██   \n";
        moverCursor(fila++, columna); std::wcout << L"   ██  ██  ██   \n";
        moverCursor(fila++, columna); std::wcout << L"  ████████████  \n";
        moverCursor(fila++, columna); std::wcout << L"  ████████████  \n";
        moverCursor(fila++, columna); std::wcout << L"████████████████\n";
        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloRegistroEstudiante(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);
        moverCursor(fila++, columna);
        std::wcout << L"░█▀▄░█▀▀░█▀▀░▀█▀░█▀▀░▀█▀░█▀▄░█▀█░░░█▀▀░█▀▀░▀█▀░█░█░█▀▄░▀█▀░█▀█░█▀█░▀█▀░█▀▀\n";
        moverCursor(fila++, columna);
        std::wcout << L"░█▀▄░█▀▀░█░█░░█░░▀▀█░░█░░█▀▄░█░█░░░█▀▀░▀▀█░░█░░█░█░█░█░░█░░█▀█░█░█░░█░░█▀▀\n";
        moverCursor(fila++, columna);
        std::wcout << L"░▀░▀░▀▀▀░▀▀▀░▀▀▀░▀▀▀░░▀░░▀░▀░▀▀▀░░░▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀░░▀▀▀░▀░▀░▀░▀░░▀░░▀▀▀\n";
        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloNombre(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila++, columna); std::wcout << L"┳┓     ┓     \n";
        moverCursor(fila++, columna); std::wcout << L"┃┃┏┓┏┳┓┣┓┏┓┏┓\n";
        moverCursor(fila++, columna); std::wcout << L"┛┗┗┛┛┗┗┗┛┛ ┗ \n";

        _setmode(_fileno(stdout), _O_TEXT);
    }    
    void tituloApellido(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila++, columna); std::wcout << L"┏┓    ┓┓• ┓  \n";
        moverCursor(fila++, columna); std::wcout << L"┣┫┏┓┏┓┃┃┓┏┫┏┓\n";
        moverCursor(fila++, columna); std::wcout << L"┛┗┣┛┗ ┗┗┗┗┻┗┛\n";
        moverCursor(fila++, columna); std::wcout << L"  ┛           \n";
        _setmode(_fileno(stdout), _O_TEXT);
    }
    void tituloConfirmar(int fila, int columna) {
        _setmode(_fileno(stdout), _O_U16TEXT);

        moverCursor(fila++, columna); std::wcout << L"┏┓    ┏•         \n";
        moverCursor(fila++, columna); std::wcout << L"┃ ┏┓┏┓╋┓┏┓┏┳┓┏┓┏┓\n";
        moverCursor(fila++, columna); std::wcout << L"┗┛┗┛┛┗┛┗┛ ┛┗┗┗┻┛ \n";
        moverCursor(fila++, columna); std::wcout << L"┏┏┓┏┓╋┏┓┏┓┏┏┓┏┓┏┓\n";
        moverCursor(fila++, columna); std::wcout << L"┗┗┛┛┗┗┛ ┗┻┛┗ ┛┗┗┻\n";
        moverCursor(fila++, columna); std::wcout << L"                  \n";

        _setmode(_fileno(stdout), _O_TEXT);
    }
};
