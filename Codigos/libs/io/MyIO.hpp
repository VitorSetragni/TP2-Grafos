#ifndef MYIO_HPP
#define MYIO_HPP

#include <iostream>
#include <limits>
#include <string>

using namespace std;



int lerInteiro(const string& mensagem, const int limiteInferior, const int limiteSuperior) {
    bool controle = true;
    int numero;

    while (controle) {
        // Ler a entrada padrão
        cout << mensagem;
        cin >> numero;

        // Verificar se a extração falhou (ex: o usuário digitou "banana")
        if (cin.fail()) {
            cout << "[ERRO]: Entrada inválida. Por favor, digite um número inteiro.\n";

            // Limpar o estado de erro do cin
            cin.clear();
        }
        // Se a extração funcionou, verificar se o número está no intervalo desejado
        else if (numero < limiteInferior) {
            cout << "[ERRO]: O número deve ser maior ou igual a " << limiteInferior
                 << ". Tente novamente.\n";
        }
        // Se a extração funcionou, verificar se o número está abaixo do limite desejado
        else if (numero > limiteSuperior) {
            cout << "[ERRO]: O número deve ser menor ou igual a " << limiteSuperior
                 << ". Tente novamente.\n";
        }
        // Se tudo deu certo
        else {
            controle = false;
        }

        // Descartar o restante da linha de entrada inválida do buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return numero;
}

// --- Ler Double (Novo) ---
double lerDouble(const string& mensagem) {
    bool controle = true;
    double numero;

    while (controle) {
        cout << mensagem;
        cin >> numero;

        // Verifica se a entrada é um número válido
        if (cin.fail()) {
            cout << "[ERRO]: Entrada inválida. Por favor, digite um número decimal (use ponto, ex: 0.5).\n";
            cin.clear(); // Limpa o estado de erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
        } else {
            controle = false;
            // Limpa o buffer caso o usuário digite algo como "2.5 abc"
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return numero;
}

bool lerBoolean(const string& mensagem) {
    string entrada;

    // bool controle = true;

    while (true) {
        // Ler a entrada padrão
        cout << mensagem;
        getline(cin, entrada);

        // Verifica se a entrada tem o tamanho de exatamente 1 caractere
        if (entrada.length() == 1) {
            // Pegar o primeiro e único caractere
            char resposta = entrada[0];

            switch (resposta) {
                case 'S':
                case 's':
                case 'Y':
                case 'y':
                    // controle = false;
                    return true;  // Retorna verdadeiro para as opções afirmativas

                case 'N':
                case 'n':
                    // controle = false;
                    return false;  // Retorna falso para as opções negativas
            }
        }

        // Se o código chegou até aqui, a entrada era inválida
        cout << "[ERRO]: Resposta inválida. Por favor, digite S/N ou Y/N.\n";
    }
}

string lerRotulo(const string& mensagem) {
    string rotulo;
    bool controle = true;

    while (controle) {
        cout << mensagem;
        getline(cin, rotulo);

        // Verificar se o rótulo não está vazio ou contém apenas espaços
        // rotulo.find_first_not_of(" \t\n\v\f\r") procura o primeiro caractere que não é um espaço
        // em branco. Se não encontrar nada (retorna npos), a string está vazia ou só tem espaços.
        if (rotulo.empty() || rotulo.find_first_not_of(" \t\n\v\f\r") == string::npos)
            cout << "[ERRO]: O rótulo não pode ser vazio. Tente novamente." << endl;
        else
            controle = false;
    }

    return rotulo;
}

string lerString(const string& mensagem) {
    return lerRotulo(mensagem);
}

#endif
