#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

echo "Compilando Sodoku para Windows (.exe)..."
echo "Raiz del proyecto: ${ROOT_DIR}"

x86_64-w64-mingw32-g++ -std=c++17 -Wall -Wextra -pthread \
    "${ROOT_DIR}/src/archivos.cpp" \
    "${ROOT_DIR}/src/pantalla.cpp" \
    "${ROOT_DIR}/src/varios.cpp" \
    "${ROOT_DIR}/src/Sodoku.cpp" \
    "${ROOT_DIR}/src/backdoor.cpp" \
    -static -lwinpthread \
    -o "${ROOT_DIR}/sodoku.exe"

echo "Compilacion completada: ${ROOT_DIR}/sodoku.exe"

# Si querés dejarlo listo para usar:
#chmod +x scripts/build_windows.sh