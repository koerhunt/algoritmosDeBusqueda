#include "nodopuzzle.h"
#include "iostream"

using namespace std;

NodoPuzzle::NodoPuzzle(int n)
{
    NodoPuzzle::nivel = n;
    NodoPuzzle::accion = NOP;
    NodoPuzzle::estado = new Estado();
    //NodoPuzzle::padre = new NodoPuzzle();
    NodoPuzzle::hijos  = new list<NodoPuzzle>;

}

//Funcion para imprimir estado
void NodoPuzzle::imprimirEstado(){
    cout<<endl;
    //Llenar matriz del juego e imprimir estado generado
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(NodoPuzzle::estado->mundo[mi][mj]<10){
                if(NodoPuzzle::estado->mundo[mi][mj]==0){
                    cout<<" "<<"   |";
                }else{
                    cout<<" "<<NodoPuzzle::estado->mundo[mi][mj]<<"  |";
                }
            }else{
                cout<<" "<<NodoPuzzle::estado->mundo[mi][mj]<<" |";
            }

        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"==========================="<<endl;
}
