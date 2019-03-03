#ifndef NODOPUZZLE_H
#include "estado.h"
#define NODOPUZZLE_H

class NodoPuzzle
{
    public:
        int nivel;
        int accion;
        NodoPuzzle(int);
        Estado *estado;
        NodoPuzzle *padre;
        std::list<NodoPuzzle> *hijos;
        void imprimirEstado();
};

#endif
