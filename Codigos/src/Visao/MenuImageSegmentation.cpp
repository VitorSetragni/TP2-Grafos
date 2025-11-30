#ifndef MENU_IMAGE_SEGMENTATION_HPP
#define MENU_IMAGE_SEGMENTATION_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <filesystem> 
#include <chrono>
#include <cstdint>

#include "../../libs/io/MyIO.hpp" 

#include "../Segmentacao/InterfaceImagem.hpp"
#include "../Segmentacao/ISegmentador.hpp"
#include "../Segmentacao/MST/SegmentadorMST.hpp"
#include "../Segmentacao/MSA/SegmentadorMSA.hpp"
#include "../Grafo/Lista/GrafoLista.hpp"

using namespace std;

using namespace std::chrono;

class MenuImageSegmentation {

public:
    void menu() {
        int opcao = 0;
        do {
            cout << "\n========================================================================" << endl;
            cout << "      BEM VINDO AO TP2 - SISTEMA DE SEGMENTACAO DE IMAGENS (GRAFOS)      " << endl;
            cout << "=========================================================================" << endl;
            cout << "1. Teste Unico (Uma imagem, um K)" << endl;
            cout << "2. Bateria de Testes (Uma imagem, varios Ks)" << endl;
            cout << "0. Sair" << endl;
            cout << "--------------------------------------------------------" << endl;
            cout << "Escolha: ";
            cin >> opcao;

            switch (opcao) {
                case 1: executarTesteUnico(); break;
                case 2: executarBateriaTestes(); break;
                case 0: cout << "Saindo..." << endl; break;
                default: cout << "Opcao invalida!" << endl;
            }
        } while (opcao != 0);
    }

private:
    // Lógica
    uint64_t timeSinceEpochMillisec() {
        // Get the current time point from the system clock
        // Busca o tempo atual do sistema
        auto now = system_clock::now();

        // Converte o tempo atual para o tempo desde epoch
        auto duration = now.time_since_epoch();

        // Converte a duração para milissegundos
        uint64_t milliseconds = chrono::duration_cast<chrono::milliseconds>(duration).count();
        
        return milliseconds;
    }

    // LOGICA DE PROCESSAMENTO
    uint64_t processarImagem(string caminhoImagem, int tipoAlgoritmo, double k, int minSize, bool coresAleatorias) {
        
        cout << "\n[PROCESSANDO] Imagem: " << caminhoImagem << " | K=" << k << " | Min=" << minSize << endl;

        //Definição do Algoritmo e Direcionalidade
        ISegmentador* segmentador = nullptr;
        bool isDirecionado = false;
        string tagAlgoritmo = "";

        if (tipoAlgoritmo == 1) {
            cout << "-> Algoritmo: MST (Kruskal)" << endl;
            segmentador = new SegmentadorMST();
            isDirecionado = false; // MST usa grafo não direcionado
            tagAlgoritmo = "MST";
        } else {
            cout << "-> Algoritmo: MSA (Edmonds)" << endl;
            segmentador = new SegmentadorMSA();
            isDirecionado = true;  // Edmonds EXIGE grafo direcionado
            tagAlgoritmo = "MSA";
        }

        // Carregar Grafo da Imagem
        GrafoLista* grafo = grafoFromImagem(caminhoImagem, isDirecionado);

        if (!grafoInstanciado(grafo)) {
            delete segmentador;
            return 0;
        }

        uint64_t inicio = timeSinceEpochMillisec();

        // Executar Segmentação
        ResultadoSegmentacao resultado = segmentador->segmentar(grafo, k, minSize);

        uint64_t fim = timeSinceEpochMillisec();

        // Gerar Grafo Pintado (Visualização)
        GrafoLista* grafoPintado = nullptr;
        if (coresAleatorias) {
            grafoPintado = gerarGrafoPintadoAleatorio(grafo, resultado);
        } else {
            grafoPintado = gerarGrafoPintado(grafo, resultado);
        }

        // Salvar Imagem
        if (grafoPintado) {
            // Pega o nome do arquivo sem extensão para montar o output
            string nomeBase = extrairNomeArquivo(caminhoImagem);
            
            stringstream ss;
            ss << "assets/output/" << (tipoAlgoritmo == 1 ? "MST/" : "MSA/") << nomeBase << "_" << tagAlgoritmo 
               << "_k" << (int)k 
               << (coresAleatorias ? "_CorAleatoria" : "_CorReal") 
               << ".ppm";
            
            string caminhoSaida = ss.str();

            int w, h, c;
            // pegar dimensão da imagem
            unsigned char* temp = stbi_load(caminhoImagem.c_str(), &w, &h, &c, 3);
            stbi_image_free(temp);

            salvarImagemBordas(caminhoSaida, resultado, w, h);

            //saveImageFromGrafo(caminhoSaida, grafoPintado, w, h);
            
            cout << "[SUCESSO] Salvo em: " << caminhoSaida << endl;

            delete grafoPintado;
        }

        delete grafo;
        delete segmentador;

        return (fim - inicio);
    }

    // MODOS DE OPERAÇÃO
    void executarTesteUnico() {
        string path;
        cout << "\nCaminho da imagem (ex: assets/input/gato.jpg): ";
        cin >> path;

        int alg = escolherAlgoritmo();
        double k = lerDouble("Valor de K (limiar): ");
        int minSize = lerDouble("Tamanho Minimo (minSize): ");
        bool randColor = escolherCores();

        uint64_t tempo = processarImagem(path, alg, k, minSize, randColor);

        cout << "\n-> Tempo de execução: " << tempo << " milissegundos." << endl;
    }

    void executarBateriaTestes() {
        string path;
        cout << "\nCaminho da imagem (ex: assets/input/gato.jpg): ";
        cin >> path;

        int alg = escolherAlgoritmo();
        
        double kIni = lerDouble("K Inicial: ");
        double kFim = lerDouble("K Final: ");
        double kPasso = lerDouble("Passo (Incremento): ");
        int minSize = lerDouble("Tamanho Minimo (minSize): ");
        bool randColor = escolherCores();

        cout << "\n--- INICIANDO BATERIA DE TESTES ---" << endl;
        
        uint64_t tempoTotal = 0;

        for (double k = kIni; k <= kFim; k += kPasso) {
            tempoTotal += processarImagem(path, alg, k, minSize, randColor);
        }

        cout << "\n-> Tempo médio de execução: " << (tempoTotal / kFim) << " milissegundos." << endl;
        
        cout << "\n--- BATERIA FINALIZADA ---" << endl;
    }

    // UTILITARIOS

    bool grafoInstanciado(GrafoLista* grafo) {
        if (grafo == NULL) cout << "\n[ERRO]: O grafo não está instanciado." << endl;
        return grafo != NULL;
    }

    int escolherAlgoritmo() {
        int op;
        cout << "\nEscolha o Algoritmo:" << endl;
        cout << "1. MST (Kruskal - Felzenszwalb) [Rapido]" << endl;
        cout << "2. MSA (Edmonds - Chu-Liu)      [Lento/Direcionado] (obs: Use imagens pequenas < 400x400)" << endl;
        cout << "Opcao: ";
        cin >> op;
        return op;
    }

    bool escolherCores() {
        int op;
        cout << "\nTipo de Saida:" << endl;
        cout << "0. Cores Reais (Media do segmento)" << endl;
        cout << "1. Cores Aleatorias (Debug de segmentos)" << endl;
        cout << "Opcao: ";
        cin >> op;
        return (op == 1);
    }

    // Extrai o nome do arquivo original para usar no resultado
    string extrairNomeArquivo(const string& caminho) {
        // Remove pasta
        size_t lastSlash = caminho.find_last_of("/\\");
        string nome = (lastSlash == string::npos) ? caminho : caminho.substr(lastSlash + 1);
        // Remove extensão
        size_t lastDot = nome.find_last_of(".");
        if (lastDot != string::npos) {
            nome = nome.substr(0, lastDot);
        }
        return nome;
    }
};

#endif