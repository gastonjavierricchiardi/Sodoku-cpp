// Pantalla.cpp = v:0.9.4
// #include <algorithm> // para random_shuffle
#include <climits> // para INT_MAX
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Dependencias de archivos separados.
#include "Sodoku.h"
#include "archivos.h"   // usa guardar/cargar/mostrarError
#include "constantes.h" // para FECHA_VERSION, HORA_VERSION, VERSION
#include "pantalla.h"
#include "varios.h" // usa colorTexto, MSGPAUSA, etc.

#ifdef _WIN32
#include <cstdlib>
#endif

void limpiarMascara(char mascara[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            mascara[i][j] = '-';
}

void marcarFila(int fila) {
    limpiarMascara(MASCARA);
    for (int j = 0; j < TAM; j++)
        MASCARA[fila][j] = '%';
}

void marcarColumna(int columna) {
    for (int i = 0; i < TAM; i++)
        if (MASCARA[i][columna] != '%') // no sobrescribe si ya había fila
            MASCARA[i][columna] = '%';
}

void marcarInterseccion(int fila, int columna) {
    MASCARA[fila][columna] = '?';
}

// ----------------------------------------------------------------
// Muestra en pantalla los top 5 scores del nivel indicado
// ----------------------------------------------------------------
void mostrarScores(int nivel) {
    cout << "Ingreso al sistema de scores" << endl;
    // exit(0);
    // Asegurarse de tener la última lista
    cargarScores();

    // Decorar nivel
    const char* nivelStr =
        (nivel == 0   ? "+++ FACIL +++++"
         : nivel == 1 ? "+++ MEDIO +++++"
                      : "+++ DIFICIL +++");

    // Cabecera retro
    cout << "\n"
         << nivelStr << "\n";
    cout << "Ini  Pos    Err  Tiempo    Timestamp\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < 5; ++i) {
        const ScoreEntry& e = scores[nivel][i];
        if (e.erroresFallidos == INT_MAX) {
            break;
        }

        int mm = e.duracionSegundos / 60;
        int ss = e.duracionSegundos % 60;

        cout << setw(3) << e.iniciales << "  "
             << setw(2) << (i + 1) << "    "
             << setw(3) << e.erroresFallidos << "    "
             << setfill('0') << setw(2) << mm << ":"
             << setw(2) << ss << setfill(' ') << "    "
             << e.timestamp << "\n";
    }

    cout << "-------------------------------------------\n";
}