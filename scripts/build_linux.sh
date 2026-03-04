#!/bin/bash
echo "Compilando Sudoku para Linux..."
g++ archivos.cpp pantalla.cpp varios.cpp Sodoku.cpp -o sodoku -std=c++17
echo "Compilación completada: ./sodoku"
