#include "astarsrategy.h"
#include "cmath"
#include <algorithm>

astarsrategy::astarsrategy()
{
    astarsrategy::frontera = new std::list<NodoPuzzle*>();
}

int astarsrategy::g(NodoPuzzle* n){

//    return h1(n); //manhatan
//    return h2(n); //# piezas incorrectas
    return h1(n) + h2(n);

}

//Heuristica distancia manhatan;
int astarsrategy::h1(NodoPuzzle* n)
{
    //|mx - px| + |my-py|
    int distance = 0;
    //para cada elemento de la matriz
    for (int i = 0; i < PUZZLESIZE; i++) {
        for (int j = 0; j < PUZZLESIZE; j++) {

            int i2 = n->estado->buscaride(estadoFinal[i][j]);
            int j2 = n->estado->buscarjde(estadoFinal[i][j]);

            distance += std::abs( (i2 - i) ) + std::abs( (j2-j));

        }
    }
    return distance;

}

//Heuristica piezas incorrectas;
int astarsrategy::h2(NodoPuzzle* n)
{
    int incorrectas = 0;
    //para cada elemento de la matriz
    for (int i = 0; i < PUZZLESIZE; i++) {
        for (int j = 0; j < PUZZLESIZE; j++) {
            //la pieza esta en el lugar correcto?
            //que pasa si..  && estadoFinal[i][j] != 0 ??
            //que pasa si se le da mas peso a el orden que se deben acomodar las fichas?
            if(estadoFinal[i][j] != n->estado->mundo[i][j]){
                incorrectas++;
            }
        }
    }
    return incorrectas;

}

bool astarsrategy::puedeExpandirse(){
    return !frontera->empty();
}

NodoPuzzle* astarsrategy::seleccionarNodo(){
    NodoPuzzle *nodoAddr = astarsrategy::frontera->front();
    astarsrategy::frontera->pop_front();
    return nodoAddr;
}

void astarsrategy::asignarRaiz(NodoPuzzle* n){
    astarsrategy::frontera->push_front(n);
}

int astarsrategy::buscar(){

    //Inicia contador de tiempo transucrrido
    auto begin = chrono::high_resolution_clock::now();

    //Si hay nodos por expandir
    while(puedeExpandirse()){

        //Seleccionar un nodo a expandir
        NodoPuzzle *n = seleccionarNodo();
        n->estado->encontrarHueco();

        //Este nodo es la solucion?
        if(pruebaObjetivo(n)){

            //Detener conteo de tiempo
            auto end = chrono::high_resolution_clock::now();
            auto dur = end - begin;
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

            //Guardar el camino en la pila
            guardarCamino(n);
            imprimirCamino();

            //Estadisticas
            cout<<"Solucionado en : "<<pasos<<" pasos"<<endl;
            cout<<"Solucion en el nivel: "<<solucion->nivel<<endl;
            cout<<"# nodos expandidos: "<<totalNodos<<endl;
            cout<<"~Memoria consumida: "<< (sizeof (NodoPuzzle) * (totalNodos))<<" bytes"<<endl;
            cout << "Tiempo: "<< ms <<" ms"<< endl;

            return 0;
        }else{
            //Si no es un estado ya explorado
            //expandirlo
            if(!SeHaExplorado(n)){
                expandir(n);
                totalNodos+=1;
            }

        }

    }
    return -1;

}


bool decentende(NodoPuzzle* a,NodoPuzzle* b) { return a->g <= b->g; }

void astarsrategy::insertar(NodoPuzzle* n){

    //insertar al frente
    frontera->push_front(n);

    //ordenar
    frontera->sort(decentende);
}

void astarsrategy::expandir(NodoPuzzle* n){

    //mov der
    if( n->estado->hc < (PUZZLESIZE-1)){

        NodoPuzzle *sn = (NodoPuzzle*)malloc(sizeof(NodoPuzzle));//new NodoPuzzle((n->nivel+1));
        *sn = NodoPuzzle(n->nivel+1);

        sn->estado->crearmundo(n->estado->mundo);

        sn->padre = n;
        n->hijos->push_front(*sn);

        sn->accion = DERECHA;
        sn->estado->moverDerecha();

        //calcular costo
        sn->g = g(n);
        insertar(sn);

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

        //calcular costo
        sn->g = g(n);
        insertar(sn);


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

        //calcular costo
        sn->g = g(n);
        insertar(sn);

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

        //calcular costo
        sn->g = g(n);
        insertar(sn);

    }

    //Registrar que este estado ya se exploro
    estadosExplorados->push_front(n->estado);

};


