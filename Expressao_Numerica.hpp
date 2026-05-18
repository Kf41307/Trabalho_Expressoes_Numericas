#include "Fila_Encadeada.hpp"
//#include "FilaEstatica.hpp"
#include "Pilha_Encadeada.hpp"
//#include "PilhaEstatica.hpp"
#include <string>
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


bool validar(string expressao){
    Pilha p;
    inicializar(p);

    // VALIDAÇÃO POR LISTA DUPLAMENTE ENCADEADA ???

    if(expressao.length() == 0) return false;

    char primeiro = expressao[0];
    if(primeiro == '*' || primeiro == '/' || primeiro == '^'){
        cout<<"Operador na primeira posicao"<<endl;
        return false;
    }
    if(ehFecha(primeiro)){
        cout<<"Fechando \'" << primeiro << "\' sem abrir"<<endl;
        return false;
    }


    for(int i = 0; i < (int) expressao.length(); i++){
        char atual = expressao[i];
        char anterior = (i > 0) ? expressao[i-1] : '\0';
        
        if(!ehOperando(atual) && !ehOperador(atual) && !ehAbre(atual) && !ehFecha(atual)){ // Remover esses caracteres invalidos antes de verificar se usar lista
            cout<<"Caractere inválido: \'" << atual << "\'" << endl;
            return false;
        }

        if (ehOperando(atual) && ehOperando(anterior)){
            cout<<"Dois operandos seguidos, era esperado um operador entre eles"<<endl;
            return false;
        }

        if(ehOperador(atual) && ehOperador(anterior)){
            cout<<"Dois operadores seguidos sem nenhum operando"<<endl;
            return false;
        }

        if(ehOperador(atual) && ehAbre(anterior)){ //Pode mudar caso seja aceito numeros negativos direto (-3 + 4) = (-3 4 +)
            cout<<"Operador logo apos a abertura de\'" << anterior << "\'" << endl;
            return false;
        }

        if(ehOperando(atual) && ehFecha(anterior)){
            cout<<"Operando diretamente depois do fechamento"<<endl;
            return false;
        }

        if(ehAbre(atual) && ehOperando(anterior)){
            cout<<"Falta um operador antes da abertura de \'" << atual << "\'"<<endl;
            return false;
        }

        if(ehAbre(atual) && ehFecha(anterior)){
            cout << "Falta operador entre \'"<<anterior<<"\' e \'"<<atual<<"\'"<<endl;
            return false;
        }
    
        if (ehFecha(atual)) {
            if (vazia(p)) {
                cout << "Erro na posicao " << i << ": '" << atual << "' fecha sem abrir\n";
                return false;
            }

            char abertura; 
            pop(p, abertura);
            if (abertura != parAbertura(atual)) {
                cout << "Erro na posicao " << i << ": '" << atual
                     << "' nao fecha '" << abertura << "'\n";
                return false;
            }
        }

        if (ehAbre(atual)) {
            push(p, atual);
        }
    }

        char ultimo = expressao[expressao.length() - 1];
        if(ehOperador(ultimo)){
            cout<<"Ultimo elemento é um operador"<<endl;
            return false;
        }

        if(ehAbre(ultimo)){
            cout<<"Abertura no ultimo"<<endl;
            return false;
        }

        char topo = top(p, topo);
        if(!vazia(p)){
            cout<<"\'" << topo << "\' foi aberto e não foi fechado"<<endl;
            return false;
        }
        
        liberar(p);
        return true;
}

int numeroAberturas(Pilha p){
    NoP * aux = p.ultimo;
    int contadorAbertura = 0;

    while(aux != NULL){
        if(ehAbre(aux->dado)){
            contadorAbertura++;
        }

        aux = aux->proximo;
    }
    return contadorAbertura;
}

int prioridade(char c){
    if(c == '^') return 3;
    else if(c == '/' || c == '*') return 2;
    return 1;
}


Fila notacaoPolonesa(string expressao){ //A expressao tem que ser passada como uma fila aqui
    // (a+3)×[(b^2)−(c/4)]+7    p/ polonesa
    // a 3 + b 2 ^ c 4 / - * 7 +
    
    // Operandos em fila
    // Divisores e operadores pilha
    
    Fila operandos;
    inicializar(operandos);
    Pilha operadores;
    inicializar(operadores);
    
    if(!validar(expressao)) return operandos;
    
    //Pilha: * [ -
    //Fila : a 3 + b 2 ^ c 4 /

    //Verificação de antes de colocar um operador, caso tenha outro operador no topo antes da inserção entra no caso das prioridades
    //Quando for desempilhar na ocorrencia de um fechamento, caso so tenha uma abertura limpar toda a pilha e passar para a fila, 
    //caso tenha mais de uma limpar ate a abertura do fechamento encontrado

    for(int i = 0; i < (int) expressao.length(); i++){
        
        if(ehAbre(expressao[i])){ //Mudar
            push(operadores, expressao[i]);
        }else if(ehOperando(expressao[i])){
            queue(operandos, expressao[i]);
        }else if(ehOperador(expressao[i])){
            char topo;
            top(operadores, topo);
            if(ehOperador(topo)){
                //Ver a prioridade entre o topo e o atual
                if(prioridade(topo) >= prioridade(expressao[i])){
                    char temp;
                    pop(operadores, temp);
                    queue(operandos, temp);
                    push(operadores, expressao[i]);

                }else{
                    queue(operandos, expressao[i]);
                }

            }else{
                push(operadores, expressao[i]);
            }
        }

        if(ehFecha(expressao[i])){
            // abertura > 1 ? pop ate que encontre o par : limpar a pilha passando pra fila
            if(numeroAberturas(operadores) == 1){
                //Limpeza da pilha passando para pilha
                NoP * aux = operadores.ultimo;
                while(!vazia(operadores)){
                    char temp;
                    pop(operadores, temp);
                    queue(operandos, temp);
                    aux = aux->proximo;
                }

            }else{
                //Limpar ate encontrar o par do fechamento
            
                char temp;
                do{
                    pop(operadores, temp);

                    if(temp != parAbertura(expressao[i])){
                        queue(operandos, temp);
                    }

                }while(temp != parAbertura(expressao[i]));

            }
        }
    }

    char temp;
    while(!vazia(operadores)){
        pop(operadores, temp);
        queue(operandos, temp);
    }

    return operandos; 
}