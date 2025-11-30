#include "SegmentadorMSA.hpp"
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

const double INF = numeric_limits<double>::max();

// BFS Otimizada (Memória)
void SegmentadorMSA::bfsMarcarComponente(const vector<vector<int>>& adj, int raiz, int idComponente, vector<int>& mapa, vector<bool>& visitado) {
    queue<int> fila;
    fila.push(raiz);
    visitado[raiz] = true;
    mapa[raiz] = idComponente;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v : adj[u]) {
            if (!visitado[v]) {
                visitado[v] = true;
                mapa[v] = idComponente;
                fila.push(v);
            }
        }
    }
}

// Núcleo Recursivo Otimizado (Lógica Tarjan para Ciclos)
vector<int> SegmentadorMSA::executarEdmondsRecursivo(int numVertices, int raiz, vector<ArestaEdmonds>& arestas, int nivel) {
    
    // Log para monitorar (evita ansiedade do usuário)
    if (nivel == 0 || nivel % 50 == 0) {
        cout << "[Edmonds] Nivel: " << nivel << " | Vertices: " << numVertices << " | Arestas: " << arestas.size() << endl;
    }

    vector<int> arestasEscolhidas;
    
    // Passo 1: Seleção Gulosa (O(E))
    vector<int> menorArestaIdx(numVertices, -1);
    vector<double> menorPeso(numVertices, INF);

    for (int i = 0; i < (int)arestas.size(); i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        double w = arestas[i].peso;

        if (u != v && v != raiz) {
            if (w < menorPeso[v]) {
                menorPeso[v] = w;
                menorArestaIdx[v] = i;
            }
        }
    }

    // Passo 2: Detecção de Ciclos (Linear O(V))
    vector<int> grupo(numVertices, -1);
    vector<int> visitado(numVertices, -1);
    vector<int> noCiclo(numVertices, -1);
    int contaGrupos = 0;
    bool temCiclo = false;
    const int PRETO = -2;

    for (int i = 0; i < numVertices; i++) {
        if (i == raiz) continue;
        if (visitado[i] == PRETO) continue; // Caminho seguro, pula
        if (menorArestaIdx[i] == -1) continue; // Inalcançável

        int v = i;
        
        // Percorre o caminho "para trás" (seguindo os pais escolhidos)
        while (v != raiz && menorArestaIdx[v] != -1 && visitado[v] != i && visitado[v] != PRETO) {
            visitado[v] = i; // Marca como CINZA (pertence à trilha atual 'i')
            v = arestas[menorArestaIdx[v]].u; // Sobe para o pai
        }

        // Se parou porque encontrou 'i' (nó CINZA da mesma iteração), achamos um ciclo!
        if (v != raiz && menorArestaIdx[v] != -1 && visitado[v] == i) {
            temCiclo = true;
            int curr = v;
            // Marca todos os nós do ciclo com um novo Grupo ID
            while (grupo[curr] == -1) {
                grupo[curr] = contaGrupos;
                noCiclo[curr] = 1; 
                curr = arestas[menorArestaIdx[curr]].u;
                if (curr == v) break;
            }
            contaGrupos++;
        }

        // Backtracking: Marca o caminho percorrido como PRETO para não reprocessar
        int u = i;
        while (u != v && u != raiz && menorArestaIdx[u] != -1 && visitado[u] != PRETO) {
            int prox = arestas[menorArestaIdx[u]].u;
            visitado[u] = PRETO;
            u = prox;
        }
        // Marca o nó final também, se não for raiz
        if (v != raiz && visitado[v] != PRETO) visitado[v] = PRETO;
    }

    // Passo 3: Base da Recursão (Sem ciclos)
    if (!temCiclo) {
        for (int i = 0; i < numVertices; i++) {
            if (i != raiz && menorArestaIdx[i] != -1) {
                arestasEscolhidas.push_back(arestas[menorArestaIdx[i]].idOriginal);
            }
        }
        return arestasEscolhidas;
    }

    // Passo 4: Contração
    for (int i = 0; i < numVertices; i++) {
        if (grupo[i] == -1) {
            grupo[i] = contaGrupos++;
        }
    }

    int numSuperVertices = contaGrupos;
    vector<ArestaEdmonds> novasArestas;
    novasArestas.reserve(arestas.size()); // Reserva memória
    
    // Constrói o grafo contraído
    for (const auto& aresta : arestas) {
        int u = aresta.u;
        int v = aresta.v;
        int gU = grupo[u];
        int gV = grupo[v];

        if (gU != gV) {
            double novoPeso = aresta.peso;
            // A mágica do Edmonds: Custo reduzido se o destino for um ciclo
            if (noCiclo[v] != -1) {
                novoPeso -= menorPeso[v];
            }
            novasArestas.push_back({gU, gV, novoPeso, aresta.idOriginal});
        }
    }

    // Chamada recursiva
    int novaRaiz = grupo[raiz];
    
    // Limpa memória local antes de recursão profunda se possível (opcional, mas bom pra stack)
    vector<int> arestasRecursao = executarEdmondsRecursivo(numSuperVertices, novaRaiz, novasArestas, nivel + 1);

    // Passo 5: Expansão (Otimizada com Map)
    vector<int> cicloRecebeuEntrada(numSuperVertices, -1);

    // Mapeia ID_Original -> Vértice_Destino_Real para acesso O(1)
    unordered_map<int, int> mapIdDestino;
    
    // Otimização: Popula o mapa apenas se necessário ou iterando 'arestas' uma vez.
    // Como precisamos do destino real de IDs arbitrários, iteramos 'todas' as arestas deste nível uma vez.
    for(const auto& a : arestas) {
        mapIdDestino[a.idOriginal] = a.v;
    }

    // Identifica quais super-vértices receberam arestas de fora
    for (int idOrig : arestasRecursao) {
        arestasEscolhidas.push_back(idOrig);
        
        // Descobre onde essa aresta entra no grafo atual
        if (mapIdDestino.count(idOrig)) {
            int vReal = mapIdDestino[idOrig];
            // Se entra num nó que faz parte de um ciclo, marcamos o ciclo
            if (noCiclo[vReal] != -1) {
                cicloRecebeuEntrada[grupo[vReal]] = idOrig;
            }
        }
    }

    // Adiciona as arestas internas (quebra o ciclo onde entrou a aresta externa)
    for (int i = 0; i < numVertices; i++) {
        if (i == raiz) continue;
        if (menorArestaIdx[i] == -1) continue;

        int gV = grupo[i];
        
        if (noCiclo[i] != -1) {
            bool deveAdicionar = true;
            
            // Se o ciclo recebeu entrada
            if (cicloRecebeuEntrada[gV] != -1) {
                int idExt = cicloRecebeuEntrada[gV];
                
                // Verifica se a aresta externa entra EXATAMENTE neste vértice 'i'
                if (mapIdDestino.count(idExt)) {
                    if (mapIdDestino[idExt] == i) {
                        deveAdicionar = false; // Quebra o ciclo aqui
                    }
                }
            }
            if (deveAdicionar) {
                arestasEscolhidas.push_back(arestas[menorArestaIdx[i]].idOriginal);
            }
        }
    }

    return arestasEscolhidas;
}

// Método Principal
ResultadoSegmentacao SegmentadorMSA::segmentar(GrafoLista* grafo, double k, int minSize) {
    cout << "Iniciando Segmentacao com Edmonds (Tarjan/Linear)..." << endl;

    if (grafo == nullptr) {
        cerr << "[ERRO] Grafo nulo no segmentar do SegmentadorMSA." << endl;
        return { {}, 0 };
    }
    
    int n = grafo->getQuantidadeVertices();
    vector<ArestaEdmonds> todasArestas;

    // Reserva agressiva para evitar realloc
    todasArestas.reserve(grafo->getQuantidadeArestas() + n);

    int idCounter = 0;

    // Extração Segura das Arestas
    { 
        // Escopo para destruir listaAdjOriginal rapidamente
        vector<NoVertice> listaAdjOriginal = grafo->getlistaPrincipal();

        for (int vertice = 0; vertice < n; vertice++) {
            const auto& arestas = listaAdjOriginal.at(vertice).getArestas();

            for (const auto& aresta : arestas) {
                int verticeAdjacente = aresta.getId();
                double peso = aresta.getPeso();
                todasArestas.push_back({vertice, verticeAdjacente, peso, idCounter++});
            }
        }
    } // Memória liberada aqui

    // Incluir uma raiz virtual
    int raizVirtual = n; 
    double maxPeso = 0;

    // Preencher as arestas com peso máximo
    for (const auto& a : todasArestas) {
        if (a.peso > maxPeso) {
            maxPeso = a.peso;
        }
    }

    double pesoRaiz = maxPeso + 1000.0;

    // Adicionar arestas que partem da raiz para todos os outros vértices do grafo
    for (int i = 0; i < n; i++) {
        todasArestas.push_back({raizVirtual, i, pesoRaiz, idCounter++});
    }

    cout << "Grafo preparado com " << todasArestas.size() << " arestas. Iniciando Recursão..." << endl;

    // Executa Edmonds
    vector<int> arestasSelecionadasIds = executarEdmondsRecursivo(n + 1, raizVirtual, todasArestas, 0);

    cout << "Recursao finalizada. Gerando componentes..." << endl;

    // Reconstrução (Economia de RAM)
    vector<vector<int>> adj(n);
    
    // Preencher um mapa auxiliar que mapeia idAresta : aresta
    unordered_map<int, ArestaEdmonds> mapaArestas;
    for (const auto& aresta : todasArestas) {
        mapaArestas[aresta.idOriginal] = aresta;
    }

    int arestasAdicionadas = 0;
    
    // Estatísticas de Peso (Debug)
    double minP = 1e9, maxP = -1;
    
    for (int id : arestasSelecionadasIds) {
        if (mapaArestas.find(id) == mapaArestas.end()) continue;

        ArestaEdmonds a = mapaArestas[id];
        
        // Ignore a aresta se um dos seus vértices adjacentes for a raiz virtual
        if (a.u == raizVirtual || a.v == raizVirtual) continue;

        // Atualiza o peso mínimo e o peso máximo encontrado
        if (a.peso < minP) minP = a.peso;
        if (a.peso > maxP) maxP = a.peso;

        // Adiciona somente arestas menores que o corte K
        if (a.peso <= k) {
            adj[a.u].push_back(a.v);
            adj[a.v].push_back(a.u); // Não direcionado para coloração de componentes
            arestasAdicionadas++;
        }
    }

    // Libera memória
    mapaArestas.clear();
    todasArestas.clear();
    todasArestas.shrink_to_fit();

    cout << "Estatisticas: Peso Min=" << minP << " Max=" << maxP << " K=" << k << endl;
    cout << "Arestas mantidas: " << arestasAdicionadas << endl;

    // Identificação de Componentes (BFS)
    ResultadoSegmentacao resultado;
    resultado.componentes.assign(n, -1);
    resultado.numComponentes = 0;
    vector<bool> visitado(n, false);

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            bfsMarcarComponente(adj, i, resultado.numComponentes, resultado.componentes, visitado);
            resultado.numComponentes++;
        }
    }
    
    cout << "Total de Componentes: " << resultado.numComponentes << endl;

    return resultado;
}
