#include <iostream>
using namespace std;

template <typename T>
struct NoF{
    T dado;
    NoF <T> *proximo, *anterior;
};

template <typename T>
struct Fila{
    NoF <T>* primeiro;
    NoF <T>* ultimo;
};

template <typename T>
void inicializar(Fila <T> &f){
    f.primeiro = NULL;
    f.ultimo = NULL;
}

template <typename T>
bool vazia(Fila <T> f){
    return (f.ultimo == NULL) ? true : false;
}

template <typename T>
bool queue(Fila <T> &f, T valor){
    NoF <T>*novo = new NoF<T>;

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

template <typename T>
bool dequeue(Fila <T> &f , T &valor){
    if(vazia(f)) return false;

    NoF <T>*aux = f.primeiro;

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

template <typename T>
void head(Fila <T> f, T &valor){
    valor = f.primeiro->dado;
}



template <typename T>
void mostrarFila(Fila <T> f){
    NoF <T>* aux = f.primeiro;

    while(aux != NULL){
        cout<<aux->dado<<" ";
        aux = aux->proximo;
    }
}

template <typename T>
void liberar(Fila <T> &f){
    NoF <T> *aux = f.primeiro;
    NoF <T> *aux2;
    while( aux != NULL){
        aux2 = aux;
        aux = aux->proximo;
        delete aux2;
    }
}