#ifndef NOVERTOCE_HPP
#define NOVERTOCE_HPP

#include "Vertice.hpp"
#include <forward_list>
#include <string>

class NoVertice {
public:
    Vertice vertice;
    std::forward_list<Vertice> arestas;

    // Variáveis de controle
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    bool verticeRotulado;
    bool arestaRotulada;

    // Construtores
    NoVertice();
    NoVertice(bool verticePonderado, bool arestaPonderada,
              bool verticeRotulado, bool arestaRotulada, int id);
    NoVertice(bool verticePonderado, bool arestaPonderada,
              bool verticeRotulado, bool arestaRotulada,
              int id, int peso, std::string rotulo);
    NoVertice(bool arestaPonderada, bool arestaRotulada, Vertice v);

    // Manipulação de arestas
    void appendAresta(const Vertice &v);
    void adicionarAresta(Vertice v);
    void adicionarAresta(Vertice v, int peso);
    void adicionarAresta(Vertice v, std::string rotulo);
    void adicionarAresta(Vertice v, int peso, std::string rotulo);
    void removerAresta(Vertice v);

    // Consultas
    bool existeAresta(Vertice v);
    std::forward_list<Vertice> getArestas();
    int getId() const;

    // Utilitários
    std::string toString();
};

#endif
