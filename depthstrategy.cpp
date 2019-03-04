#include "depthstrategy.h"

depthstrategy::depthstrategy(int l)
{
    frontera =new std::stack<NodoPuzzle*>();
    limite = l;
}

bool depthstrategy::puedeExpandirse()
{
    return !frontera->empty();
}

void depthstrategy::asignarRaiz(NodoPuzzle *n)
{
    //Agregar a la frontera el estado inicial para expandir
    depthstrategy::frontera->push(n);
}


void depthstrategy::expandir(NodoPuzzle *n)
{

    if(n->nivel==limite){
        return;
    }

    estadosExplorados->push_front(n->estado);

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

}


NodoPuzzle* depthstrategy::seleccionarNodo()
{
    NodoPuzzle *nodoAddr = depthstrategy::frontera->top();
    frontera->pop();
    return nodoAddr;
}
