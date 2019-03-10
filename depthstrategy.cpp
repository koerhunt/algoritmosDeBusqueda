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

    //Si es objetivo devolver
    if(pruebaObjetivo(n)){

        guardarCamino(n);
        imprimirCamino();

        //Estadisticas
        cout<<"Solucionado en : "<<pasos<<" pasos"<<endl;
        cout<<"Solucion en el nivel: "<<solucion->nivel<<endl;
        cout<<"# nodos expandidos: "<<totalNodos<<endl;
        cout<<"~Memoria consumida: "<< (sizeof (NodoPuzzle) * (totalNodos))<<" bytes"<<endl;

        return;
    }else{
        estadosExplorados->push_front(n->estado);
    }

    //si se llego al limite de profundidad devolver
    if(n->nivel==limite){
        return;
    }

    //paracada susesor expandir
    //mov der
    if( n->estado->hc < (PUZZLESIZE-1)){

        NodoPuzzle *sn = (NodoPuzzle*)malloc(sizeof(NodoPuzzle));//new NodoPuzzle((n->nivel+1));
        *sn = NodoPuzzle(n->nivel+1);

        sn->estado->crearmundo(n->estado->mundo);

        sn->padre = n;
        n->hijos->push_front(*sn);

        sn->accion = DERECHA;
        sn->estado->moverDerecha();

        if(!SeHaExplorado(sn)){
            totalNodos+=1;
            expandir(sn);
        }

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

        if(!SeHaExplorado(sn)){
            totalNodos+=1;
            expandir(sn);
        }

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

        if(!SeHaExplorado(sn)){
            totalNodos+=1;
            expandir(sn);
        }
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

        if(!SeHaExplorado(sn)){
            totalNodos+=1;
            expandir(sn);
        }

    }
}


int depthstrategy::buscar(){
    auto begin = chrono::high_resolution_clock::now();
    expandir(seleccionarNodo());

    //Detener conteo de tiempo
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    cout << "Tiempo: "<< ms <<" ms"<< endl;
    if(solucion==nullptr){
        return -1;
    }else{


        return 1;
    }
}

NodoPuzzle* depthstrategy::seleccionarNodo()
{
    NodoPuzzle *nodoAddr = depthstrategy::frontera->top();
    frontera->pop();
    return nodoAddr;
}
