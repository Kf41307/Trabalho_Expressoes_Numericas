#include "Fila_Encadeada.hpp"
// #include "FilaEstatica.hpp"
// #include "Fila_Circular.hpp"
#include "Pilha_Encadeada.hpp"
// #include "PilhaEstatica.hpp"
#include <string>
#include <cmath>
using namespace std;

bool ehDigito(char c){
    return c >= '0' && c <= '9';
}
bool ehLetra(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
} 
bool ehOperando(char c){ 
    return ehDigito(c) || ehLetra(c); 
}
bool ehOperador(char c){ 
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^'; 
}
bool ehAbre(char c){ 
    return c=='(' || c=='[' || c=='{'; 
}
bool ehFecha(char c){
    return c==')' || c==']' || c=='}'; 
}
char parAbertura(char c) {
    if (c == ')') return '(';
    if (c == ']') return '[';
    return '{';
}

bool validarParenteses(string e){
    Pilha <char> p;
    inicializar(p);

    for(int i = 0; i < (int) e.length(); i++){
        if(ehAbre(e[i])){
            push(p, e[i]);
        }else if(ehFecha(e[i])){
            if(vazia(p)){
                return false;
            }else{
                char topo;
                top(p, topo);
                if(parAbertura(e[i]) != topo) return false;

                pop(p, topo);
            }
        }
    }
    return vazia(p);
}

int prioridade(char c){
    if(c == '^') return 3;
    if(c == '/' || c == '*') return 2;
    return 1;
}

bool validar(string e){
    bool esperandoOperando = true;

    if(validarParenteses(e)){
        for( int i = 0; i < (int) e.length(); i++){
            if(ehOperando(e[i])){
                if(!esperandoOperando) return false;
            
                esperandoOperando = false;
            }else if(ehOperador(e[i])){
                if(esperandoOperando) return false;
            
                esperandoOperando = true;
            }
        }
    }else return false;

    return !esperandoOperando;
}

Fila <char> transformar(string e){
    Fila <char> filaInfixa;
    inicializar(filaInfixa);
    
    for(int i = 0; i < (int) e.length(); i++){
        queue(filaInfixa, e[i]);
    }

    return filaInfixa;
}

Fila <char> notacaoPolonesa(Fila <char> f){
    Fila <char> operandos;
    inicializar(operandos);
    Pilha <char> operadores;
    inicializar(operadores);
    
    //
    //Pilha: 
    //Fila : 

    char aux;
    while(dequeue(f, aux)){
        
        if(ehAbre(aux)){
            push(operadores, aux);
        }else if(ehOperando(aux)){
            queue(operandos, aux);
        }else if(ehOperador(aux)){
            char topo;
            while(!vazia(operadores)){
                top(operadores, topo);
                
                if(ehAbre(topo)){
                    break;
                }

                if(prioridade(topo) > prioridade(aux) || ((prioridade(topo) == prioridade(aux)) && aux != '^')){
                    pop(operadores, topo);
                    queue(operandos, topo);
                }else{
                    break;
                }
            }
            push(operadores, aux);
        }else if(ehFecha(aux)){
            char temp;
            do{
                pop(operadores, temp);
                if(temp != parAbertura(aux)){
                    queue(operandos, temp);
                }
            }while(temp != parAbertura(aux));
        }
    }

    char temp;
    while(!vazia(operadores)){
        pop(operadores, temp);
        queue(operandos, temp);
    }

    return operandos; 
}

double valorExpressao(Fila <char> f, Fila <double> valorVariaveis){
    double resultadoFinal = 0; 
    Pilha <double> resolucao;
    inicializar(resolucao);

    while(!vazia(f)){
        char temp;

        dequeue(f, temp);

        if(ehLetra(temp)){ 
            double valor;
            dequeue(valorVariaveis, valor);

            push(resolucao, valor);

        }else if(ehDigito(temp)){
            double valorDouble = temp - '0';
            push(resolucao, valorDouble);
        }else{
            //Tirar dois da pilha operandos e aplicar o sinal encontrado (temp) neles
            double op1, op2;
            pop(resolucao, op1);
            pop(resolucao, op2);
            double resultado = 0;

            if(temp == '+') resultado = op1 + op2;
            else if(temp == '-') resultado= op2 - op1;
            else if(temp == '*') resultado = op2 * op1; 
            else if(temp == '/') resultado = op2 / op1;
            else resultado = pow(op2, op1);

            push(resolucao, resultado);
        }
    }

    pop(resolucao, resultadoFinal);
    return resultadoFinal;
}