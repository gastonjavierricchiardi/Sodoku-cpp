// Archivos.cpp = v:0.9.4
#include <algorithm>
#include <climits> // para INT_MAX (VER SI MOVERLO)
#include <cstring> // para strncpy, strlen
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>  // sacarlo o moverlo del excel
#include <iostream> // sacarlo
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Dependencias de archivos separados:
#include "Sodoku.h"
#include "archivos.h"
#include "backdoor.h"
#include "constantes.h" // para FECHA_VERSION, HORA_VERSION, VERSION
#include "pantalla.h"   // Lo dejo porlas.
#include "varios.h"     // usa mostrarError() o colorTexto()
// ─── Sistema de Score Retro v0.9 ───
// Nombre del archivo de puntuaciones ESTA EN CONSTANTES.H
ScoreEntry scores[3][5];

#ifdef _WIN32
#include <cstdlib>
#endif

// Funciones de color y mensajes
void mostrarError(string mensaje) {
    colorTexto("rojo");
    cout << mensaje << endl;
    resetColor();
    MSGPAUSA();
}
// Generación de nombre de archivo basado en fecha y hora actual con segundos:
string generarNombreArchivo() {
    time_t ahora = time(0);
    tm* tiempo = localtime(&ahora);

    ostringstream nombre;
    nombre << (tiempo->tm_year + 1900)
           << setw(2) << setfill('0') << tiempo->tm_mon + 1
           << setw(2) << setfill('0') << tiempo->tm_mday
           << "-"
           << setw(2) << setfill('0') << tiempo->tm_hour
           << setw(2) << setfill('0') << tiempo->tm_min
           << setw(2) << setfill('0') << tiempo->tm_sec
           << ".txt";

    return nombre.str();
}

// Listar archivos guardados en orden cronológico (por nombre)
vector<string> listarArchivosGuardados() {
    vector<string> archivos;
    string patron = "2025"; // Cambiar si en el futuro el año cambia

    namespace fs = std::filesystem;

    for (const auto& entrada : fs::directory_iterator(".")) {
        string nombre = entrada.path().filename().string();
        if (nombre.find(patron) == 0 && nombre.size() > 4 && nombre.substr(nombre.size() - 4) == ".txt") {
            archivos.push_back(nombre);
        }
    }

    // Ordenar alfabéticamente = orden cronológico por el patrón de nombre
    std::sort(archivos.begin(), archivos.end());

    return archivos;
}

// Guardar partida en archivo
void guardarPartidaEnArchivo() {
    string nombreArchivo = generarNombreArchivo();
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        mostrarError("No se pudo crear el archivo para guardar la partida.");
        return;
    }

    // 1) Guardar la dificultad para reanudar la partida
    // archivo << "Nivel:" << nivelCargado << '\n';
    // Ahora guardamos 1=Fácil, 2=Medio, 3=Difícil
    archivo << "Nivel:" << (nivelCargado + 1) << '\n';

    // 2) Guardar MATRIZ (sin encabezado)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            archivo << MATRIZ[i][j] << " ";
        }
        archivo << endl;
    }

    // 3) Guardar CELDAFIJA (sin encabezado)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            archivo << (CELDAFIJA[i][j] ? "1" : "0") << " ";
        }
        archivo << endl;
    }

    archivo.close();

    // 4) Guardar datos internos: SOLUCION + INTENTOS + VICTORIA + INICIO + DURACION_S
    {
        ofstream extras(nombreArchivo, ios::app);
        if (!extras.is_open()) {
            mostrarError("No se pudo abrir el archivo para guardar extras.");
            return;
        }

        extras << "// ---- DATOS INTERNOS ----\n";

        // (a) SOLUCION — 9 filas primero (LO QUE TU LOADER ESPERA)
        for (int i = 0; i < TAM; ++i) {
            for (int j = 0; j < TAM; ++j)
                extras << SOLUCION[i][j] << ' ';
            extras << '\n';
        }

        // (b) INTENTOS
        extras << "INTENTOS: " << intentosFallidos << '\n';

        // (c) VICTORIA
        extras << "VICTORIA: " << (SODOKU_RESUELTO ? 1 : 0) << '\n';

        // (d) INICIO y DURACION_S (después de SOLUCION/INTENTOS/VICTORIA)
        std::time_t t = std::time(nullptr);
        std::tm* tm = std::localtime(&t);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", tm);
        extras << "INICIO: " << buf << '\n';
        extras << "DURACION_S: 0\n";

        extras.close();
    }

    /*
    // 4) Guardar datos internos: solución + intentos fallidos
    ofstream extras(nombreArchivo, ios::app);
    if (extras.is_open()) {
        extras << "// ---- DATOS INTERNOS ----\n";

            //////////////////////////////////////////////////////////////

            // Timestamp de inicio (formato YYYYMMDD-HHMMSS) y duracion placeholder
            std::time_t t = std::time(nullptr);
            std::tm* tm = std::localtime(&t);
            char buf[20];
            std::strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", tm);

            extras << "INICIO: " << buf << '\n';
            extras << "DURACION_S: 0\n";

            //////////////////////////////////////////////////////////////

            for (int i = 0; i < TAM; i++) {
                for (int j = 0; j < TAM; j++) {
                    extras << SOLUCION[i][j] << " ";
                }
                extras << '\n';
            }

            extras << "INTENTOS: " << intentosFallidos << '\n';
            extras.close();
        }

        */
    colorTexto("verde");
    cout << "💾 Partida guardada correctamente en: " << nombreArchivo << endl;
    resetColor();
    MSGPAUSA();
}

// Carga de partida desde archivo (con soporte para reanudar nivel guardado)
void cargarPartidaDesdeArchivo() {
    std::string linea;
    std::vector<std::string> archivos = listarArchivosGuardados();

    if (archivos.empty()) {
        mostrarError("No hay archivos de partida disponibles.");
        return;
    }

    std::cout << "Archivos disponibles para cargar:\n";
    for (size_t i = 0; i < archivos.size(); ++i) {
        std::cout << "[" << i + 1 << "] " << archivos[i] << '\n';
    }

    int seleccion;
    std::cout << "Seleccione el numero de archivo a cargar (0 o " << CODIGO_SALIR << " para cancelar): ";
    std::cin >> seleccion;

    if (seleccion == 0 || seleccion == CODIGO_SALIR)
        return;
    if (seleccion < 1 || seleccion > (int)archivos.size()) {
        mostrarError("Seleccion invalida.");
        return;
    }

    std::ifstream archivo(archivos[seleccion - 1]);
    if (!archivo.is_open()) {
        mostrarError("No se pudo abrir el archivo.");
        return;
    }

    // 1) Leer linea de dificultad: "Nivel:X" (1=Facil,2=Medio,3=Dificil)
    if (!std::getline(archivo, linea) || linea.rfind("Nivel:", 0) != 0) {
        mostrarError("Archivo de partida invalido. No se encontro Nivel.");
        return;
    }

    int nivelLeido;
    try {
        nivelLeido = std::stoi(linea.substr(6));
    } catch (...) {
        mostrarError("Nivel invalido en el archivo de partida.");
        return;
    }
    if (nivelLeido < 0 || nivelLeido > 3) {
        mostrarError("Nivel fuera de rango en partida guardada.");
        return;
    }
    partidaEnCurso = true;
    // 0 (libre) queda 0; 1..3 -> 0..2
    nivelCargado = (nivelLeido > 0 ? nivelLeido - 1 : 0);

    // 2) Leer MATRIZ (9 filas)
    int matrizTemporal[TAM][TAM];
    int fila = 0;
    while (fila < TAM && std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        int valor;
        std::vector<int> filaValores;
        while (ss >> valor) {
            if (valor < 0 || valor > TAM) {
                mostrarError("Valor fuera de rango en MATRIZ.");
                return;
            }
            filaValores.push_back(valor);
        }
        if ((int)filaValores.size() != TAM) {
            mostrarError("Formato incorrecto en fila de MATRIZ.");
            return;
        }
        for (int col = 0; col < TAM; ++col)
            matrizTemporal[fila][col] = filaValores[col];
        ++fila;
    }
    if (fila != TAM) {
        mostrarError("Faltan filas para MATRIZ.");
        return;
    }

    // 3) Leer CELDAFIJA (9 filas)
    bool fijaTemporal[TAM][TAM];
    fila = 0;
    while (fila < TAM && std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        int valor;
        std::vector<int> filaValores;
        while (ss >> valor) {
            if (valor != 0 && valor != 1) {
                mostrarError("CELDAFIJA debe ser 0 o 1.");
                return;
            }
            filaValores.push_back(valor);
        }
        if ((int)filaValores.size() != TAM) {
            mostrarError("Formato incorrecto en fila de CELDAFIJA.");
            return;
        }
        for (int col = 0; col < TAM; ++col)
            fijaTemporal[fila][col] = (filaValores[col] == 1);
        ++fila;
    }
    if (fila != TAM) {
        mostrarError("Faltan filas para CELDAFIJA.");
        return;
    }

    // 4) Validacion logica basica
    if (!sudokuValido(matrizTemporal)) {
        mostrarError("Errores logicos detectados. No se cargo.");
        return;
    }

    // 5) Copiar a estructuras reales
    for (int f = 0; f < TAM; ++f) {
        for (int c = 0; c < TAM; ++c) {
            MATRIZ[f][c] = matrizTemporal[f][c];
            CELDAFIJA[f][c] = fijaTemporal[f][c];
        }
    }

    // 6) Bloque opcional: // ---- DATOS INTERNOS ----
    if (std::getline(archivo, linea) && linea.rfind("// ---- DATOS INTERNOS", 0) == 0) {
        // 6.a) SOLUCION (9 filas)
        fila = 0;
        while (fila < TAM && std::getline(archivo, linea)) {
            std::istringstream ss(linea);
            int valor;
            std::vector<int> filaValores;
            while (ss >> valor)
                filaValores.push_back(valor);
            if ((int)filaValores.size() != TAM) {
                mostrarError("Formato incorrecto en fila de SOLUCION.");
                return;
            }
            for (int col = 0; col < TAM; ++col)
                SOLUCION[fila][col] = filaValores[col];
            ++fila;
        }

        // 6.b) INTENTOS
        if (std::getline(archivo, linea) && linea.rfind("INTENTOS:", 0) == 0) {
            try {
                intentosFallidos = std::stoi(linea.substr(9));
            } catch (...) {
                intentosFallidos = 0;
            }
        } else {
            intentosFallidos = 0;
        }

        // 6.c) Autodeteccion: completa y coincide con SOLUCION
        bool sinCeros = true;
        for (int i = 0; i < TAM && sinCeros; ++i)
            for (int j = 0; j < TAM; ++j)
                if (MATRIZ[i][j] == 0) {
                    sinCeros = false;
                    break;
                }

        bool coincideSol = true;
        for (int i = 0; i < TAM && coincideSol; ++i)
            for (int j = 0; j < TAM; ++j)
                if (MATRIZ[i][j] != SOLUCION[i][j]) {
                    coincideSol = false;
                    break;
                }

        if (sinCeros && coincideSol) {
            partidaEnCurso = false;
            colorTexto("verde");
            std::cout << "🟢 Juego terminado (partida ya resuelta al cargar)." << std::endl;
            resetColor();
            MSGPAUSA();
            return;
        }

        // 6.d) VICTORIA (opcional). Si no esta, NO consumimos la linea siguiente.
        std::streampos posAntesVictoria = archivo.tellg();
        if (std::getline(archivo, linea) && linea.rfind("VICTORIA:", 0) == 0) {
            int v = 0;
            try {
                v = std::stoi(linea.substr(9));
            } catch (...) {
                v = 0;
            }
            SODOKU_RESUELTO = (v != 0);
        } else {
            SODOKU_RESUELTO = false;
            if (archivo.good()) {
                archivo.clear();
                archivo.seekg(posAntesVictoria);
            }
        }

        // ✅ reanudacion confirmada
        esPartidaNueva = false; // <-- NUEVO

        // Banner de estado
        colorTexto("amarillo");
        std::cout << "📂 Partida reanudada en nivel "
                  << (nivelLeido == 0 ? "LIBRE"
                                      : (nivelCargado == 0 ? "FACIL" : (nivelCargado == 1 ? "MEDIO" : "DIFICIL")))
                  << " (" << nivelLeido << "). ";
        std::cout << "✅ Estadisticas cargadas." << std::endl;
        resetColor();
        MSGPAUSA();
    } else {
        // Sin bloque interno: inicializar por defecto
        for (int i = 0; i < TAM; ++i)
            for (int j = 0; j < TAM; ++j)
                SOLUCION[i][j] = 0;
        intentosFallidos = 0;
        SODOKU_RESUELTO = false;

        // ✅ reanudacion confirmada (sin datos internos)
        esPartidaNueva = false; // <-- NUEVO
    }

    // La llamada a jugarPartida() se maneja en el menu principal
}

// Función auxiliar para validar lógicamente una matriz Sudoku
bool sudokuValido(int matriz[TAM][TAM]) {
    // Validar filas
    for (int fila = 0; fila < TAM; fila++) {
        bool vistos[10] = {false};
        for (int col = 0; col < TAM; col++) {
            int val = matriz[fila][col];
            if (val == 0)
                continue;
            if (vistos[val])
                return false;
            vistos[val] = true;
        }
    }

    // Validar columnas
    for (int col = 0; col < TAM; col++) {
        bool vistos[10] = {false};
        for (int fila = 0; fila < TAM; fila++) {
            int val = matriz[fila][col];
            if (val == 0)
                continue;
            if (vistos[val])
                return false;
            vistos[val] = true;
        }
    }

    // Validar subcuadros 3x3
    for (int baseFila = 0; baseFila < TAM; baseFila += 3) {
        for (int baseCol = 0; baseCol < TAM; baseCol += 3) {
            bool vistos[10] = {false};
            for (int f = 0; f < 3; f++) {
                for (int c = 0; c < 3; c++) {
                    int val = matriz[baseFila + f][baseCol + c];
                    if (val == 0)
                        continue;
                    if (vistos[val])
                        return false;
                    vistos[val] = true;
                }
            }
        }
    }

    // Si pasó todo, es válido
    return true;
}

void exportarMatrizACSV() {
    // Generar nombre con fecha y hora
    time_t ahora = time(0);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "matriz_%Y%m%d-%H%M%S.csv", localtime(&ahora));
    string nombreArchivo = buffer;

    // Crear archivo CSV
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        mostrarError("No se pudo crear el archivo CSV.");
        return;
    }

    // Exportar datos de MATRIZ
    for (int fila = 0; fila < TAM; fila++) {
        for (int col = 0; col < TAM; col++) {
            archivo << MATRIZ[fila][col];
            if (col < 8)
                archivo << ",";
        }
        archivo << "\n";
    }

    archivo.close();

    // Confirmación visual
    colorTexto("verde");
    cout << "\n✅ MATRIZ exportada correctamente a '" << nombreArchivo << "'.\n";
    resetColor();
    MSGPAUSA();
}

// ----------------------------------------------------------------
// Carga los scores desde ARCHIVO_SCORES y los ordena en 'scores'
// ----------------------------------------------------------------
void cargarScores() {
    // 0) Asegurar existencia del archivo
    if (!std::filesystem::exists(ARCHIVO_SCORES)) {
        std::ofstream f(ARCHIVO_SCORES);
        f.close();
    }

    // 1) Inicializar con entradas “vacías” (errores y tiempos muy altos)
    for (int lvl = 0; lvl < 3; ++lvl) {
        for (int i = 0; i < 5; ++i) {
            scores[lvl][i] = ScoreEntry{
                "---",            // iniciales
                lvl,              // nivel
                INT_MAX,          // erroresFallidos
                INT_MAX,          // duracionSegundos
                endGame,          // erroresPermitidos
                "00000000-000000" // timestamp
            };
        }
    }

    // 2) Leer y parsear cada línea del archivo
    std::ifstream f(ARCHIVO_SCORES);
    if (!f.is_open())
        return;

    std::string linea;
    while (std::getline(f, linea)) {
        if (linea.empty())
            continue;
        // 2.1) Ignorar encabezados de nivel (comienzan con "+++")
        if (linea.rfind("+++", 0) == 0)
            continue;

        // 2.2) Leer los 6 campos separados por espacios
        std::istringstream iss(linea);
        std::string iniStr, timestamp;
        int lvl, erroresFall, durSeg, erroresPermit;
        if (!(iss >> iniStr >> lvl >> erroresFall >> durSeg >> erroresPermit >> timestamp)) {
            // línea mal formateada
            continue;
        }

        // 3) Mapear a ScoreEntry
        ScoreEntry e;
        // Iniciales (hasta 3 caracteres)
        for (int k = 0; k < 3; ++k)
            e.iniciales[k] = (k < (int)iniStr.size() ? toupper(iniStr[k]) : ' ');
        e.iniciales[3] = '\0';

        e.nivel = lvl;
        e.erroresFallidos = erroresFall;
        e.duracionSegundos = durSeg;
        e.erroresPermitidos = erroresPermit; // el nuevo campo

        // Timestamp
        std::strncpy(e.timestamp, timestamp.c_str(), sizeof(e.timestamp));
        e.timestamp[sizeof(e.timestamp) - 1] = '\0';

        // 4) Insertar en la matriz ordenada
        actualizarScores(e);
    }
}

// ----------------------------------------------------------------
// Inserta una nueva entrada en 'scores', manteniendo orden y top 5
// ----------------------------------------------------------------
void actualizarScores(const ScoreEntry& entrada) {
    int lvl = entrada.nivel;
    for (int i = 0; i < 5; ++i) {
        // Encuentra la posición donde entra la nueva entrada
        if (entrada.erroresFallidos < scores[lvl][i].erroresFallidos ||
            (entrada.erroresFallidos == scores[lvl][i].erroresFallidos &&
             entrada.duracionSegundos < scores[lvl][i].duracionSegundos)) {
            // Desplaza todos los elementos desde el final hasta i
            for (int j = 4; j > i; --j) {
                scores[lvl][j] = scores[lvl][j - 1];
            }
            // Inserta la nueva entrada en la posición i
            scores[lvl][i] = entrada;
            break;
        }
    }
}

// ----------------------------------------------------------------
// Guarda la matriz 'scores' en ARCHIVO_SCORES
// ----------------------------------------------------------------
void guardarScores() {
    std::ofstream f(ARCHIVO_SCORES);
    if (!f.is_open()) {
        mostrarError("No se pudo abrir el archivo de scores.");
        return;
    }

    // Para cada nivel, de 0 a 2
    for (int lvl = 0; lvl < 3; ++lvl) {
        // Decoración de nivel
        const char* nivelStr = (lvl == 0   ? "+++ FACIL +++"
                                : lvl == 1 ? "+++ MEDIO +++"
                                           : "+++ DIFICIL +++");
        f << nivelStr << '\n';

        // Entradas del ranking
        for (int i = 0; i < 5; ++i) {
            const ScoreEntry& e = scores[lvl][i];
            // Línea: iniciales - nivel - erroresFallidos - duracionSegundos - erroresPermitidos - timestamp
            f << e.iniciales << ' '
              << e.nivel << ' '
              << e.erroresFallidos << ' '
              << e.duracionSegundos << ' '
              << e.erroresPermitidos << ' '
              << e.timestamp << '\n';
        }
    }

    f.close();
}

// ----------------------------------------------------------------
// Resetea los 5 mejores scores por nivel y sobrescribe el archivo
// ----------------------------------------------------------------
void resetScores() {
    for (int lvl = 0; lvl < 3; ++lvl) {
        for (int i = 0; i < 5; ++i) {

            scores[lvl][i] = ScoreEntry{
                "---",            // iniciales
                lvl,              // nivel
                INT_MAX,          // erroresFallidos
                INT_MAX,          // duracionSegundos
                endGame,          // erroresPermitidos   ← ahora lo incluimos
                "00000000-000000" // timestamp
            };
        }
    }
    guardarScores();
}
