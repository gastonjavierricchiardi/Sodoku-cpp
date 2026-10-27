// Sodoku.h = v:0.9.4
#ifndef SODOKU_H
#define SODOKU_H

#include "constantes.h" // Para usar TAM, etc.
#include <string>       // Necesario para usar std::string
using namespace std;
#pragma once

// Fecha y hora de compilación de la versión actual
#define FECHA_VERSION "Jun 17 2025"
#define HORA_VERSION "00:00:00"
#define VERSION "0.9.4" // Versión del juego

// Variables Globales y CONSTANTES:
// Tamaño del tablero en constantes.h
// Variables globales accesibles desde otros módulos
extern int MATRIZ[TAM][TAM];     // juego
extern int SOLUCION[TAM][TAM];   // tablero resuelto
extern char MASCARA[TAM][TAM];   // máscara visual del tablero
extern bool CELDAFIJA[TAM][TAM]; // celdas fijas
extern char CARACTERPAUSA;       // carácter de pausa visual
extern int endGame;              // número de intentos fallidos para terminar el juego
extern bool partidaEnCurso;      // Flag para saber si hay una partida suspendida
extern int intentosFallidos;     // Contador de intentos fallidos que tambien se usa para grabar el Game Over
extern int nivelCargado;         // Nivel de la partida cargada (0=Fácil,1=Medio,2=Difícil)
// Códigos especiales de menú en constantes.h
// Nuevo: estado de lectura de ingreso de usuario
enum class IngresoStatus {
    OK,         // fila, columna y valor válidos
    CANCELAR,   // código de “cancelar” (CODIGO_SALIR)
    BACKDOOR,   // código de menú oculto (CODIGO_BACKDOOR)
    ERROR_SALIR // rango inválido, cin.fail() o “salir” (0)
};

// Cantidad de celdas a vaciar por dificultad en constantes.h
void limpiarTablero();
void generarMascara(int fila, int columna, char mascara[TAM][TAM]);
void generarMascaraCompletaPausa(char CARACTERPAUSA);
void generarTableroAleatorio(int nivel); // Genera tablero desde solución
void DibujarPantalla();                  // Actualizado a v.0.8.5
void modoIngresoManual();
int seleccionarDificultad();  // Elegir nivel de dificultad
void iniciarJuego();          // Modo competitivo
void jugarPartida(int nivel); // Juego con control de tiempo y errores
bool validaHorizontal(int matriz[TAM][TAM], int fila, int valor);
bool validaVertical(int matriz[TAM][TAM], int columna, int valor);
bool validaRecuadro(int matriz[TAM][TAM], int fila, int columna, int valor);
void fijarCeldasActuales(); // Fijar celdas
bool hayCeldasFijas();
bool numeroAgotadoGlobal(int numero);
bool numeroPresenteEnCuadro(int fila, int columna, int numero); // NUEVA 01
int cantidadRestante(int numero);
void menuPrincipal();
void subMenuBackDoor(int nivel); // 0 = Básico, 1 = Avanzado, 2 = SuperUsuario
int main();
void mostrarMatriz(int matriz[TAM][TAM], std::string titulo); // 👈 declaración necesaria para otros módulos
// Nuevo: función auxiliar para procesar ingreso de fila/columna/valor
IngresoStatus procesarIngresoUsuario(
    int& fila,
    int& columna,
    int& valor);
// Prueba rápida de la generación aleatoria de soluciones
// void pruebaRandom();
void configurarGameOver();

// End of file
#endif // SODOKU_H