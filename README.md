# Sodoku C++

Proyecto de Sudoku por consola en C++, con modo de juego competitivo, persistencia de partidas, validaciones lógicas y herramientas internas de administración.

## Estado del proyecto

Este repositorio está activo y versionado con Git/GitHub.

### Importante

- La compilación habitual del proyecto se hace **desde consola**.
- Los scripts de `scripts/` existen, pero deben considerarse auxiliares.
- La fuente real del proyecto está en `src/`.

## Estructura actual

```text
Sodoku-cpp/
├── src/        # código fuente y headers del proyecto
├── include/    # reservado / actualmente sin uso relevante
├── scripts/    # scripts auxiliares de compilación y verificación
├── docs/       # changelog, convenciones, directivas y UX
├── README.md
├── LICENSE
└── .gitignore
```

## Código fuente principal

Actualmente el proyecto compila con estos archivos fuente:

- `src/archivos.cpp`
- `src/pantalla.cpp`
- `src/varios.cpp`
- `src/Sodoku.cpp`
- `src/backdoor.cpp`

Y utiliza sus headers correspondientes dentro de `src/`.

## Compilación manual recomendada

### Linux / Zorin OS

Desde la raíz del proyecto:

```bash
g++ -std=c++17 -Wall -Wextra \
    src/archivos.cpp src/pantalla.cpp src/varios.cpp src/Sodoku.cpp src/backdoor.cpp \
    -o sodoku
```

Ejecutar:

```bash
./sodoku
```

---

### Windows con MinGW-w64 (MSYS2 o cross-compile)

#### Opción habitual 64 bits

```bash
x86_64-w64-mingw32-g++ -std=c++17 -Wall -Wextra -pthread \
    src/archivos.cpp src/pantalla.cpp src/varios.cpp src/Sodoku.cpp src/backdoor.cpp \
    -static -lwinpthread \
    -o sodoku.exe
```

#### Opción 32 bits

```bash
i686-w64-mingw32-g++ -std=c++17 -Wall -Wextra \
    src/archivos.cpp src/pantalla.cpp src/varios.cpp src/Sodoku.cpp src/backdoor.cpp \
    -static \
    -o sodoku_32bit.exe
```

## Scripts auxiliares

Los scripts de la carpeta `scripts/` deben reflejar esta estructura real del proyecto:

- los fuentes están en `src/`
- la compilación no debe asumir `.cpp` en la raíz

Si un script no coincide con esto, debe corregirse antes de usarse como referencia.

## Documentación

En `docs/` se conserva documentación de trabajo del proyecto:

- `CHANGELOG_Sodoku_C++.md`
- `CHANGELOG_Sodoku_C++Historico.md`
- `CONVENCIONES.md`
- `DIRECTIVAS.md`
- `UX.md`

## Licencia

Este proyecto se distribuye bajo licencia **MIT**. Ver archivo `LICENSE`.

## Nota de mantenimiento

El repositorio fue reorganizado para trabajar fuera de Dropbox y mantener un único repo Git activo.
La ubicación de trabajo actual es la carpeta local del proyecto, y GitHub funciona como remoto principal.

```

```
