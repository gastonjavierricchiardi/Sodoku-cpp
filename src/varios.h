// varios.h = v:0.9.4
#ifndef VARIOS_H
#define VARIOS_H
#include <string>
using namespace std;
#pragma once
#include <random>
extern std::mt19937 rng;
// Fin RANDOM
#ifdef _WIN32
// Evitar macro y tipos innecesarios
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#ifndef CP_UTF8
#define CP_UTF8 65001
#endif

// Eliminar el typedef byte de RPC para que no choque con std::byte
#undef byte
#endif

// Funciones generales de utilidad
void autor();
void MSGPAUSA();
void limpiarPantalla();
void colorTexto(const std::string& color);
void resetColor();

// Jugabilidad
void generarTableroAleatorio(int nivel);
bool generarSodokuResuelto();
bool resolverSudoku(int matriz[TAM][TAM]);
bool esSeguro(int matriz[TAM][TAM], int fila, int columna, int numero);
void vaciarCeldas(int nivel); // Borra celdas según el nivel de dificultad

// Inicialización de consola (UTF-8, colores, etc.)
void configurarConsola();

#endif // VARIOS_H