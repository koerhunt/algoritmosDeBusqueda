#ifndef DEPTHSTRATEGY_H
#define DEPTHSTRATEGY_H
#include "searchstrategy.h"
#include "stack"

class depthstrategy : public SearchStrategy
{
public:
    depthstrategy(int);
    int limite;
    stack<NodoPuzzle*> *frontera;
    void expandir(NodoPuzzle *);
    bool puedeExpandirse();
    NodoPuzzle *seleccionarNodo();
    void asignarRaiz(NodoPuzzle *);
    int buscar();
};

#endif // DEPTHSTRATEGY_H
