#include<iostream>
#include<limits>
#include "interfaz.h"

void mostrarMenu() {
    std::cout << "\n=== SHIKAKU ===\n";
    std::cout << "1. Cargar tablero desde archivo\n";
    std::cout << "2. Mostrar tablero\n";
    std::cout << "3. Validar tablero\n";
    std::cout << "4. Ayuda\n";
    std::cout << "0. Salir\n";
    std::cout << "Opcion: ";
}

void mostrarAyuda() {
    std::cout << "\n"
    << "  ┌─── COMANDOS ──────────────────────────────────────────┐\n"
    << "  │  c <archivo>        ->  cargar tablero desde .txt     │\n"
    << "  │  p <f> <c> <h> <w>  ->  colocar rectangulo            │\n"
    << "  │  u                  ->  deshacer ultima region        │\n"
    << "  │  l                  ->  limpiar todo el tablero       │\n"
    << "  │  v                  ->  verificar solucion            │\n"
    << "  │  m                  ->  mostrar tablero               │\n"
    << "  │  i                  ->  info de regiones              │\n"
    << "  │  h                  ->  mostrar esta ayuda            │\n"
    << "  │  q                  ->  salir                         │\n"
    << "  └───────────────────────────────────────────────────────┘\n\n";
}