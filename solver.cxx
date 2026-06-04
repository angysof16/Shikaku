/*
SHIKAKU ES NP COMPLETO - https://arxiv.org/pdf/2202.09788

tengo un tablero W x H
el tablero puede tener valores enteros positivos v
la suma de los valores v debe ser el área de la matriz, es decir, W x H

ENTRADAS :
- W (numero natural) -> ancho del tablero FILAS
- H (numero natural) -> alto del tablero COLUMNAS
- MATRIZ de W x H donde cada celda sin numero vale 0,
  de lo contrario, vale un entero positivo v

SALIDAS :
una solucion o decision

CONDICIONES :
val = W x H
un rectángulo R no puede contener más de un numero val, o encontrarse con otro rectángulo


Un algoritmo de fuerza bruta puede ser:
- ordeno los numeros de mayor a menor, y empizo con el primer numero NO ASIGNADO
- busco todos los rectangulos posibles con esa area.
- si hay rectangulos asignados alrededor y no chocan entre si, puedo asignar el rectangulo

continúo con el siguiente numero no asignado

*/

#include <iostream>
#include <algorithm>
#include "tablero.h"
#include <vector>

// Estructura para representar una pista
struct Pista {
    int fila;
    int col;
    int val;
};


// dada una pista en (pf, pc) con valor val, genera todos los rectangulos posibles
// que la contienen, caben en el tablero, y no encierran otra pista
std::vector<Rectangulo> generarPosibilidades(const Tablero &tablero, int pf, int pc, int val){
    std::vector<Rectangulo> posibilidades;

    int H = tablero.filas;
    int W = tablero.columnas;

    for (int alto = 1; alto <= val; alto++){
        if (val % alto != 0) continue;
        int ancho = val / alto;
        if (ancho > W) continue;

        int fila_min = std::max(0, pf - alto + 1);
        int fila_max = std::min(H - alto, pf);
        int col_min  = std::max(0, pc - ancho + 1);
        int col_max  = std::min(W - ancho, pc);

        for (int fila = fila_min; fila <= fila_max; fila++){
            for (int col = col_min; col <= col_max; col++){
                bool otraPista = false;
                for (int i = fila; i < fila + alto; i++){
                    for (int j = col; j < col + ancho; j++){
                        if (tablero.celdas[i][j] > 0 && !(i == pf && j == pc)){
                            otraPista = true;
                        }
                    }
                }
                if (!otraPista){
                    posibilidades.push_back({fila, col, alto, ancho});
                }
            }
        }
    }

    return posibilidades;
}

// verificar que el rectangulo R no solape con ninguna region ya asignada en tablero.regiones
bool esValido(const Tablero &tablero, const Rectangulo &R){
    for (int i = R.fila; i < R.fila + R.alto; i++){
        for (int j = R.col; j < R.col + R.ancho; j++){
            if (tablero.regiones[i][j] >= 0){
                return false;
            }
        }
    }
    return true;
}

// asignar el id del rectangulo a las celdas que cubre
void marcar(Tablero &tablero, const Rectangulo &R, int id){
    for (int i = R.fila; i < R.fila + R.alto; i++)
        for (int j = R.col; j < R.col + R.ancho; j++)
            tablero.regiones[i][j] = id;
}

// ------------------------------------------------------------
// Desmarcar: libera las celdas del rectangulo (backtracking)
// ------------------------------------------------------------
void desmarcar(Tablero &tablero, const Rectangulo &R){
    for (int i = R.fila; i < R.fila + R.alto; i++)
        for (int j = R.col; j < R.col + R.ancho; j++)
            tablero.regiones[i][j] = -1;
}

// ------------------------------------------------------------
// BacktrackingFB: intenta asignar un rectangulo a cada pista
// siguiendo el Algoritmo 2 del documento (fuerza bruta).
// ------------------------------------------------------------
bool backtrackingFB(Tablero &tablero,
                    const std::vector<Pista> &pistas,
                    std::vector< std::vector<Rectangulo> > &posibilidades,
                    int idx){
    if (idx == (int)pistas.size())
        return true;

    for (Rectangulo &R : posibilidades[idx]){
        if (esValido(tablero, R)){
            int id = (int)tablero.rectangulos.size();
            tablero.rectangulos.push_back(R);
            marcar(tablero, R, id);

            if (backtrackingFB(tablero, pistas, posibilidades, idx + 1))
                return true;

            // backtrack
            tablero.rectangulos.pop_back();
            desmarcar(tablero, R);
        }
    }
    return false;
}

// ------------------------------------------------------------
// resolver: punto de entrada del solucionador.
// Implementa Principal_FB (Algoritmo 2) o Principal_H (Algoritmo 3)
// segun el parametro heuristica.
// ------------------------------------------------------------
bool resolver(Tablero &tablero, bool heuristica){
    // limpiar estado previo
    for (auto &fila : tablero.regiones)
        for (auto &c : fila)
            c = -1;
    tablero.rectangulos.clear();
    while (!tablero.historial.empty()) tablero.historial.pop();

    // pistas <- todas las (r, c) donde tablero.celdas[r][c] > 0
    std::vector<Pista> pistas;
    for (int i = 0; i < tablero.filas; i++)
        for (int j = 0; j < tablero.columnas; j++)
            if (tablero.celdas[i][j] > 0)
                pistas.push_back({i, j, tablero.celdas[i][j]});

    if (pistas.empty()) return false;

    // para cada pista, generar sus posibilidades
    std::vector< std::vector<Rectangulo> > posibilidades(pistas.size());
    for (int k = 0; k < (int)pistas.size(); k++)
        posibilidades[k] = generarPosibilidades(tablero, pistas[k].fila, pistas[k].col, pistas[k].val);

    // heuristica: ordenar pistas de menor a mayor numero de posibilidades
    if (heuristica){
        std::vector<int> orden(pistas.size());
        for (int i = 0; i < (int)orden.size(); i++) orden[i] = i;

        for (int i = 0; i < (int)orden.size() - 1; i++)
            for (int j = i + 1; j < (int)orden.size(); j++)
                if (posibilidades[orden[i]].size() > posibilidades[orden[j]].size())
                    std::swap(orden[i], orden[j]);

        std::vector<Pista> pistasOrdenadas;
        std::vector< std::vector<Rectangulo> > posibilidadesOrdenadas;
        for (int i : orden){
            pistasOrdenadas.push_back(pistas[i]);
            posibilidadesOrdenadas.push_back(posibilidades[i]);
        }
        pistas         = pistasOrdenadas;
        posibilidades  = posibilidadesOrdenadas;
    }

    return backtrackingFB(tablero, pistas, posibilidades, 0);
}