// archivos.h = v:0.9.4
#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include "constantes.h"
#include <string>
#include <vector>
using namespace std;

// Manejo de archivos de guardado y carga
string generarNombreArchivo();
vector<string> listarArchivosGuardados();
void mostrarError(string mensaje);
void guardarPartidaEnArchivo();
void cargarPartidaDesdeArchivo();
bool sudokuValido(int matriz[TAM][TAM]); // Se usa en menuBackDoor() de Sodoku.cpp
void exportarMatrizACSV();
// ─── Score Retro v0.9 ───
// Registro de score para cada partida
struct ScoreEntry {
    char iniciales[4];
    int nivel;
    int erroresFallidos;
    int duracionSegundos;
    int erroresPermitidos; // nuevo
    char timestamp[16];    // ← un único timestamp
};
// Declaración externa del arreglo de scores, para que otros módulos lo vean
extern ScoreEntry scores[3][5];
// Prototipos de funciones de score (antes eran static en .cpp)
//  ─── Score Retro v0.9 ───
void cargarScores();
void actualizarScores(const ScoreEntry& entrada);
void guardarScores();
void resetScores();

#endif // ARCHIVOS_H