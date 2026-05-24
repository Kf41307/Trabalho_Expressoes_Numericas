#include <iostream>
using namespace std;
#ifndef TAM
#define TAM 50
#endif

template <typename T>
struct Fila{
    T vetor[TAM];
    int primeiro, ultimo;
    int cont;
};

template <typename T>
void inicializar(Fila <T> &f){
    f.primeiro = 0;
    f.ultimo = -1;
    f.cont = 0;
}

template <typename T>
bool vazia(Fila <T> f){
    return (f.cont == 0) ? true : false;
}

template <typename T>
bool cheia(Fila <T> f){
    return (f.cont == TAM) ? true : false;
}

template <typename T>
bool queue(Fila <T> &f, T valor){
    if( cheia(f) ) return false;
    f.ultimo++;
    if( f.ultimo == TAM ) f.ultimo = 0;
    f.cont++;
    f.vetor[f.ultimo] = valor;
    return true;
}

template <typename T>
bool dequeue(Fila <T> &f, T &valor){
    if( vazia(f) ) return false;
    valor = f.vetor[f.primeiro];
    f.primeiro = (f.primeiro == TAM-1) ? 0 : f.primeiro+1;
    f.cont--;
    return true;
}

template <typename T>
void head(Fila <T> f, T &valor){
    valor = f.vetor[f.primeiro];
}

template <typename T>
void mostrarFila(Fila <T> f){
    for(int i = f.primeiro; i <= f.ultimo; i++){
        cout << f.vetor[i] << " ";
    }
    cout << endl;
}
