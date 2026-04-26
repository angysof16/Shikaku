#include <iostream>
#include <fstream>
#include <iomanip>
#include "tablero.h"

bool cargarTablero(const std::string &archivo, Tablero &tablero){
  std::ifstream f(archivo);
  if (!f.is_open()){
    std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
    return false;
  }

  if ((!(f >> tablero.filas >> tablero.columnas)) || tablero.filas <= 0 || tablero.columnas <= 0){
    std::cerr << "Error al leer las dimensiones del tablero o dimensiones no validas.\n";
    return false;
  }

  tablero.celdas.assign(tablero.filas, std::vector<int>(tablero.columnas, 0));
  tablero.regiones.assign(tablero.filas, std::vector<int>(tablero.columnas, -1));

  for (int i = 0; i < tablero.filas; i++){
    for (int j = 0; j < tablero.columnas; j++){
      if (!(f >> tablero.celdas[i][j])){
        std::cerr << "Error: datos insuficientes en el archivo.\n";
        return false;
      }
    }
  }

  f.close();
  return true;
}

bool mostrarTablero(const Tablero &tablero){
  if (tablero.celdas.empty()){
    std::cerr << "Error: tablero vacio.\n";
    return false;
  }

  std::cout << "   ";
  for (int j = 0; j < tablero.columnas; j++){
    std::cout << std::setw(3) << j;
  }
  std::cout << "\n";

  std::cout << "   ";
  for (int j = 0; j < tablero.columnas; j++)
    std::cout << "---";
  std::cout << "-\n";

  for (int i = 0; i < tablero.filas; i++){
    std::cout << std::setw(2) << i << " |";
    for (int j = 0; j < tablero.columnas; j++){
      int val = tablero.celdas[i][j];
      if (val == 0)
        std::cout << "  .";
      else
        std::cout << std::setw(3) << val;
    }
    std::cout << " |\n";
  }

  std::cout << "   ";
  for (int j = 0; j < tablero.columnas; j++)
    std::cout << "---";
  std::cout << "-\n";

  return true;
}

bool validarTablero(const Tablero &tablero){
  if ((tablero.filas <= 0 || tablero.columnas <= 0) || ((int)tablero.celdas.size() != tablero.filas)){
    std::cerr << "Tablero no valido para validar." << std::endl;
    return false;
  }

  int sumaArea = 0;
  int totalCeldas = tablero.filas * tablero.columnas;

  for (int i = 0; i < tablero.filas; i++){
    if ((int)tablero.celdas[i].size() != tablero.columnas)
      return false;

    for (int j = 0; j < tablero.columnas; j++){
      int valor = tablero.celdas[i][j];
      if (valor < 0)
        return false;
      if (valor > totalCeldas)
        return false;
      if (valor > 0)
        sumaArea += valor;
    }
  }

  // La suma de todas las pistas debe ser igual al total de celdas
  if (sumaArea != totalCeldas){
    std::cerr << "La suma de las pistas (" << sumaArea << ") no coincide con el total de celdas (" << totalCeldas << ").\n";
    return false;
  }

  return true;
}