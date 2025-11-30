#ifndef MENU_MATRIZ_HPP
#define MENU_MATRIZ_HPP

#include <vector>
#include <string>
#include <limits>
#include <iostream>

#include "../Grafo/Matriz/GrafoMatriz.hpp"

// Funções auxiliares usadas pelo menu
int lerInteiro(const std::string& mensagem, int min, int max);
bool lerBoolean(const std::string& mensagem);
std::string lerRotulo(const std::string& mensagem);

class MenuMatriz {
   private:
    GrafoMatriz* grafo = nullptr;

    const int limiteVertice = 100;
    const int limitePeso = 100;

    bool grafoInstanciado();

    void intanciaGrafo();
    void adicionaVertice();
    void adicionaAresta();
    void removeVertice();
    void removeAresta();
    void consultaVizinhosVertice();
    void consultarFechoTransitivoDireto();
    void consultarFechoTransitivoInverso();
    void buscaProfundidade();
    void buscaLargura();
    void imprimeGrafo();
    void removeGrafo();
    void criarGrafoPadrao();

   public:
    void menu();
};

#endif // MENU_MATRIZ_HPP
