#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include <stack>

struct Tablero {
  int filas;
  int columnas;
  std::vector< std::vector<int> > celdas;
  std::vector< std::vector<int> > regiones;

  // rectangulos colocados
  std::vector<struct Rectangulo> rectangulos;
  // para deshacer (u)
  std::stack<struct Rectangulo>  historial;
};

struct Rectangulo {
  int fila;
  int col;
  int alto;
  int ancho;
};

// tablero
bool cargarTablero(const std::string &archivo, Tablero &tablero);
bool mostrarTablero(const Tablero &tablero);
bool validarTablero(const Tablero &tablero);

// rectangulo
bool colocarRectangulo(Tablero &tablero, int fila, int col, int alto, int ancho);
bool deshacerRectangulo(Tablero &tablero);

#endif