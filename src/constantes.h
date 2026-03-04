// constantes.h = v:0.9.4
#pragma once
using namespace std;
// ───────────────── Versión y compilación ────────────────
#define FECHA_VERSION "Jun 17 2025"
#define HORA_VERSION "00:00:00"
#define VERSION "0.9.4"

// ───────────────── Tamaño del tablero ───────────────────
constexpr int TAM = 9;

// ──────────── Celdas a vaciar según dificultad ──────────
constexpr int VACIOS_FACIL = 40;
constexpr int VACIOS_MEDIA = 50;
constexpr int VACIOS_DIFICIL = 60;

// ──────────── Códigos especiales de menú ────────────────
constexpr int CODIGO_BACKDOOR = 98;
constexpr int CODIGO_SALIR = 99;
constexpr int CODIGO_SALIR_MENU = 0;     // Variable de salir de los menus = 0
constexpr int CODIGO_SALIDA_TOTAL = 100; // Salida total de los prg.
extern bool SODOKU_RESUELTO;             // BANDERA PARA PARTIDA RESUELTA CASE 8

// ──────────── Intentos fallidos y límites ───────────────
constexpr int MAX_INTENTOS_FALLIDOS = 3;

// ──────────── Extensiones y nombres de archivos ─────────
constexpr const char* EXTENSION_PARTIDA = ".sodoku";
constexpr const char* ARCHIVO_SCORES = "scores.txt";

// ──────────── Otras globales necesarias ─────────────────
extern bool esPartidaNueva;
extern time_t tsSesionInicio;  // marca inicio de la sesion actual de juego
extern long duracionAcumulada; // segundos acumulados entre sesiones
