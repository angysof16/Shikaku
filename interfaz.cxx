#include <iostream>
#include <limits>
#include <sstream>
#include <cctype>
#include "interfaz.h"

void mostrarAyuda()
{
    std::cout << "\n"
              << "  ┌─── COMANDOS ──────────────────────────────────────────┐\n"
              << "  │  c <archivo>        ->  cargar tablero desde .txt     │\n"
              << "  │  p <f> <c> <h> <w>  ->  crear rectangulo              │\n"
              << "  │  u                  ->  deshacer ultima region        │\n"
              << "  │  l                  ->  limpiar todo el tablero       │\n"
              << "  │  v                  ->  verificar solucion            │\n"
              << "  │  m                  ->  mostrar tablero               │\n"
              << "  │  i                  ->  info de regiones              │\n"
              << "  │  h                  ->  mostrar esta ayuda            │\n"
              << "  │  q                  ->  salir                         │\n"
              << "  └───────────────────────────────────────────────────────┘\n\n";
}

void loopJuego(Tablero &tablero)
{
    mostrarAyuda();

    std::string linea;
    while (true)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, linea))
            break;

        // quitar especios al inicio
        size_t inicio = linea.find_first_not_of(' ');
        // linea vacia
        if (inicio == std::string::npos)
            continue;
        linea = linea.substr(inicio);

        char cmd = (char)std::tolower((unsigned char)linea[0]);
        std::istringstream args(linea.size() > 1 ? linea.substr(2) : "");

        switch (cmd)
        {
        // CARGAR TABLERO DESDE ARCHIVO TXT
        case 'c':
        {
            std::string ruta;
            if (!(args >> ruta))
            {
                std::cout << "Uso: c <archivo>\n";
                break;
            }
            if (cargarTablero(ruta, tablero))
                std::cout << "Tablero cargado (" << tablero.filas << "x" << tablero.columnas << ").\n";
        }
        // CREAR RECTANGULO
        case 'p':
        {
            int f, c, h, w;
            if (!(args >> f >> c >> h >> w))
            {
                std::cout << "Uso: p <fila> <columna> <alto> <ancho>\n";
                break;
            }

            std::cout << "  [p] fila=" << f << " col=" << c << " alto=" << h << " ancho=" << w << " (FAlta implementar)\n";
            break;
        }

        // DESHACER ULTIMA REGION
        case 'u':
        {
            std::cout << "  [u] deshacer ultima region (pendiente implementar)\n";
            break;
        }

        // LIMPIAR TODO EL TABLERO
        case 'l':
        {
            for (auto &fila : tablero.regiones)
                for (auto &celda : fila)
                    celda = -1;
            std::cout << "Tablero limpiado.\n";
            break;
        }

        // VERIFICAR SOLUCION
        case 'v':
        {
            if (tablero.celdas.empty())
            {
                std::cout << "No hay tablero cargado.\n";
                break;
            }
            else if (validarTablero(tablero))
            {
                std::cout << "El tablero es valido.\n";
            }
            else
            {
                std::cout << "El tablero no es valido.\n";
            }
        }

        // MOSTRAR TABLERO
        case 'm':
        {
            mostrarTablero(tablero);
            break;
        }

        // INFO DE REGIONES
        case 'i':
        {
            std::cout << "  [i] info de regiones (pendiente implementar)\n";
            break;
        }

        // MOSTRAR AYUDA
        case 'h':
        {
            mostrarAyuda();
            break;
        }

        // SALIR
        case 'q':
        {
            std::cout << "Saliendo del juego...\n";
            return;
        }

        default:
        {
            std::cout << "Comando incorrecto. Usa 'h' para ver la ayuda.\n";
        }
        }
        }
    }
