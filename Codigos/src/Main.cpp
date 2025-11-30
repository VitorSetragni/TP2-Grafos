#include <iostream>
#include <string>

#include "./Visao/MenuImageSegmentation.cpp" 
#include "./Visao/MenuGrafoManager.cpp" 

#include "../libs/io/io.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        int opcaoPrincipal = 0;

        cout << "---------------------------------------------" << endl;
        cout << "--- Bem vindo aos TPs de Teoria dos Grafos ---"<< endl;
        cout << "---------------------------------------------" << endl;
        cout << "--------------- Integrantes: ----------------" << endl
             << "---------- Augusto Stambassi Duarte ---------" << endl
             << "---------- Davi Cândido de Almeida ----------" << endl
             << "-------  Gabriela de Assis dos Reis ---------" << endl
             << "-------- Lucas Carneiro Nassau Malta --------" << endl
             << "------------- João Pedro Torres -------------" << endl
             << "------------ Vitor Leite Setragni -----------" << endl;
        cout << "---------------------------------------------" << endl;
 
        do {
            cout << "\n> Menu Principal (Geral)" << endl << endl;
            cout << "Escolha o módulo:" << endl;
            cout << "1) Testar Implementação de Grafo (TP1 - CRUD/Buscas)" << endl;
            cout << "2) Segmentação de Imagem via MST (TP2)" << endl;
            cout << "0) Sair" << endl << endl;

            opcaoPrincipal = lerInteiro("Opção: ", 0, 2);

            switch (opcaoPrincipal) {
                case 1:
                    (new MenuGrafoManager())->menu();
                    break;
                
                case 2:
                    (new MenuImageSegmentation())->menu();
                    break;
                
                case 0:
                    cout << "\nSaindo da aplicação..." << endl;
                    break;
                
                default:
                    cout << "\nOpção inválida." << endl;
                    break;
            }
        } while (opcaoPrincipal != 0);

    } catch (exception& e) {
        cout << "Erro crítico na main: " << e.what() << endl;
    }

    return 0;
}