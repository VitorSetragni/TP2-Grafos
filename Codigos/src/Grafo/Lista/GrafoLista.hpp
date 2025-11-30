#ifndef GRAFOLISTA_HPP
#define GRAFOLISTA_HPP

#include <vector>
#include <string>

#include "Vertice.hpp"
#include "NoVertice.hpp"
#include "../IGrafo.hpp"

class GrafoLista : public IGrafo<Vertice> {
private:
    // Método auxiliar da DFS recursiva
    void dfsRec_(int uId, std::vector<char>& visitado, std::vector<Vertice>& ordem) const;

public:
    std::vector<NoVertice> listaPrincipal;

    int numVertices;
    int numArestas;
    int ultimoId;

    // Características
    bool simples;
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    bool verticeRotulado;
    bool arestaRotulada;

    // Construtores
    GrafoLista(bool simples, bool direcionado, bool vPonderado, bool aPonderada,
               bool vRotulado, bool aRotulada, int quantidadeVerticesInicial);

    GrafoLista(bool simples, bool direcionado, bool vPonderado, bool aPonderada,
               bool vRotulado, bool aRotulada);

    Vertice getVertice(int i);


    // Manipulação de vértices
    bool adicionarVertice(Vertice v) override;
    bool adicionarVertice(Vertice v, std::string rotulo);
    bool adicionarVertice(Vertice v, double peso);
    bool adicionarVertice(Vertice v, double peso, std::string rotulo);

    bool removerVertice(Vertice v) override;

    // Manipulação de arestas
    bool adicionarAresta(Vertice origem, Vertice destino) override;
    bool adicionarAresta(Vertice origem, Vertice destino, double peso) override;
    bool adicionarAresta(Vertice origem, Vertice destino, std::string rotulo);
    bool adicionarAresta(Vertice origem, Vertice destino, double peso, std::string rotulo);

    bool removerAresta(Vertice origem, Vertice destino) override;

    // Consultas
    std::vector<Vertice> getVizinhos(Vertice v) const override;

    std::vector<Vertice> fechoTransitivoDireto(Vertice v) const override;
    std::vector<Vertice> fechoTransitivoInverso(Vertice v) const override;

    bool validarVertice(Vertice v) const;
    bool existeVertice(Vertice v) const override;
    bool existeAresta(Vertice origem, Vertice destino) const override;

    int procurarVertice(Vertice v) const;
    std::vector<Vertice> procurarAresta(Vertice destino);

    // Capacidades
    int getQuantidadeVertices() const override;
    int getQuantidadeArestas() const override;
    std::vector<NoVertice> getlistaPrincipal() const;

    // Impressões
    void imprimir() const override;
    void imprimir(std::vector<Vertice> vertices) const;


    // Buscas
    std::vector<Vertice> buscaEmLargura(const Vertice& origem) const;
    std::vector<Vertice> caminhoEmLargura(const Vertice& origem, const Vertice& destino) const;
    std::vector<Vertice> buscaEmProfundidade(const Vertice& origem) const;
    std::vector<Vertice> buscaEmProfundidadeCompleta(const Vertice& origem) const;

    int getUltimoId() const;

};

#endif
