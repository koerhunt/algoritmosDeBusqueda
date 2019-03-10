#include "searchstrategy.h"

SearchStrategy::SearchStrategy()
{
    estadosExplorados = new list<Estado*>();
    camino = new list<NodoPuzzle*>();
    pasos = 0;
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


void SearchStrategy::guardarCamino(NodoPuzzle* n){
    solucion = n;
    for (NodoPuzzle *tmp = n;;) {
        camino->push_front(tmp);
        tmp=tmp->padre;
        pasos++;
        if(tmp==nullptr)
            break;
    }
}

void SearchStrategy::imprimirCamino(){
    for (std::list<NodoPuzzle*>::iterator it = (camino->begin());it != camino->end();++it){
        switch((*it)->accion){
            case IZQUIERDA:
                cout << "izquierda" <<endl;
            break;
            case DERECHA:
                    cout << "derecha" << endl;
                break;
            case ARRIBA:
                    cout << "arriba" << endl;
                break;
            case ABAJO:
                    cout << "abajo" <<endl;
                break;
        }
        (*it)->imprimirEstado();
    }
}
