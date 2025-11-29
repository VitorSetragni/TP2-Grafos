#include "GrafoMatriz.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "../IGrafo.hpp"
#include "../utils/utils.hpp"

using namespace std;

// Função auxiliar para imprimir uma string centralizada dentro de uma largura específica
void imprimirCentralizado(const string &texto, int largura) {
    int espacos = largura - texto.length();
    if (espacos < 0) espacos = 0;
    int pad_esquerdo = espacos / 2;
    int pad_direito = espacos - pad_esquerdo;

    cout << string(pad_esquerdo, ' ') << texto << string(pad_direito, ' ');
}

// Sobrecarga da função para imprimir um inteiro centralizado (converte para string)
void imprimirCentralizado(int numero, int largura) {
    imprimirCentralizado(to_string(numero), largura);
}

// Validar se um vértice está dentro dos limites
bool GrafoMatriz::verticeValido(int v) const {
    return (0 <= v && v < numVertices);
}

// Construtor: cria um grafo com um número fixo de vértices
GrafoMatriz::GrafoMatriz(int totalVertices, bool direcionado, bool verticePonderado,
                         bool arestaPonderada, bool verticeRotulado, bool arestaRotulada) {
    // Testar se o número de vértices é válido
    if (totalVertices <= 0) {
        throw invalid_argument("O número de vértices deve ser positivo.");
    }

    // Atribuir valores iniciais
    this->numVertices = totalVertices;
    this->numArestas = 0;

    // Atribuir variáveis de controle
    this->direcionado = direcionado;
    this->verticePonderado = verticePonderado;
    this->arestaPonderada = arestaPonderada;
    this->verticeRotulado = verticeRotulado;
    this->arestaRotulada = arestaRotulada;

    // Inicializa a matriz com tamanho N x N preenchida com 0 (ou seja, sem arestas)
    matrizAdjacencias.resize(numVertices, vector<int>(numVertices, 0));

    // Se os vértices do grafo forem ponderados, criar o vector com peso padrão 1
    if (this->verticePonderado) {
        verticesPesos.resize(numVertices, 1);
    }

    // Se os vértices do grafo forem rotulados, criar o Hash Map com strings vazias
    if (this->verticeRotulado) {
        for (int i = 0; i < numVertices; i++) {
            verticesRotulos[i] = "";
        }
    }

    // Se as arestas do grafo forem rotuladas, criar a matriz dos rótulos preenchida com strings
    // vazias
    if (this->arestaRotulada) {
        arestasRotulos.resize(numVertices, vector<string>(numVertices, ""));
    }
}

// Construtor: cria um grafo sem um número fixo de vértices
GrafoMatriz::GrafoMatriz(bool direcionado, bool verticePonderado, bool arestaPonderada,
                         bool verticeRotulado, bool arestaRotulada) {
    // Atribuir valores iniciais
    this->numVertices = 0;
    this->numArestas = 0;

    // Atribuir variáveis de controle
    this->direcionado = direcionado;
    this->verticePonderado = verticePonderado;
    this->arestaPonderada = arestaPonderada;
    this->verticeRotulado = verticeRotulado;
    this->arestaRotulada = arestaRotulada;
}

// Destrutor: padrão
GrafoMatriz::~GrafoMatriz() {
    matrizAdjacencias.clear();
    verticesPesos.clear();
    verticesRotulos.clear();
    arestasRotulos.clear();
    this->numVertices = 0;
    this->numArestas = 0;
    this->direcionado = false;
    this->verticePonderado = false;
    this->arestaPonderada = false;
    this->verticeRotulado = false;
    this->arestaRotulada = false;
};

// --- Implementar as funções da interface ---

int GrafoMatriz::getQuantidadeVertices() const {
    return numVertices;
}

int GrafoMatriz::getQuantidadeArestas() const {
    return numArestas;
}

bool GrafoMatriz::adicionarVertice(int v) {
    return adicionarVertice(v, 1, "");  // Peso padrão é 1 e rótulo padrão é string vazia
}

bool GrafoMatriz::adicionarVertice(int v, int peso) {
    return adicionarVertice(v, peso, "");  // Rótulo padrão é string vazia
}

bool GrafoMatriz::adicionarVertice(int v, string label) {
    return adicionarVertice(v, 1, label);  // Peso padrão é 1
}

bool GrafoMatriz::adicionarVertice(int v, int peso, string label) {
    // O novo vértice terá o índice do tamanho atual da matriz.
    int novoIndice = this->numVertices;

    // Incrementar o contador de vértices ANTES de redimensionar.
    this->numVertices++;

    // Aumenta o número de linhas para o novo tamanho (de N para N+1) - A nova linha é criada vazia
    matrizAdjacencias.resize(this->numVertices);

    // Para cada linha (as N antigas e a 1 nova), redimensiona o número de colunas para o novo
    // tamanho, preenchendo com 0.
    for (auto &linha : matrizAdjacencias) {
        linha.resize(this->numVertices, 0);
    }

    // Se as arestas forem rotuladas, reestruturas a matriz de rótulos também
    if (this->arestaRotulada) {
        arestasRotulos.resize(this->numVertices);
        for (auto &linha : arestasRotulos) {
            linha.resize(this->numVertices, "");
        }
    }

    // Definir os atributos para o NOVO vértice usando o 'novoIndice'
    if (this->verticePonderado) {
        verticesPesos.push_back(peso);
    }

    if (this->verticeRotulado) {
        verticesRotulos[novoIndice] = label;
    }

    return true;
}

bool GrafoMatriz::adicionarAresta(int origem, int destino) {
    return adicionarAresta(origem, destino, 1);  // Peso padrão é 1
}

bool GrafoMatriz::adicionarAresta(int origem, int destino, int peso) {
    return adicionarAresta(origem, destino, peso, "");  // Rótulo padrão é string vazia
}

bool GrafoMatriz::adicionarAresta(int origem, int destino, string label) {
    return adicionarAresta(origem, destino, 1, label);  // Peso padrão é 1
}

bool GrafoMatriz::adicionarAresta(int origem, int destino, int peso, string label) {
    // Testar se os vértices existem, se o peso não é nulo e se a aresta JÁ NÃO EXISTE
    if (!verticeValido(origem) || !verticeValido(destino) || peso == 0 ||
        matrizAdjacencias[origem][destino] != 0) {
        return false;
    }

    // Adicionar a aresta com o seu peso (caso o grafo não seja ponderado, o seu peso será 1 por
    // padrão)
    matrizAdjacencias[origem][destino] = peso;

    // Se o grafo for não-direcionado, inserir a aresta e o seu rótulo no sentido inverso também
    if (!this->direcionado) {
        matrizAdjacencias[destino][origem] = peso;
    }

    // Se o grafo for rotulado, alterar o nome da aresta na matriz já construída anteriormente
    if (this->arestaRotulada) {
        arestasRotulos[origem][destino] = label;
        if (!this->direcionado) {
            arestasRotulos[destino][origem] = label;
        }
    }

    // Incrementar o número de arestas
    numArestas++;

    // Retornar status de sucesso
    return true;
}

// bool removerVertice(int v) override {
//     return verticeValido(v);
// }

/**
 * @bug Erro na variável 'iNovo' (Declaração Ausente)
 */

bool GrafoMatriz::removerVertice(int v) {
    // Testar se a posição é válida
    if (!verticeValido(v)) {
        return false;
    }

    // Criar as novas estruturas de dados menores
    int novoTamanho = numVertices - 1;

    vector<vector<int>> novaMatrizAdjacencias(novoTamanho, vector<int>(novoTamanho, 0));
    vector<vector<string>> novosRostulosArestas;

    if (arestaRotulada) {
        novosRostulosArestas.resize(novoTamanho, vector<string>(novoTamanho, ""));
    }

    // Copiar os dados relevantes, pulando o vértice 'v'
    int iNovo = 0;  // Contador para as linhas da nova matriz

    for (int i = 0; i < numVertices; ++i) {
        if (i == v) continue;  // Pula a linha do vértice removido

        int jNovo = 0;  // Contador para as colunas da nova matriz
        for (int j = 0; j < numVertices; ++j) {
            if (j == v) continue;  // Pula a coluna do vértice removido

            // Copia o valor da matriz de adjacências e dos rótulos de aresta
            novaMatrizAdjacencias[iNovo][jNovo] = matrizAdjacencias[i][j];
            if (arestaRotulada) {
                novosRostulosArestas[iNovo][jNovo] = arestasRotulos[i][j];
            }
            jNovo++;
        }
        iNovo++;
    }

    // Se os vértices forem ponderados, remover o elemento na posição 'v'
    if (verticePonderado) {
        verticesPesos.erase(verticesPesos.begin() + v);
    }

    // Se os vértices forem rotulados, remover 'v' do mapa e reindexar todas as chaves maiores que
    // 'v'
    if (verticeRotulado) {
        verticesRotulos.erase(v);  // Remove o rótulo do vértice v
        unordered_map<int, string> novosRotulos;
        for (auto const &[chave, valor] : verticesRotulos) {
            int novaChave = (chave < v) ? chave : chave - 1;  // Desloca os índices maiores que v
            novosRotulos[novaChave] = valor;
        }
        verticesRotulos = novosRotulos;  // Substitui o map antigo pelo reindexado
    }

    // Atribui a nova matriz de adjacências
    matrizAdjacencias = novaMatrizAdjacencias;
    if (arestaRotulada) {
        arestasRotulos = novosRostulosArestas;
    }

    // Decrementa o número de vértices
    numVertices--;

    // Recalcula o número de arestas (a forma mais segura para evitar erros de contagem)
    int contagemArestas = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = (direcionado ? 0 : i); j < numVertices; ++j) {
            if (matrizAdjacencias[i][j] != 0) {
                contagemArestas++;
            }
        }
    }
    this->numArestas = contagemArestas;

    return true;
}

bool GrafoMatriz::removerAresta(int origem, int destino) {
    // Testar se os vértices são válidos e se há aresta para remover
    if (!verticeValido(origem) || !verticeValido(destino) ||
        matrizAdjacencias[origem][destino] == 0) {
        return false;
    }

    // Remover a aresta da matriz
    matrizAdjacencias[origem][destino] = 0;

    if (this->direcionado == false) {
        matrizAdjacencias[destino][origem] = 0;
    }

    if (this->arestaRotulada) {
        arestasRotulos[origem][destino] = "";
        if (!this->direcionado) {
            arestasRotulos[destino][origem] = "";
        }
    }

    numArestas--;
    return true;
}

bool GrafoMatriz::existeVertice(int v) const {
    return verticeValido(v);
}

bool GrafoMatriz::existeAresta(int origem, int destino) const {
    if (!verticeValido(origem) || !verticeValido(destino)) {
        return false;
    }
    return matrizAdjacencias[origem][destino] != 0;
}

vector<int> GrafoMatriz::getVizinhos(int v) const {
    // Definir vector com todos os vizinhos do vértice
    vector<int> vizinhos;

    // Se o vértice não existe, retorna um vector vazio
    if (!verticeValido(v)) {
        return vizinhos;
    }

    // Percorrer a linha da matriz correspondente ao vértice 'v'
    for (int j = 0; j < numVertices; ++j) {
        if (matrizAdjacencias[v][j] != 0) {
            vizinhos.push_back(j);
        }
    }

    return vizinhos;
}

// Fecho transitivo direto (Todos os alcançados pelo vértice 'v', incluindo ele) - DFS (Busca em
// Profundidade)
vector<int> GrafoMatriz::fechoTransitivoDireto(int v) const{
    vector<int> sucessores;
    vector<bool> visitados(numVertices, false);
    return fechoTransitivoDireto(v, visitados);
}

vector<int> GrafoMatriz::fechoTransitivoDireto(int v, vector<bool> &visitados) const {
    vector<int> sucessores;

    // Marca o vértice como visitado
    visitados[v] = true;

    sucessores.push_back(v);

    for (int i = 0; i < numVertices; i++) {
        if (matrizAdjacencias[v][i] != 0 && !visitados[i]) {
            // Chama recursivamente para explorar os sucessores do sucessor - DFS
            vector<int> subSucessores = fechoTransitivoDireto(i, visitados);

            /* Junta os resultado
                for (int x : subSucessores)
                sucessores.push_back(x);
            */
            sucessores.insert(sucessores.end(), subSucessores.begin(), subSucessores.end());
        }
    }
    return sucessores;
}

// Fecho transitivo inverso (Todos que poderiam alcançar o vértice 'v', incluindo ele) - DFS
// (Busca em Profundidade)
vector<int> GrafoMatriz::fechoTransitivoInverso(int v) const {
    vector<int> predecessores;
    vector<bool> visitados(numVertices, false);

    return fechoTransitivoInverso(v, visitados);
}

vector<int> GrafoMatriz::fechoTransitivoInverso(int v, vector<bool> &visitados) const {
    vector<int> predecessores;

    // Marca o vértice como visitado
    visitados[v] = true;

    predecessores.push_back(v);

    for (int i = 0; i < numVertices; i++) {
        if (matrizAdjacencias[i][v] != 0 && !visitados[i]) {
            predecessores.push_back(v);

            // Chama recursivamente para explorar os sucessores do sucessor - DFS
            vector<int> subPredecessores = fechoTransitivoInverso(i, visitados);

            /* Junta os resultado
                for (int x : subSucessores)
                sucessores.push_back(x);
            */
            predecessores.insert(predecessores.end(), subPredecessores.begin(),
                                 subPredecessores.end());
        }
    }
    return predecessores;
}

/**
 * Busca em profundidade (DFS) do grafo.
 *
 * O vetor de cores é utilizado para marcar os vértices como branco (não visitado),
 * vermelho (visitado) ou preto (visitado e finalizado).O vetor de tempos é utilizado para
 * armazenar os tempos de início e fim de cada vértice.
 *
 * @return Vetor com os tempos de início e fim de cada vértice.
 */

vector<vector<int>> GrafoMatriz::buscaEmProfundidade(int v) const {
    // Definir vector com todos os vizinhos do grafo como branco
    vector<cores> coresVertices(numVertices, cores::BRANCO);
    vector<vector<int>> temposVertices(numVertices, vector<int>(2, 0));

    for (int i = 0; i < numVertices; i++) {
        if (coresVertices[i] == cores::BRANCO) {
            buscaEmProfundidade(i, coresVertices, temposVertices);
        }
    }

    tempo = 0;

    return temposVertices;
}

vector<vector<int>> GrafoMatriz::buscaEmProfundidade(int i, vector<cores> &coresVertices,
                                                     vector<vector<int>> &temposVertices) const {
    coresVertices[i] = cores::VERMELHO;
    temposVertices[i][0] = ++tempo;
    for (int j = 0; j < numVertices; j++) {
        if (matrizAdjacencias[i][j] != 0 && coresVertices[j] == cores::BRANCO) {
            buscaEmProfundidade(j, coresVertices, temposVertices);
        }
    }

    coresVertices[i] = cores::PRETO;
    temposVertices[i][1] = ++tempo;
    return temposVertices;
}

/**
 * Busca em Largura não ponderada e ponderada
 * Caso a matriz seja ponderada ele vai entrar no algoritmo de Dijkistra, caso não ele entra na
 * busca em largura
 * @param v_inicial O vértice de onde a busca começará.
 * @return Um vetor de inteiros onde o valor na posição 'i' é a menor
 * distância (soma dos pesos ou número de arestas) de 'v_inicial' até 'i'.
 */
vector<int> GrafoMatriz::buscas(int v_inicial) const {
    if (!verticeValido(v_inicial)) {
        return {};  // Retorna um vetor vazio se o vértice não existir.
    }

    const int INFINITO = numeric_limits<int>::max();

    if (arestaPonderada == true) {
        // --- Início do Algoritmo de Dijkstra ---
        vector<int> distancias(numVertices, INFINITO);
        distancias[v_inicial] = 0;

        // Fila de Prioridade para armazenar {distância, vértice}
        using Par = pair<int, int>;
        priority_queue<Par, vector<Par>, greater<Par>> fila_prioridade;
        fila_prioridade.push({0, v_inicial});

        while (!fila_prioridade.empty()) {
            int u = fila_prioridade.top().second;
            int dist_u = fila_prioridade.top().first;
            fila_prioridade.pop();

            if (dist_u > distancias[u]) {
                continue;
            }

            // Itera sobre todos os vizinhos
            for (int v = 0; v < numVertices; ++v) {
                // Se existe aresta de u para v
                if (matrizAdjacencias[u][v] != 0) {
                    int peso_aresta = matrizAdjacencias[u][v];
                    // "Relaxamento": Tenta encurtar o caminho para o vizinho 'v'
                    if (distancias[u] != INFINITO && distancias[u] + peso_aresta < distancias[v]) {
                        distancias[v] = distancias[u] + peso_aresta;
                        fila_prioridade.push({distancias[v], v});
                    }
                }
            }
        }
        return distancias;

    }

    else {
        // --- Início da Busca em Largura (BFS) para distâncias ---
        vector<int> distancias(numVertices, INFINITO);
        queue<int> fila;

        distancias[v_inicial] = 0;
        fila.push(v_inicial);

        while (!fila.empty()) {
            int u = fila.front();
            fila.pop();

            // Usa a função getVizinhos para encontrar os adjacentes
            vector<int> vizinhos = getVizinhos(u);
            for (int v : vizinhos) {
                // Se o vizinho ainda não foi alcançado (distância infinita)
                if (distancias[v] == INFINITO) {
                    // A distância é a do pai + 1 (pois cada aresta vale 1)
                    distancias[v] = distancias[u] + 1;
                    fila.push(v);
                }
            }
        }
        return distancias;
    }
}

void GrafoMatriz::imprimir() const {
    imprimirMatriz();
    imprimirRotulosVertice();
    imprimirRotulosArestas();
    cout << endl;  // Adiciona uma linha extra no final para espaçamento
}

void GrafoMatriz::imprimirMatriz() const {
    // Calcular a largura dinâmica das colunas
    int max_valor = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (matrizAdjacencias[i][j] > max_valor) {
                max_valor = matrizAdjacencias[i][j];
            }
        }
    }

    // A largura deve acomodar o maior peso ou o maior índice de vértice
    int largura_num = max(to_string(max_valor).length(), to_string(numVertices).length());
    int largura_coluna = largura_num + 2;  // Adiciona 2 para um espaço de cada lado
    int largura_primeira_coluna = 9;       // tamanho de " Vértice "

    // Linha superior da borda
    cout << "+-" << string(largura_primeira_coluna, '-') << "-+";
    for (int i = 0; i < numVertices; ++i) {
        cout << string(largura_coluna, '-') << "+";
    }
    cout << endl;

    // Cabeçalho da tabela
    cout << "|  ";
    imprimirCentralizado("Vértice", largura_primeira_coluna);
    cout << " |";
    for (int i = 0; i < numVertices; ++i) {
        imprimirCentralizado(i, largura_coluna);
        cout << "|";
    }
    cout << endl;

    // Linha separadora do cabeçalho
    cout << "+-" << string(largura_primeira_coluna, '-') << "-+";
    for (int i = 0; i < numVertices; ++i) {
        cout << string(largura_coluna, '-') << "+";
    }
    cout << endl;

    // Corpo da Matriz
    for (int i = 0; i < numVertices; ++i) {
        cout << "| ";
        imprimirCentralizado(i, largura_primeira_coluna);
        cout << " |";
        for (int j = 0; j < numVertices; ++j) {
            imprimirCentralizado(matrizAdjacencias[i][j], largura_coluna);
            cout << "|";
        }
        cout << endl;
    }

    // Linha inferior da borda
    cout << "+-" << string(largura_primeira_coluna, '-') << "-+";
    for (int i = 0; i < numVertices; ++i) {
        cout << string(largura_coluna, '-') << "+";
    }
    cout << endl;
}

void GrafoMatriz::imprimirRotulosVertice() const {
    // Só imprime a tabela se o grafo for rotulado e tiver vértices
    if (!this->verticeRotulado || numVertices == 0) {
        return;
    }

    // Largura da coluna "Vértice"
    size_t largura_col_vertice = max(string("Vértice").length(), to_string(numVertices).length());
    largura_col_vertice += 2;  // Adiciona espaços para preenchimento

    // Largura da coluna "Rótulo" (encontra o rótulo mais longo)
    size_t largura_col_rotulo = string("Rótulo").length();
    for (int i = 0; i < numVertices; ++i) {
        if (verticesRotulos.at(i).length() > largura_col_rotulo) {
            largura_col_rotulo = verticesRotulos.at(i).length();
        }
    }
    largura_col_rotulo += 2;  // Adiciona espaços para preenchimento

    cout << "\n------- Rótulos dos Vértices -------" << endl;

    // Borda superior
    cout << "+-" << string(largura_col_vertice, '-') << "-+-" << string(largura_col_rotulo, '-')
         << "-+" << endl;

    // Cabeçalho
    cout << "| ";
    imprimirCentralizado("Vértice", largura_col_vertice);
    cout << "  | ";
    imprimirCentralizado("Rótulo", largura_col_rotulo);
    cout << "  |" << endl;

    // Linha separadora do cabeçalho
    cout << "+-" << string(largura_col_vertice, '-') << "-+-" << string(largura_col_rotulo, '-')
         << "-+" << endl;

    // Corpo da tabela
    for (int i = 0; i < numVertices; ++i) {
        cout << "| ";
        imprimirCentralizado(i, largura_col_vertice);
        cout << " | ";
        imprimirCentralizado(verticesRotulos.at(i), largura_col_rotulo);
        cout << " |" << endl;
    }

    // Borda inferior
    cout << "+-" << string(largura_col_vertice, '-') << "-+-" << string(largura_col_rotulo, '-')
         << "-+" << endl;
}

void GrafoMatriz::imprimirRotulosArestas() const {
    // Só imprime a tabela se o grafo for rotulado e tiver arestas
    if (!this->arestaRotulada || numArestas == 0) {
        return;
    }

    // Verifica se existe pelo menos um rótulo para ser impresso
    bool temRotulo = false;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (!arestasRotulos[i][j].empty()) {
                temRotulo = true;
                break;
            }
        }
        if (temRotulo) break;
    }

    if (!temRotulo) return;  // Se nenhuma aresta tiver rótulo, não imprime a tabela

    // Largura da coluna "Aresta"
    string exemplo_aresta = to_string(numVertices) + " -> " + to_string(numVertices);
    size_t largura_col_aresta = max(string("Aresta").length(), exemplo_aresta.length());
    largura_col_aresta += 2;

    // Largura da coluna "Rótulo"
    size_t largura_col_rotulo = string("Rótulo").length();
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (arestasRotulos[i][j].length() > largura_col_rotulo) {
                largura_col_rotulo = arestasRotulos[i][j].length();
            }
        }
    }
    largura_col_rotulo += 2;

    // Desenhar a Tabela

    cout << "\n-------- Rótulos das Arestas --------" << endl;

    // Borda superior
    cout << "+-" << string(largura_col_aresta, '-') << "-+-" << string(largura_col_rotulo, '-')
         << "-+" << endl;

    // Cabeçalho
    cout << "| ";
    imprimirCentralizado("Aresta", largura_col_aresta);
    cout << " |  ";
    imprimirCentralizado("Rótulo", largura_col_rotulo);
    cout << " |" << endl;

    // Linha separadora do cabeçalho
    cout << "+-" << string(largura_col_aresta, '-') << "-+-" << string(largura_col_rotulo, '-')
         << "-+" << endl;

    // Corpo da tabela
    for (int i = 0; i < numVertices; ++i) {
        for (int j = (direcionado ? 0 : i); j < numVertices; ++j) {
            if (matrizAdjacencias[i][j] != 0 && !arestasRotulos[i][j].empty()) {
                string aresta_str = to_string(i) + (direcionado ? " -> " : " - ") + to_string(j);
                cout << "| ";
                imprimirCentralizado(aresta_str, largura_col_aresta);
                cout << " | ";
                imprimirCentralizado(arestasRotulos[i][j], largura_col_rotulo);
                cout << " |" << endl;
            }
        }
    }

    // Borda inferior
    cout << "+-" << string(largura_col_aresta, '-') << "-+-" << string(largura_col_rotulo, '-')
         << "-+" << endl;
}
