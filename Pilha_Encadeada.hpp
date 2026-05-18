#include <iostream>
using namespace std;

struct NoP{
    char dado;
    NoP  *anterior, *proximo;
};

struct Pilha{
    NoP * primeiro;
    NoP * ultimo;
};

void inicializar(Pilha &p){
    p.primeiro = NULL;
    p.ultimo = NULL;
}

bool vazia(Pilha p){
    return (p.ultimo == NULL) ? true : false;
}

bool push(Pilha  &p, char valor){
    NoP * novo = new NoP;

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

bool pop(Pilha &p, char &valor){
    if( vazia(p) ) return false;

    NoP *aux = p.ultimo;
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

bool top(Pilha &p, char &valor){
    if( vazia(p) ) return false;
    valor = p.ultimo->dado;
    return true;
}

void mostrarPilha(Pilha p){
    NoP * aux = p.ultimo;

    while(aux != NULL){
        cout<< aux->dado <<"\n";
        aux = aux->anterior;
    }
}

void liberar(Pilha &p){
    NoP * aux = p.primeiro;
    NoP * aux2;
    while( aux != NULL ){
        aux2 = aux;
        aux = aux->proximo;
        delete aux2;
    }
    inicializar(p);
}