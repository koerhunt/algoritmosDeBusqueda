#include <QCoreApplication>
#include <iostream>
#include <queue>
#include <list>
#include <stack>

#include "definiciones.h"
#include "estado.h"
#include "nodopuzzle.h"
#include "searchstrategy.h"
#include "breadthstrategy.h"
#include "depthstrategy.h"
#include "astarsrategy.h"

using namespace std;
NodoPuzzle *raiz;

//MAIN
int main()
{


    //Nodo Raiz
    raiz = new NodoPuzzle(0);
    raiz->estado->crearmundo(estadoInicial);

    //Mezclar juego
    if(MEZCLAR){
        raiz->estado->mezclar();
    }

    cout<<"COMIENZA EJECUCION ==>"<<endl;
    cout<<"==== Estado inicial ===="<<endl;
    raiz->imprimirEstado();
    cout<<endl;

    int r;

//    SearchStrategy *s = new BreadthStrategy();
//    virtual int buscar(){return -1;}

//    SearchStrategy *s = new depthstrategy(25);
    SearchStrategy *s = new astarsrategy();

    s->asignarRaiz(raiz);
    r = s->buscar();


    if(r==-1){
        cout<<"Solucion no encontrada"<<endl;
    }

    //Esperar tecla para cerrar.
    return 0;

}
