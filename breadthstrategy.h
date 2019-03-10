#include "iostream"
#include "queue"
#include "searchstrategy.h"

using namespace std;

#ifndef BREADTHSTRATEGY_H
#define BREADTHSTRATEGY_H


class BreadthStrategy : public SearchStrategy{
    public:
        BreadthStrategy();
        queue<NodoPuzzle*> *frontera;
        void expandir(NodoPuzzle*);
        NodoPuzzle* seleccionarNodo();
        bool puedeExpandirse();
        void asignarRaiz(NodoPuzzle*);
        int buscar();
};

#endif // BREADTHSTRATEGY_H
