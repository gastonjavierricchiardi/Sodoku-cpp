## 🗂️ CHANGELOG – PROYECTO "Sodoku C++"

👤 **Autor:** Gastón Ricchiardi
🧾 **Formato de versiones:** v:0.X
📌 **Última versión funcional estable:** v:0.8.1

---

### 🔹 v:0.1 – Estructura inicial del juego

📅 Fecha aproximada: inicio del proyecto
**Cambios:**

* Creación del proyecto Sodoku en C++.
* Declaración de matriz global `MATRIZ[9][9]` inicializada en cero.
* Función básica `DibujarPantalla()` para mostrar el tablero en consola.
* Implementación del `menuPrincipal()` con opción 1: Ingreso Manual.
* Primera versión de `modoIngresoManual()` para insertar valores en la matriz.

---

### 🔹 v:0.2 – Introducción de interfaz visual

📅 Fecha: versión temprana
**Cambios:**

* Incorporación de la función `autor()` con datos del desarrollador.
* Formato visual mejorado del tablero con líneas y bordes.
* Introducción de la matriz `MASCARA[9][9]` para destacar celdas en edición.
* Implementación de `generarMascara()` y `limpiarMascara()`.

---

### 🔹 v:0.3 – Validaciones y mejoras de experiencia

📅 Fecha: cuando se incorporó validación
**Cambios:**

* Creación de las funciones:

  * `validaHorizontal()`
  * `validaVertical()`
  * `validaRecuadro()`
* Incorporación de mensajes de error en rojo con `mostrarError()`.
* Manejo de entrada inválida usando `cin.fail()` y `cin.clear()`.
* Valor `99` implementado para cancelar un ingreso sin modificar.
* Corrección de bucles infinitos con caracteres no numéricos o símbolos.

---

### 🔹 v:0.4 – Color y modularización multiplataforma

📅 Fecha: justo antes de limpiar el tablero
**Cambios:**

* Funciones `colorTexto()` y `resetColor()` con soporte multiplataforma.
* Colores diferenciados para mensajes de sistema, errores y títulos.
* Inclusión de `MSGPAUSA()` y `limpiarPantalla()` adaptadas a Windows y Linux.
* Organización incipiente de funciones por categoría.

---

### 🔹 v:0.5 – Función “Limpiar Tablero”

📅 Fecha: implementación original
**Cambios:**

* Nueva opción 3 en el menú principal: “Limpiar Tablero”.
* Función `limpiarTablero()` que borra todos los valores de `MATRIZ`.
* Llamado conjunto a `limpiarMascara()` para reiniciar también la máscara.
* Confirmación visual en rojo al limpiar el tablero.

---

### 🔹 v:0.6 – Celdas fijas, tiempo desde versión y carga de partidas

📅 Fecha: 2 de julio de 2025
**Cambios:**

* Se agrega la matriz `CELDAFIJA[9][9]` para bloquear valores en el tablero.
* Función `fijarCeldasActuales()` para proteger valores cargados.
* `DibujarPantalla()` adaptada con colores blanco (fijas) y verde (normales).
* Cálculo de tiempo transcurrido desde compilación (`autor()`).
* Función `cargarPartidaDesdeArchivo()` con soporte para múltiples archivos guardados.
* Listado automático de archivos con `listarArchivosGuardados()`.

---

### 🔹 v:0.7 – Versión funcional completa y estable

📅 Fecha: 3 de julio de 2025
**Cambios:**

* Consolidación de todas las funciones implementadas hasta el momento.
* Refactor completo de entrada manual, validaciones y confirmaciones.
* Establecido como punto base para modularización futura.

---

### 🔹 v:0.7.1 – Inicio de modularización del proyecto

📅 Fecha de inicio: 3 de julio de 2025
**Objetivo:**

* Separar el archivo `Sodoku.cpp` en módulos temáticos:

  * `varios.cpp` / `varios.h` → funciones utilitarias (colores, autor, limpieza de pantalla)
  * `archivos.cpp` / `archivos.h` → guardado, carga y gestión de mensajes
  * `Sodoku.cpp` / `Sodoku.h` → núcleo del juego y control de flujo
    **Estado:**
* Migración de funciones de utilidades y archivos completada.
* Compilación verificada con múltiples archivos fuente.

---

### 🔹 v:0.8.1 – Modularización de pantalla y depuración interna

📅 Fecha: 4 de julio de 2025
**Cambios:**

* Se crea el módulo `pantalla.cpp` y `pantalla.h`.
* Migración de las funciones:

  * `limpiarMascara()`
  * `marcarFila()`
  * `marcarColumna()`
  * `marcarInterseccion()`
* Declaración de `extern char MASCARA[9][9];` en `Sodoku.h`.
* Eliminadas duplicaciones de lógica y mejora de claridad de flujo.
* Compilación validada con:

  ```bash
  g++ Sodoku.cpp archivos.cpp varios.cpp pantalla.cpp -o sodoku
  ```

---

### 🔹 v:0.8.3 – Validación lógica y corrección del sistema de archivos

📅 Fecha: 6 de julio de 2025
**Cambios:**

* Implementación de `sudokuValido(int[9][9])` en `archivos.cpp` para validación lógica en carga de archivos.
* Refactor de `guardarPartidaEnArchivo()` y `cargarPartidaDesdeArchivo()` para formato plano y validaciones por sección.
* Mejora de `generarNombreArchivo()` para incluir segundos (`YYYYMMDD-HHMMSS.txt`).

---

### 🔹 v:0.8.4 – Colorea celdas fijas y muestra tiempo desde versión

📅 Fecha: 8 de julio de 2025
**Cambios:**

* Mejora de estilo visual del menú BackDoor (colores, emoticones).
* Casos 8,11,12 y 13 del BackDoor implementados con confirmaciones y nivel de acceso.
* Ajustes en `mostrarMatriz()` para reutilizar firma genérica.

---

### 🔹 v:0.8.5 – Control de números agotados en modo manual

📅 Fecha: 9 de julio de 2025
**Cambios:**

* Nueva función `numeroAgotadoGlobal(int)` para detectar uso completo (9 veces) de un número.
* Integración en `modoIngresoManual()` para bloquear números agotados.
* `DibujarPantalla()` muestra números agotados resaltados en rojo.

---

### 🔹 v:0.8.6 – Modo competitivo, tablero aleatorio y sistema de dificultad

📅 Fecha: 9 de julio de 2025
**Cambios:**

* Incorporación de `iniciarJuego()` y `jugarPartida(int nivel)`.
* Función `generarTableroAleatorio(int nivel)` con tablero base fijo.
* Seguimiento de tiempo y errores en `jugarPartida()`.

---

### 🔹 v:0.8.7 – Generación dinámica de tableros resueltos + corrección de flujo de fijación

📅 Fecha: 11 de julio de 2025
**Cambios:**

* Implementación de `generarSodokuResuelto()` con backtracking.
* Refactor de `generarTableroAleatorio()` para usar solución generada y vaciar celdas.
* Corrección de orden: vaciado antes de fijar celdas.

---

### 🔹 v:0.8.8 – Sistema de acceso BackDoor por niveles + depuración avanzada

📅 Fecha: 14 de julio de 2025
**Cambios:**

* Creación de `backdoor.cpp`/`backdoor.h` con `subMenuBackDoor()` separado.
* `validarNivelDeAcceso()` implementado con claves `CLAVE_NIVEL_0/1/2`.
* Opciones del submenu con niveles de acceso progresivo.
* Firma genérica `mostrarMatriz(int[9][9], std::string)` para depuración.

---

### 🔹 v:0.8.9 – Depuración de jugabilidad y validación contra solución

📅 Fecha: 16 de julio de 2025
**Cambios:**

* Sembrado de `rand()` movido a `main()` y eliminadas llamadas dispersas.
* Añadidos `break;` faltantes en todos los `switch`.
* Uso de constantes (`TAM`, `VACIOS_*`, `CODIGO_BACKDOOR`) en lugar de literales.
* Refinamientos en `procesarIngresoUsuario()` y métricas de error vs. SOLUCION.

---

### 🔹 Pendientes para v0.9.0

1. Migrar a `<random>` completo y eliminar `rand()`.
2. `configurarGameOver()` implementar Game Over dinámico.
3. Documentar flujos de UX en `UX.md`.
4. Definir pruebas mínimas en `DIRECTIVAS.md`.
5. Inicializar repositorio GitHub y configurar CI.

---

### 🔹 v:0.9 – Sistema de ranking retro de mejores tiempos y errores

📅 Fecha: 24 de julio de 2025
**Cambios:**

* Sistema de puntuaciones retro en `archivos.cpp` y `archivos.h`.
* `scores[3][5]`, `ScoreEntry`, `cargarScores()`, `actualizarScores()`, `mostrarScores()`, `resetScores()`.
* Opción 4 en `menuPrincipal()` integrando ranking por nivel.

---

### 🔹 v:0.9.1 – Reparaciones y Refactorizaciones internas

📅 Fecha: 31 de julio de 2025
**Cambios:**

* Consolidación de `procesarIngresoUsuario()`.
* Integración de `<random>` en backtracking y generación de tableros.
* Refactor de `mostrarScores()` a `pantalla.cpp`.
* Limpieza de prototipos y duplicados.

---

### 🔹 v:0.9.2 – Ajustes finales BackDoor y Resolver automático

📅 Fecha: 4 de agosto de 2025
**Cambios:**

* **Corrección de `MSGPAUSA()`**: se añadió `std::cin.get();` tras `std::cin.ignore(...)` para pausar correctamente.
* **Submenú BackDoor numérico**: eliminadas salidas “x”/“z”; ahora solo números (`0` = volver, `100` = salida total).
* **Lectura directa de opción**: reemplazado `opcionStr`+`stoi` por `int opcion` con validación robusta.
* **Resolver automáticamente (case 8)**: confirmación S/N; copia y backtracking; barra de progreso; pregunta de sobrescritura/restauración.

---

### 🔹 v:0.9.2.1 – Bugfixes críticos

📅 Fecha: 6 de agosto de 2025
**Correcciones:**

* **Sincronización de SOLUCIÓN tras auto‐solve (case 8):** se añadió `memcpy(SOLUCION, copia, sizeof(copia));` y flag `SODOKU_RESUELTO = true` tras resolver.
* **Serialización de SOLUCIÓN y errores en guardar/cargar:** extendido `guardarPartidaEnArchivo()` para escribir 9 filas de `SOLUCION` y `intentosFallidos`; modificado `cargarPartidaDesdeArchivo()` para leerlos.
* **Reactivación de Game Over en modo competitivo (case 2):** se asegura que al entrar en case 2 bajo `SODOKU_RESUELTO==true` se recargue `SOLUCION` y `intentosFallidos`, habilitando el fin de partida.

---

### 🔹 v:0.9.2 – Ajustes finales BackDoor y Resolver automático

📅 Fecha: 4 de agosto de 2025
**Cambios:**

* **Corrección de MSGPAUSA()**: se añadió `std::cin.get();` tras `std::cin.ignore(...)` para pausar correctamente.
* **Submenú BackDoor numérico**: eliminadas salidas “x”/“z” y migrado a todo númerico (`0` = volver, `100` = salida total).
* **Lectura directa de opción**: reemplazado `opcionStr` + `stoi` por `int opcion` con validación robusta (`cin.clear()`, `cin.ignore()`).
* **Resolver automáticamente (case 8)**: confirmación S/N; copia de matriz y backtracking en copia; animación de barra de progreso; pregunta de sobrescritura con restauración del original.

---

### 🔹 v:0.9.3 – Hotfixes críticos, guardado extendido y mejoras de flujo

📅 Fecha: 11 de agosto de 2025
**Cambios:**

* **HOTFIX 1 – Resolver automático (case 8, `menuPrincipal()`)**

  * Sincronización de la matriz resuelta en memoria (`SOLUCION`) tras confirmación de sobrescritura.
  * `SODOKU_RESUELTO = true;` para marcar estado consolidado al guardar o reanudar.

* **HOTFIX 2 – Guardado y carga extendidos**

  * **Guardar (`guardarPartidaEnArchivo`)**: ahora incluye bloque adicional unificado con formato:

    ```
    // ---- DATOS INTERNOS ----
    [SOLUCION 9x9]
    INTENTOS: <n>
    ```
  * **Cargar (`cargarPartidaDesdeArchivo`)**: lectura opcional de bloque interno; restauración de `SOLUCION` e `intentosFallidos` si existen.

* **Mensajes contextuales de carga**

  * Aviso “✅ Estadísticas cargadas” si `intentosFallidos > 0` (o `SODOKU_RESUELTO` si se decide).
  * Aviso “⚠️ Sin estadísticas previas” en caso contrario.

* **Cancelación en selección de dificultad**

  * `seleccionarDificultad()` acepta `0`/`CODIGO_SALIR` para volver al menú sin modificar `nivelCargado`.

* **Colores en Windows (preparado, pendiente de test)**

  * `configurarConsola()` habilita secuencias ANSI en Windows 10+.
  * `colorTexto()` y `resetColor()` unificados para ANSI en todas las plataformas.

---

**Pendientes para v0.9.4:**

1. Validar automáticamente la integridad de la solución al cargar partida y, si está completa, marcar `SODOKU_RESUELTO` y mostrar mensaje de “Juego terminado”.
2. Integrar tiempos y estadísticas reales en el guardado/carga.
3. Documentar casos de prueba manual en `DIRECTIVAS.md`.
4. Seguridad de claves/backdoor.
5. Segmentar funciones largas para cumplir SRP.

---

*Fecha de cierre: 11 de agosto de 2025*

---