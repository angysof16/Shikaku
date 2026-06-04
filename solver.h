#ifndef SOLVER_H
#define SOLVER_H

#include "tablero.h"

// intenta resolver el tablero usando backtracking
// heuristica=true ordena las pistas por numero de posibilidades
// heuristica=false usa el orden original
// Devuelve true si encontro solucion (tablero.regiones queda lleno)
bool resolver(Tablero &tablero, bool heuristica = false);

#endif