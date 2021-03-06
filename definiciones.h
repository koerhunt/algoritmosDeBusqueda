#include <list>
#include <queue>

#ifndef DEFINICIONES_H

#define DEFINICIONES_H

#define NOP 0
#define ARRIBA 1
#define DERECHA 2
#define ABAJO 3
#define IZQUIERDA 4

#define PUZZLESIZE 3
#define IMPRIMIR_CAMINO true
#define MEZCLA 12
#define MEZCLAR false

//Estado inicial del juego
static int estadoInicial[PUZZLESIZE][PUZZLESIZE] = {
    { 1,2,3},
    { 5,0,6},
    { 4,7,8}
};

//Estado final del juego
static int estadoFinal[PUZZLESIZE][PUZZLESIZE] = {
    { 1,2,3},
    { 4,5,6},
    { 7,8,0}
};

#endif // DEFINICIONES_H
