---

# 📘 CONVENCIONES INTERNAS DE DESARROLLO – PROYECTO "Sodoku C++"

👤 **Autor:** Gastón Ricchiardi
🗓 **Última revisión:** 6 de agosto de 2025
📌 **Versión mínima aplicable:** v:0.8.4

---

## 🧹 ESTRUCTURA GENERAL DEL PROYECTO

El código fuente está dividido en cuatro archivos `.cpp` y sus respectivos `.h`:

| Archivo        | Contenido principal                                   |
| -------------- | ----------------------------------------------------- |
| `Sodoku.cpp`   | Lógica principal del juego, menú y flujo general      |
| `pantalla.cpp` | Funciones visuales de máscara e intersecciones        |
| `archivos.cpp` | Guardado/carga de partidas, validaciones y ranking    |
| `varios.cpp`   | Funciones auxiliares: autor, colores, pausa, limpieza |

---

## 📄 CONVENCIONES PARA ARCHIVOS `.h`

* No incluir `using namespace std;` en headers.
* Evitar headers STL (`<vector>`, `<algorithm>`, etc.) salvo que sea imprescindible.
* Siempre usar directivas de inclusión segura:

```cpp
#ifndef NOMBRE_HEADER_H
#define NOMBRE_HEADER_H
// declaraciones
#endif
```

* Incluir únicamente:

  * Declaraciones de funciones
  * Variables `extern`
  * Estructuras o constantes compartidas

---

## 📄 CONVENCIONES PARA ARCHIVOS `.cpp`

* Incluir headers STL **solo si se utilizan directamente**.
* No repetir funciones ya declaradas en los `.h`.
* Las funciones **privadas** deben declararse con forward-declaration si se llaman antes de su definición.
* Agrupar funciones por temática (p.ej. I/O, lógica de juego, utilidades).
* Colocar funciones auxiliares al final del archivo si no son reutilizadas externamente.

---

## 🧪 VALIDACIÓN Y ESTRUCTURA DE ARCHIVOS DE PARTIDA

* Cada archivo `.txt` de partida contiene exactamente **18 líneas**:

  1. 9 líneas de `MATRIZ` (valores de 0 a 9)
  2. 9 líneas de `CELDAFIJA` (valores 0 o 1)

* No usar encabezados como `"MATRIZ:"` o `"CELDAFIJA:"`.

* El nombre de archivo debe usar el formato:

```
YYYYMMDD-HHMMSS.txt
```

* Durante la carga:

  * Validar estructura (filas, columnas, valores válidos).
  * Validar lógica (sin repetidos en filas, columnas o subcuadros 3×3).
  * Rechazar el archivo si falla cualquiera de esas condiciones.

---

## 📩 CONVENCIÓN AMPLIADA – GUARDADO EXTENDIDO Y ESTADÍSTICAS (v:0.9.3)

* **Formato de archivo de partida** actualizado:

  1. Línea de nivel:

     ```
     Nivel:X
     ```

     (0 = modo libre, 1 = fácil, 2 = media, 3 = difícil)
  2. 9 líneas de `MATRIZ` (valores 0 a 9).
  3. 9 líneas de `CELDAFIJA` (valores 0 o 1).
  4. **Bloque adicional opcional**:

     ```
     // ---- DATOS INTERNOS ----
     [SOLUCION 9×9]
     INTENTOS: <n>
     ```

* **Carga (`cargarPartidaDesdeArchivo`)**:

  * Si el bloque adicional existe, se cargan `SOLUCION` e `intentosFallidos`.
  * Mensaje “✅ Estadísticas cargadas” si hay intentos o sudoku resuelto; “⚠️ Sin estadísticas previas” en caso contrario.

* **Guardado (`guardarPartidaEnArchivo`)**:

  * Siempre incluye el bloque de datos internos, aunque esté vacío (intentos = 0).

* **Compatibilidad**:

  * El sistema es retrocompatible con partidas antiguas (sin bloque interno).
  * Si no existe el bloque, `SOLUCION` se inicializa a ceros e `intentosFallidos` se pone en 0.

---

## 📂 ORGANIZACIÓN DEL REPOSITORIO

```
/Sodoku/
├── Sodoku.cpp
├── Sodoku.h
├── pantalla.cpp
├── pantalla.h
├── archivos.cpp
├── archivos.h
├── varios.cpp
├── varios.h
├── backdoor.cpp
├── backdoor.h
├── constantes.h
├── CHANGELOG.md
├── UX.md
├── CONVENCIONES.md
└── *.txt (partidas guardadas)
```

---

## 📌 ANEXO: FUNCIONES INTERNAS ESPECIALES

### 🔹 `sudokuValido(int matriz[9][9])`

* Ubicada en `archivos.cpp`.
* Verifica que no haya duplicados en filas, columnas ni bloques 3×3 (ignora ceros).
* Uso interno exclusivo en carga de partidas.

---

## 🔐 SISTEMA BACKDOOR – CONVENCIONES DE USO

### 🎯 Objetivo

Proveer acceso especial para desarrolladores/testers: inspección, edición y debugging.

### 🔑 Niveles de acceso

| Nivel | Rol             | Alcance                   |
| ----- | --------------- | ------------------------- |
| `0`   | Usuario inicial | Solo lectura e inspección |
| `1`   | Usuario medio   | Testeo y pre-carga        |
| `2`   | SuperUsuario    | Edición y control total   |

### Estructura del `subMenuBackDoor(int nivelAcceso)`

```cpp
if (nivelAcceso >= N)
{
    // acción permitida
}
else
{
    mostrarError("Nivel insuficiente para esta opción.");
    MSGPAUSA();
}
```

**Acciones disponibles por nivel:**

1. Mostrar `MATRIZ`        (nivel 0)
2. Mostrar `CELDAFIJA`     (nivel 0)
3. Mostrar `MASCARA`       (nivel 0)
4. Diagnóstico lógico      (nivel 0)
5. Cargar tablero de prueba(nivel 1)
6. Inyectar error lógico   (nivel 1)
7. Borrar tablero parcial  (nivel 1)
8. Fijar celda por coord.  (nivel 1)
9. Forzar guardado partida (nivel 1)
10. Editar `MATRIZ` manual (nivel 2)
11. Editar `CELDAFIJA`     (nivel 2)
12. Quitar todas celdas fijas (nivel 2)
13. Hard reset tablero     (nivel 2)
14. Asignar puntaje manual (nivel 2)
15. Mostrar/reset stats    (nivel 2)
16. Exportar a CSV         (nivel 2)

---

## 💻 COMPATIBILIDAD MULTIPLATAFORMA

* **Windows 64-bits** (MinGW-w64) y **Linux** sin cambios.
* Colores ANSI básicos compatibles en CMD/PowerShell (emojis no garantizados).
* Fuente UTF-8 sin BOM.
* Compilación estática recomendada (`-static`).

---

## 🧩 CONVENCIÓN AMPLIADA – MODO COMPETITIVO (v:0.8.6)

* Funciones clave:

  * `iniciarJuego()`, `seleccionarDificultad()`, `jugarPartida(int nivel)`
  * `generarTableroAleatorio()` (solución fija, pendiente aleatorización real)
* Flujo:

  1. Elegir nivel → copiar solución en `MATRIZ`
  2. Ocultar celdas (`vaciarCeldas`) según dificultad
  3. Fijar celdas visibles (`fijarCeldasActuales()`)

---

## 🧩 CONVENCIÓN AMPLIADA – TABLEROS RESUELTOS (v:0.8.7)

* Se implementa `generarSodokuResuelto()` con backtracking en `varios.cpp`.
* Flujo correcto:

  1. Generar solución → `SOLUCION[9][9]`
  2. Copiar a `MATRIZ`
  3. `vaciarCeldas(nivel)`
  4. `fijarCeldasActuales()`

---

## 🔐 CONVENCIÓN AMPLIADA – MENÚ BACKDOOR CENTRALIZADO (v:0.8.8)

* `subMenuBackDoor()` movido a `backdoor.cpp`/`backdoor.h`.
* `validarNivelDeAcceso()` retorna 0/1/2/–1.
* `mostrarMatriz(int matriz[9][9], std::string titulo)` con firma unificada.

---

## 🏆 CONVENCIÓN AMPLIADA – RANKING RETRO (v:0.9)

* En `archivos.h`: `struct ScoreEntry` y prototipos:

```cpp
void cargarScores();
void actualizarScores(const ScoreEntry&);
void guardarScores();
void mostrarScores(int nivel);
void resetScores();
```

* En `archivos.cpp`:

  * `static constexpr const char* nombreArchivoScores = "scores.txt";`
  * `static ScoreEntry scores[3][5];`
  * Implementación de `cargarScores()`, `actualizarScores()`, `guardarScores()`, `mostrarScores()`, `resetScores()`.
* Integración en flujo:

  * Opción 4 en `menuPrincipal()`: muestra top 5.
  * Tras victoria en `jugarPartida()`: pide iniciales y registra score.

---

## 🕗 BACKLOG DE MEJORAS – PARA v:0.9.1

1. Refactorizar ingreso de datos duplicado.
2. Migrar a `<random>` y `std::shuffle`.
3. Aplicar `clang-format` al proyecto.
4. Game Over dinámico configurable.
5. Menú de configuración de parámetros de juego.
6. Limpieza final de código y comentarios.
7. 📄 Crear **UX.md** con los flujos de usuario críticos.
8. 🧪 Documentar en **DIRECTIVAS.md** la “Prueba mínima: Modificar/Borrar celda ocupada”.

---