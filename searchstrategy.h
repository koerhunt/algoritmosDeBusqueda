#ifndef SEARCHSTRATEGY_H
#include "nodopuzzle.h"
#include "iostream"
#define SEARCHSTRATEGY_H

using namespace std;

class SearchStrategy
{
public:
        int t; //tiempo ms
        int totalNodos;
        SearchStrategy();
        std::list<Estado*>     *estadosExplorados;
        std::list<NodoPuzzle*> *camino;
        virtual void expandir(NodoPuzzle*){}
        virtual bool puedeExpandirse(){return false;}
        virtual NodoPuzzle* seleccionarNodo(){return nullptr;}
        virtual void asignarRaiz(NodoPuzzle*){}
        bool pruebaObjetivo(NodoPuzzle*);
        bool SeHaExplorado(NodoPuzzle*);
};
#endif // SEARCHSTRATEGY_H

