#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

echo "Compilando Sodoku para Linux..."
echo "Raiz del proyecto: ${ROOT_DIR}"

g++ -std=c++17 -Wall -Wextra \
    "${ROOT_DIR}/src/archivos.cpp" \
    "${ROOT_DIR}/src/pantalla.cpp" \
    "${ROOT_DIR}/src/varios.cpp" \
    "${ROOT_DIR}/src/Sodoku.cpp" \
    "${ROOT_DIR}/src/backdoor.cpp" \
    -o "${ROOT_DIR}/sodoku"

echo "Compilacion completada: ${ROOT_DIR}/sodoku"

# Si querés dejarlo listo para usar:
# chmod +x scripts/build_linux.sh
