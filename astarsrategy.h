#ifndef ASTARSRATEGY_H
#define ASTARSRATEGY_H

#include "searchstrategy.h"



class astarsrategy  : public SearchStrategy
{
public:
    astarsrategy();
    list<NodoPuzzle*> *frontera;
    void expandir(NodoPuzzle *);
    bool puedeExpandirse();
    NodoPuzzle *seleccionarNodo();
    void asignarRaiz(NodoPuzzle *);
    int buscar();
    int h1(NodoPuzzle*);
    int h2(NodoPuzzle*);
    int g(NodoPuzzle*);
    void insertar(NodoPuzzle* n);
};

#endif // ASTARSRATEGY_H
