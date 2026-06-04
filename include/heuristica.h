#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "tablero.h"

// intenta resolver el tablero usando backtracking con heuristica MRV
// en cada nivel elige el numero con menos rectangulos validos en el estado actual
// Devuelve true si encontro solucion
bool resolverH(Tablero &tablero);

#endif