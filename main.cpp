//Trabalho: Expressões numéricas (notação polonesa invertida) 
//Disciplina: Estrutura de Dados - Professor: Marcos Cesar Cardoso Carrard
//Autores: Guilherme Krieger Ferreira, Thifany Ribeiro Rodrigues

#include "Expressao_Numerica.hpp"
#include <iostream>
#include <string>

int main(){
    system("chcp 65001");
    system("cls");

    string expressao;

    cout<<"Informe a expressão: ";
    getline(cin, expressao);

    Fila <char> polonesa;
    inicializar(polonesa);

    if(validar(expressao)){
        Fila<char> filaInfixa = transformar(expressao);
        polonesa = notacaoPolonesa(filaInfixa);

        cout<<"Expressão na notação polonesa: ";
        mostrarFila(polonesa);
        cout<<endl<<endl;


        Fila <double> variaveis;
        inicializar(variaveis);

        for(int i = 0; i < (int) expressao.length(); i++){
            double input = 0;
            if(ehLetra(expressao[i])){
                do{
                    cout<<"Informe um número para \'"<<expressao[i]<< "\': ";
                    cin>>input;

                    if(cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout<<"Entrada inválida, digite um número."<<endl;
                    }else break;
                }while(true);

                queue(variaveis, input);
            }
        }

        cout<<endl<<"Resultado numérico da expressão: "<< valorExpressao(polonesa, variaveis)<<endl;
    }else{
        cout<<"Expressão digitada é inválida"<<endl;
    }
    
    return 0;
}