#include "interfaz.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "\n=== SHIKAKU ===\n";

    Tablero tablero;

    if (argc >= 2) {
        if (cargarTablero(argv[1], tablero))
            std::cout << "Tablero cargado ("
                    << tablero.filas << "x" << tablero.columnas << ").\n";
        else
            return 1;
    }

    loopJuego(tablero);
    return 0;
}