#include <iostream>
#include <limits>
#include <sstream>
#include <cctype>
#include <iomanip>
#include "human.h"

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
    while ( true )
    {
        std::cout << "> ";
        if ( !std::getline( std::cin, linea ) )
            break;

        // quitar espacios al inicio
        size_t inicio = linea.find_first_not_of(' ');
        // linea vacia
        if ( inicio == std::string::npos )
            continue;
        linea = linea.substr( inicio );

        char cmd = (char)std::tolower( (unsigned char)linea[0] );
        std::istringstream args( linea.size() > 1 ? linea.substr(2) : "" );

        switch (cmd)
        {
        // CARGAR TABLERO DESDE ARCHIVO TXT
        case 'c':
        {
            std::string ruta;
            if ( !(args >> ruta) )
            {
                std::cout << "Uso: c <archivo>\n";
                break;
            }
            if ( cargarTablero(ruta, tablero) ){
                std::cout << "Tablero cargado (" << tablero.filas << "x" << tablero.columnas << ").\n";
                mostrarTablero(tablero);
            }
            break;
        }

        // CREAR RECTANGULO
        case 'p':
        {
            if ( tablero.celdas.empty() ){
                std::cout << "Carga primero un tablero con 'c <archivo>'\n";
                break;
            }
            int f, c, h, w;
            if ( !(args >> f >> c >> h >> w) )
            {
                std::cout << "Uso: p <fila> <columna> <alto> <ancho>\n";
                break;
            }
            if ( colocarRectangulo( tablero, f, c, h, w ) ){
                std::cout << "Rectangulo colocado (id=" << tablero.rectangulos.size() - 1 << ")\n";
                mostrarTablero( tablero );
            }
            break;
        }

        // DESHACER ULTIMA REGION
        case 'u':
        {
            if ( deshacerRectangulo( tablero ) ){
                std::cout << "Ultimo rectangulo deshecho.\n";
                mostrarTablero( tablero );
            }
            break;
        }

        // LIMPIAR TODO EL TABLERO
        case 'l':
        {
            for ( auto &fila : tablero.regiones )
                for ( auto &celda : fila )
                    celda = -1;
            tablero.rectangulos.clear();
            while ( !tablero.historial.empty() ) tablero.historial.pop();
            std::cout << "Tablero limpiado\n";
            mostrarTablero( tablero );
            break;
        }

        // VERIFICAR SOLUCION
        case 'v':
        {
            if ( tablero.celdas.empty() )
            {
                std::cout << "No hay tablero cargado\n";
                break;
            }
            else if ( validarTablero(tablero) )
            {
                std::cout << "Solucion correcta!\n";
            }
            else
            {
                std::cout << "El tablero no es valido\n";
            }
            break;
        }

        // MOSTRAR TABLERO
        case 'm':
        {
            if ( tablero.celdas.empty() )
                std::cout << "No hay tablero cargado\n";
            else
                mostrarTablero(tablero);
            break;
        }

        // INFO DE REGIONES
        case 'i':
        {
            if ( tablero.rectangulos.empty() ){
                std::cout << "No hay rectangulos colocados aun\n";
                break;
            }
            std::cout << "\n  ID  Fila  Col  Alto  Ancho  Area  Numero\n";
            std::cout <<   "  --  ----  ---  ----  -----  ----  ------\n";
            for ( int k = 0; k < (int)tablero.rectangulos.size(); k++ ){
                const Rectangulo &r = tablero.rectangulos[k];
                int area = r.alto * r.ancho;
                int val  = 0;
                for ( int i = r.fila; i < r.fila + r.alto; i++ )
                    for ( int j = r.col; j < r.col + r.ancho; j++ )
                        if ( tablero.celdas[i][j] > 0 )
                            val = tablero.celdas[i][j];
                std::cout << "  " << std::setw(2) << k
                        << "  " << std::setw(4) << r.fila
                        << "  " << std::setw(3) << r.col
                        << "  " << std::setw(4) << r.alto
                        << "  " << std::setw(5) << r.ancho
                        << "  " << std::setw(4) << area
                        << "  " << std::setw(6) << (val ? std::to_string(val) : "?")
                        << "\n";
            }
            std::cout << "\n";
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
            std::cout << "Comando incorrecto. Usa 'h' para ver la ayuda\n";
        }
        }
    }
}