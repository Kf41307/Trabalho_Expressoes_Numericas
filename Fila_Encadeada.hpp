#include <iostream>
using namespace std;

struct NoF{
    char dado;
    NoF *proximo, *anterior;
};

struct Fila{
    NoF * primeiro;
    NoF * ultimo;
};

void inicializar(Fila &f){
    f.primeiro = NULL;
    f.ultimo = NULL;
}

bool vazia(Fila f){
    return (f.ultimo == NULL) ? true : false;
}

bool queue(Fila &f, char valor){
    NoF *novo = new NoF;

    if(novo == NULL) return false;

    novo->dado = valor;
    novo->proximo = NULL;
    novo->anterior = NULL;

    if(f.primeiro == NULL){
        f.primeiro = novo;
        f.ultimo = novo;
    }else{
        f.ultimo->proximo = novo;
        novo->anterior = f.ultimo;
        f.ultimo = novo;
    }
    return true;
}

bool dequeue(Fila &f , char &valor){
    if(vazia(f)) return false;

    NoF *aux = f.primeiro;

    valor = aux->dado;

    if(aux == f.primeiro && aux == f.ultimo){
        f.primeiro = NULL;
        f.ultimo = NULL;
    }else{
        f.primeiro = aux->proximo;
        f.primeiro->anterior = NULL;
    }
    delete aux;
    return true;
}

void mostrarFila(Fila  f){
    NoF * aux = f.primeiro;

    while(aux != NULL){
        cout<<aux->dado<<" ";
        aux = aux->proximo;
    }
}

void liberar(Fila &f){
    NoF *aux = f.primeiro;
    NoF *aux2;
    while( aux != NULL){
        aux2 = aux;
        aux = aux->proximo;
        delete aux2;
    }
}