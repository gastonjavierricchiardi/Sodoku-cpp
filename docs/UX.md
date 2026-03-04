---

# 💡 UX – Flujos de Usuario

## 1. Ingreso simple

* **Prompt**: “Ingrese la fila (1–9):”
* **Códigos especiales**:

  * `0` = salir
  * `99` = cancelar
  * `98` = backdoor
* **Validaciones**:

  * Verificar rango 1–9 y `cin.fail()`
  * Mostrar mensaje de error y `MSGPAUSA()`
  * Tras cancelación (99), volver al prompt de fila sin cambiar nada
  * Tras backdoor (98), invocar **validarNivelDeAcceso()** y **subMenuBackDoor()**
  * Detectar agotamiento global (`numeroAgotadoGlobal`)
  * Reglas de Sudoku: no duplicados en fila/columna/cuadro

---

## 2. Modificar/Borrar celda ocupada

* **Detección**: `if (MATRIZ[f-1][c-1] != 0)`
* **Menú**:

  1. Modificar valor → salto a prompt de valor
  2. Borrar valor → `MATRIZ[f-1][c-1] = 0`, limpiar máscara, volver a prompt de fila
  3. Cancelar → limpiar máscara, volver a prompt de fila
* **Validaciones**:

  * Si input inválido en selección, error + `MSGPAUSA()` + volver a menú de opciones

---

## 3. Cancelar ingreso

* **Código**: 99
* **Comportamiento**: retorna estatus `CANCELAR`, `intentosFallidos++`, limpia máscara, vuelve a prompt de fila

---

## 4. Backdoor

* **Código**: 98
* **Pasos**:

  1. Invocar `validarNivelDeAcceso()`
  2. Si nivel válido, `subMenuBackDoor(nivel)`
  3. Limpiar máscara y regresar al bucle principal de partida

---

## 5. Nueva Partida Competitiva

* **Flujo**:

  1. Desde menú principal, opción 2:

     * Si existe `partidaEnCurso`, preguntar “¿Reanudarla? (s/n)”
     * **S** → `jugarPartida(nivelCargado)`
     * **N** → limpiar flags (`partidaEnCurso = false; nivelCargado = -1;`) y continuar
  2. Llamar `iniciarJuego()`:

     * Si `nivelCargado < 0`, `seleccionarDificultad()` → guardar en `nivelCargado`
     * Mostrar dificultad seleccionada
     * `jugarPartida(nivelCargado)`

---

## 6. Reanudar Partida Guardada

* **Flujo**:

  1. Desde menú, opción 5: `cargarPartidaDesdeArchivo()`

     * Mostrar lista de archivos (`listarArchivosGuardados()`)
     * Seleccionar o cancelar (0/99)
     * Leer primera línea `Nivel:X` y mapear a `nivelCargado`
     * Validar y cargar matrices temporales
     * Validar lógico con `sudokuValido()`
     * Copiar a `MATRIZ` y `CELDAFIJA`, setear `partidaEnCurso = true`
     * Si existe bloque interno (`// ---- DATOS INTERNOS ----`):

       * Cargar `SOLUCION` y `intentosFallidos`
       * Mostrar mensaje:

         * `✅ Estadísticas cargadas` si `INTENTOS > 0` o `SODOKU_RESUELTO=true`
         * `⚠️ Sin estadísticas previas` en caso contrario
     * Si no existe bloque interno:

       * Inicializar `SOLUCION` en ceros, `intentosFallidos=0`, mostrar `⚠️ Sin estadísticas previas`
  2. Luego, al elegir opción 2, detecta `partidaEnCurso` y permite reanudar

---

## 7. Game Over y Victoria

* **Game Over**:

  * Contador `intentosFallidos` vs. `endGame`
  * Al alcanzar, mostrar mensaje, bajar `partidaEnCurso`, volver a menú
* **Victoria**:

  * Detectar `MATRIZ == SOLUCION`
  * Mostrar felicitaciones, estadísticas (inicio/fin/duración/errores/números agotados)
  * **Registro de score**:

    1. Pedir iniciales (3 caracteres alfanuméricos)
    2. Construir `ScoreEntry` con `erroresFallidos`, `duracion`, `endGame`
    3. `cargarScores()`, `actualizarScores()`, `guardarScores()`
    4. Mostrar top 5 con `mostrarScores(nivel)`
  * Bajar `partidaEnCurso`, volver a menú

---

## 8. Guardar Partida en Archivo

* **Opción**: menú principal caso 6
* **Flujo**:

  1. `generarNombreArchivo()` → timestamped file
  2. Escribir:

     * `Nivel:X`
     * 9 líneas de `MATRIZ`
     * 9 líneas de `CELDAFIJA`
     * `// ---- DATOS INTERNOS ----`
     * 9 líneas de `SOLUCION`
     * `INTENTOS: n`
  3. Mostrar confirmación y `MSGPAUSA()`

---

## 9. Resolver automáticamente

* **Opción**: menú principal caso 8
* **Flujo**:

  1. Mostrar mensaje de confirmación: “Resolver automáticamente el Sudoku. ¿Deseas continuar? (S/N):”
  2. Si **N** → regresar al menú principal sin cambios.
  3. Si **S**:

     1. Crear copia de `MATRIZ`
     2. Invocar `resolverSudoku(copia)` con backtracking
     3. Si falla, mostrar error y regresar al menú
     4. Si tiene éxito, mostrar barra de progreso basada en celdas vacías
     5. Al completar, preguntar “¿Sobreescribir la partida actual con la solución? (S/N):”

        * **S**: copiar `copia` a `MATRIZ`, `memcpy(SOLUCION, copia)`, `SODOKU_RESUELTO = true`, mostrar éxito
        * **N**: descartar copia y regresar al menú
* **Validaciones**:

  * Comprobar reglas de Sudoku antes de sobreescribir
  * Actualizar `SOLUCION` global para validaciones futuras
* **Integración BackDoor**:

  * El submenú BackDoor caso 18 habilita/deshabilita la bandera `SODOKU_RESUELTO`, que permite reingresar al modo competitivo (case 2)

---

## 10. Cancelar selección de dificultad (v:0.9.3)

* **Opción**: 0 en `seleccionarDificultad()`
* **Flujo**:

  1. Mostrar “Selección cancelada, regresando al menú principal”
  2. Retornar código especial (`CANCELAR_NIVEL`)
  3. El bloque de llamada en `menuPrincipal()` debe detectar este código y no avanzar a `jugarPartida()`
* **Objetivo**:

  * Evitar que se intente iniciar juego con dificultad inválida tras cancelación

---