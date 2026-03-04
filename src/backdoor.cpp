// SubMenu Backdoor.cpp = v:0.9.4
// #include <algorithm> // para random_shuffle
#include <chrono> // Para calcular el tiempo
// #include <cstdlib>   // exit() está aquí, sin importar el sistema
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits> // numeric_limits
#include <sstream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

// Dependencias de archivos separados.
#include "Sodoku.h"
#include "archivos.h"   // usa guardar/cargar/mostrarError/scores
#include "constantes.h" // para FECHA_VERSION, HORA_VERSION, VERSION
#include "pantalla.h"
#include "varios.h" // usa colorTexto, MSGPAUSA, etc.

// Claves de BACKDOOR: en backdoor.h
int CLAVE_NIVEL_0 = 1234;
int CLAVE_NIVEL_1 = 5678;
int CLAVE_NIVEL_2 = 1111;

//***********************

/*
| Nivel | Rol             | Descripción general                                                              |
| ----- | --------------- | -------------------------------------------------------------------------------- |
| `0`   | Usuario inicial | Solo consulta e inspección del estado interno                                    |
| `1`   | Usuario medio   | Puede ejecutar herramientas de testeo, pre-carga y validación                    |
| `2`   | SuperUsuario    | Accede a edición manual, modificación directa de estructuras, y sistema de score |
| ----- | --------------- | -------------------------------------------------------------------------------- |
| Opción                                 | Nivel mínimo |
| -------------------------------------- | ------------ |
| `'1'` a `'4'`                          | >= 0         |
| `'5'` a `'9'`                          | >= 1         |
| `'10'`, `'12'`, `'13'`, `'14'`, `'15'` | >= 2         |
| -------------------------------------- | ------------ |
*/

void subMenuBackDoor(int nivelAcceso) {
    colorTexto("verde");
    int opcion;
    while (true) {
        limpiarPantalla();
        colorTexto("verde");
        switch (nivelAcceso) {
        case 0:
            cout << "Ingreso con nivel de acceso: " << nivelAcceso << endl;
            cout << "=============================================" << endl;
            cout << "=  🔐 BACKDOOR – Nivel 0 (Usuario Inicial)  =\n";
            cout << "=============================================" << endl;
            cout << "🕹️  TABLERO Y CELDAS\n";
            cout << "[  1  ] Mostrar MATRIZ\n";
            cout << "[  2  ] Mostrar CELDAFIJA\n";
            cout << "[  3  ] Mostrar MASCARA\n";
            cout << "[ 20  ] Fijar celdas actuales como fijas" << endl;
            cout << "\n✔️  DIAGNÓSTICO Y TESTEOS\n";
            cout << "[  4  ] Validar tablero actual (sudokuValido)\n";
            cout << "\n💾  ARCHIVOS Y GUARDADO\n";
            cout << "[ 16  ] Exportar datos a CSV\n";
            cout << "\n[  0  ] Volver al menú principal\n";
            cout << "=============================================" << endl;
            break;
        case 1:
            cout << "Ingreso con nivel de acceso: " << nivelAcceso << endl;
            cout << "=============================================" << endl;
            cout << "=  🔐 BACKDOOR – Nivel 0 (Usuario Inicial)  =\n";
            cout << "=  🔐 BACKDOOR – Nivel 1 (Usuario Medio)    =\n";
            cout << "=============================================" << endl;
            cout << "🕹️  TABLERO Y CELDAS\n";
            cout << "[  1  ] Mostrar MATRIZ\n";
            cout << "[  2  ] Mostrar CELDAFIJA\n";
            cout << "[  3  ] Mostrar MASCARA\n";
            cout << "[ 20  ] Fijar celdas actuales como fijas" << endl;
            cout << "\n✔️  DIAGNÓSTICO Y TESTEOS\n";
            cout << "[  4  ] Validar tablero actual (sudokuValido)\n";
            cout << "[  6  ] Inyectar error lógico (repetidos)\n";
            cout << "\n💾  ARCHIVOS Y GUARDADO\n";
            cout << "[  5  ] Cargar tablero de prueba predefinido\n";
            cout << "[  7  ] Borrado de tablero (no borra CELDAFIJA)\n";
            cout << "[  8  ] Fijar celda por coordenada\n";
            cout << "[  9  ] Forzar guardado rápido\n";
            cout << "[ 15  ] Mostrar y resetear estadísticas\n";
            cout << "[ 16  ] Exportar datos a CSV\n";
            cout << "\n[  0  ] Volver\n";
            cout << "=============================================" << endl;
            break;
        case 2:
            cout << "Ingreso con nivel de acceso: " << nivelAcceso << endl;
            cout << "=============================================" << endl;
            cout << "=  🔐 BACKDOOR – Nivel 0 (Usuario Inicial)  =\n";
            cout << "=  🔐 BACKDOOR – Nivel 1 (Usuario Medio)    =\n";
            cout << "=  🔐 BACKDOOR – Nivel 2 (SuperUsuario)     =\n";
            cout << "=============================================" << endl;
            cout << "🕹️  TABLERO Y CELDAS\n";
            cout << "[  1  ] Mostrar MATRIZ\n";
            cout << "[  2  ] Mostrar CELDAFIJA\n";
            cout << "[  3  ] Mostrar MASCARA\n";
            cout << "[ 17  ] Mostrar Matriz Resuelta (Requiere doble factor de autentificación)\n";
            cout << "[  8  ] Fijar celda por coordenada\n";
            cout << "[ 10  ] Editar MATRIZ manualmente\n";
            cout << "[ 11  ] Editar CELDAFIJA\n";
            cout << "[ 12  ] Quitar todas las CELDAFIJA\n";
            cout << "[ 20  ] Fijar celdas actuales como fijas" << endl;
            cout << "\n✔️  DIAGNÓSTICO Y TESTEOS\n";
            cout << "[  4  ] Validar tablero actual (sudokuValido)\n";
            cout << "[  6  ] Inyectar error lógico (repetidos)\n";
            cout << "\n💾  ARCHIVOS Y GUARDADO\n";
            cout << "[  5  ] Cargar tablero de prueba predefinido\n";
            cout << "[  9  ] Forzar guardado rápido\n";
            cout << "[ 16  ] Exportar datos a CSV\n";
            cout << "[ 15  ] Mostrar y resetear estadísticas\n";
            cout << "\n🛠️  FUNCIONES AVANZADAS\n";
            cout << "[  7  ] Borrado de tablero (no borra CELDAFIJA)\n";
            cout << "[ 13  ] Borrar tablero completo (hard reset)\n";
            cout << "[ 14  ] Asignar puntaje manual                         [EN DESARROLLO]\n";
            cout << "[ 18  ] Habilita Ingresar al [2] Modo competitivo (con niveles) con [8] Resolver automáticamente.\n";
            cout << "\n[ 100 ] SALIDA TOTAL\n";
            cout << "[  0  ] Volver\n";
            cout << "=============================================" << endl;
            break;
        default:
            mostrarError("Nivel de acceso no válido.");
            return;
        }

        // Opción para volver
        cout << "Seleccione una opción: " << std::flush;

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mostrarError("Entrada inválida, ingrese un número.");
            continue;
        }
        // Salir del submenu
        if (opcion == CODIGO_SALIR_MENU) {
            cout << "Usted ingreso: " << opcion;
            resetColor();
            return;
        }

        if (opcion == CODIGO_SALIDA_TOTAL) {
            if (nivelAcceso >= 2) {
                cout << "Saliendo del BackDoor y del programa..." << endl;
                exit(0);
            } else {
                mostrarError("Nivel insuficiente para salida total.");
                continue;
            }
        }
        // cout << "La opción seleccionada es: " << opcion << endl;
        // MSGPAUSA(); // OPCIONES DEL MENU:
        switch (opcion) {
        case 1: // Mostrar matriz
            mostrarMatriz(MATRIZ, "MATRIZ EN JUEGO");
            MSGPAUSA();
            break;
        case 2: // [  2  ] Mostrar CELDAFIJA
            colorTexto("amarillo");
            cout << "🔒 CELDAS FIJAS (F = fija, . = libre):\n\n";
            // Encabezado columnas
            cout << "     ";
            for (int col = 0; col < TAM; col++)
                cout << " " << col + 1 << " ";
            cout << "\n    ---------------------------\n";

            for (int fila = 0; fila < TAM; fila++) {
                cout << " " << fila + 1 << " |";
                for (int col = 0; col < TAM; col++) {
                    if (CELDAFIJA[fila][col])
                        cout << " F ";
                    else
                        cout << " . ";
                }
                cout << "\n";
            }
            resetColor();
            MSGPAUSA();
            break;
        case 3: // [  3  ] Mostrar MASCARA
            colorTexto("amarillo");
            cout << "🟡 MÁSCARA ACTUAL:\n\n";
            cout << "Símbolos:\n";
            cout << "  % = fila activa\n";
            cout << "  ? = celda actual\n";
            cout << "  - = columna activa\n";
            cout << "  . = sin marca\n\n";
            // Encabezado columnas
            cout << "     ";
            for (int col = 0; col < TAM; col++)
                cout << " " << col + 1 << " ";
            cout << "\n    ---------------------------\n";

            for (int fila = 0; fila < TAM; fila++) {
                cout << " " << fila + 1 << " |";
                for (int col = 0; col < TAM; col++) {
                    char c = MASCARA[fila][col];
                    if (c == '\0' || c == ' ')
                        cout << " . ";
                    else
                        cout << " " << c << " ";
                }
                cout << "\n";
            }
            resetColor();
            MSGPAUSA();
            break;
        case 4: // Validar tablero actual (sudokuValido)
        {
            // limpiarPantalla();
            colorTexto("amarillo");
            cout << "🔍 DIAGNÓSTICO LÓGICO DE MATRIZ\n\n";

            if (sudokuValido(MATRIZ)) {
                colorTexto("verde");
                cout << "✔️ MATRIZ VÁLIDA (sin conflictos lógicos).\n";
            } else {
                colorTexto("rojo");
                cout << "❌ MATRIZ INVÁLIDA (contiene errores lógicos).\n";
            }
            resetColor();
            MSGPAUSA();
            break;
        } break;
        // NUEVO NIVEL DE ACCESO //
        case 5: // [  5  ] Cargar tablero de prueba predefinido
        {
            /* TABLERO DE PRUEBA 2 IMPLEMENTADO PARA RESOLVER EVENTOS (DESPUES
            VEMOS SI LO INCORPORAMOS AQUÍ)
            int solucionSudoku[TAM][TAM] = {
            {5, 3, 4, 6, 7, 8, 9, 1, 2},
            {6, 7, 2, 1, 9, 5, 3, 4, 8},
            {1, 9, 8, 3, 4, 2, 5, 6, 7},
            {8, 5, 9, 7, 6, 1, 4, 2, 3},
            {4, 2, 6, 8, 5, 3, 7, 9, 1},
            {7, 1, 3, 9, 2, 4, 8, 5, 6},
            {9, 6, 1, 5, 3, 7, 2, 8, 4},
            {2, 8, 7, 4, 1, 9, 6, 3, 5},
            {3, 4, 5, 2, 8, 6, 1, 7, 9}
        };                                  */
            if (nivelAcceso >= 1) {
                int tableroPrueba[TAM][TAM] = {
                    {5, 3, 0, 0, 7, 0, 0, 0, 0},
                    {6, 0, 0, 1, 9, 5, 0, 0, 0},
                    {0, 9, 8, 0, 0, 0, 0, 6, 0},
                    {8, 0, 0, 0, 6, 0, 0, 0, 3},
                    {4, 0, 0, 8, 0, 3, 0, 0, 1},
                    {7, 0, 0, 0, 2, 0, 0, 0, 6},
                    {0, 6, 0, 0, 0, 0, 2, 8, 0},
                    {0, 0, 0, 4, 1, 9, 0, 0, 5},
                    {0, 0, 0, 0, 8, 0, 0, 7, 9}};

                for (int i = 0; i < TAM; i++) {
                    for (int j = 0; j < TAM; j++) {
                        MATRIZ[i][j] = tableroPrueba[i][j];
                        CELDAFIJA[i][j] = (tableroPrueba[i][j] != 0);
                    }
                }

                colorTexto("verde");
                cout << "✅ Tablero de prueba cargado exitosamente.\n";
                resetColor();
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            MSGPAUSA();
            break;
        } break;
        case 6: // [  6  ] Inyectar error lógico (repetidos)
            if (nivelAcceso >= 1) {
                // Inyectamos dos valores idénticos en la misma fila (fila 0, columnas 0 y 1)
                MATRIZ[0][0] = TAM;
                MATRIZ[0][1] = TAM;
                colorTexto("rojo");
                cout << "❌ Se inyectó un error lógico en la fila 1 (dos '9' consecutivos).\n";
                resetColor();
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            MSGPAUSA();
            break;
        case 7: // [  7  ] Borrado de tablero (no borra CELDAFIJA)
            if (nivelAcceso >= 1) {
                limpiarTablero();
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            MSGPAUSA();
            break;
        case 8: // [ 8 ] Fijar celda por coordenada
            if (nivelAcceso >= 1) {
                int fila, columna;
                do {
                    limpiarPantalla();
                    colorTexto("cyan");
                    cout << "📌 FIJAR CELDA POR COORDENADA\n";
                    cout << "(Ingrese 0 0 para salir)\n\n";
                    resetColor();

                    mostrarMatriz(MATRIZ, "MATRIZ EN JUEGO");

                    // Mostrar matriz de celdas fijas
                    cout << "\n🔒 Estado de CELDAFIJA (celdas fijas = 1):\n\n";
                    cout << "     ";
                    for (int col = 0; col < TAM; col++)
                        cout << " " << col + 1 << " ";
                    cout << "\n    ---------------------------\n";
                    for (int f = 0; f < TAM; f++) {
                        cout << " " << f + 1 << " |";
                        for (int c = 0; c < TAM; c++)
                            cout << " " << (CELDAFIJA[f][c] ? "1" : ".") << " ";
                        cout << "\n";
                    }

                    cout << "\nIngrese Fila (1–9): ";
                    cin >> fila;
                    cout << "Ingrese Columna (1–9): ";
                    cin >> columna;

                    if (fila == 0 && columna == 0)
                        break;

                    if (fila < 1 || fila > TAM || columna < 1 || columna > TAM) {
                        mostrarError("Coordenadas fuera de rango.");
                        continue;
                    }

                    if (CELDAFIJA[fila - 1][columna - 1]) {
                        colorTexto("amarillo");
                        cout << "\n⚠️  La celda [" << fila << "," << columna << "] ya estaba marcada como fija.\n";
                    } else {
                        if (MATRIZ[fila - 1][columna - 1] == 0) {
                            colorTexto("amarillo");
                            cout << "\n🤔 Estás fijando una celda vacía… ¿te parece lógico?\n";
                            cout << "😎 Bueno, sos el admin... así que adelante si querés.\n";

                            int confirmacion;
                            cout << "\n¿Deseás fijarla igual?\n[0 = Sí / 1 = No]: ";
                            cin >> confirmacion;

                            if (confirmacion != 0) {
                                colorTexto("rojo");
                                cout << "\n❌ Operación cancelada. La celda no fue fijada.\n";
                                resetColor();
                                MSGPAUSA();
                                continue;
                            }
                        }

                        CELDAFIJA[fila - 1][columna - 1] = true;
                        colorTexto("verde");
                        cout << "\n✅ Celda [" << fila << "," << columna << "] marcada como fija correctamente.\n";
                    }
                    resetColor();
                    MSGPAUSA();
                } while (true);
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            break;
        case 9: // [  9  ] Forzar guardado rápido
            if (nivelAcceso >= 1) {
                guardarPartidaEnArchivo();
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            break;
            // NUEVO NIVEL DE ACCESO
        case 10: // [ 10  ] Editar MATRIZ manualmente
            if (nivelAcceso >= 2) {
                int fila, columna, valor;
                do {
                    limpiarPantalla();
                    colorTexto("amarillo");
                    cout << "✏️  EDICIÓN MANUAL DE MATRIZ\n";
                    cout << "(Ingrese 0 0 0 para salir)\n\n";
                    resetColor();
                    mostrarMatriz(MATRIZ, "MATRIZ EN JUEGO");
                    // Mostrar estado actual de la fila editada opcionalmente
                    cout << "Ingrese Fila (1–9): ";
                    cin >> fila;
                    cout << "Ingrese Columna (1–9): ";
                    cin >> columna;
                    cout << "Ingrese Valor (1–9 o 0 para borrar): ";
                    cin >> valor;

                    if (fila == 0 && columna == 0 && valor == 0)
                        break;

                    if (fila < 1 || fila > TAM || columna < 1 || columna > TAM || valor < 0 || valor > TAM) {
                        mostrarError("Valores fuera de rango.");
                        continue;
                    }

                    MATRIZ[fila - 1][columna - 1] = valor;

                    colorTexto("verde");
                    cout << "✅ Celda [" << fila << "," << columna << "] actualizada con valor " << valor << ".\n";
                    resetColor();
                    MSGPAUSA();

                } while (true);
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            break;
        case 11: // [ 11  ] Editar CELDAFIJA
            if (nivelAcceso >= 2) {
                int fila, columna;
                do {
                    limpiarPantalla();
                    colorTexto("cyan");
                    cout << "✏️  EDICIÓN DE CELDAFIJA\n";
                    cout << "(Ingrese 0 0 para salir)\n\n";
                    resetColor();
                    mostrarMatriz(MATRIZ, "MATRIZ EN JUEGO");
                    // Mostrar matriz de celdas fijas
                    cout << "\n🔒 Estado de CELDAFIJA (celdas fijas = 1):\n\n";
                    cout << "     ";
                    for (int col = 0; col < TAM; col++)
                        cout << " " << col + 1 << " ";
                    cout << "\n    ---------------------------\n";
                    for (int f = 0; f < TAM; f++) {
                        cout << " " << f + 1 << " |";
                        for (int c = 0; c < TAM; c++)
                            cout << " " << (CELDAFIJA[f][c] ? "1" : ".") << " ";
                        cout << "\n";
                    }
                    cout << "\nIngrese Fila (1–9): ";
                    cin >> fila;
                    cout << "Ingrese Columna (1–9): ";
                    cin >> columna;
                    if (fila == 0 && columna == 0)
                        break;
                    if (fila < 1 || fila > TAM || columna < 1 || columna > TAM) {
                        mostrarError("Coordenadas fuera de rango.");
                        continue;
                    }
                    if (CELDAFIJA[fila - 1][columna - 1]) {
                        CELDAFIJA[fila - 1][columna - 1] = false;
                        colorTexto("verde");
                        cout << "\n✅ Celda fija [" << fila << "," << columna << "] fue desmarcada.\n";
                    } else {
                        colorTexto("amarillo");
                        cout << "\n⚠️  La celda [" << fila << "," << columna << "] no estaba marcada como fija.\n";
                    }
                    resetColor();
                    MSGPAUSA();
                } while (true);
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            break;
        case 12: // [ 12  ] Quitar todas las CELDAFIJA
            if (nivelAcceso >= 2) {
                int opcion;
                do {
                    limpiarPantalla();
                    colorTexto("cyan");
                    cout << "🧹 QUITAR TODAS LAS CELDAS FIJAS\n";
                    cout << "(Ingrese 0 = SÍ / 1 = NO / 2 = SALIR)\n\n";
                    resetColor();

                    mostrarMatriz(MATRIZ, "MATRIZ EN JUEGO");

                    // Mostrar matriz de celdas fijas
                    cout << "\n🔒 Estado de CELDAFIJA (celdas fijas = 1):\n\n";
                    cout << "     ";
                    for (int col = 0; col < TAM; col++)
                        cout << " " << col + 1 << " ";
                    cout << "\n    ---------------------------\n";
                    for (int f = 0; f < TAM; f++) {
                        cout << " " << f + 1 << " |";
                        for (int c = 0; c < TAM; c++)
                            cout << " " << (CELDAFIJA[f][c] ? "1" : ".") << " ";
                        cout << "\n";
                    }

                    cout << "\n¿Desea DESFIJAR todas las celdas del tablero?\n";
                    cout << "[0 = Sí / 1 = No / 2 = Salir]: ";
                    /////////// VER ESTA VARIABLE SI LA CAMBIAMOS O SI SE PISA CON LA DEL MENÚ
                    cin >> opcion; // VERLA

                    if (opcion == 2)
                        break;

                    if (opcion == CODIGO_SALIR_MENU) {
                        for (int f = CODIGO_SALIR_MENU; f < TAM; f++)
                            for (int c = CODIGO_SALIR_MENU; c < TAM; c++)
                                CELDAFIJA[f][c] = false;

                        colorTexto("verde");
                        cout << "\n✅ Todas las celdas fijas fueron desmarcadas exitosamente.\n";
                    } else if (opcion == 1) {
                        colorTexto("amarillo");
                        cout << "\n⚠️  Operación cancelada por el usuario.\n";
                    } else {
                        mostrarError("Opción inválida. Use 0, 1 o 2.");
                        continue;
                    }

                    resetColor();
                    MSGPAUSA();

                } while (false);
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            break;
        case 13: // [ 13 ] Borrar tablero completo (hard reset)
            if (nivelAcceso >= 2) {
                int opcion;
                limpiarPantalla();
                colorTexto("rojo");
                cout << "💣 HARD RESET: BORRAR TABLERO COMPLETO\n\n";
                resetColor();

                mostrarMatriz(MATRIZ, "MATRIZ EN JUEGO");

                cout << "\n⚠️  Esta acción borrará todos los valores y celdas fijas del tablero.\n";
                cout << "¿Desea continuar?\n";
                cout << "[0 = Sí / 1 = No]: ";
                ////////// VER SI ESTAS VARIABLES SE PISAN CON LAS DEL MENÚ
                cin >> opcion; // VERLA

                if (opcion == CODIGO_SALIR_MENU) {
                    for (int fila = CODIGO_SALIR_MENU; fila < TAM; fila++)
                        for (int col = CODIGO_SALIR_MENU; col < TAM; col++) {
                            MATRIZ[fila][col] = CODIGO_SALIR_MENU;
                            CELDAFIJA[fila][col] = false;
                        }

                    colorTexto("verde");
                    cout << "\n✅ Reinicio total realizado exitosamente.\n";
                } else {
                    colorTexto("amarillo");
                    cout << "\n🚫 Operación cancelada por el usuario.\n";
                }

                resetColor();
                MSGPAUSA();
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            break;
        case 14: // [ 14  ] Asignar puntaje manual                         [EN DESARROLLO]
            break;
        case 15: // [ 15  ] Mostrar y resetear estadísticas
            // limpiarPantalla();
            // autor();
            // Desplegar top 5 para cada nivel
            mostrarScores(0); // +++ FACIL +++
            mostrarScores(1); // +++ MEDIO +++
            mostrarScores(2); // +++ DIFICIL +++
            // MSGPAUSA();
            if (nivelAcceso >= 1) {
                // Dentro de subMenuBackDoor(), en el switch(opcion):
                {
                    // desde aquí: confirmar y resetear mejores tiempos
                    char opcion;
                    do {
                        cout << "\n¿Desea borrar los mejores tiempos? (s/n): ";
                        cin >> opcion;
                        opcion = tolower(opcion);
                        if (opcion != 's' && opcion != 'n') {
                            mostrarError("Opción inválida, ingrese 's' o 'n'.");
                        }
                    } while (opcion != 's' && opcion != 'n');

                    if (opcion == 's') {
                        resetScores();
                        mostrarError("🏁 Mejores tiempos borrados.");
                    } else {
                        mostrarError("Acción de borrado cancelada.");
                    }
                    MSGPAUSA();
                }
                resetColor();
                return;
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            MSGPAUSA();
            break;
        case 16: // [ 16  ] Exportar datos a CSV
            exportarMatrizACSV();
            break;
        case 17: // cout << "[ 17  ] Ver Matriz Resuelta (Requiere doble factor de autentificación)
            if (nivelAcceso >= 1) {

                cout << "Ingrese doble factor de autentificación: " << endl;
                mostrarMatriz(SOLUCION, "SOLUCIÓN DEL TABLERO");
                MSGPAUSA();
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            break;
        case 18: // cout << "[ 18  ] Habilita Ingresar al [2] Modo competitivo (con niveles) con [8] Resolver automáticamente.\n";

            if (nivelAcceso >= 1) {
                cout << "Se habilita Ingresar al [2] 'Modo competitivo' habiendo usado el [8] 'Resolver automáticamente'." << endl;
                SODOKU_RESUELTO = false;
                resetColor();
            } else {
                mostrarError("Nivel insuficiente para esta opción.");
            }
            MSGPAUSA();
            break;
        case 19: // borrar scores.
            break;
        case 20: // [ 20  ] Fijar celdas actuales como fijas
            fijarCeldasActuales();
            break;
        default:
            mostrarError("Función aún en desarrollo o no implementada.");
            break;
        }
    }
}

int validarNivelDeAcceso() {
    limpiarPantalla();
    colorTexto("verde");
    cout << "Validación de ingreso de usuario: " << endl;
    cout << "🔐 BACKDOOR – Nivel 0 (Usuario Inicial): " << CLAVE_NIVEL_0 << " \n";
    cout << "🔐 BACKDOOR – Nivel 1 (Usuario Medio)  : " << CLAVE_NIVEL_1 << " \n";
    cout << "🔐 BACKDOOR – Nivel 2 (SuperUsuario)   : " << endl;
    cout << "Contraseña: ";
    colorTexto("rojo");

    int clave;
    cin >> clave;
    colorTexto("verde");

    if (clave == CLAVE_NIVEL_0) {
        cout << "✅ Acceso concedido como Usuario Inicial.\n";
        MSGPAUSA();
        return 0;
    }
    if (clave == CLAVE_NIVEL_1) {
        cout << "✅ Acceso concedido como Usuario Medio.\n";
        MSGPAUSA();
        return 1;
    }
    if (clave == CLAVE_NIVEL_2) {
        cout << "✅ Acceso concedido como SuperUsuario.\n";
        MSGPAUSA();
        return 2;
    }

    colorTexto("rojo");
    cout << "❌ Acceso denegado.\n";
    resetColor();
    MSGPAUSA();
    return -1;
}