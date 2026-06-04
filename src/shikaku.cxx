#include "human.h"
#include "fuerza_bruta.h"
#include "heuristica.h"
#include <iostream>
#include <string>
#include <vector>

int main( int argc, char *argv[] ){
    std::cout << "\n=== SHIKAKU ===\n";

    Tablero tablero;

    if ( argc >= 2 ) {
        if ( cargarTablero( argv[1], tablero ) ){
            std::cout << "Tablero cargado (" << tablero.filas << "x" << tablero.columnas << ").\n";
            mostrarTablero( tablero );
        }
        else {
            return 1;
        }
    }

    // si se pasa "fb" como segundo argumento, corre el solucionador de fuerza bruta
    if ( argc >= 3 && std::string( argv[2] ) == "fb" ) {
        std::cout << "Ejecutando solucionador de fuerza bruta...\n";
        if ( resolverFB ( tablero ) ){
            std::cout << "Solucion encontrada:\n";
            mostrarTablero( tablero );
            if ( validarTablero( tablero ) ){
                std::cout << "Solucion verificada correctamente\n";
            }
        } else {
            std::cout << "NO se encontro solucion\n";
        }
        return 0;
        
    }

    // si se pasa "h" como segundo argumento, corre el solucionador heuristico (MRV)
    if ( argc >= 3 && std::string( argv[2] ) == "h" ){
        std::cout << "\nEjecutando solucionador heuristico (MRV dinamico)...\n";
        if (resolverH( tablero )){
            std::cout << "Solucion encontrada:\n";
            mostrarTablero( tablero );
            if ( validarTablero( tablero ) )
                std::cout << "Solucion verificada correctamente\n";
        } else {
            std::cout << "No se encontro solucion\n";
        }
        return 0;
    }

    //FALTA DIAGRAMA DE LO QUE ÁSA EN EL JUEGO MIENTRAS EL LOOP
    loopJuego(tablero);
    return 0;
}