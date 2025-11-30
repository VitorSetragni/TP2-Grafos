#include <iostream>
#include <string>

#include "MenuLista.hpp" 
#include "../Visao/MenuMatriz.hpp"
#include "../libs/io/io.hpp"
#include "../libs/io/MyIO.hpp"

#define OUTPUT_PATH "/output/saida.png"
#define K_VALUE 600
#define MIN_SEGMENT_SIZE 500


using namespace std;

class MenuImageSegmentation {

public: 
    void menu() {
        try {
            int opcao = 0;
            
            cout << "--------------------------------------------------------" << endl;
            cout << "--- TP2: Segmentação de Imagens via MST (Felzenszwalb) ---" << endl;
            cout << "--------------------------------------------------------" << endl;

            // 1. Entrada de Dados da Imagem
            cout << "\n> Configuração Inicial da Imagem" << endl;
            string nomeImagem = lerString("Digite o caminho/nome da imagem (ex: image.ppm): ");

            // 2. Coleta de Parâmetros do Algoritmo
            cout << "\n> Parâmetros do Algoritmo de Felzenszwalb & Huttenlocher" << endl;
            
            // parâmetro 'k' -> controla o grau de granularidade 
            // Valores baixos = muitos segmentos; Valores altos = segmentos maiores
            int k = lerInteiro("Informe o valor de 'k' (Limiar de corte, ex: 300): ", 0, 1000);

            // pós-processamento para remover componentes menores que 'min_size' 
            int minSize = lerInteiro("Informe o 'min_size' (Tamanho mínimo do componente, ex: 50): ", 0, 1000);
            
            // uso de Gaussian Blur no pré-processamento
            double sigma = lerDouble("Informe o sigma do Gaussian Blur (ex: 0.8): ");

            do {
                // ! DECIDIR SE REALMENTE TEREMOS MAIS DE UMA OPÇÃO DE MODELAGEM

                cout << "\n> Seleção da Estrutura de Dados do Grafo" << endl;
                cout << "Modelando a imagem como um grafo G=(V,E)" << endl;
                cout << "Escolha como armazenar esse grafo:" << endl;
                
                cout << "1) Matriz de Adjacências" << endl;
                cout << "2) Lista de Adjacências" << endl;
                cout << "0) Voltar ao Menu Principal" << endl;
                cout << "-------" << endl;

                opcao = lerInteiro("Opção: ", 0, 2);

                if (opcao == 0) {
                    cout << "\nRetornando..." << endl;
                    break;
                }

                cout << "\n--- Iniciando Processamento ---" << endl;
                cout << "1. Pré-processamento (Gaussian Blur + Sobel)... " << endl;
                cout << "2. Construindo Grafo (CIELAB + Pesos)..." << endl;
                
                // Lógica de despacho para a implementação correta
                switch (opcao) {
                    case 1:
                        cout << "3. Executando Segmentação (MST) usando [Matriz de Adjacências]..." << endl;
                        // TODO: Chamar o controlador de segmentação passando a MATRIZ
                        // Exemplo: processador.executarComMatriz(nomeImagem, k, minSize, sigma);
                        break;
                    case 2:
                        cout << "3. Executando Segmentação (MST) usando [Lista de Adjacências]..." << endl;
                        // TODO: Chamar o controlador de segmentação passando a LISTA
                        // Exemplo: processador.executarComLista(nomeImagem, k, minSize, sigma);
                        break;
                    default:
                        cout << "\nOpção inválida." << endl;
                        break;
                }

                if (opcao == 1 || opcao == 2) {
                    cout << "4. Pós-processamento (Fusão de pequenas regiões)... " << endl;
                    cout << "--- Processo Finalizado! Verifique a imagem de saída. ---" << endl;
                    
                    // Pausa para visualizar antes de limpar ou voltar
                    cout << "\nPressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    opcao = 0; // Força a saída do loop após executar
                }

            } while (opcao != 0);

        } catch (exception& e) {
            cout << "Erro na execução do TP2: " << e.what() << endl;
        }
    }
};