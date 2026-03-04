// pantalla.h = v:0.9.4
#ifndef PANTALLA_H
#define PANTALLA_H
using namespace std;
#pragma once
// Funciones relacionadas con el manejo de la máscara visual del tablero
void limpiarMascara(char mascara[TAM][TAM]);
void marcarFila(int fila);
void marcarColumna(int columna);
void marcarInterseccion(int fila, int columna);
void mostrarScores(int nivel);

#endif // PANTALLA_H