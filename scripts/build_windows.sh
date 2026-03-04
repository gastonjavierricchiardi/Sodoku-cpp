#!/bin/bash
echo "Compilando Sudoku para Windows (.exe)..."
x86_64-w64-mingw32-g++ archivos.cpp pantalla.cpp varios.cpp Sodoku.cpp -o sodoku.exe -std=c++17 -static
echo "Compilación completada: sodoku.exe"
