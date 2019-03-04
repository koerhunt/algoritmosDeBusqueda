#include <QCoreApplication>
#include <iostream>
#include <queue>
#include <list>
#include <chrono>
#include <stack>

#include "definiciones.h"
#include "estado.h"
#include "nodopuzzle.h"
#include "searchstrategy.h"
#include "breadthstrategy.h"
#include "depthstrategy.h"

using namespace std;
NodoPuzzle *raiz;

// Genera un estado aleatorio para el Juego
int realizarBusqueda(SearchStrategy *s){

    //Inicia contador de tiempo transucrrido
    auto begin = chrono::high_resolution_clock::now();

    //Si hay nodos por expandir
    while(s->puedeExpandirse()){

        //Seleccionar un nodo a expandir
        NodoPuzzle *n = s->seleccionarNodo();
        n->estado->encontrarHueco();

        //Este nodo es la solucion?
        if(s->pruebaObjetivo(n)){

            //Detener conteo de tiempo
            auto end = chrono::high_resolution_clock::now();
            auto dur = end - begin;
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

            int pasos = 0;

                for (NodoPuzzle *tmp = n;;) {
                    s->camino->push_front(tmp);
                    tmp=tmp->padre;
                    pasos++;
                    if(tmp==nullptr)
                        break;
                }

                for (std::list<NodoPuzzle*>::iterator it = (s->camino->begin());it != s->camino->end();++it){
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


            //Estadisticas
            //cout<<"Solucionado en : "<<pasos<<" pasos"<<endl;
            cout<< "solucion en el nivel: "<<n->nivel<<endl;
            cout<<"# nodos expandidos: "<<s->totalNodos<<endl;
            cout<<"~Memoria consumida: "<< (sizeof (NodoPuzzle) * (s->totalNodos))<<" bytes"<<endl;
            cout << "Tiempo: "<< ms <<" ms"<< endl;

            return 0;
        }else{
            //Si no es un estado ya explorado
            //expandirlo
            if(!s->SeHaExplorado(n)){
                s->expandir(n);
                s->totalNodos+=1;
            }

        }

    }
    return -1;

}


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

    cout<<"==== Estado inicial ===="<<endl;
    raiz->imprimirEstado();
    cout<<endl;

    //Preparar estrategia
//    SearchStrategy *s = new BreadthStrategy();
//    s->asignarRaiz(raiz);

    SearchStrategy *s = new depthstrategy(4);
    s->asignarRaiz(raiz);

    int r = realizarBusqueda(s);
    if(r==-1){
        cout<<"Solucion no encontrada"<<endl;
    }

    //Esperar tecla para cerrar.
    return 0;

}
