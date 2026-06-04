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
  tablero.rectangulos.clear();
  while (!tablero.historial.empty()) tablero.historial.pop();

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
      int val    = tablero.celdas[i][j];
      int region = tablero.regiones[i][j];
      if (val > 0)
        std::cout << std::setw(3) << val;
      else if (region >= 0)
        std::cout << "  #";
      else
        std::cout << "  .";
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

  // todas las celdas deben estar cubiertas
  for (int i = 0; i < tablero.filas; i++)
    for (int j = 0; j < tablero.columnas; j++)
      if (tablero.regiones[i][j] < 0){
        std::cerr << "Celda (" << i << "," << j << ") sin cubrir\n";
        return false;
      }

  // cada rectangulo debe tener exactamente un numero 
  // area == valor de ese numero
  for (int id = 0; id < (int)tablero.rectangulos.size(); id++){
    const Rectangulo &r = tablero.rectangulos[id];
    int area    = r.alto * r.ancho;
    int val     = 0;
    int npistas = 0;

    for (int i = r.fila; i < r.fila + r.alto; i++)
      for (int j = r.col; j < r.col + r.ancho; j++)
        if (tablero.celdas[i][j] > 0){
          val = tablero.celdas[i][j];
          npistas++;
        }

    if (npistas != 1){
      std::cerr << "Rectangulo " << id << " tiene " << npistas << " pistas (debe tener exactamente 1)\n";
      return false;
    }
    if (val != area){
      std::cerr << "Rectangulo " << id << ": pista=" << val << " pero area=" << area << "\n";
      return false;
    }
  }

  return true;
}

// rectangulo

bool colocarRectangulo(Tablero &tablero, int fila, int col, int alto, int ancho){
  // verificar limites
  if (fila < 0 || col < 0 ||
      fila + alto > tablero.filas ||
      col  + ancho > tablero.columnas){
    std::cerr << "Rectangulo fuera de los limites del tablero.\n";
    return false;
  }
  if (alto <= 0 || ancho <= 0){
    std::cerr << "El alto y ancho deben ser positivos.\n";
    return false;
  }

  // verificar que las celdas esten libres
  for (int i = fila; i < fila + alto; i++)
    for (int j = col; j < col + ancho; j++)
      if (tablero.regiones[i][j] >= 0){
        std::cerr << "Celda (" << i << "," << j << ") ya esta cubierta.\n";
        return false;
      }

  // colocar
  int id = (int)tablero.rectangulos.size();
  Rectangulo r{fila, col, alto, ancho};
  tablero.rectangulos.push_back(r);
  tablero.historial.push(r);

  for (int i = fila; i < fila + alto; i++)
    for (int j = col; j < col + ancho; j++)
      tablero.regiones[i][j] = id;

  return true;
}

bool deshacerRectangulo(Tablero &tablero){
  if (tablero.historial.empty()){
    std::cerr << "No hay acciones que deshacer.\n";
    return false;
  }

  Rectangulo r = tablero.historial.top();
  tablero.historial.pop();

  // buscar id del rectangulo en el vector
  int id = -1;
  for (int k = (int)tablero.rectangulos.size() - 1; k >= 0; k--){
    Rectangulo &rk = tablero.rectangulos[k];
    if (rk.fila == r.fila && rk.col == r.col &&
        rk.alto == r.alto && rk.ancho == r.ancho){
      id = k;
      break;
    }
  }
  if (id < 0) return false;

  tablero.rectangulos.erase(tablero.rectangulos.begin() + id);

  // reconstruir regiones desde cero
  for (auto &fila : tablero.regiones)
    for (auto &c : fila)
      c = -1;

  for (int k = 0; k < (int)tablero.rectangulos.size(); k++){
    const Rectangulo &rk = tablero.rectangulos[k];
    for (int i = rk.fila; i < rk.fila + rk.alto; i++)
      for (int j = rk.col; j < rk.col + rk.ancho; j++)
        tablero.regiones[i][j] = k;
  }

  return true;
}