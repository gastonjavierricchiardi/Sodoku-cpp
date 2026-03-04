#!/usr/bin/env bash

# Nombre del .sfv a crear (p.ej. Linux.sfv)
nombre_archivo="$(basename "$PWD").sfv"

echo "🛠 Generando archivo de verificación: $nombre_archivo"

# -b para sólo nombre de archivo, no ruta.
# El wildcard (*) recorre todos los ficheros del directorio actual.
cksfv -b * > "$nombre_archivo"

echo "✅ Archivo $nombre_archivo creado con éxito."

