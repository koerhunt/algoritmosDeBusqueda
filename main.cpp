#include <QCoreApplication>
#include <iostream>
#include <queue>

//dificultad del puzzle
const int PUZZLESIZE = 3;

//acciones
enum ACCIONES{ARRIBA,DERECHA,ABAJO,IZQUIERDA};

//Namespace para utilidades
using namespace std;

//Matriz de estado
static int estadoInicial[PUZZLESIZE][PUZZLESIZE] = {
    {1,2,3},
    {6,4,5},
    {0,7,8}
};

static int estadoFinal[PUZZLESIZE][PUZZLESIZE] = {
    { 1, 2, 3},
    { 4, 5, 6},
    { 7, 8, 0}
};


//Matriz del estado final
//static int estadoFinal[PUZZLESIZE][PUZZLESIZE] = {
//    { 1, 2, 3, 4},
//    { 5, 6, 7, 8},
//    { 9,10,11,12},
//    {13,14,15, 0}
//};

//Funciones para encontrar el hueco
int renglonHueco(int st[PUZZLESIZE][PUZZLESIZE]){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(st[mi][mj]==0){
                return mj;
            }
        }
    }
}
int columnaHueco(int st[PUZZLESIZE][PUZZLESIZE]){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(st[mi][mj]==0){
                return mi;
            }
        }
    }
}

class Estado{
  public:
    Estado();
    int mundo[PUZZLESIZE][PUZZLESIZE];
    void crearmundo(int[PUZZLESIZE][PUZZLESIZE]);
};

Estado::Estado(){};


bool SeHaExplorado(Estado);

static queue<Estado> *estadosExplorados;

//Guarda la informacion del estado del puzzle
void Estado::crearmundo(int nuevoestado[PUZZLESIZE][PUZZLESIZE]){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            mundo[mi][mj] = nuevoestado[mi][mj];
        }
    }
}

class NodoPuzzle{
    public:
        NodoPuzzle();
        Estado *estado;
        NodoPuzzle *padre;
};

NodoPuzzle::NodoPuzzle(){
    NodoPuzzle::estado = new Estado();
};

class SearchStrategy{
    public:
        int t; //tiempo ms
        int totalNodos;
        SearchStrategy();
        virtual void expandir(NodoPuzzle){};
        virtual bool puedeExpandirse(){};
        virtual NodoPuzzle seleccionarNodo(){};
        virtual void asignarRaiz(NodoPuzzle){};
};
SearchStrategy::SearchStrategy(){}

class BreadthStrategy : public SearchStrategy{
    public:
        BreadthStrategy();
        queue<NodoPuzzle> *estados;
        void expandir(NodoPuzzle);
        NodoPuzzle seleccionarNodo();
        bool puedeExpandirse();
        void asignarRaiz(NodoPuzzle);
};

BreadthStrategy::BreadthStrategy(){
    estados = new queue<NodoPuzzle>();
}

void BreadthStrategy::asignarRaiz(NodoPuzzle n){
    estados->push(n);
}

void BreadthStrategy::expandir(NodoPuzzle n){

    //Explorar (encontrar donde esta el hueco)
    int r = renglonHueco(n.estado->mundo);
    int c = columnaHueco(n.estado->mundo);

    //ACCIONES
    //si la accion es valida, entonces...

    //mov izq
    if( r > 0){

        NodoPuzzle *sn = new NodoPuzzle();
        sn->estado->crearmundo(n.estado->mundo); //Crear nuevo estado

        //realizar movimiento
        sn->estado->mundo[c][r] = sn->estado->mundo[c][r-1];
        sn->estado->mundo[c][r-1] = 0;

        //guardar padre
        sn->padre = &n;

        if(!SeHaExplorado(*sn->estado)){
            //Agregar al arbol de busqueda
            estados->push(*sn);
        }

    }

    //mov der
    if( r < (PUZZLESIZE-1)){

        NodoPuzzle *sn;
        sn = new NodoPuzzle();
        sn->estado->crearmundo(n.estado->mundo); //Crear nuevo estado

        //realizar movimiento
        sn->estado->mundo[c][r] = sn->estado->mundo[c][r+1];
        sn->estado->mundo[c][r+1] = 0;

        //guardar padre
        sn->padre = &n;

        if(!SeHaExplorado(*sn->estado)){
            //Agregar al arbol de busqueda
            estados->push(*sn);
        }
    }

    //mov arr
    if( c > 0 ){

        NodoPuzzle *sn;
        sn = new NodoPuzzle();
        sn->estado->crearmundo(n.estado->mundo); //Crear nuevo estado

        //realizar movimiento
        sn->estado->mundo[c][r] = sn->estado->mundo[c-1][r];
        sn->estado->mundo[c-1][r] = 0;

        //guardar padre
        sn->padre = &n;

        if(!SeHaExplorado(*sn->estado)){
            //Agregar al arbol de busqueda
            estados->push(*sn);
        }
    }

    //mov arr
    if( c < (PUZZLESIZE-1) ){

        NodoPuzzle *sn;
        sn = new NodoPuzzle();
        sn->estado->crearmundo(n.estado->mundo); //Crear nuevo estado

        //realizar movimiento

        sn->estado->mundo[c][r] = sn->estado->mundo[c+1][r];
        sn->estado->mundo[c+1][r] = 0;

        //guardar padre
        sn->padre = &n;

        if(!SeHaExplorado(*sn->estado)){
            //Agregar al arbol de busqueda
            estados->push(*sn);
        }
    }


}

//Verifica si el estado puede ser expandido
bool BreadthStrategy::puedeExpandirse(){
    return !estados->empty();
}

//Agarrar el primer elemento de la cola
NodoPuzzle BreadthStrategy::seleccionarNodo(){
    NodoPuzzle n = estados->front();
    estados->pop();
    return n;
}

// Genera un estado aleatorio para el Juego
void generarEstadoInicialAleatorio(){

    //Todas las piezas
    vector<int> piezas;

    //Generar todas las piezas
    for(int i = 0; i<(PUZZLESIZE*PUZZLESIZE); i++)
        piezas.push_back(i);

    //mezclar piezas
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle ( piezas.begin(), piezas.end() );

    //Llenar matriz del juego e imprimir estado generado
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            //Acomodar piezza
            estadoInicial[mi][mj] = piezas.back();
            piezas.pop_back();
        }
    }

};

//Funcion para imprimir estado
void imprimirEstado(NodoPuzzle n){
    cout<<endl;
    cout<<"==========================="<<endl;
    //Llenar matriz del juego e imprimir estado generado
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(n.estado->mundo[mi][mj]<10){
                if(n.estado->mundo[mi][mj]==0){
                    cout<<" "<<"   |";
                }else{
                    cout<<" "<<n.estado->mundo[mi][mj]<<"  |";
                }
            }else{
                cout<<" "<<n.estado->mundo[mi][mj]<<" |";
            }

        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"==========================="<<endl;
}

//Funcion Objetivo
bool pruebaObjetivo(NodoPuzzle n){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(estadoFinal[mi][mj] != n.estado->mundo[mi][mj]){
                return false;
            }
        }
    }
    return true;
}

bool comparar(Estado &a, Estado &b){
    for(int mi = 0; mi < PUZZLESIZE; mi++){
        for(int mj = 0; mj < PUZZLESIZE; mj++){
            if(a.mundo[mi][mj] != b.mundo[mi][mj]){
                return false;
            }
        }
    }
    return true;
}

bool SeHaExplorado(Estado st){
    bool flag = false;

   queue<Estado> *tmp = new queue<Estado>();
   Estado et = estadosExplorados->front();
   estadosExplorados->pop();

   if(comparar(et,st)){
       flag = true;
   }

   tmp->push(et);
   delete estadosExplorados;
   estadosExplorados = tmp;

   return flag;
}

int realizarBusqueda(SearchStrategy *s){

    while(s->puedeExpandirse()){

        NodoPuzzle n = s->seleccionarNodo();

        if(pruebaObjetivo(n)){
            cout<<"Solucion encontrada"<<endl;
            imprimirEstado(n);
            return 0;
        }else{
//            cout<<"No es nodo solucion, expandiendo..."<<endl;
//            if(!SeHaExplorado(*n.estado)){
                estadosExplorados->push(*n.estado);
                s->totalNodos+=1;
                cout<<"nodos expandidos: "<<s->totalNodos<<endl;
//                imprimirEstado(n);
                s->expandir(n);
//            }
        }



    }
    return -1;

}

//MAIN
int main(int argc, char *argv[])
{

    //Estado inicial
//    generarEstadoInicialAleatorio();
    estadosExplorados = new queue<Estado>();

    //Nodo Raiz
    NodoPuzzle *raiz = new NodoPuzzle();
    raiz->padre = nullptr;
    raiz->estado->crearmundo(estadoInicial);
    imprimirEstado(*raiz);

    //Preparar estrategia
    SearchStrategy *s = new BreadthStrategy();
    s->asignarRaiz(*raiz);

    int r = realizarBusqueda(s);
    if(r==-1){
        cout<<"Solucion no encontrada"<<endl;
    }

    //Esperar tecla para cerrar.
    QCoreApplication a(argc, argv);
    return 0;

}




