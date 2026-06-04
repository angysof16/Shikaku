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
- continúo con el siguiente numero no asignado
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "tablero.h"
#include "fuerza_bruta.h"

// numero natural con el área del rectángulo
struct Numero{
    int fila;
    int col;
    int val;
};

// dado un numero en (pf, pc) con valor val, devuelve todos los rectángulos posibles
std::vector<Rectangulo> generarPosibilidadesFB( const Tablero &tablero, int pf, int pc, int val ){
    std::vector<Rectangulo> posibilidades;

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
                bool otroNumero = false;
                for ( int i = fila; i < fila + alto; i++ ){
                    for ( int j = col; j < col + ancho; j++ ){
                        if ( tablero.celdas[i][j] > 0 && !(i == pf && j == pc ) ) {
                            otroNumero = true;
                        }
                    }
                }
                if ( !otroNumero ){
                    posibilidades.push_back( { fila, col, alto, ancho } );
                }
            }
        }
    }
    return posibilidades;
}


// verificar que el rectangulo R no solape con ninguna region asignada
static bool esValidoFB( const Tablero &tablero, const Rectangulo &R ){
    for ( int i = R.fila; i < R.fila + R.alto; i++ ){
        for ( int j = R.col; j < R.col + R.ancho; j++ ){
            if ( tablero.regiones[i][j] >= 0 ){
                return false;
            }
        }
    }
    return true;
}


// asigna el id del rectangulo a las celdas que cubre
static void marcarFB ( Tablero &tablero, const Rectangulo &R, int id ){
    for ( int i = R.fila; i < R.fila + R.alto; i++ ){
        for ( int j = R.col; j < R.col + R.ancho; j++ ){
            tablero.regiones[i][j] = id;
        }
    }
}


// BACKTRACKING liberar las celdas del rectangulo
static void desmarcarFB ( Tablero &tablero, const Rectangulo &R ){
    for ( int i = R.fila; i < R.fila + R.alto; i++ ){
        for ( int j = R.col; j < R.col + R.ancho; j++ ){
            tablero.regiones[i][j] = -1;
        }
    }
}


// algoritmo de fuerza bruta con backtracking ALGORITMO 2
static bool backtrackingFB ( Tablero &tablero, const std::vector<Numero> &numeros, std::vector< std::vector<Rectangulo> > &posibilidades, int idx ){
    if ( idx == (int)numeros.size() ) {
        return true; // se asignaron todos los numeros
    }

    for (Rectangulo &R : posibilidades[idx] ){
        if ( esValidoFB ( tablero, R ) ){
            int id = (int)tablero.rectangulos.size();
            tablero.rectangulos.push_back( R );
            marcarFB ( tablero, R, id );

            if ( backtrackingFB ( tablero, numeros, posibilidades, idx + 1 ) ){
                return true;
            }

            //backtracking
            tablero.rectangulos.pop_back();
            desmarcarFB ( tablero, R );
        }
    }
    return false;
}


// entrada del solucionador por fuerza bruta ALGORITMO 2
bool resolverFB ( Tablero &tablero ){
    for ( auto &fila : tablero.regiones ){
        for (auto &c : fila ){
            c = -1; // inicializo las regiones como no asignadas
        }
    }
    tablero.rectangulos.clear();
    while ( !tablero.historial.empty() ) tablero.historial.pop(); 

    //numeros son todas las (r, c) donde tablero.celdas[r][c] > 0
    std::vector<Numero> numeros;
    for ( int i = 0; i < tablero.filas; i++ ){
        for ( int j = 0; j < tablero.columnas; j++ ){
            if ( tablero.celdas[i][j] > 0 ){
                numeros.push_back( { i, j, tablero.celdas[i][j] } );
            }
        }
    }

    // generar posibilidades de cada numero
    std::vector< std::vector<Rectangulo> > posibilidades( numeros.size() );
    for ( int k = 0; k < (int)numeros.size(); k++ ){
        posibilidades[k] = generarPosibilidadesFB( tablero, numeros[k].fila, numeros[k].col, numeros[k].val );
    }

    return backtrackingFB( tablero, numeros, posibilidades, 0 );
}
