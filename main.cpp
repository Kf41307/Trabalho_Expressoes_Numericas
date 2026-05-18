#include "Expressao_Numerica.hpp"
#include <iostream>
#include <string>

int main(){
    system("chcp 65001");
    system("cls");

    string expressao;

    cout<<"Informe a expressão: "<<endl;
    getline(cin, expressao);

    Fila polonesa = notacaoPolonesa(expressao);

    mostrarFila(polonesa);

    return 0;
}