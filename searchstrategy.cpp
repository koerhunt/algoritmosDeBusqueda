#include "searchstrategy.h"

SearchStrategy::SearchStrategy()
{
    estadosExplorados = new list<Estado*>();
    camino = new list<NodoPuzzle*>();
}

bool comparar(int a[PUZZLESIZE][PUZZLESIZE], int b[PUZZLESIZE][PUZZLESIZE]){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(a[mi][mj] != b[mi][mj]){
                return false;
            }
        }
    }
    return true;
}

bool SearchStrategy::SeHaExplorado(NodoPuzzle *nd){
   bool flag = false;

   std::list<Estado*>::iterator it;
   it = SearchStrategy::estadosExplorados->begin();

   while(it != estadosExplorados->end()){
       if(comparar( (*it)->mundo,nd->estado->mundo )){
           flag = true;
       }
       it++;
   }

   return flag;
}


//Funcion Objetivo
bool SearchStrategy::pruebaObjetivo(NodoPuzzle *n){
    return comparar(n->estado->mundo, estadoFinal);
}
