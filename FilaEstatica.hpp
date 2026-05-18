#ifndef TAM
#define TAM 50
#endif

template <typename T>
struct Fila{
    T vetor[TAM];
    int primeiro, ultimo;
};

template <typename T>
void inicializar(Fila <T> &f){
    f.primeiro = 0;
    f.ultimo = -1;
}

template <typename T>
bool vazia(Fila <T> f){
    return (f.primeiro > f.ultimo) ? true : false;
}

template <typename T>
bool cheia(Fila <T> f){
    return (f.ultimo == TAM-1) ? true : false;
}

template <typename T>
bool queue(Fila <T> &f, T valor){
    if( cheia(f) ) return false;
    f.ultimo++;
    f.vetor[f.ultimo] = valor;
    return true;
}

template <typename T>
bool dequeue(Fila <T> &f, T &valor){
    if( vazia(f) ) return false;
    valor = f.vetor[f.primeiro];
    f.primeiro++;
    return true;
}
