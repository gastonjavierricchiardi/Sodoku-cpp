# Documentación gráfica de Sodoku C++

Estado: Fases A y B aprobadas; sincronización documental con `5c48cd4` aprobada para publicación.

## Fuente de arquitectura

- [Informe de arquitectura completo](../informes/INFORME_ARQUITECTURA_SODOKU.txt), conservado íntegro como evidencia histórica de `d9cc5c6`.
- [Informe incremental de arquitectura](../informes/INFORME_ACTUALIZACION_ARQUITECTURA_5c48cd4.txt), con ubicaciones, hashes, diferencias y pendientes de `5c48cd4`.
- Versión declarada del programa: **0.9.4**.
- Commit del informe base: [`d9cc5c6904db2f79930b9d5757a04766cd67502d`](https://github.com/gastonjavierricchiardi/Sodoku-cpp/commit/d9cc5c6904db2f79930b9d5757a04766cd67502d).
- Fecha del análisis estático base: **19/11/2026**.
- Código actualizado contrastado: [`5c48cd4889ee3c94813ffea99269ae95ff6b80ee`](https://github.com/gastonjavierricchiardi/Sodoku-cpp/commit/5c48cd4889ee3c94813ffea99269ae95ff6b80ee).
- Fecha del contraste incremental: **24/11/2026**.

El informe base se conserva íntegramente, manteniendo su contenido y el contexto original de elaboración. Identifica firmas, líneas, llamadas, dependencias, estado compartido, flujos y observaciones pendientes. Sus comprobaciones estáticas no equivalen a pruebas de ejecución.

## Estado de los diagramas

- [Arquitectura de Sodoku C++](ARQUITECTURA.md): primer documento Mermaid, aprobado para la Fase A. Representa los cinco módulos C++, sus dependencias y llamadas, la persistencia y el estado global compartido, con referencias al informe y pendientes de verificación.
- [Funciones y llamadas de Sodoku C++](FUNCIONES.md): documento aprobado para la Fase B. Incluye las 50 funciones implementadas, sus firmas y 14 diagramas Mermaid de llamadas, con referencias al informe TXT.

Se conservan los **16 diagramas Mermaid** y sus relaciones. Las etiquetas `Lnnn` siguen señalando líneas del TXT base; el informe incremental aporta la correspondencia con el código actualizado. Las 18 observaciones técnicas heredadas permanecen pendientes.

La nueva **INC-5C48CD4-01** de BackDoor queda **PENDIENTE DE VERIFICACIÓN** y separada de ARQ-14, sin declarar equivalencia ni duplicación: [§8, L298–L322](../informes/INFORME_ACTUALIZACION_ARQUITECTURA_5c48cd4.txt#L298-L322).

La publicación de esta actualización en `docs/diagramas-sodoku` está autorizada. El inicio de la Fase C requiere autorización previa.

La trazabilidad de cada diagrama deberá indicar el informe y la revisión de código utilizados. Un cambio posterior del código no actualiza automáticamente la vigencia de la evidencia.

## Documentos de referencia

- [Plan de documentación gráfica](../PLAN_DIAGRAMAS_SODOKU.md), conservado en su ubicación actual.
- [Directivas del proyecto](../DIRECTIVAS.md).
- [Convenciones de desarrollo](../CONVENCIONES.md).
- [Flujos de usuario documentados](../UX.md).
