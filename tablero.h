#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>

struct Tablero {
  int filas;
  int columnas;
  std::vector< std::vector<int> > celdas;
  std::vector< std::vector<int> > regiones;
};

struct Rectangulo {
  int fila_inicio;
  int fila_fin;
  int columna_inicio;
  int columna_fin;
};

// tablero
bool cargarTablero(const std::string &archivo, Tablero &tablero);
bool mostrarTablero(const Tablero &tablero);
bool validarTablero(const Tablero &tablero);

// rectangulo


#endif