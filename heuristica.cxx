#include <iostream>
#include <vector>
#include <algorithm>
#include "tablero.h"
#include "heuristica.h"

// numero naturakl con el área del rectángulo
struct NumeroH{
    int fila;
    int col;
    int val;
};

// dado un numero en (pf, pc) con valor val, devuelve todos los rectángulos posibles
static std::vector< Rectangulo > generarValidos(const Tablero &tablero, int pf, int pc, int val ){
    std::vector<Rectangulo> validos;

    int H = tablero.filas;
    int W = tablero.columnas;

    for ( int alto = 1; alto <= val; alto++ ){
        if( val % alto != 0 ) continue;

        int ancho = val / alto;
        if ( ancho > W ) continue;

        int fila_min = std::max( 0, pf - alto + 1 );
        int fila_max = std::min( H - alto, pf );
        int col_min = std::max( 0, pc - ancho + 1 );
        int col_max = std::min( W - ancho, pc );

        for ( int fila = fila_min; fila <= fila_max; fila++ ){
            for ( int col = col_min; col <= col_max; col++ ){
                bool descartado = false;
                for ( int i = fila; i < fila + alto && !descartado; i++ ){
                    for ( int j = col; j < col + ancho && !descartado; j++ ){
                        // otro numero dentro del rectangulo
                        if ( tablero.celdas[i][j] > 0 && !(i == pf && j == pc ) ) {
                            descartado = true;
                        }
                        if (tablero.regiones[i][j] >= 0 ){
                            descartado = true;
                        }
                    }
                }
                
                if ( !descartado ){
                    validos.push_back( { fila, col, alto, ancho } );
                }
            }
        }
    }
    return validos;
}


// asigna el id del rectangulo a las celdas que cubre
static void marcarH(Tablero &tablero, const Rectangulo &R, int id){
    for (int i = R.fila; i < R.fila + R.alto; i++){
        for (int j = R.col; j < R.col + R.ancho; j++){
            tablero.regiones[i][j] = id;
        }
    }
}


// BACKTRACKING liberar las celdas del rectangulo
static void desmarcarH ( Tablero &tablero, const Rectangulo &R ){
    for ( int i = R.fila; i < R.fila + R.alto; i++ ){
        for ( int j = R.col; j < R.col + R.ancho; j++ ){
            tablero.regiones[i][j] = -1;
        }
    }
}

// BACKTRACKING HEURISTICA MRV
// en cada nivel elige el numero (no asignado) con menos posibilidades de rectangulos validos
// asignados[k] = true si el numero k ya tiene un rectangulo asignado
static bool backtrackingMRV( Tablero &tablero, const std::vector<NumeroH> &numeros, std::vector<bool> &asignados, int restantes ){
    // se asignaron todos los numeros
    if ( restantes == 0 ) {
        return true;
    }

    // elegir el numero no asignado con menos rectangulos validos
    int mejor = -1;
    int mejorCount = -1;
    std::vector<Rectangulo> mejorValidos;

    for ( int k = 0; k < (int)numeros.size(); k++ ){
        if (asignados[k]) continue;
        std::vector<Rectangulo> v = generarValidos( tablero, numeros[k].fila, numeros[k].col, numeros[k].val );

        //si algun numero no tiene una opcion, es un camino cerrado
        if ( v.empty() ) return false;

        if ( mejor == -1 || (int)v.size() < mejorCount ){
            mejor = k;
            mejorCount = (int)v.size();
            mejorValidos = v;
        }
    }

    // no hay numeros sin asignar, pero no se asignaron todos
    if ( mejor == -1 ) return false;

    asignados[mejor] = true;

    for ( const Rectangulo &R : mejorValidos ){
        int id = (int)tablero.rectangulos.size();
        tablero.rectangulos.push_back( R );
        marcarH ( tablero, R, id );

        if ( backtrackingMRV ( tablero, numeros, asignados, restantes - 1 ) ){
            return true;
        }

        tablero.rectangulos.pop_back();
        desmarcarH ( tablero, R );
    }

    asignados[mejor] = false;
    return false;

}


// entrada del solucionador por heurística ALGORITMO 3
bool resolverH ( Tablero &tablero ){
    //limpiar regiones
    for ( auto &fila : tablero.regiones ){
        for (auto &c : fila ){
            c = -1; // inicializo las regiones como no asignadas
        }
    }
    tablero.rectangulos.clear();
    while ( !tablero.historial.empty() ) tablero.historial.pop();

    //numeros son todas las (r, c) donde tablero.celdas[r][c] > 0
    std::vector<NumeroH> numeros;
    for ( int i = 0; i < tablero.filas; i++ ){
        for ( int j = 0; j < tablero.columnas; j++ ){
            if ( tablero.celdas[i][j] > 0 ){
                numeros.push_back( { i, j, tablero.celdas[i][j] } );
            }
        }
    }
    if ( numeros.empty() ) return true; // no hay numeros, ya esta resuelto

    std::vector<bool> asignados( numeros.size(), false );
    
    return backtrackingMRV( tablero, numeros, asignados, (int)numeros.size() );
}
