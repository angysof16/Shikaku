#include<iostream>
#include<fstream>

#include "interfaz.h"
#include "tablero.h"

int main(int argc, char* argv[]) {
    Tablero tablero;
    int opcion;

    do {
        mostrarMenu();
        std::cin >> opcion;
        ejecutarOpcion(opcion, tablero);
    } while (opcion != 0);

    return 0;
}