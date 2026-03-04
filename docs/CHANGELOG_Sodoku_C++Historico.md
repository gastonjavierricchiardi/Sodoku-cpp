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

* Nueva opción 2 en el menú principal: “Limpiar Tablero”.
* Función `limpiarTablero()` que borra todos los valores de `MATRIZ`.
* Llamado conjunto a `limpiarMascara()` para reiniciar también la máscara.
* Confirmación visual en rojo al limpiar el tablero.

---

### 🔹 v:0.5 – Mejora de seguridad al limpiar tablero \[🆕 no oficial]

📅 Fecha estimada: 17 de junio de 2025
**Cambios:**

* Incorporación de la función `hayCeldasFijas()` para detectar celdas protegidas.
* Confirmación adicional si existen celdas fijas antes de limpiar.
* Limpieza conjunta de `MATRIZ`, `MASCARA` y `CELDAFIJA`.
* Mensajes diferenciados por color (advertencia, éxito, error).

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
* Se considera versión **funcional completa** del proyecto.

---

### 🔹 v:0.7.1 – Inicio de modularización del proyecto

📅 Fecha de inicio: 3 de julio de 2025
**Objetivo:**

* Separar el archivo `Sodoku.cpp` en módulos temáticos.
  **Estructura definida:**
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
* Se eliminan duplicaciones de lógica y se mejora la claridad del flujo.
* Compilación validada con:

  ```
  g++ Sodoku.cpp archivos.cpp varios.cpp pantalla.cpp -o sodoku
  ```
* Proyecto final distribuido en los siguientes archivos fuente:

  * `Sodoku.cpp`
  * `archivos.cpp`
  * `varios.cpp`
  * `pantalla.cpp`
  * * headers correspondientes (.h)
* Resultado: código más limpio, modular y mantenible.

---
### 🔹 v:0.8.3 – Validación lógica y corrección del sistema de archivos

📅 Fecha: 6 de julio de 2025
**Cambios:**

* 🔍 Se implementa validación lógica completa del tablero durante la carga:

  * Nueva función auxiliar `sudokuValido(int matriz[9][9])`, ubicada en `archivos.cpp`, que verifica que no existan valores repetidos en filas, columnas ni subcuadros 3x3 (exceptuando ceros).
  * Esta validación se ejecuta **dentro de `cargarPartidaDesdeArchivo()`** luego de validar el formato estructural.
  * Si se detecta error lógico, el archivo **no se carga** y se muestra un mensaje con `mostrarError()`.

* 🧾 Se corrige el sistema de guardado/carga de archivos:

  * La función `guardarPartidaEnArchivo()` ahora guarda **únicamente los valores** de `MATRIZ` y `CELDAFIJA`, **sin encabezados** tipo `"MATRIZ:"` o `"CELDAFIJA:"`, respetando el formato plano esperado por la carga.
  * `cargarPartidaDesdeArchivo()` fue reestructurada para leer primero las 9 filas de `MATRIZ`, luego las 9 filas de `CELDAFIJA`, con validaciones independientes por sección.
  * Se evita la carga si alguna línea tiene cantidad incorrecta de valores, valores fuera de rango, o caracteres inválidos.

* 🕒 Se mejora la función `generarNombreArchivo()`:

  * Se agregan los **segundos (`%S`)** al nombre del archivo, con formato: `YYYYMMDD-HHMMSS.txt`.
  * Esto evita sobrescribir archivos si se guardan múltiples partidas en el mismo minuto.

* ✅ Todos los archivos `.txt` generados a partir de esta versión:

  * Cumplen con el formato de 18 filas exactas: 9 de `MATRIZ` y 9 de `CELDAFIJA`.
  * Pueden ser validados tanto estructural como lógicamente antes de usarse.

🎯 Resultado: sistema de archivos robusto, validación completa del tablero, y sin conflictos al guardar múltiples partidas consecutivas.

---
### 🔹 v:0.8.3 – Validación lógica y corrección del sistema de archivos

📅 Fecha: 6 de julio de 2025
**Cambios:**

* 🔍 Se implementa **validación lógica completa del tablero** durante la carga:

  * Nueva función auxiliar `sudokuValido(int matriz[9][9])` ubicada en `archivos.cpp`, que verifica que no existan valores repetidos en filas, columnas ni subcuadros 3x3 (exceptuando ceros).
  * Esta validación se ejecuta **dentro de `cargarPartidaDesdeArchivo()`**, luego de validar el formato estructural.
  * Si se detecta error lógico, el archivo **no se carga** y se muestra un mensaje mediante `mostrarError()`.

* 🧾 Se corrige el sistema de **guardado/carga de archivos**:

  * La función `guardarPartidaEnArchivo()` ahora guarda únicamente los valores de `MATRIZ` y `CELDAFIJA`, **sin encabezados** tipo `"MATRIZ:"` o `"CELDAFIJA:"`, respetando el formato plano esperado por la carga.
  * `cargarPartidaDesdeArchivo()` fue reestructurada para leer primero las 9 filas de `MATRIZ`, luego las 9 filas de `CELDAFIJA`, con **validaciones independientes** por sección.
  * Se evita la carga si alguna línea tiene cantidad incorrecta de valores, valores fuera de rango o caracteres inválidos.

* 🕒 Se mejora la función `generarNombreArchivo()`:

  * Se agregan los **segundos (`%S`)** al nombre del archivo.
  * Nuevo formato: `YYYYMMDD-HHMMSS.txt`.
  * Evita sobrescribir archivos si se guardan múltiples partidas en el mismo minuto.

* 🧪 Se incorpora validación silenciosa como función auxiliar de diagnóstico.

* ✅ Todos los archivos `.txt` generados a partir de esta versión:

  * Cumplen con el formato **de 18 filas exactas**: 9 de `MATRIZ` + 9 de `CELDAFIJA`.
  * Pueden ser validados tanto estructural como lógicamente antes de usarse.

🎯 **Resultado:** sistema de archivos robusto, validación completa del tablero, y sin conflictos al guardar múltiples partidas consecutivas.

---

### 🔹 v:0.8.4 – Colorea celdas fijas y muestra tiempo desde versión

📅 Fecha: 8 de julio de 2025
**Cambios:**

* 🔹 Se unifica el estilo visual y estructural del `menuBackdoor`, aplicando formato consistente, uso de colores, emoticones y estructura en todos los casos nuevos.

* 🔢 Se reorganiza y mejora el `switch (opcion)` para admitir opciones con valores enteros y mantener compatibilidad con opciones especiales tipo 'x' y 'z'.

* 🔹 Se reemplaza el código embebido en el `case 1` del backdoor por la llamada a `mostrarMatriz()`, limpiando la estructura.

* 📄 Se renombra el `case 7` como:

  * “\[ 7 ] Borrado de tablero (no borra CELDAFIJA)”
  * (La funcionalidad no se modifica, solo se aclara el efecto del borrado parcial.)

* 📊 Nuevos casos implementados en el `menuBackdoor`:

  * `case 8` – “\[8] Fijar celda por coordenada”:

    * Nivel de acceso 1
    * Permite marcar como fija cualquier celda
    * Si la celda está vacía, se emite un mensaje gracioso y se solicita confirmación antes de fijarla

  * `case 11` – “\[11] Editar CELDAFIJA”:

    * Nivel de acceso 2
    * Permite desmarcar una celda fija mediante coordenadas
    * Verifica si está fijada y actúa en consecuencia

  * `case 12` – “\[12] Quitar todas las CELDAFIJA”:

    * Nivel de acceso 2
    * Muestra confirmación interactiva antes de eliminar todas las celdas fijas

  * `case 13` – “\[13] Borrar tablero completo (hard reset)”:

    * Nivel de acceso 2
    * Borra toda la matriz y todas las celdas fijas
    * Confirmación previa obligatoria

🔹 Se confirma que la versión es funcionalmente estable y servirá como base para la siguiente etapa de desarrollo: exportación a CSV y mejoras de interfaz.

---

### 🔹 v:0.8.5 – Control de números agotados en modo manual

📅 Fecha: 9 de julio de 2025
**Cambios:**

* 🔢 Se implementa la función `numeroAgotadoGlobal(int numero)` que detecta si un número fue utilizado 9 veces en la matriz.
* 🚫 En `modoIngresoManual()`, si el número está agotado, se muestra un mensaje de error y se bloquea su ingreso.
* 👀 Se actualiza la función `DibujarPantalla()` para mostrar en tiempo real los números agotados debajo del tablero.
* 🎨 Los números agotados se resaltan en rojo como ayuda visual persistente durante toda la jugabilidad.

🎯 **Resultado:** el jugador puede identificar rápidamente qué números ya no están disponibles, evitando errores de ingreso y mejorando la experiencia general.

---

### 🔹 v:0.8.5 – Control de números agotados en modo manual (actualización extendida)

📅 Fecha: 9 de julio de 2025
**Cambios:**

* 🔢 Se implementa la función `numeroAgotadoGlobal(int numero)` que detecta si un número fue utilizado 9 veces en la matriz.
* 🚫 En `modoIngresoManual()`, si el número está agotado, se muestra un mensaje de error y se bloquea su ingreso.
* 👀 Se actualiza la función `DibujarPantalla()` para mostrar en tiempo real los números agotados debajo del tablero.
* 🎨 Los números agotados se resaltan en rojo como ayuda visual persistente durante toda la jugabilidad.

---

**🆕 Actualización extendida:**

* 🧠 Se implementa `numeroPresenteEnCuadro(fila, columna, numero)` para detectar si un número ya se encuentra en el subcuadro 3x3 correspondiente antes de validar la jugada.
* 🔍 Nueva función `cantidadRestante(numero)` que devuelve cuántas veces más puede colocarse ese número en el tablero.
* 💥 En `modoIngresoManual()`, si el número que se ingresa **completa las 9 apariciones válidas**, se muestra un mensaje visual de agotamiento inmediato.
* 🧪 Se realizó prueba de consistencia con mensajes `[DEBUG]` para confirmar que `cantidadRestante()` se actualiza correctamente tras cada ingreso.

🎯 **Resultado:** el juego anticipa el agotamiento de números con advertencias claras, previene ingresos inválidos, y mejora la experiencia visual y lógica del usuario sin modificar la estructura original.

---

### 🔹 v:0.8.6 – Modo competitivo, tablero aleatorio y sistema de dificultad

📅 Fecha: 9 de julio de 2025
**Cambios:**

* 🎮 **Nuevo flujo de juego tipo "partida competitiva"**:

  * Se incorporan las funciones `iniciarJuego()` y `jugarPartida(int nivel)`.
  * El usuario selecciona una dificultad (`FÁCIL`, `MEDIA`, `DIFÍCIL`) mediante `seleccionarDificultad()`, y luego se inicia una partida con seguimiento de errores y tiempo.

* 🧩 **Generación de tablero base completo (modo simulado):**

  * Se crea la función `generarTableroAleatorio(int nivel)` en `varios.cpp`.
  * Por ahora, se utiliza un tablero resuelto fijo como base (hardcodeado), que se copia en `MATRIZ`.
  * Este tablero reemplaza temporalmente la generación real de sudokus válidos.

* ⏱️ **Seguimiento temporal en `jugarPartida()`:**

  * Se registra hora de inicio y fin de la partida.
  * Se calcula duración total y se simulan errores cometidos.
  * Se muestra todo con formato legible, incluyendo duraciones en minutos y segundos.

* ✅ **Integración total al flujo principal:**

  * `menuPrincipal()` redirecciona correctamente al modo competitivo vía `iniciarJuego()`.
  * `jugarPartida()` muestra la matriz antes de iniciar y luego simula una jugabilidad real.
  * Confirmación visual de dificultad seleccionada y resultados finales.

🔄 **Nota importante:**
Aunque el nombre de la función `generarTableroAleatorio()` sugiere aleatoriedad, **esta versión utiliza aún una matriz fija**. La generación aleatoria real será implementada en futuras versiones.

🎯 **Resultado:** el juego ahora permite iniciar partidas competitivas, establecer niveles de dificultad, y simula una experiencia de juego con tiempo y errores, preparando el terreno para la jugabilidad completa.

---

### 🔹 v:0.8.7 – Generación dinámica de tableros resueltos + corrección de flujo de fijación

📅 Fecha: 11 de julio de 2025
**Cambios:**

* 🧠 Se implementa la función `generarSodokuResuelto()` en `varios.cpp`, que crea un tablero Sudoku válido y completamente resuelto de forma aleatoria, utilizando backtracking.

* 🔁 Se refactoriza la función `generarTableroAleatorio(int nivel)` para seguir el flujo correcto de armado del juego:

  1. Generar una solución completa en `SOLUCION`.
  2. Copiar la solución a `MATRIZ`.
  3. Llamar a `vaciarCeldas(nivel)` sobre `MATRIZ`.
  4. Llamar a `fijarCeldasActuales()` **después del vaciado**, corrigiendo un error crítico en versiones anteriores donde se fijaban celdas vacías.

* 🔄 Se elimina completamente el uso del tablero fijo `solucionTemporal`, reemplazado por una matriz generada aleatoriamente y validada.

* 🛑 Se corrige el error donde celdas vacías aparecían como fijas, impidiendo que el jugador las modificara. Esto se debía a un orden incorrecto entre `vaciarCeldas()` y `fijarCeldasActuales()`.

* 🧪 Confirmación manual mediante `menuBackdoor()` muestra que:

  * Las celdas vacías (`0`) ahora aparecen como **no fijas**.
  * Las celdas con valores visibles están correctamente fijadas.
  * El jugador puede ingresar valores en celdas jugables sin errores.

* 🧱 Se incorpora la variable global `int SOLUCION[9][9];` como estructura de referencia para detección de errores en jugabilidad futura.

🎯 **Resultado:** el sistema ahora genera tableros aleatorios resueltos válidos, vacía posiciones según dificultad y marca correctamente las celdas fijas, sin errores de fijación ni bloqueo de celdas editables. Esto sienta las bases para una jugabilidad real y validación contra solución esperada.

---
### 🔹 v:0.8.8 – Sistema de acceso BackDoor por niveles + depuración avanzada

📅 Fecha: 14 de julio de 2025
**Cambios:**

* 🧩 Se separa completamente el menú oculto `SubMenuBackDoor()` en un nuevo archivo `backdoor.cpp`, junto con su header `backdoor.h`. Se elimina su definición de `Sodoku.cpp`.

* 🛡️ Se implementa el sistema de validación de niveles de acceso:

  * Nueva función `validarNivelDeAcceso()` que devuelve `0`, `1`, `2` o `-1` según la clave ingresada.
  * Variables `CLAVE_NIVEL_0`, `CLAVE_NIVEL_1`, `CLAVE_NIVEL_2` definidas como `extern` en `backdoor.h` para centralizar el control de acceso.

* 🔐 Accesos disponibles:

  * Desde `menuPrincipal()` mediante el `case 11`.
  * Desde `modoIngresoManual()` usando el valor especial `98` como fila.
  * Desde `jugarPartida()` también detectando el número `98`.

* 🧠 Lógica del `SubMenuBackDoor()`:

  * Muestra opciones progresivas según el nivel (`0` a `2`).
  * Valida automáticamente que el usuario no acceda a funciones no permitidas.
  * Funciones de edición, borrado y manipulación estructural reservadas para nivel `2`.

* 📦 Nueva firma para `mostrarMatriz(int matriz[9][9], std::string titulo)`:

  * Se permite mostrar cualquier matriz (`MATRIZ`, `SOLUCION`, etc.) con un título personalizado.
  * Se mantiene como default `"MATRIZ ACTUAL"`.
  * Se actualiza todo el código del `backdoor` para usar esta nueva firma.

* 🔍 Diagnóstico visual mejorado:

  * Las funciones `[1]`, `[2]`, `[3]`, `[4]` del backdoor permiten inspección directa de `MATRIZ`, `CELDAFIJA`, `MASCARA`, y la validez lógica.
  * La opción `[16]` exporta a CSV el estado actual de `MATRIZ`.

* 📊 Validación visual confirmada:

  * `CELDAFIJA` refleja correctamente las celdas fijadas solo al comienzo del juego.
  * `SubMenuBackDoor()` muestra diagnóstico visual completo para depurar partidas.

* ✅ Validación de compilación:

  * Se corrige un error de doble asignación de argumento por defecto en la declaración de `mostrarMatriz()` (C++17).
  * Se incluye `#include <string>` donde corresponde para evitar errores de compilación.

🎯 **Resultado:**
Se completa la migración del menú oculto a un módulo independiente, se implementa un sistema de niveles de acceso robusto y se permite la inspección profunda del estado del tablero. Todo el flujo de ejecución está preparado para depuración y jugabilidad real sin conflictos. Esta versión se considera estable y funcional como base para la versión 0.8.9.

---

### 🔹 v:0.8.9 – Depuración de jugabilidad y validación contra solución

📅 Fecha: 16 de julio de 2025
**Cambios:**

* ☑️ **Sincronización de firmas**

  * Ajustada la declaración y definición de `iniciarJuego()` para que coincidan en `Sodoku.h` y `Sodoku.cpp`.

* 🎲 **Aleatoriedad centralizada**

  * Sembrado de `rand()` movido a `main()`; eliminadas llamadas dispersas a `srand(time(0))`.
  * Shuffle manual en `resolverSudoku()` usando `rand()` (se suprimió `<random>` y `std::shuffle`).

* 🔀 **Switchs completos**

  * Se añadieron `break;` faltantes en todos los `switch` del proyecto para evitar fall-through.

* 📚 **Prototipos centralizados**

  * Eliminadas declaraciones forward en los `.cpp`.
  * Todos los headers (`Sodoku.h`, `varios.h`, `archivos.h`, `pantalla.h`, `backdoor.h`) definen ya los prototipos de sus funciones.

* 🔢 **Constantes en lugar de “magic numbers”**

  * Uso de `TAM`, `CODIGO_BACKDOOR`, `VACIOS_FACIL`, `VACIOS_MEDIA`, `VACIOS_DIFICIL`, etc., reemplazando todos los literales numéricos en código y headers.

* 🗑️ **Limpieza de código y warnings**

  * Eliminada variable `clave` sin usar en `menuPrincipal`.
  * Inicializadas `fila`, `columna` y `valor` para evitar “may be used uninitialized”.
  * Eliminados bloques de código inalcanzable y comentarios superfluos.

* 🖥️ **Configuración de consola unificada**

  * Creada `configurarConsola()` en `varios.cpp` para centralizar `SetConsoleOutputCP`, `resetColor()` y demás ajustes.

* 📝 **Comentarios depurados**

  * Retirados comentarios redundantes (ej. “// Fin del main”, marcas de posición, bloques obsoletos) dejando sólo anotaciones de alto nivel.

* ⚙️ **Mejoras de jugabilidad**

  * Renombrado contador `errores` a `intentosFallidos`; añadido `numerosAgotados` para rastrear cuántas veces se agotó un dígito.
  * Métricas de juego impresas en cada iteración, antes del ingreso de datos.
  * **Validación contra la solución real**: tras las validaciones de fila/columna/cuadro, se comprueba `valor == SOLUCION[fila-1][columna-1]`; si no coincide, se suma un fallo y se avisa.

* 🛠️ **Correcciones menores**

  * Ajuste de flujos de `cin`/`cout` para mantener `using namespace std;` sin prefijos `std::`.
  * Refinamiento de `mostrarError()` y `MSGPAUSA()` en todas las ramas de error.

🎯 **Resultado:** La versión v:0.8.9 ofrece una jugabilidad más sólida, con métricas de error claras, validación fiel a la solución, y un código fuente pulido y homogéneo, listo para la siguiente fase de refactorización y expansión de funcionalidades.

---

**Pendientes para v0.9.0** (en CHANGELOG y CONVENCIONES.md):

* Refactorizar rutina de ingreso de datos duplicada (`jugarPartida` y `modoIngresoManual`).
* Migrar a `<random>` y `std::shuffle` con `std::mt19937`.
* Aplicar `clang-format` al código completo.
* Implementar límite de intentos fallidos y Game Over dinámico.
* Extraer menú de configuración de parámetros de juego.

---
### 🔹 v:0.9 – Sistema de ranking retro de mejores tiempos y errores

📅 Fecha: 24 de julio de 2025  
**Cambios:**

* 🏆 **Ranking retro**  
  - Se declara en `archivos.h` el `struct ScoreEntry` y la matriz estática `scores[3][5]`.  
  - Se implementan en `archivos.cpp` las funciones de gestión:
    - `cargarScores()` (crea `scores.txt` si no existe).  
    - `actualizarScores(const ScoreEntry&)` (inserta y ordena top 5 por nivel).  
    - `guardarScores()` (escribe en `scores.txt` con formato “Ini - Nivel - Err - Seg - Timestamp”).  
    - `mostrarScores(int nivel)` (presentación ASCII retro con encabezado e iniciales).  
    - `resetScores()` (backdoor → opción 15, confirma con s/n y borra el histórico).  
* 🎮 **Integración en flujo de juego**  
  - **Opción 4** en `menuPrincipal()`: muestra top 5 de Fácil, Medio y Difícil.  
  - En `jugarPartida()`, tras la victoria:
    1. Se piden 3 iniciales al jugador.  
    2. Se registra un `ScoreEntry` con nivel, erroresFallidos, duración (s) y timestamp `YYYYMMDD-HHMMSS`.  
    3. Se recarga, actualiza y guarda el ranking, y se llama a `mostrarScores(nivel)`.  
* 🔧 **Control de ausencia de archivo**  
  - `cargarScores()` detecta si `scores.txt` no existe y lo crea vacío para evitar errores en opción 4.  
* 🔐 **Reset desde BackDoor**  
  - En `subMenuBackDoor()`, opción 15 pregunta “¿Desea borrar los mejores tiempos? (s/n)” y usa `resetScores()`.

🎯 **Resultado:**  
Se integra un sistema completo y retro de puntuaciones, persistent y personalizable, directamente en el flujo de juego y accesible en el menú principal y en el BackDoor.

---
## 📘 CHANGELOG – Sodoku C++ v0.9.1

### 🔍 Reparaciones y Refactorizaciones

#### R-01: Refactor ingreso de usuario en jugada competitiva

* **Descripción**: Consolidación de la lógica de ingreso (fila, columna, valor) en la función `procesarIngresoUsuario()`.
* **Estado**: ✅ Resuelto.
* **Cambios clave**:

  * Un único prompt de dificultad en `iniciarJuego()`.
  * Flag `partidaEnCurso` controlado en `iniciarJuego()` y consumido en `jugarPartida()`.

#### R-02: Adaptación de backtracking y vaciado de celdas

* **Descripción**: Se migró la generación de soluciones y vaciado de celdas a `generarSodokuResuelto()` y uso de `std::mt19937`.
* **Estado**: ✅ Resuelto.
* **Cambios clave**:

  * Uso de `generarSodokuResuelto()` para llenar `SOLUCION`.
  * `generarTableroAleatorio()` y `fijarCeldasActuales()` integrados en flujo.

#### F-01: Separación de mostrarScores en módulo pantalla.cpp

* **Descripción**: Refactor para mover `mostrarScores()` a `pantalla.cpp` y ajustar firmas.
* **Estado**: ✅ Resuelto.
* **Cambios clave**:

  * Inclusión de `<climits>` y `<cstring>` en archivos correspondientes.
  * Corrige indentation en bucle de impresión.

#### S-01: Sistema de gestión de flags de partida

* **Descripción**: Manejo de `partidaEnCurso` y `nivelCargado` para inicio, reanudación y cierre de sesiones.
* **Estado**: ✅ Resuelto.
* **Cambios clave**:

  * Flag levantada en `iniciarJuego()` solo tras generar tablero.
  * Consumo de flag en `jugarPartida()` al finalizar.
  * Reset de flag y nivel al rechazar reanudación.

### 🛠️ Pendientes para v0.9.2

1. **Migrar a `<random>` completo y eliminar `rand()`**
2. **Game Over configurable desde menú** (`configurarGameOver()` implemetar)
3. **Documentación viva de UX**: crear `UX.md` con flujos críticos.
4. **Pruebas mínimas**: anotar en `DIRECTIVAS.md` casos de prueba.
5. **Integración con GitHub**: inicializar repositorio y CI básica.

---

*Fecha de cierre: 31 de julio de 2025*


### 🔹 v:0.9.2 – Ajustes finales BackDoor y Resolver automático

📅 Fecha: 4 de agosto de 2025
**Cambios:**

* **Corrección de MSGPAUSA()**: se añadió `std::cin.get();` tras `std::cin.ignore(...)` para pausar correctamente.
* **Submenú BackDoor numérico**: eliminadas salidas “x”/“z” y migrado a todo númerico (`0` = volver, `100` = salida total).
* **Lectura directa de opción**: reemplazado `opcionStr` + `stoi` por `int opcion` con validación robusta (`cin.clear()`, `cin.ignore()`).
* **Resolver automáticamente (case 8)**: confirmación S/N; copia de matriz y backtracking en copia; animación de barra de progreso; pregunta de sobrescritura con restauración del original.

*Fecha de cierre: 4 de agosto de 2025*

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