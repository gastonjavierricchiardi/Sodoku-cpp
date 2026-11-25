---

# 📄 DIRECTIVAS DE PRUEBAS – PROYECTO "Sodoku C++"

Además de la prueba de modificación/borrado de celdas, conviene cubrir al menos estos escenarios en “Pruebas Mínimas” para garantizar que todo el flujo básico — y backdoor — funcione:

---

#### 1. Ingreso Simple

1. Ejecutar **modoIngresoManual** o **jugarPartida**.
2. Ingresar un valor correcto (e.g. fila 3, col 5, valor 7).

   * Verificar que `MATRIZ[2][4] == 7` y que no se incremente `intentosFallidos`.
3. Ingresar un valor fuera de rango (e.g. fila 10, col 10).

   * Debe mostrarse error, `MSGPAUSA()`, y volver al prompt de fila sin cambiar nada.
   * En `jugarPartida`, ingresar `0` en fila o columna es un comando de salida al menú principal, no un error de rango.
4. Ingresar un carácter no numérico (e.g. letra).

   * Debe limpiar el stream (`cin.clear()`, `cin.ignore()`), mostrar error, pausar, y re-preguntar fila.
5. Ingresar código de cancelar (99).

   * Debe devolver estatus `CANCELAR`, no incrementar `intentosFallidos`, limpiar máscara y volver al prompt de fila.
6. Ingresar código de backdoor (98).

   * Debe invocar `validarNivelDeAcceso()`, luego `subMenuBackDoor()`, limpiar máscara y re-preguntar fila.

---

#### 2. Nueva Partida Competitiva y Game Over

1. En el menú principal, elegir opción 2 → **Iniciar Juego**.

   * Al seleccionar “N” en “¿Reanudar?” debe reiniciar flags correctamente.
2. Configurar `endGame = 2` (desde menú 11) y, en modo competitivo, cometer dos errores lógicos consecutivos.

   * Tras el segundo, debe disparar “Game Over”, limpiar `partidaEnCurso` y volver al menú principal.
3. Ingresar todos los valores correctamente hasta completar el tablero.

   * Debe detectar victoria, mostrar felicidades, registrar score y volver al menú principal.

---

#### 3. Guardar y Cargar Partida

1. Resolver o avanzar parcialmente la partida, luego elegir opción 6 (guardar).

   * Verificar que el fichero incluya 9 líneas de `MATRIZ`, 9 de `CELDAFIJA`, 9 de `SOLUCION` y el contador de fallos.
2. Salir y relanzar el programa; elegir opción 5 (cargar).

   * Validar que `MATRIZ`, `CELDAFIJA`, `SOLUCION` y `intentosFallidos` queden exactamente como al guardar.
3. Intentar cargar un archivo corrupto (línea con menos de 9 valores).

   * Debe abortar la carga y mostrar error sin modificar el estado actual.

---

#### 4. BackDoor

1. Desde el menú principal, ingresar código 98 (backdoor).

   * Debe pedir clave, mostrar submenú según nivel, y respetar permisos.
2. En submenú, ejecutar el case 18 para habilitar `SODOKU_RESUELTO`.

   * Debe cambiar la bandera, mostrarse mensaje de éxito y permitir luego entrar a opción 2 para resolver.
3. Intentar “salida total” con nivel insuficiente (0/1).

   * Debe mostrar “Nivel insuficiente” y no salir del programa.

---

#### 5. Resolver Automáticamente (case 8)

1. Con un tablero válido pero parcialmente vacío, elegir opción 8 y contestar **N**.

   * Debe regresar al menú principal sin modificar nada.
2. Contestar **S**.

   * Debe “dibujar” la barra de progreso, preguntar sobreescritura y, si se acepta:

     * Copiar `copia` a `MATRIZ` y a `SOLUCION`, fijar `SODOKU_RESUELTO=true`.
   * Si se rechaza, debe descartar cambios.
3. Tras resolver automáticamente y aceptar, entrar de nuevo al modo competitivo (2) y verificar que:

   * `SOLUCION` esté cargada (se puede mostrar con backdoor 17).
   * Comenzar con la partida ya completa dispara inmediatamente la detección de victoria.

---

#### 6. Carga de Partida con Estadísticas (v:0.9.3)

1. Iniciar una partida y cometer errores lógicos hasta tener `intentosFallidos > 0`.
2. Guardar la partida (opción 6) y abrir el archivo `.txt` generado.

   * Verificar que incluya:

     * Línea `Nivel:X`
     * 9 líneas de `MATRIZ`
     * 9 líneas de `CELDAFIJA`
     * Línea `// ---- DATOS INTERNOS ----`
     * 9 líneas de `SOLUCION`
     * Línea `INTENTOS: n` con `n > 0`
3. Salir del programa, volver a iniciar y elegir opción 5 (cargar).

   * Al seleccionar el archivo anterior, debe mostrar:

     * `✅ Estadísticas cargadas` si `INTENTOS > 0` o `SODOKU_RESUELTO=true`
     * `⚠️ Sin estadísticas previas` si `INTENTOS=0` y no está resuelto.
4. Repetir la carga con un archivo antiguo (sin bloque interno).

   * Debe inicializar `SOLUCION` en ceros, `intentosFallidos=0` y mostrar `⚠️ Sin estadísticas previas`.
5. Probar carga con archivo corrupto en la sección `SOLUCION` (menos de 9 valores por fila).

   * Debe abortar la carga y mantener el estado previo.

---

## 7. Control de impacto documental y mantenimiento de diagramas

**Actualizacion de la directiva:** v1.1 — 25/11/2026 (referencia de version anterior: v1.0 — 17/07/2025).
**Linea base de documentacion:** commit \`7e46428eeaae248b0536fcb173c3604f77c3646a\` de \`main\`, con 35 diagramas Mermaid aprobados.
**Alcance:** toda modificacion autorizada de jugabilidad, funciones, llamadas, variables globales, permisos, estados, persistencia o interfaz del programa.

### 7.1. Antes del cambio

1. Identificar el commit de partida y consultar los informes TXT disponibles en \`docs/informes/\`. Para analizar codigo, utilizar los informes TXT como evidencia; no inferir contenido ausente ni asumir acceso a fuentes originales.
2. Identificar las funciones, declaraciones, variables y recorridos que podrian cambiar, asi como los diagramas potencialmente afectados.
3. Proponer el cambio con referencias exactas \`Lx-Ly\` del informe y solicitar: **"¿Confirmas este cambio?"** antes de aplicarlo. Respetar las convenciones y las condiciones de acceso ya autorizadas.

### 7.2. Despues de cada cambio de codigo autorizado

1. Preparar un **informe TXT incremental** que registre: commit base y revision nueva; archivos y rangos modificados; funciones y firmas completas (implementacion frente a declaracion); llamadas propias; variables globales, banderas y condiciones afectadas; cambios de ubicaciones; observaciones y limitaciones. Si la evidencia cubre solo parte del codigo, indicar **PENDIENTE DE VERIFICACION**.
2. Contrastar el impacto contra estos documentos:
   - \`docs/diagramas/ARQUITECTURA.md\`: modulos, dependencias y estado compartido.
   - \`docs/diagramas/FUNCIONES.md\`: funciones, firmas, ubicaciones y llamadas.
   - \`docs/diagramas/FLUJOS.md\`: menus, decisiones, validaciones y retornos.
   - \`docs/diagramas/ESTADOS.md\`: transiciones, banderas, permisos y condiciones.
   - \`docs/diagramas/INTERFAZ.md\`: pantallas, mensajes, tablero y navegacion.
3. Presentar el resultado por documento: **ACTUALIZAR** o **SIN IMPACTO**, con motivo y referencia al TXT. Los desplazamientos de lineas de codigo tambien deben evaluarse; no modificar las etiquetas \`Lnnn\` cuando refieran al informe historico.
4. Si se propone actualizar documentacion, mostrar el cambio y pedir aprobacion antes de aplicarlo. No reescribir informes historicos: agregar evidencia incremental con trazabilidad a cada revision.
5. Para cada refactor o funcion nueva, indicar una **Prueba Minima** concreta. No compilar ni ejecutar sin autorizacion expresa.

### 7.3. Verificacion, incidencias y publicacion

1. Una vez aprobada la actualizacion documental, verificar firmas y declaraciones, referencias y rangos, sintaxis y renderizado Mermaid, y coherencia entre todos los documentos afectados.
2. Conservar observaciones e incidencias **PENDIENTES** hasta que exista evidencia suficiente para resolverlas; registrar nuevas inconsistencias graves como **PENDIENTE**. No asumir que las 19 pendientes de la linea base siguen siendo las mismas despues de futuras revisiones: informar altas y cierres justificados.
3. Informar al cierre el porcentaje de funciones implementadas frente a declaradas, las observaciones resueltas y pendientes, los diagramas modificados o no afectados, la revision de codigo y la prueba minima propuesta.
4. No crear commits, hacer push, abrir PR ni integrar ramas sin autorizacion. Conservar la rama principal estable y mantener documentacion y codigo trazables a commits concretos.

**Regla general:** cambio de codigo -> informe TXT incremental -> control de impacto -> propuesta y aprobacion -> actualizacion documental -> verificacion -> publicacion autorizada. Si el impacto es nulo, dejar constancia expresa del motivo.
