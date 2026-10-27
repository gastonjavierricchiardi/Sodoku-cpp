// Cambiar la versión es desde: SODOKU.H VARIABLE VERSION
// Sudoku C++ v:0.9.4
// #include <algorithm> // para random_shuffle
#include <chrono> // Para calcular el tiempo
// #include <cstdlib>   // exit() está aquí, sin importar el sistema y srand, rand
#include <cctype>  // std::toupper
#include <cstring> // para strlen, strncpy
#include <ctime>   // time
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream> // cout, endl
#include <limits>   // para numeric_limits
#include <sstream>
#include <string>
#include <thread> // sleep_for
// **************************************************************
#include <unistd.h> // solo en Linux (SOLO PRUEBA DE TIEMPO)
// **************************************************************
#include <vector>
using namespace std;

// ********** Dependencias de archivos separados. **********
#include "Sodoku.h"     // resolverSudoku, mostrarMatriz, TAM
#include "archivos.h"   // usa guardar/cargar/mostrarError/scores
#include "backdoor.h"   // Se usa para el BackDoor
#include "constantes.h" // para FECHA_VERSION, HORA_VERSION, VERSION
#include "pantalla.h"
#include "varios.h" // usa colorTexto, MSGPAUSA, etc.
// ─── Plataforma Windows ───
// ___ Tema windows:
#ifdef _WIN32
// Para consola UTF-8
extern "C" __declspec(dllimport) int __stdcall SetConsoleOutputCP(unsigned int);
extern "C" __declspec(dllimport) int __stdcall SetConsoleCP(unsigned int);
#define CP_UTF8 65001
#include <windows.h> // Sleep(), SetConsoleOutputCP, SetConsoleCP
#else
// Para sleep_for en Linux/macOS
#include <chrono>
#include <thread>
#endif

// Matrices y Variables GLOBALES
char MASCARA[TAM][TAM];
int MATRIZ[TAM][TAM] = {0};
bool CELDAFIJA[TAM][TAM] = {false};
int SOLUCION[TAM][TAM];
char CARACTERPAUSA = 'X';            // Caracter para pausa, se puede cambiar
int endGame = MAX_INTENTOS_FALLIDOS; // Número de intentos fallidos para terminar el juego
bool partidaEnCurso = false;         // Flag para saber si hay una partida suspendida
int nivelCargado = -1;               // Flag para saber si hay una partida suspendida
bool SODOKU_RESUELTO = false;        // falso cerrado / verdadero abierto // Variable para saber si el Sudoku fue resuelto
int intentosFallidos = 0;            // Contador de intentos fallidos que tambien se usa para grabar el Game Over
// Del Juego
bool esPartidaNueva = false; // Bandera para partida nueva o en curso
// Tema acumulador de tiempo de sesión
time_t tsSesionInicio = 0;
long duracionAcumulada = 0;

// Definición de funciones
//---------------------------------------------------------------------------------------
// Que comience el juego
void limpiarTablero() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            MATRIZ[i][j] = 0;
}
//---------------------------------------------------------------------------------------
void generarMascara(int fila, int columna, char mascara[TAM][TAM]) {
    limpiarMascara(mascara);
    for (int j = 0; j < TAM; j++)
        mascara[fila - 1][j] = '%';
    for (int i = 0; i < TAM; i++)
        mascara[i][columna - 1] = '%';
    mascara[fila - 1][columna - 1] = '?';
}
//---------------------------------------------------------------------------------------
void mostrarMatriz(int matriz[TAM][TAM], std::string titulo) {
    colorTexto("amarillo");
    cout << "📋 " << titulo << ":\n\n";

    // Encabezado de columnas
    cout << "     ";
    for (int col = 0; col < TAM; col++)
        cout << " " << col + 1 << " ";
    cout << "\n    ---------------------------\n";

    for (int fila = 0; fila < TAM; fila++) {
        cout << " " << fila + 1 << " |";
        for (int col = 0; col < TAM; col++) {
            int val = matriz[fila][col];
            if (val == 0)
                cout << " . ";
            else
                cout << " " << val << " ";
        }
        cout << "\n";
    }

    resetColor();
}
//---------------------------------------------------------------------------------------
void generarMascaraCompletaPausa(char CARACTERPAUSA) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            MASCARA[i][j] = CARACTERPAUSA;
}
//---------------------------------------------------------------------------------------
void DibujarPantalla() {
    cout << "     1 2 3   4 5 6   7 8 9" << endl;
    cout << "   +-------+-------+-------+" << endl;
    for (int i = 0; i < TAM; i++) {
        cout << " " << i + 1 << " |";
        for (int j = 0; j < TAM; j++) {
            char celda = MATRIZ[i][j] ? '0' + MATRIZ[i][j] : MASCARA[i][j];
            if (MATRIZ[i][j] != 0 && CELDAFIJA[i][j])
                colorTexto("blanco");
            else if (MATRIZ[i][j] != 0)
                colorTexto("verde");
            cout << " " << celda;
            resetColor();
            if ((j + 1) % 3 == 0)
                cout << " |";
        }
        cout << " " << i + 1 << endl;
        if ((i + 1) % 3 == 0)
            cout << "   +-------+-------+-------+" << endl;
    }
    cout << "     1 2 3   4 5 6   7 8 9" << endl;
    cout << endl;
    cout << "Números agotados: ";
    for (int i = 1; i <= TAM; i++) {
        if (numeroAgotadoGlobal(i)) {
            colorTexto("rojo");
            cout << i << " ";
            resetColor();
        }
    }
    cout << endl;
}
//---------------------------------------------------------------------------------------
// Jugabilidad:

void modoIngresoManual() {
    bool seguir = true;

    while (seguir) {
        limpiarPantalla();
        autor();
        DibujarPantalla();
        cout << "Cero (0) en cualquier momento para salir." << endl;
        // NUEVO BLOQUE:
        // ─── Inicio de refactor R-01 ───
        int fila, columna, valor;
        IngresoStatus status = procesarIngresoUsuario(fila, columna, valor);
        switch (status) {
        case IngresoStatus::OK:
            // Colocar valor y chequeo de agotamiento
            MATRIZ[fila - 1][columna - 1] = valor;
            if (cantidadRestante(valor) == 0) {
                colorTexto("rojo");
                cout << "💥 ¡Atención! El número " << valor << " ha sido agotado. Ya no podrá ser ingresado nuevamente." << endl;
                resetColor();
                MSGPAUSA();
            }
            limpiarMascara(MASCARA);
            break;
        case IngresoStatus::BACKDOOR: {
            int nivelBD = validarNivelDeAcceso();
            if (nivelBD != -1)
                subMenuBackDoor(nivelBD);
            limpiarMascara(MASCARA);
            continue;
        }
        case IngresoStatus::CANCELAR:
            limpiarMascara(MASCARA);
            continue;
        case IngresoStatus::ERROR_SALIR:
            limpiarMascara(MASCARA);
            return;
        }
        // ─── Fin de refactor R-01 ───
        limpiarMascara(MASCARA);
    }
}

int seleccionarDificultad() {
    int opcion = -1;

    do {
        colorTexto("verde");
        std::cout << "\n🎮 SELECCION DE DIFICULTAD\n\n";
        resetColor();

        colorTexto("cyan");
        std::cout << "[1] Facil\n";
        std::cout << "[2] Media\n";
        std::cout << "[3] Dificil\n";
        std::cout << "[0] Cancelar\n";
        resetColor();

        std::cout << "\n>> ";
        std::cin >> opcion;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mostrarError("Entrada no valida. Ingrese 1, 2, 3 o 0 para cancelar.");
            opcion = -1;
            continue;
        }

        // 0 => cancelar (coherente con CODIGO_SALIR_MENU)
        if (opcion == CODIGO_SALIR_MENU) {
            return CODIGO_SALIR_MENU; // 0
        }

        if (opcion < 1 || opcion > 3) {
            mostrarError("Opcion fuera de rango. Ingrese 1, 2, 3 o 0 para cancelar.");
            opcion = -1;
        }

    } while (opcion < 1 || opcion > 3);

    // DEVOLVER 1..3 (NO restar 1 aca)
    return opcion;
}

// Iniciar Juego
void iniciarJuego() {
    limpiarPantalla();
    colorTexto("verde");
    std::cout << "\n🎮 INICIO DEL JUEGO – MODO COMPETITIVO\n\n";
    resetColor();

    // nivelIndex es siempre 0..2 internamente
    int nivelIndex = -1;

    if (nivelCargado >= 0) {
        // Ya hay nivel cargado en formato indice 0..2 (posible reanudada)
        nivelIndex = nivelCargado;
        // ⚠ No tocamos esPartidaNueva aqui: lo seteara cargarPartidaDesdeArchivo()
    } else {
        // Pedimos 0..3 (0 = cancelar, 1..3 = opcion)
        int opcion = seleccionarDificultad();

        // Cancelacion
        if (opcion == CODIGO_SALIR_MENU) {
            colorTexto("amarillo");
            std::cout << "Operacion cancelada. Volviendo al menu..." << std::endl;
            resetColor();
            MSGPAUSA();
            return;
        }

        // Convertimos 1..3 a indice 0..2
        nivelIndex = opcion - 1;

        // ✅ Partida nueva (seleccion por menu)
        esPartidaNueva = true;
    }

    // Seguridad
    if (nivelIndex < 0 || nivelIndex > 2) {
        mostrarError("Nivel invalido.");
        return;
    }

    // Persistimos nivel y marcamos partida (si corresponde)
    nivelCargado = nivelIndex;
    // partidaEnCurso = true; // descomentar si este es el momento de marcarla

    // Mensaje usuario
    std::string nombreDificultad;
    switch (nivelIndex) {
    case 0:
        nombreDificultad = "FACIL";
        break;
    case 1:
        nombreDificultad = "MEDIA";
        break;
    case 2:
        nombreDificultad = "DIFICIL";
        break;
    default:
        nombreDificultad = "DESCONOCIDA";
        break;
    }
    std::cout << "\nDificultad seleccionada: " << nombreDificultad << std::endl;

    // Arranca la partida
    jugarPartida(nivelIndex);
}

//---------------------------------------------------------------------------------------
// Funcion principal del juego COMPETITIVO
void jugarPartida(int nivel) {
    limpiarPantalla();

    bool nuevaPartida = esPartidaNueva;
    esPartidaNueva = false;

    bool esReanudar = partidaEnCurso;
    partidaEnCurso = false;

    string nombreDificultad;
    switch (nivel) {
    case 0:
        nombreDificultad = "Fácil";
        break;
    case 1:
        nombreDificultad = "Media";
        break;
    case 2:
        nombreDificultad = "Difícil";
        break;
    default:
        nombreDificultad = "Desconocida";
        break;
    }

    colorTexto("cyan");
    cout << "📘 Nivel seleccionado: " << nombreDificultad << " (" << nivel << ")" << endl;
    resetColor();

    if (nuevaPartida) {
        intentosFallidos = 0;
    }

    if (!esReanudar) {
        generarSodokuResuelto();
        generarTableroAleatorio(nivel);
        fijarCeldasActuales();
        partidaEnCurso = true;
    }

    // ⏱️ tiempos
    time_t tiempoInicio = time(nullptr);
    tm* inicio = localtime(&tiempoInicio);
    tsSesionInicio = tiempoInicio; // acumulo sesion

    int numerosAgotados = 0;
    bool seguir = true;
    while (seguir) {
        limpiarPantalla();
        autor();
        DibujarPantalla();
        bool completo = true;

        // GAME OVER
        if (endGame > 0 && intentosFallidos >= endGame) {
            cout << "❌ Intentos fallidos: " << intentosFallidos
                 << "   |   🔢 Números agotados: " << numerosAgotados << endl
                 << endl;

            colorTexto("rojo");
            cout << "JUEGO TERMINADO" << endl;
            resetColor();

            // resumen de sesion
            time_t tiempoFin = time(nullptr);
            tm* fin = localtime(&tiempoFin);
            int duracion = static_cast<int>(difftime(tiempoFin, tiempoInicio));
            int minutos = duracion / 60, segundos = duracion % 60;
            char horaInicioStr[9], horaFinStr[9];
            strftime(horaInicioStr, sizeof(horaInicioStr), "%H:%M:%S", inicio);
            strftime(horaFinStr, sizeof(horaFinStr), "%H:%M:%S", fin);

            colorTexto("cyan");
            cout << "\n⏱️ Hora de inicio  : " << horaInicioStr << endl;
            cout << "⏱️ Hora de fin     : " << horaFinStr << endl;
            cout << "⏱️ Duración total  : " << minutos << " min " << segundos << " seg." << endl;
            cout << "🔢 Números agotados  : " << numerosAgotados << endl;
            cout << "❌ Intentos fallidos : " << intentosFallidos << endl;
            resetColor();

            duracionAcumulada += static_cast<long>(difftime(time(nullptr), tsSesionInicio));
            partidaEnCurso = false;
            MSGPAUSA();
            break;
        }

        cout << "❌ Intentos fallidos: " << intentosFallidos
             << "   |   🔢 Números agotados: " << numerosAgotados << endl
             << endl;
        cout << "Cero (0) en cualquier momento para salir." << endl;

        int fila, columna, valor;
        IngresoStatus status = procesarIngresoUsuario(fila, columna, valor);
        switch (status) {
        case IngresoStatus::OK: {
            // 🔒 nunca escribir en celdas fijas
            if (CELDAFIJA[fila - 1][columna - 1]) {
                mostrarError("Celda fija: no se puede modificar.");
                limpiarMascara(MASCARA);
                continue;
            }

            // escribir valor
            MATRIZ[fila - 1][columna - 1] = valor;

            if (cantidadRestante(valor) == 0) {
                numerosAgotados++;
                colorTexto("rojo");
                cout << "💥 ¡Atención! El número " << valor << " ha sido agotado." << endl;
                resetColor();
                MSGPAUSA();
            }
            limpiarMascara(MASCARA);
            break;
        }
        case IngresoStatus::BACKDOOR: {
            int nivelBD = validarNivelDeAcceso();
            if (nivelBD != -1)
                subMenuBackDoor(nivelBD);
            limpiarMascara(MASCARA);
            continue;
        }
        case IngresoStatus::CANCELAR:
            limpiarMascara(MASCARA);
            continue;
        case IngresoStatus::ERROR_SALIR:
            duracionAcumulada += static_cast<long>(difftime(time(nullptr), tsSesionInicio));
            seguir = false;
            return;
        }

        // Chequeo de victoria
        for (int i = 0; i < TAM && completo; ++i) {
            for (int j = 0; j < TAM; ++j) {
                if (MATRIZ[i][j] != SOLUCION[i][j]) {
                    completo = false;
                    break;
                }
            }
        }
        if (completo) {
            colorTexto("verde");
            cout << "🎉 ¡Felicitaciones! Completaste el Sudoku." << endl;
            resetColor();

            time_t tiempoFin = time(nullptr);
            tm* fin = localtime(&tiempoFin);
            int duracion = static_cast<int>(difftime(tiempoFin, tiempoInicio));
            int minutos = duracion / 60, segundos = duracion % 60;
            char horaInicioStr[9], horaFinStr[9];
            strftime(horaInicioStr, sizeof(horaInicioStr), "%H:%M:%S", inicio);
            strftime(horaFinStr, sizeof(horaFinStr), "%H:%M:%S", fin);

            colorTexto("cyan");
            cout << "\n⏱️ Hora de inicio  : " << horaInicioStr << endl;
            cout << "⏱️ Hora de fin     : " << horaFinStr << endl;
            cout << "⏱️ Duración total  : " << minutos << " min " << segundos << " seg." << endl;
            cout << "🔢 Números agotados  : " << numerosAgotados << endl;
            cout << "❌ Intentos fallidos : " << intentosFallidos << endl;
            resetColor();

            duracionAcumulada += static_cast<long>(difftime(time(nullptr), tsSesionInicio));
            partidaEnCurso = false;

            // (scores retro)  —— sin cambios
            char inic[4];
            std::string iniciales;
            do {
                cout << "Ingresá tus 3 iniciales (A–Z, 0–9): ";
                if (!(std::cin >> iniciales))
                    return;
                if (iniciales.size() != 3)
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (iniciales.size() != 3);
            for (int k = 0; k < 3; ++k)
                inic[k] = std::toupper(static_cast<unsigned char>(iniciales[k]));
            inic[3] = '\0';

            ScoreEntry nueva;
            strncpy(nueva.iniciales, inic, 4);
            nueva.nivel = nivel;
            nueva.erroresFallidos = intentosFallidos;
            nueva.duracionSegundos = static_cast<int>(difftime(time(nullptr), tiempoInicio));
            nueva.erroresPermitidos = endGame;
            {
                time_t ahora = time(nullptr);
                tm* t = localtime(&ahora);
                strftime(nueva.timestamp, sizeof(nueva.timestamp), "%Y%m%d-%H%M%S", t);
            }
            cargarScores();
            actualizarScores(nueva);
            guardarScores();
            mostrarScores(nivel);

            MSGPAUSA();
            break;
        }
    }
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// Validaciones
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
bool validaHorizontal(int matriz[TAM][TAM], int fila, int valor) {
    for (int j = 0; j < TAM; j++) {
        if (matriz[fila][j] == valor)
            return false;
    }
    return true;
}
//---------------------------------------------------------------------------------------
bool validaVertical(int matriz[TAM][TAM], int columna, int valor) {
    for (int i = 0; i < TAM; i++) {
        if (matriz[i][columna] == valor)
            return false;
    }
    return true;
}
//---------------------------------------------------------------------------------------
bool validaRecuadro(int matriz[TAM][TAM], int fila, int columna, int valor) {
    int filaInicio = (fila / 3) * 3;
    int columnaInicio = (columna / 3) * 3;
    for (int i = filaInicio; i < filaInicio + 3; i++) {
        for (int j = columnaInicio; j < columnaInicio + 3; j++) {
            if (matriz[i][j] == valor)
                return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------------------
void fijarCeldasActuales() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (MATRIZ[i][j] != 0)
                CELDAFIJA[i][j] = true;

    mostrarError("Celdas actuales fijadas correctamente.");
}
//---------------------------------------------------------------------------------------
bool hayCeldasFijas() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (CELDAFIJA[i][j])
                return true;
    return false;
}
//---------------------------------------------------------------------------------------
bool numeroAgotadoGlobal(int numero) {
    int contador = 0;
    for (int fila = 0; fila < TAM; fila++) {
        for (int columna = 0; columna < TAM; columna++) {
            if (MATRIZ[fila][columna] == numero) {
                contador++;
                if (contador >= TAM)
                    return true;
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------------------
bool numeroPresenteEnCuadro(int fila, int columna, int numero) {
    int filaInicio = (fila / 3) * 3;
    int columnaInicio = (columna / 3) * 3;

    for (int i = filaInicio; i < filaInicio + 3; i++) {
        for (int j = columnaInicio; j < columnaInicio + 3; j++) {
            if (MATRIZ[i][j] == numero)
                return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------------------
int cantidadRestante(int numero) {
    int contador = 0;

    for (int fila = 0; fila < TAM; fila++) {
        for (int columna = 0; columna < TAM; columna++) {
            if (MATRIZ[fila][columna] == numero)
                contador++;
        }
    }

    return TAM - contador;
}
//---------------------------------------------------------------------------------------
// Menu Principal del juego
void menuPrincipal() {
    int opcion = 0;
    bool salir = false;
    // bool SODOKU_RESUELTO;
    while (!salir) {
        limpiarPantalla();
        autor();
        cout << "=========== 🕹️ MODO JUEGO ===========" << endl;
        cout << "[  1 ] Ingreso manual de datos." << endl;
        cout << "[  2 ] Modo competitivo (con niveles).              [EN TESTEO]" << endl;
        cout << "[  3 ] Limpiar tablero completo." << endl;
        cout << "[  4 ] Mejores tiempos registrados.                 [ 85% DE COMPLETADO]" << endl; // Scores
        cout << endl;
        cout << "=========== 💾 ARCHIVOS ===========" << endl;
        cout << "[  5 ] Cargar partida desde archivo." << endl;
        cout << "[  6 ] Guardar partida en archivo." << endl;
        cout << endl;
        cout << "=========== ✔️ VALIDACIONES ===========" << endl;
        cout << "[  7 ] Validar Sudoku completo.                     [ESTA DESARROLLADO, FALTA IMPLEMENTAR]" << endl;
        cout << "[  8 ] Resolver automáticamente.                    [EN TESTEO]" << endl;
        cout << endl;
        cout << "=========== 🛠️ OTROS ===========" << endl;
        cout << "[  9 ] Ver créditos del juego.                      [EN DESARROLLO]" << endl;
        cout << "[ 10 ] Fijar celdas actuales como fijas." << endl;
        cout << "[ 11 ] Configurar Game Over (intentos máximos)" << endl;
        cout << "[ " << CODIGO_BACKDOOR << " ] Ingreso a Submenu Backdoor" << endl;
        cout << "[  0 ] Salir del programa." << endl;
        cout << "=====================================" << endl;
        cout << "Seleccione una opción: ";
        std::cin >> opcion;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mostrarError("Entrada no válida.");
            continue;
        }

        switch (opcion) {
        case CODIGO_SALIR_MENU:
            salir = true;
            break;
        case 1: // "[ 1 ] Ingreso manual de datos"
            modoIngresoManual();
            break;
        case 2: // "[ 2 ] Modo competitivo (con niveles)"
            limpiarPantalla();
            if (partidaEnCurso) {
                if (SODOKU_RESUELTO == true) {
                    mostrarError("El Sudoku ya fue resuelto. No se puede reanudar.");
                    break;
                } else {
                    char resp;
                    cout << "⚠️  Hay una partida cargada. ¿Reanudarla? (s/n): ";
                    std::cin >> resp;
                    if (resp == 's' || resp == 'S') {
                        jugarPartida(nivelCargado);
                        break;
                    }
                }
            }

            // Si no reanuda, inicia flujo de nueva partida
            colorTexto("verde");
            cout << "\n🎮 MODO COMPETITIVO – NUEVA PARTIDA\n\n";
            resetColor();
            partidaEnCurso = false; // Reiniciar bandera de partida en curso
            nivelCargado = -1;      // Reiniciar nivel cargado
            iniciarJuego();         // aquí volverá a llamar a jugarPartida()
            break;

        case 3: // "[ 3 ] Limpiar tablero completo"
            if (hayCeldasFijas()) {
                colorTexto("amarillo");
                cout << "⚠️  Atención: hay celdas fijadas actualmente." << endl;
                cout << "¿Está seguro de que desea limpiar el tablero completo? (s/n): ";
                resetColor();
                char confirmacion;
                std::cin >> confirmacion;
                if (tolower(confirmacion) != 's') {
                    mostrarError("Limpieza cancelada por el usuario.");
                    break;
                }
            }
            limpiarTablero();
            limpiarMascara(MASCARA);
            for (int i = 0; i < TAM; i++)
                for (int j = 0; j < TAM; j++)
                    CELDAFIJA[i][j] = false;
            // Ver si hay que blanquear otras variables ademas de la limpieza del tablero.
            SODOKU_RESUELTO = false; // CIERRA EL SODOKU RESUELTO Y PERMITE VOLVER A ENTRAR al case 2
            cout << "Tablero y celdas fijas limpiadas correctamente." << endl;
            cout << "Opción de: Resolver automáticamente liberada, se puede jugar nuevamente." << endl;
            MSGPAUSA();
            break;
        case 4: // "[ 4 ] Mejores tiempos registrados"
            cout << "Ingreso al sistema de scores " << opcion << endl;
            // … casos 1 a 3 existentes …
            // desde aquí: mostrar mejores tiempos
            limpiarPantalla();
            autor();
            // Desplegar top 5 para cada nivel
            mostrarScores(0); // +++ FACIL +++
            mostrarScores(1); // +++ MEDIO +++
            mostrarScores(2); // +++ DIFICIL +++
            MSGPAUSA();
            break;
        case 5: // "[ 5 ] Cargar partida desde archivo"
            cargarPartidaDesdeArchivo();
            limpiarMascara(MASCARA); // Viene de "archivos.cpp" que daba error allá (se implementa aquí)
            break;
        case 6: // "[ 6 ] Guardar partida en archivo"
            guardarPartidaEnArchivo();
            break;
        case 7: // "[ 7 ] Validar Sudoku completo        [EN DESARROLLO]"
            cout << "Funcionalidad en desarrollo..." << endl;
            MSGPAUSA();
            break;
        case 8: { // "[ 8 ] Resolver automáticamente"
            // 1) Confirmación
            cout << "\n⚡ Resolver automáticamente el Sudoku.\n";
            cout << "¿Deseas continuar? (S/N): " << flush;
            char confirma;
            std::cin >> confirma;
            SODOKU_RESUELTO = true; // Variable para saber si el Sudoku fue resuelto
            confirma = toupper(static_cast<unsigned char>(confirma));
            if (confirma != 'S') {
                break; // volvemos al menú
            }

            // 2) Guardar original y copiar tablero
            int original[TAM][TAM];
            memcpy(original, MATRIZ, sizeof(original));
            int copia[TAM][TAM];
            memcpy(copia, MATRIZ, sizeof(copia));

            // 3) Backtracking en copia
            if (!resolverSudoku(copia)) {
                mostrarError("🚫 El Sudoku actual no es válido y no se puede resolver automáticamente.");
                break;
            }

            // 4) Barra de progreso basada en celdas vacías
            int vacios = 0;
            for (int i = 0; i < TAM; ++i)
                for (int j = 0; j < TAM; ++j)
                    if (original[i][j] == 0)
                        ++vacios;
            const int ancho = 20;
            int llenadas = 0;
            cout << "\nResolviendo...\n";
            for (int i = 0; i < TAM; ++i) {
                for (int j = 0; j < TAM; ++j) {
                    if (original[i][j] == 0) {
                        MATRIZ[i][j] = copia[i][j];
                        ++llenadas;
                        int pct = llenadas * 100 / vacios;
                        int barras = llenadas * ancho / vacios;
                        cout << "\r"
                             << setw(3) << pct << "% ["
                             << string(barras, '=') << '>'
                             << string(ancho - barras, ' ')
                             << "]" << flush;
#ifdef _WIN32
                        Sleep(50);
#else
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
#endif
                        // std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    }
                }
            }
            cout << "\n";

            // 5) Mostrar solución y preguntar si se guarda
            mostrarMatriz(MATRIZ, "SOLUCIÓN AUTOMÁTICA");
            cout << "¿Sobreescribir tablero actual? (S/N): " << flush;
            std::cin >> confirma;
            confirma = toupper(static_cast<unsigned char>(confirma));
            if (confirma != 'S') {
                // Restaurar original
                memcpy(MATRIZ, original, sizeof(original));
                cout << "Tablero original conservado.\n";
            } else {
                cout << "Tablero actualizado con la solución.\n";
                // 🔧 HOTFIX 1 – sincronizar solución
                memcpy(SOLUCION, copia, sizeof(copia)); // sincroniza también la solución
                SODOKU_RESUELTO = true;
            }
            MSGPAUSA();
        } break;
        case 9: // "[ 9 ] Ver créditos del juego         [EN DESARROLLO]"
            cout << "Funcionalidad en desarrollo..." << endl;
            MSGPAUSA();
            break;
        case 10: // "[ 10 ] Fijar celdas actuales como fijas"
            colorTexto("verde");
            cout << "✅ Se procede a fijar las Celdas." << endl;
            // Fijar celdas actuales
            fijarCeldasActuales();
            cout << "✅ Celdas fijadas correctamente." << endl;
            resetColor();
            break;
        case 11: // "[ 12 ] Configurar Game Over (intentos máximos)"
            configurarGameOver();
            break;
        case CODIGO_BACKDOOR: // BackDoor ver que clave se le pone
        {                     // ← inicio bloque case BackDoor
            int nivel = validarNivelDeAcceso();
            if (nivel != -1) {
                subMenuBackDoor(nivel);
            } else {
                mostrarError("Acceso denegado.");
            }
            // Al terminar el BackDoor, limpiamos y salimos del menú
            resetColor();
            salir = false; // Nos aseguramos de que no se salga del menú
            break;
        } break; // ← fin bloque case BackDoor
        default:
            mostrarError("Opción inválida.");
        }
    }
}
//---------------------------------------------------------------------------------------
IngresoStatus procesarIngresoUsuario(int& fila, int& columna, int& valor) {
    // Fila
    cout << "Ingrese la fila (1 a " << TAM << "): ";
    cin >> fila;
    if (cin.fail() || fila < 0 || fila > TAM) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        mostrarError("Fila inválida.");
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR; // no cuenta intento
    }
    if (fila == 0)
        return IngresoStatus::ERROR_SALIR;

    marcarFila(fila - 1);
    limpiarPantalla();
    autor();
    DibujarPantalla();

    // Columna
    cout << "Ingrese la columna (1 a " << TAM << "): ";
    cin >> columna;
    if (cin.fail() || columna < 0 || columna > TAM) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        mostrarError("Columna inválida.");
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR; // no cuenta intento
    }
    if (columna == 0)
        return IngresoStatus::ERROR_SALIR;

    marcarColumna(columna - 1);
    marcarInterseccion(fila - 1, columna - 1);
    limpiarPantalla();
    autor();
    DibujarPantalla();

    // Si la celda es fija, no permitir (defensa en profundidad)
    if (CELDAFIJA[fila - 1][columna - 1]) {
        mostrarError("Celda fija: no se puede modificar.");
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR; // no cuenta intento
    }

    // Si ya tiene valor, menu contextual (sin contar intentos)
    if (MATRIZ[fila - 1][columna - 1] != 0) {
        colorTexto("amarillo");
        cout << "⚠️  Atención: esa celda ya contiene un valor: "
             << MATRIZ[fila - 1][columna - 1] << endl;
        resetColor();
        cout << "[1] Modificar valor\n[2] Borrar valor (volver a '-')\n[0] Cancelar\nSeleccione una opción: ";
        int decision;
        cin >> decision;
        if (cin.fail() || decision < 0 || decision > 2) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mostrarError("Opción inválida.");
            limpiarMascara(MASCARA);
            return IngresoStatus::CANCELAR;
        }
        if (decision == 0) {
            limpiarMascara(MASCARA);
            return IngresoStatus::CANCELAR;
        }
        if (decision == 2) {
            MATRIZ[fila - 1][columna - 1] = 0;
            limpiarMascara(MASCARA);
            return IngresoStatus::CANCELAR;
        }
        // decision==1 -> seguimos
    }

    // Valor
    cout << "Ingrese valor (1-" << TAM
         << ", " << CODIGO_SALIR << " = cancelar, "
         << CODIGO_BACKDOOR << " = menú oculto): ";
    cin >> valor;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        mostrarError("Valor inválido.");
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR; // no cuenta intento
    }

    if (valor == CODIGO_BACKDOOR)
        return IngresoStatus::BACKDOOR;
    if (valor == CODIGO_SALIR)
        return IngresoStatus::CANCELAR;
    if (valor == CODIGO_SALIR_MENU)
        return IngresoStatus::ERROR_SALIR;

    if (valor < 1 || valor > TAM) {
        mostrarError("Valor fuera de rango.");
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR; // no cuenta intento
    }

    // ✅ Debe coincidir con la solucion (si disponible)
    {
        int esperado = SOLUCION[fila - 1][columna - 1];
        if (esperado != 0 && valor != esperado) {
            mostrarError("Valor incorrecto segun la solucion.");
            ++intentosFallidos; // cuenta intento (regla)
            limpiarMascara(MASCARA);
            return IngresoStatus::CANCELAR;
        }
    }

    // Reglas de Sudoku (cuentan intento)
    if (numeroAgotadoGlobal(valor)) {
        mostrarError("🚫 Número ya fue utilizado 9 veces.");
        ++intentosFallidos;
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR;
    }
    if (numeroPresenteEnCuadro(fila - 1, columna - 1, valor)) {
        mostrarError("⚠️ Ese número ya está presente en este subcuadro 3x3.");
        ++intentosFallidos;
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR;
    }

    bool hayError = false;
    if (!validaHorizontal(MATRIZ, fila - 1, valor)) {
        mostrarError("Error: El valor ya existe en esa fila.");
        hayError = true;
    }
    if (!validaVertical(MATRIZ, columna - 1, valor)) {
        mostrarError("Error: El valor ya existe en esa columna.");
        hayError = true;
    }
    if (!validaRecuadro(MATRIZ, fila - 1, columna - 1, valor)) {
        mostrarError("Error: El valor ya existe en el recuadro 3x3.");
        hayError = true;
    }
    if (hayError) {
        ++intentosFallidos;
        limpiarMascara(MASCARA);
        return IngresoStatus::CANCELAR;
    }

    return IngresoStatus::OK;
}

//---------------------------------------------------------------------------------------
// Game over
void configurarGameOver() {
    /*
    solo algo, de color, que para la versión final dejemos algunas opciones de game over tipo, 1, 2, 3, 4, 5
    y que solo pueda usarse libre tipo 9*9*9 como maximo, o algo similar desde el backdoor()
    */
    limpiarPantalla();
    autor();
    cout << "🔧 Configurar Game Over\n\n";
    cout << "Intentos fallidos maximos actuales: " << endGame << "\n";
    cout << "Ingrese nuevo valor (> 0) o 0 para cancelar: ";

    int nuevo;
    while (true) {
        if (!(cin >> nuevo)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mostrarError("Entrada no valida. Ingrese un entero.");
            cout << "Ingrese nuevo valor (> 0) o 0 para cancelar: ";
            continue;
        }

        // 0 = cancelar (si el usuario tecleo "0 0 0", el primer 0 ya cancela)
        if (nuevo == 0) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpia restos de la linea
            colorTexto("amarillo");
            cout << "Operacion cancelada. Volviendo al menu...\n";
            resetColor();
            MSGPAUSA();
            limpiarPantalla();
            return;
        }

        if (nuevo > 0)
            break;

        mostrarError("Valor invalido. Debe ser un entero positivo.");
        cout << "Ingrese nuevo valor (> 0) o 0 para cancelar: ";
    }

    endGame = nuevo;
    colorTexto("verde");
    cout << "\n✔ Ahora Game Over se activa a los " << endGame << " intentos fallidos.\n";
    resetColor();
    MSGPAUSA();
    limpiarPantalla();
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
// Fin de las funciones
//---------------------------------------------------------------------------------------
int main() {
    configurarConsola();
    resetColor();
    limpiarMascara(MASCARA);
    menuPrincipal();
    return 0;
}
