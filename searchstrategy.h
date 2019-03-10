#ifndef SEARCHSTRATEGY_H
#include "nodopuzzle.h"
#include "iostream"
#include <chrono>

#define SEARCHSTRATEGY_H

using namespace std;

class SearchStrategy
{
public:
        int t; //tiempo ms
        int totalNodos;
        int pasos;
        NodoPuzzle* solucion;
        SearchStrategy();
        std::list<Estado*>     *estadosExplorados;
        std::list<NodoPuzzle*> *camino;
        virtual void expandir(NodoPuzzle*){}
        virtual bool puedeExpandirse(){return false;}
        virtual NodoPuzzle* seleccionarNodo(){return nullptr;}
        virtual void asignarRaiz(NodoPuzzle*){}
        virtual int buscar(){return -1;}
        bool pruebaObjetivo(NodoPuzzle*);
        bool SeHaExplorado(NodoPuzzle*);
        void imprimirCamino();
        void guardarCamino(NodoPuzzle* n);
};
#endif // SEARCHSTRATEGY_H

