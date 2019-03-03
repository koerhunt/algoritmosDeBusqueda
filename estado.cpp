#include "estado.h"
#include "random"
#include "iostream"

Estado::Estado()
{

}

//Guarda la informacion del estado del puzzle
void Estado::crearmundo(int nuevoestado[PUZZLESIZE][PUZZLESIZE]){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            mundo[mi][mj] = nuevoestado[mi][mj];
        }
    }
    encontrarHueco();
}


//Guarda la informacion del estado del puzzle
void Estado::mezclar(){

    std::cout<<"Mezclando piezas..."<<std::endl;

    srand(time(NULL));

    for(int i = 0;i<MEZCLA;i++){

        int mv = rand() %4 + 1;
        Estado::encontrarHueco();

        switch(mv){
        case 1:
            {
                this->moverAbajo();
            }
            break;
        case 2:
            {
                this->moverArriba();
            }
            break;
        case 3:
            {
                this->moverIzquierda();
            }
            break;
        case 4:
            {
                this->moverDerecha();
            }
            break;
        }

    }

}

//Funciones para encontrar el hueco
void Estado::encontrarHueco(){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(mundo[mj][mi]==0){
               hr = mj;
               hc = mi;
               //Romper ciclo
               mi = PUZZLESIZE;
               mj = PUZZLESIZE;
            }
        }
    }
}

void Estado::moverDerecha(){
    if( hc < (PUZZLESIZE-1)){

        //realizar movimiento
        Estado::mundo[hr][hc] = Estado::mundo[hr][hc+1];
        Estado::mundo[hr][hc+1] = 0;

    }
}
void Estado::moverIzquierda(){
    if( hc > 0){
        Estado::mundo[hr][hc] = Estado::mundo[hr][hc-1];
        Estado::mundo[hr][hc-1] = 0;
    }
}

void Estado::moverArriba(){
    if( hr > 0 ){

        //realizar movimiento
        Estado::mundo[hr][hc] = Estado::mundo[hr-1][hc];
        Estado::mundo[hr-1][hc] = 0;

    }
}

void Estado::moverAbajo(){
    if( hr < (PUZZLESIZE-1) ){
        Estado::mundo[hr][hc] = Estado::mundo[hr+1][hc];
        Estado::mundo[hr+1][hc] = 0;
    }
}

