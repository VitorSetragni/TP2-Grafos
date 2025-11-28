#include <iostream>
#include <string>

#include "../EstruturaDeDados/Lista/GrafoLista.cpp"
#include "../libs/io/io.hpp"
#include "../libs/io/MyIO.hpp"

using namespace std;
#define maxVertice 2147483647

class MenuLista {
   public:
    GrafoLista* grafo;

    /**
     * Menu de operações para manipular o grafo.
     *
     * Pergunta ao usuario qual opção ele deseja fazer, dependendo da escolha,
     * chama a respectiva função para realizar a operação que desejada.
     *
     * @see intanciaGrafo()
     * @see adicionaVertice()
     * @see adicionaAresta()
     * @see removeVertice()
     * @see removeAresta()
     * @see consultaVizinhosVertice()
     * @see consultarSucessoresVertice()
     * @see consultarPredecessoresVertice()
     * @see removeGrafo()
     * @see imprimeGrafo()
     */

    void menu() {
        int opcao = -1;
        while (opcao != 0) {
            cout << "\n> Menu > Lista" << endl << endl;
            cout << "1) Instanciar Grafo" << endl;
            cout << "2) Adicionar Vértice" << endl;
            cout << "3) Adicionar Aresta" << endl;
            cout << "4) Remover Vértice" << endl;
            cout << "5) Remover Aresta" << endl;
            cout << "6) Consultar Vizinhos de um Vértice" << endl;
            cout << "7) Consultar Fecho Transitivo Direto de um Vértice" << endl;
            cout << "8) Consultar Fecho Transitivo Inverso de um Vértice" << endl;
            cout << "9) Busca em Profundidade - DFS" << endl;
            cout << "10) Busca em Largura - BFS" << endl;
            cout << "11) Imprimir Grafo" << endl;
            cout << "12) Remover Grafo" << endl;
            cout << "0) Sair" << endl << endl;

            cout << "Opção: ";
            cin >> opcao;

            switch (opcao) {
                case 1:
                    intanciaGrafo();
                    break;

                case 2:
                    if(grafoInstanciado()) adicionaVertice();
                    break;

                case 3:
                    if(grafoInstanciado()) adicionaAresta();
                    break;

                case 4:
                    if(grafoInstanciado()) removeVertice();
                    break;

                case 5:
                    if(grafoInstanciado()) removeAresta();
                    break;

                case 6:
                    if(grafoInstanciado()) consultaVizinhosVertice();
                    break;

                case 7:
                    if(grafoInstanciado()) consultarSucessoresVertice();
                    break;

                case 8:
                    if(grafoInstanciado()) consultarPredecessoresVertice();
                    break;
                    
                case 9:
                    if(grafoInstanciado()) buscaEmProfundidade();
                    break;
                    
                case 10:
                    if(grafoInstanciado()) buscaEmLargura();
                    break;                

                case 11:
                    if(grafoInstanciado()) imprimeGrafo();
                    break;

                case 12:
                    if(grafoInstanciado()) removeGrafo();
                    break;
                
                case 0:
                    cout << "\nSaindo..." << endl;
                    break;
                default:
                    cout << "\nOpção inválida!" << endl;
                    break;
            }
        }
    }

    /**
     * Verifica se o grafo está instanciado.
     *
     * @note Se o grafo não estiver instanciado, uma mensagem de erro é impressa na
     *       saída padrão.
     *
     * @return true se o grafo estiver instanciado, false caso contrário.
     */
    bool grafoInstanciado() {
        if (grafo == null) cout << "\n[ERRO]: O grafo não está instanciado." << endl;
        return grafo != null;
    }

    /**
     * Cria um grafo e o armazena em 'grafo'. O grafo pode ser direcionado ou não-direcionado,
     * ponderado ou não ponderado e rotulado ou não rotulado.
     */
    void intanciaGrafo() {
        cout << "\n> Menu > Lista > Instanciar Grafo" << endl << endl;

        // Atributo do grafo
        int numVertices;

        // Variáveis de controle
        bool simples;
        bool direcionado;
        bool verticePonderado;
        bool arestaPonderada;
        bool verticeRotulado;
        bool arestaRotulada;

        // Ler as informações do usuário
        numVertices = lerInteiro("Número de vértices: ", 1, maxVertice);

        simples          = lerBoolean("O grafo é simples?          (S/N): ");
        direcionado      = lerBoolean("O grafo é direcionado?      (S/N): ");
        verticePonderado = lerBoolean("Os vértices são ponderados? (S/N): ");
        arestaPonderada  = lerBoolean("As arestas são ponderadas?  (S/N): ");
        verticeRotulado  = lerBoolean("Os vértices são rotulados?  (S/N): ");
        arestaRotulada   = lerBoolean("As arestas são rotuladas?   (S/N): ");

        this->grafo = new GrafoLista(simples, direcionado, verticePonderado, arestaPonderada,                          verticeRotulado, arestaRotulada, numVertices);
    }

    void adicionaVertice() {
        cout << "\n> Menu > Lista > Adicionar Vértice" << endl << endl;

        // Variaveis nas suas formas padrão caso seja não rotulado e não ponderado
        string rotulo = "";
        int peso = 1;
        // teste de ponderado e de rotulo

        if (grafo->verticePonderado == 1) {
            peso = lerInteiro("Peso do vértice: ", (0 - maxVertice), maxVertice);
        }

        if (grafo->verticeRotulado == 1) {
            rotulo = lerRotulo("Rótulo do vértice: ");
        }

        Vertice novo(grafo->numVertices, peso, rotulo);
        if (grafo->adicionarVertice(novo)) {
            cout << "Vértice adicionado com sucesso!" << endl;
        } else
            cout << "Houve um erro" << endl;
    }

    void adicionaAresta() {
        cout << "\n> Menu > Lista > Adicionar Aresta" << endl << endl;

        // Variaveis nas suas formas padrão caso seja não rotulado e não ponderado
        string rotulo = "";
        int peso = 1;
        // Variaveis para indicar qual vertice o usario deseja
        int inicio;
        int fim;
        grafo->imprimir();
        // pegando a posição dos vertices na Lista
        inicio = lerInteiro("Digite o número do vértice de saida: ", 0,
             grafo->getQuantidadeVertices());
        fim = lerInteiro("Digite o número do vértice de chegada: ", 0,
                         grafo->getQuantidadeVertices());

        // teste de ponderado e de rotulo
        if (grafo->arestaRotulada == 1) {
            rotulo = lerRotulo("Rótulo da aresta: ");
        }

        if (grafo->arestaPonderada == 1) {
            peso = lerInteiro("Peso da aresta: ", (0 - maxVertice), maxVertice);
        }
        // O vertice esta dentro da listaPrincipal que é feita de NoVertice e dentro do Novertice
        // que esta o vertice
        Vertice inicioV = grafo->listaPrincipal[inicio].vertice;
        Vertice fimV = grafo->listaPrincipal[fim].vertice;
        // if (grafo->adicionarAresta(inicioV, fimV, peso, rotulo)) {
        if(grafo->arestaPonderada || grafo->arestaRotulada){
            if(grafo->adicionarAresta(inicioV,fimV,peso,rotulo)) {
                cout << "Aresta adicionada com sucesso!" << endl << endl;
            } else
                cout << "Houve um erro." << endl;
        } else {
            if(grafo->adicionarAresta(inicioV,fimV)){
                cout << "Aresta adicionada com sucesso!" << endl << endl;
            } else {
                cout << "Houve um erro" << endl;
            }
        }
        
    }

    void removeVertice() {
        cout << "\n> Menu > Lista > Remover Vértice" << endl << endl;
        // Variavel para indicar a posição do vertice no array
        int vertice;

        grafo->imprimir();
        // pegando a posição dos vertices na Lista
        vertice = lerInteiro("Digite o número do vértice que deseja remover: ", 0,
                             grafo->getQuantidadeVertices());
        // O vertice esta dentro da listaPrincipal que é feita de NoVertice e dentro do Novertice
        // que esta o vertice
        Vertice inicioV = grafo->listaPrincipal[vertice].vertice;
        if (grafo->removerVertice(inicioV)) {
            cout << "Vértice removido com sucesso" << endl;
        } else
            cout << "Houve um erro" << endl;
    }

    void removeAresta() {
        cout << "\n> Menu > Lista > Remover Aresta" << endl << endl;
        // Variaveis para indicar qual vertice o usario deseja
        int inicio;
        int fim;
        grafo->imprimir();
        // pegando a posição dos vertices na Lista
        inicio =
            lerInteiro("Digite o número do vértice de saida: ", 0, grafo->getQuantidadeVertices());
        fim = lerInteiro("Digite o número do vértice de chegada: ", 0,
                         grafo->getQuantidadeVertices());

        // O vertice esta dentro da listaPrincipal que é feita de NoVertice e dentro do Novertice
        // que esta o vertice
        Vertice inicioV = grafo->listaPrincipal[inicio].vertice;
        Vertice fimV = grafo->listaPrincipal[fim].vertice;
        if (grafo->removerAresta(inicioV, fimV)) {
            cout << "Aresta removida com sucesso" << endl;
        } else
            cout << "Houve um erro" << endl;
    }

    void consultaVizinhosVertice() {
        cout << "\n> Menu > Lista > Consultar Vizinhos de Vértice" << endl << endl;

        // Variavel para indicar a posição do vertice no array
        int verticei;

        grafo->imprimir();

        // pegando a posição dos vertices na Lista
        verticei = lerInteiro("Digite o número do vértice que deseja consultar os vizinhos: ", 0,
                              grafo->getQuantidadeVertices());

        // O vertice esta dentro da listaPrincipal que é feita de NoVertice e dentro do Novertice
        // que esta o vertice
        Vertice inicioV = grafo->listaPrincipal[verticei].vertice;

        vector<Vertice> vizinho = grafo->getVizinhos(inicioV);
        if (vizinho.empty()) {
            cout << "Sem vizinhos\n";
        } else {
            cout << endl << "Vizinhos de " << inicioV.toString() <<": ";
            for (const Vertice& v : vizinho) {
                cout << v.toString() << " ";
            }
            cout << endl << endl;
        }
    }

    void consultarSucessoresVertice() {
        cout << "\n> Menu > Lista > Consultar Fecho Transitivo Direto de Vértice" << endl << endl;
           // Variavel para indicar a posição do vertice no array
        int verticei;

        grafo->imprimir();

        //pegando a posição dos vertices na Lista
        verticei = lerInteiro("Digite o número do vértice que deseja consultar: ", 0,grafo->getQuantidadeVertices());

        //O vertice esta dentro da listaPrincipal que é feita de NoVertice e dentro do Novertice que esta o vertice
        Vertice inicioV = grafo->listaPrincipal[verticei].vertice;
        
        vector<Vertice> vizinho = grafo->fechoTransitivoDireto(inicioV);
        if (vizinho.empty()) {
            cout << "Vazio\n";
        } else {
            cout << endl << "Fecho Transito Direto de " << inicioV.toString() <<": ";
            for (const Vertice& v : vizinho) {
                cout << v.toString() << " ";
            }
            cout << endl << endl;
        }
    }

    void consultarPredecessoresVertice() {
        cout << "\n> Menu > Lista > Consultar Fecho Transitivo Inverso de Vértice" << endl << endl;
           // Variavel para indicar a posição do vertice no array
        int verticei;

        grafo->imprimir();

        //pegando a posição dos vertices na Lista
        verticei = lerInteiro("Digite o número do vértice que deseja consultar: ", 0,grafo->getQuantidadeVertices());

        //O vertice esta dentro da listaPrincipal que é feita de NoVertice e dentro do Novertice que esta o vertice
        Vertice inicioV = grafo->listaPrincipal[verticei].vertice;
        
        vector<Vertice> vizinho = grafo->fechoTransitivoInverso(inicioV);
        if (vizinho.empty()) {
            cout << "Vazio\n";
        } else {
            cout << endl << "Fecho Transito Inverso de " << inicioV.toString() <<": ";
            for (const Vertice& v : vizinho) {
                cout << v.toString() << " ";    
            }
            cout << endl << endl;
        }
    }

    void removeGrafo() {
        cout << "\n> Menu > Lista > Remover Grafo" << endl << endl;

        bool controle = lerBoolean("Você confirma a exclusão do grafo? (S/N): ");

        if (controle) {
            delete grafo;
            grafo = NULL;
            cout << "\nGrafo removido com sucesso." << endl;
        }
    }

    void buscaEmLargura(){
        cout << "\n> Menu > Lista > Busca em Largura - BFS" << endl << endl;
        imprimeGrafo();
        int verticei = lerInteiro("Digite o número do vértice para começar o caminho: ", 0,grafo->getQuantidadeVertices());
        Vertice inicioV = grafo->listaPrincipal[verticei].vertice;

        vector<Vertice> resposta = grafo->buscaEmLargura(inicioV);

        if(resposta.empty()){
            cout << "Caminho vazio" << endl << endl;
        } else {
            cout << endl << "BFS a partir de " << inicioV.toString() <<": ";
            for (const Vertice& v : resposta) {
                cout << v.toString() << " ";    
            }
            cout << endl << endl;
        }
    }

    void buscaEmProfundidade(){
        cout << "\n> Menu > Lista > Busca em profundidade - DFS" << endl << endl;
        imprimeGrafo();

        int verticei = lerInteiro("Digite o número do vértice para começar o caminho: ", 0,grafo->getQuantidadeVertices());
        Vertice inicioV = grafo->listaPrincipal[verticei].vertice;

        vector<Vertice> resposta = grafo->buscaEmProfundidade(inicioV);

        if(resposta.empty()){
            cout << "Caminho vazio" << endl << endl;
        } else {
            cout << endl << "DFS a partir de " << inicioV.toString() <<": ";
            for (const Vertice& v : resposta) {
                cout << v.toString() << " ";    
            }
            cout << endl << endl;
        }
    }

    void imprimeGrafo() {
        grafo->imprimir();
    }
};
