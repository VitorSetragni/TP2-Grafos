#ifndef GRAFO_MATRIZ_HPP
#define GRAFO_MATRIZ_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "../../utils/utils.hpp"
#include "../IGrafo.hpp"

class GrafoMatriz : public IGrafo<int> {
   private:
    std::vector<std::vector<int>> matrizAdjacencias;
    std::vector<int> verticesPesos;
    std::unordered_map<int, std::string> verticesRotulos;
    std::vector<std::vector<std::string>> arestasRotulos;

    int numVertices;
    int numArestas;

    bool verticeValido(int v) const;

    // Funções auxiliares de DFS
    std::vector<int> fechoTransitivoDireto(int v, std::vector<bool>& visitados) const;
    std::vector<int> fechoTransitivoInverso(int v, std::vector<bool>& visitados) const;

    mutable int tempo = 0;
    std::vector<std::vector<int>> buscaEmProfundidade(int i,
        std::vector<cores>& coresVertices,
        std::vector<std::vector<int>>& temposVertices) const;

   public:
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    bool verticeRotulado;
    bool arestaRotulada;

    // Construtores
    GrafoMatriz(int totalVertices, bool direcionado, bool verticePonderado,
                bool arestaPonderada, bool verticeRotulado, bool arestaRotulada);

    GrafoMatriz(bool direcionado, bool verticePonderado,
                bool arestaPonderada, bool verticeRotulado, bool arestaRotulada);

    ~GrafoMatriz() override;

    // Implementação da interface
    int getQuantidadeVertices() const override;
    int getQuantidadeArestas() const override;

    bool adicionarVertice(int v) override;
    bool adicionarVertice(int v, double peso);
    bool adicionarVertice(int v, std::string label);
    bool adicionarVertice(int v, double peso, std::string label);

    bool adicionarAresta(int origem, int destino) override;
    bool adicionarAresta(int origem, int destino, double peso) override;
    bool adicionarAresta(int origem, int destino, std::string label);
    bool adicionarAresta(int origem, int destino, double peso, std::string label);

    bool removerVertice(int v) override;
    bool removerAresta(int origem, int destino) override;

    bool existeVertice(int v) const override;
    bool existeAresta(int origem, int destino) const override;

    std::vector<int> getVizinhos(int v) const override;

    std::vector<int> fechoTransitivoDireto(int v) const override;
    std::vector<int> fechoTransitivoInverso(int v) const override;

    std::vector<std::vector<int>> buscaEmProfundidade(int v) const;

    std::vector<int> buscas(int v_inicial) const;

    void imprimir() const override;

    // Funções de impressão
    void imprimirMatriz() const;
    void imprimirRotulosVertice() const;
    void imprimirRotulosArestas() const;
};

#endif
