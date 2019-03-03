#ifndef ESTADO_H

#include "definiciones.h"
#define ESTADO_H

class Estado{
  public:
    Estado();
    int mundo[PUZZLESIZE][PUZZLESIZE];
    void crearmundo(int[PUZZLESIZE][PUZZLESIZE]);
    void mezclar();
    void encontrarHueco();
    void moverDerecha();
    void moverIzquierda();
    void moverArriba();
    void moverAbajo();
    int hr;
    int hc;
};

#endif // ESTADO_H
