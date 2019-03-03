#include "breadthstrategy.h"
#include "queue"
#include "searchstrategy.h"

BreadthStrategy::BreadthStrategy(){

    //frontera
    BreadthStrategy::frontera = new std::queue<NodoPuzzle*>();

}

void BreadthStrategy::asignarRaiz(NodoPuzzle *n){

    //Agregar a la frontera el estado inicial para expandir
    BreadthStrategy::frontera->push(n);

}

void BreadthStrategy::expandir(NodoPuzzle *n){

    //mov der
    if( n->estado->hc < (PUZZLESIZE-1)){

        NodoPuzzle *sn = (NodoPuzzle*)malloc(sizeof(NodoPuzzle));//new NodoPuzzle((n->nivel+1));
        *sn = NodoPuzzle(n->nivel+1);

        sn->estado->crearmundo(n->estado->mundo);

        sn->padre = n;
        n->hijos->push_front(*sn);

        sn->accion = DERECHA;
        sn->estado->moverDerecha();

        frontera->push(sn);

    }

    //mov izq
    if( n->estado->hc > 0){

        NodoPuzzle *sn = (NodoPuzzle*)malloc(sizeof(NodoPuzzle));//new NodoPuzzle((n->nivel+1));
        *sn = NodoPuzzle(n->nivel+1);

        sn->estado->crearmundo(n->estado->mundo);

        sn->padre = n;
        n->hijos->push_front(*sn);

        sn->accion = IZQUIERDA;
        sn->estado->moverIzquierda();

        frontera->push(sn);


    }

    //mov arr
    if( n->estado->hr > 0 ){

        NodoPuzzle *sn = (NodoPuzzle*)malloc(sizeof(NodoPuzzle));//new NodoPuzzle((n->nivel+1));
        *sn = NodoPuzzle(n->nivel+1);

        sn->estado->crearmundo(n->estado->mundo);

        sn->padre = n;
        n->hijos->push_front(*sn);

        sn->accion = ARRIBA;
        sn->estado->moverArriba();

        frontera->push(sn);

    }

    //mov abj
    if( n->estado->hr < PUZZLESIZE-1 ){

        NodoPuzzle *sn = (NodoPuzzle*)malloc(sizeof(NodoPuzzle));//new NodoPuzzle((n->nivel+1));
        *sn = NodoPuzzle(n->nivel+1);

        sn->estado->crearmundo(n->estado->mundo);

        sn->padre = n;
        n->hijos->push_front(*sn);

        sn->accion = ABAJO;
        sn->estado->moverAbajo();

        frontera->push(sn);

    }

    //Registrar que este estado ya se exploro
    estadosExplorados->push_front(n->estado);

}

//Verifica si el estado puede ser expandido
bool BreadthStrategy::puedeExpandirse(){
    return !BreadthStrategy::frontera->empty();
}

//Agarrar el primer elemento de la cola
NodoPuzzle* BreadthStrategy::seleccionarNodo(){
    NodoPuzzle *nodoAddr = BreadthStrategy::frontera->front();
    frontera->pop();
    return nodoAddr;
}
