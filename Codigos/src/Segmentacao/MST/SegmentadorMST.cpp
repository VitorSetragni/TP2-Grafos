#include "SegmentadorMST.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

// Função auxiliar para marcar todos os nós de um componente conexo
void bfsMarcarComponente(GrafoLista* floresta, int raiz, int idComponente, vector<int>& mapaComponentes) {
    queue<int> fila;
    fila.push(raiz);
    mapaComponentes[raiz] = idComponente;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        // Acessa o nó no grafo retornado pelo Kruskal
        NoVertice* noU = &floresta->listaPrincipal[u]; 
        
        // Percorre os vizinhos (que agora são apenas os nós da mesma região)
        for (const auto& adj : noU->getArestas()) {
            int v = adj.getId();
            
            // Se ainda não foi visitado (ou seja, mapeado)
            if (mapaComponentes[v] == -1) {
                mapaComponentes[v] = idComponente;
                fila.push(v);
            }
        }
    }
}

// Estrutura simples para facilitar a ordenação das arestas
struct ArestaSimples {
    int u;
    int v;
    double peso;

    // Sobrecarga para o std::sort
    bool operator<(const ArestaSimples& outra) const {
        return peso < outra.peso;
    }
};

// DSU Especializado para Felzenszwalb (rastreia maxPeso e tamanho)
class DSUFelzenszwalb {
    private:
        struct Subset {
            int pai;
            int rank;
            int tamanho;       // |C|
            double maxPeso;    // Int(C) - Maior peso na MST interna deste componente
        };
        vector<Subset> subsets;

    public:
        DSUFelzenszwalb(int n) {
            subsets.resize(n);
            for (int i = 0; i < n; ++i) {
                subsets[i].pai = i;
                subsets[i].rank = 0;
                subsets[i].tamanho = 1;
                subsets[i].maxPeso = 0.0; // Inicialmente, componente unitário tem peso interno 0
            }
        }

        int find(int i) {
            if (subsets[i].pai != i)
                subsets[i].pai = find(subsets[i].pai);

            return subsets[i].pai;
        }

        void unite(int i, int j, double pesoAresta) {
            int raiz_i = find(i);
            int raiz_j = find(j);

            if (raiz_i != raiz_j) {
                // União por Rank
                if (subsets[raiz_i].rank < subsets[raiz_j].rank) {
                    subsets[raiz_i].pai = raiz_j;
                    subsets[raiz_j].tamanho += subsets[raiz_i].tamanho;

                    // O novo peso máximo é o max dos anteriores ou o peso da aresta que conectou
                    subsets[raiz_j].maxPeso = max({subsets[raiz_j].maxPeso, subsets[raiz_i].maxPeso, pesoAresta});
                } else {
                    subsets[raiz_j].pai = raiz_i;
                    subsets[raiz_i].tamanho += subsets[raiz_j].tamanho;
                    subsets[raiz_i].maxPeso = max({subsets[raiz_i].maxPeso, subsets[raiz_j].maxPeso, pesoAresta});
                    
                    if (subsets[raiz_i].rank == subsets[raiz_j].rank) {
                        subsets[raiz_i].rank++;
                    }
                }
            }
        }

        int getTamanho(int i) { return subsets[find(i)].tamanho; }
        double getMaxPeso(int i) { return subsets[find(i)].maxPeso; }
};

// Retorna o valor MInt
double SegmentadorMST::calcularMInt(double maxC1, int tamC1, double maxC2, int tamC2, double k) {
    // Tau(C) = k / |C|
    double tau1 = k / tamC1;
    double tau2 = k / tamC2;

    // MInt(C1, C2) = min(Int(C1) + Tau(C1), Int(C2) + Tau(C2))
    double minInternalDifference = min(maxC1 + tau1, maxC2 + tau2);

    // Predicado: Peso da aresta <= MInt
    return minInternalDifference;
}

// Função auxiliar para extrair e ordenar arestas do GrafoLista
vector<SegmentadorMST::ArestaSimples> SegmentadorMST::buscarListaDeArestasOrdenadas(GrafoLista* grafo) {
    vector<SegmentadorMST::ArestaSimples> arestas;
    int numVertices = grafo->getQuantidadeVertices(); 

    // Otimização de reserva de memória para evitar realocações (Grade 4-vizinhos ~ 2*N arestas)
    arestas.reserve(numVertices * 2);

    // Itera sobre todos os vértices u
    for (int u = 0; u < numVertices; u++) {
        NoVertice* noU = &grafo->listaPrincipal[u];
        
        // Itera sobre a forward_list de adjacências
        for (const auto& aresta : noU->getArestas()) {
            int v = aresta.getId();
            double peso = aresta.getPeso();

            // Pega apenas uma instância de uma aresta quando u < v para evitar duplicatas
            if (u < v) {
                arestas.push_back({u, v, peso});
            }
        }
    }

    // Ordena as arestas por peso (crescente)
    sort(arestas.begin(), arestas.end());
    
    return arestas;
}

// Algoritmo Principal
GrafoLista* SegmentadorMST::kruskalCondicional(GrafoLista* grafoEntrada, double k) {
    cout << "Iniciando Segmentacao MST (Felzenszwalb)..." << endl;

    int numVertices = grafoEntrada->getQuantidadeVertices();
    
    // Busca arestas ordenadas
    vector<ArestaSimples> arestas = buscarListaDeArestasOrdenadas(grafoEntrada);
    
    // Inicializa o DSU Customizado
    DSUFelzenszwalb dsu(numVertices);

    // Cria o grafo de saída
    GrafoLista* floresta = new GrafoLista(
        false, // simples
        false, // direcionado (false para floresta de árvores não direcionadas)
        true,  // ponderado vértices (copiar do original se necessário)
        true,  // ponderado arestas
        false, // rotulado vértices
        false, // rotulado arestas
        numVertices
    );

    // Loop principal (Kruskal Condicionado)
    int arestasAdicionadas = 0;

    for (const auto& aresta : arestas) {
        // Idenfifica os vértices adjacentes da aresta e o seu peso
        int u = aresta.u;
        int v = aresta.v;
        double w = aresta.peso;

        // Identifica a raiz do UnionFind
        int raizU = dsu.find(u);
        int raizV = dsu.find(v);

        // Se forem diferentes, a aresta deve ser adicionada ao grafo de saída
        if (raizU != raizV) {
            // Verifica condição de Felzenszwalb
            double maxC1 = dsu.getMaxPeso(raizU);
            int tamC1 = dsu.getTamanho(raizU);
            
            double maxC2 = dsu.getMaxPeso(raizV);
            int tamC2 = dsu.getTamanho(raizV);

            // Testa se a aresta é menor variabilidade interna dos componentes
            if (w < calcularMInt(maxC1, tamC1, maxC2, tamC2, k)) {                
                // Une no DSU
                dsu.unite(raizU, raizV, w);
                
                // Adiciona ida e volta pois o resultado é não-direcionado
                floresta->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), w);
                floresta->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), w);
                
                arestasAdicionadas++;
            }
        }
    }

    cout << "Segmentacao Concluida." << endl;
    cout << "Arestas na floresta original: " << arestas.size() << endl;
    cout << "Arestas mantidas na segmentacao: " << arestasAdicionadas << endl;

    return floresta;
}

// Executa o algoritmo de Felzenszwalb
ResultadoSegmentacao SegmentadorMST::segmentar(GrafoLista* grafo, double k, int minSize) {
    // Isso retorna um grafo onde as arestas só existem entre pixels da mesma região
    GrafoLista* floresta = kruskalCondicional(grafo, k);

    if (floresta == nullptr) {
        cerr << "[ERRO] Kruskal retornou nulo." << endl;
        return { {}, 0 };
    }

    int numVertices = grafo->getQuantidadeVertices();
    
    // Prepara a estrutura de resposta
    ResultadoSegmentacao resultado;
    resultado.componentes.assign(numVertices, -1); // Inicializa com -1 (não visitado)
    resultado.numComponentes = 0;

    // Identifica de componentes conexsos
    // Percorre todos os pixels. Se encontrar um não visitado, é o início de um novo componente
    for (int i = 0; i < numVertices; i++) {
        if (resultado.componentes[i] == -1) {
            // Inicia uma busca em largura (BFS) na FLORESTA para marcar todo o componente
            bfsMarcarComponente(floresta, i, resultado.numComponentes, resultado.componentes);
            
            // Incrementa o ID para o próximo componente
            resultado.numComponentes++;
        }
    }

    // Limpar a memória
    delete floresta; 

    return resultado;
}