// varios.cpp = v:0.9.4
#include <algorithm>
// #include <cstdlib>   // conserva si aún usas rand(), si no bórralo
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits> // Nuevo
#include <random> // std::mt19937, std::random_device
#include <sstream>
#include <string>
#include <utility> // NUEVO R-02 para std::pair
#include <vector>  // para std::vector
using namespace std;
// Definición y semilla única del generador global
std::mt19937 rng(std::random_device{}());
// Headers de tu proyecto
#include "Sodoku.h"
#include "archivos.h"
#include "constantes.h"
#include "varios.h" // declara rng y VACIOS_*
#ifdef _WIN32
#include <windows.h>
#ifndef CP_UTF8
#define CP_UTF8 65001
#endif
#endif

using std::cout;
using std::string;

///////////////////////////////////////////////////////////////////////////////////////

void autor() {
    string fechaStr = FECHA_VERSION;
    string horaStr = HORA_VERSION;
    string mesStr = fechaStr.substr(0, 3);
    int dia = stoi(fechaStr.substr(4, 2));
    int anio = stoi(fechaStr.substr(7, 4));
    int hora = stoi(horaStr.substr(0, 2));
    int minuto = stoi(horaStr.substr(3, 2));
    int segundo = stoi(horaStr.substr(6, 2));
    string meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int mes = 0;
    for (int i = 0; i < 12; i++)
        if (mesStr == meses[i]) {
            mes = i;
            break;
        }
    tm fechaVersion = {};
    fechaVersion.tm_year = anio - 1900;
    fechaVersion.tm_mon = mes;
    fechaVersion.tm_mday = dia;
    fechaVersion.tm_hour = hora;
    fechaVersion.tm_min = minuto;
    fechaVersion.tm_sec = segundo;
    fechaVersion.tm_isdst = -1;
    time_t tiempoVersion = mktime(&fechaVersion);
    time_t ahora = time(0);
    double segundosTranscurridos = difftime(ahora, tiempoVersion);
    int horas = segundosTranscurridos / 3600;
    int minutos = ((int)segundosTranscurridos % 3600) / 60;
    colorTexto("cyan");
    cout << "Sodoku C++ v:" << VERSION << endl; // AQUI SE PUEDE CAMBIAR LA VERSION
    cout << "Desarrollado por: Gaston Ricchiardi" << endl;
    cout << "Colaboración: Desirée Benitez" << endl;
    cout << "Testeo:" << endl;
    cout << "+ Francisco" << endl;
    cout << "+ Tiago" << endl;
    cout << "+ Valeria" << endl;
    cout << "\U0001F4E6 Build: " << FECHA_VERSION << " - " << HORA_VERSION << endl;
    cout << "⏱️ Tiempo desde versión: "; // Movi un espacio a la izq porque estaba raro
    if (horas > 0)
        cout << horas << "h ";
    cout << minutos << "min" << endl;
    cout << "----------------------------------------" << endl;
    resetColor();
}

///////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------
// Reemplazo de system("cls") / system("pause") por implementaciones
// portables y más seguras.
// ----------------------------------------------------------------

void limpiarPantalla() {
#ifdef _WIN32
    // Windows API para limpiar consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD written, dwSize;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', dwSize, coordScreen, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwSize, coordScreen, &written);
    SetConsoleCursorPosition(hConsole, coordScreen);
#else
    // ANSI escape codes para Unix/Linux/macOS
    std::cout << "\x1B[2J\x1B[H";
#endif
}

///////////////////////////////////////////////////////////////////////////////////////

void MSGPAUSA() {
    // Espera a que el usuario presione Enter
    std::cout << "Presione Enter para continuar..." << std::flush;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // captura el Enter que el usuario presiona
}
///////////////////////////////////////////////////////////////////////////////////////
void colorTexto(const std::string& color) {
    if (color == "rojo")
        std::cout << "\033[1;31m";
    else if (color == "verde")
        std::cout << "\033[1;32m";
    else if (color == "amarillo")
        std::cout << "\033[1;33m";
    else if (color == "azul")
        std::cout << "\033[1;34m";
    else if (color == "magenta")
        std::cout << "\033[1;35m";
    else if (color == "cyan")
        std::cout << "\033[1;36m";
    else if (color == "blanco")
        std::cout << "\033[1;37m";
    else
        std::cout << "\033[0m"; // por defecto
}

///////////////////////////////////////////////////////////////////////////////////////
void resetColor() {
    std::cout << "\033[0m";
}
///////////////////////////////////////////////////////////////////////////////////////
// Jugabilidad:
void generarTableroAleatorio(int nivel) {
    limpiarPantalla();

    // Paso 1: Generar solución aleatoria
    bool exito = generarSodokuResuelto();
    if (!exito) {
        mostrarError("No se pudo generar un tablero resuelto válido.");
        return;
    }

    // Paso 2: Copiar solución a MATRIZ (para trabajar sobre ella)
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            MATRIZ[i][j] = SOLUCION[i][j];

    // 🧼 Paso 3: Vaciar celdas (esto deja ceros en algunas posiciones)
    vaciarCeldas(nivel);

    // 🔒 Paso 4: Fijar celdas restantes como no modificables
    // fijarCeldasActuales();

    // 🎯 Mensaje final
    string dificultad;
    switch (nivel) {
    case 0:
        dificultad = "FÁCIL";
        break;
    case 1:
        dificultad = "MEDIA";
        break;
    case 2:
        dificultad = "DIFÍCIL";
        break;
    default:
        dificultad = "DESCONOCIDA";
        break;
    }

    colorTexto("verde");
    cout << "\n✅ Tablero generado con dificultad: " << dificultad << endl;
    resetColor();
}

///////////////////////////////////////////////////////////////////////////////////////
bool generarSodokuResuelto() {
    // Inicializamos con ceros
    for (int fila = 0; fila < TAM; fila++) {
        for (int col = 0; col < TAM; col++) {
            SOLUCION[fila][col] = 0;
        }
    }
    return resolverSudoku(SOLUCION);
}

///////////////////////////////////////////////////////////////////////////////////////
// Nuevo Vaciar Celdas
void vaciarCeldas(int nivel) {
    int celdasAVaciar;
    switch (nivel) {
    case 0:
        celdasAVaciar = VACIOS_FACIL;
        break;
    case 1:
        celdasAVaciar = VACIOS_MEDIA;
        break;
    case 2:
        celdasAVaciar = VACIOS_DIFICIL;
        break;
    default:
        celdasAVaciar = VACIOS_MEDIA;
        break;
    }

    // 1) Construir lista de todas las posiciones
    std::vector<std::pair<int, int>> posiciones;
    posiciones.reserve(TAM * TAM);
    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j)
            posiciones.emplace_back(i, j);

    // 2) Mezclar con mt19937
    std::shuffle(posiciones.begin(), posiciones.end(), rng);

    // 3) Vaciar las primeras 'celdasAVaciar'
    for (int k = 0; k < celdasAVaciar && k < (int)posiciones.size(); ++k) {
        int i = posiciones[k].first;
        int j = posiciones[k].second;
        MATRIZ[i][j] = 0;
    }

    colorTexto("amarillo");
    std::cout << "🧽 Se vaciaron " << celdasAVaciar
              << " celdas para la dificultad seleccionada." << std::endl;
    resetColor();
}

bool esSeguro(int matriz[TAM][TAM], int fila, int columna, int numero) {
    // Verificar fila
    for (int col = 0; col < TAM; col++)
        if (matriz[fila][col] == numero)
            return false;

    // Verificar columna
    for (int fil = 0; fil < TAM; fil++)
        if (matriz[fil][columna] == numero)
            return false;

    // Verificar subcuadro 3x3
    int inicioFila = fila - fila % 3;
    int inicioCol = columna - columna % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (matriz[inicioFila + i][inicioCol + j] == numero)
                return false;

    return true;
}

bool resolverSudoku(int matriz[TAM][TAM]) {
    for (int fila = 0; fila < TAM; fila++) {
        for (int columna = 0; columna < TAM; columna++) {
            if (matriz[fila][columna] == 0) {
                std::vector<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                // Nuevo shuffle con mt19937
                std::shuffle(numeros.begin(), numeros.end(), rng);
                for (int num : numeros) {
                    if (esSeguro(matriz, fila, columna, num)) {
                        matriz[fila][columna] = num;
                        if (resolverSudoku(matriz))
                            return true;
                        matriz[fila][columna] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// configuramos la consola
void configurarConsola() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);

    // Activar soporte de secuencias ANSI (colores) en Windows 10+
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif
    resetColor();
}
