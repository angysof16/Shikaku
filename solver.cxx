/*
SHIKAKU ES NP COMPLETO
https://arxiv.org/pdf/2202.09788

tengo un tablero W x H
el tablero puede tener valores enteros positivos v
la suma de los valores v debe ser el área de la matriz, es decir, W x H


ENTRADAS :
- W (numero natural) -> ancho del tablero FILAS
- H (numero natural) -> alto del tablero COLUMNAS
- MATRIZ de W x H donde cada celda sin numero vale 0,
  de lo contrario, vale un entero positivo v

SALIDAS :
una solucion
una matriz?

CONDICIONES :
v = W x H
un rectángulo R no puede contener más de un numero v, o encontrarse con otro rectángulo



Un algoritmo de fuerza bruta puede ser:

ordeno los numeros de mayor a menor, y empizo con el primer numero NO ASIGNADO

busco todos los rectangulos posibles con esa area.
si hay rectangulos asignados alrededor y no chocan entre si, puedo asignar el rectangulo

continúo con el siguiente numero no asignado


BACKTRACKING 

por que fuerza bruta?



*/



#include <iostream>
#include "tablero.h"
#include <vector>

int main() {
    //ancho y alto temporal
    int W, H, val;
    std::vector<int> posibilidades;

    for (int H = 1; H <= val; ++H) {
        if (val % H != 0) continue;
        int ancho = val / H;
        if (ancho > W) continue;
    }
}