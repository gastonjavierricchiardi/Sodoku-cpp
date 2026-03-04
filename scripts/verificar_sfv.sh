#!/usr/bin/env bash

# Buscamos el primer .sfv en el directorio actual
archivo_sfv=$(find . -maxdepth 1 -type f -name "*.sfv" | head -n 1)

if [ -z "$archivo_sfv" ]; then
  echo "❌ No se encontró ningún archivo .sfv en el directorio actual."
  exit 1
fi

echo "🔎 Verificando archivos usando: $archivo_sfv"

# -g para 'go to' y verificar
cksfv -g "$archivo_sfv"

echo "✅ Verificación completada."

