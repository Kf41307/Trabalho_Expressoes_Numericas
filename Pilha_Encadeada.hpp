#include <iostream>
using namespace std;

template <typename T>
struct NoP{
    T dado;
    NoP <T>*anterior, *proximo;
};

template <typename T>
struct Pilha{
    NoP <T> * primeiro;
    NoP <T> * ultimo;
};

template <typename T>
void inicializar(Pilha <T> &p){
    p.primeiro = NULL;
    p.ultimo = NULL;
}

template <typename T>
bool vazia(Pilha <T> p){
    return (p.ultimo == NULL) ? true : false;
}

template <typename T>
bool push(Pilha <T> &p, T valor){
    NoP <T>* novo = new NoP<T>;

    if( novo == NULL ) return false;
    novo->dado = valor;
    novo->proximo= NULL;
    novo->anterior= NULL;

    if( p.primeiro == NULL ){
        p.primeiro = novo;
        p.ultimo = novo;
    }
    else{
        p.ultimo->proximo = novo;
        novo->anterior = p.ultimo;
        p.ultimo = novo;
    }
    return true;
}

template <typename T>
bool pop(Pilha <T> &p, T &valor){
    if( vazia(p) ) return false;

    NoP <T>* aux = p.ultimo;
    if( aux == NULL ) return false;
    valor = aux->dado;

    if( aux == p.primeiro && aux == p.ultimo  ){
        p.primeiro = NULL;
        p.ultimo = NULL;
    }
    else {
        p.ultimo = aux->anterior;
        p.ultimo->proximo = NULL;
    }
    delete aux;
    return true;
}

template <typename T>
bool top(Pilha <T> &p, T &valor){
    if( vazia(p) ) return false;
    valor = p.ultimo->dado;
    return true;
}

template <typename T>
void mostrarPilha(Pilha <T> p){
    T aux;

    while(!vazia(p)){
        pop(p, aux);
        cout<<aux<<" ";
    }
}

template <typename T>
void liberar(Pilha <T> &p){
    NoP <T>* aux = p.primeiro;
    NoP <T>* aux2;
    while( aux != NULL ){
        aux2 = aux;
        aux = aux->proximo;
        delete aux2;
    }
    inicializar(p);
}