#ifndef MENULISTA_HPP
#define MENULISTA_HPP

#include <iostream>
#include <string>
#include <vector>

#include "../Grafo/Lista/GrafoLista.hpp"
#include "../libs/io/io.hpp"
#include "../libs/io/MyIO.hpp"

using namespace std;

class MenuLista{
    public:

    GrafoLista* grafo;

    // Construtor padrão
    MenuLista() : grafo(nullptr) {}

    // Menu principal
    void menu();

    // Verifica se o grafo está instanciado
    bool grafoInstanciado();

    // Instancia um novo grafo
    void intanciaGrafo();

    // Operações básicas
    void adicionaVertice();
    void adicionaAresta();
    void removeVertice();
    void removeAresta();

    // Consultas
    void consultaVizinhosVertice();
    void consultarSucessoresVertice();
    void consultarPredecessoresVertice();

    // Remover grafo
    void removeGrafo();

    // Buscas
    void buscaEmLargura();
    void buscaEmProfundidade();

    // Impressão
    void imprimeGrafo();
};

#endif
