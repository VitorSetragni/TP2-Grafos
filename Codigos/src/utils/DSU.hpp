#pragma once
#include <vector>
#include <numeric>

struct ElementoConjunto {
    int pai;
    int rank;
    int tamanho;           // Quantos pixels tem nesse componente
    double maxPesoInterno; // Maior peso de aresta dentro deste componente (Int(C))
};

class DSU {
public:
    DSU(int n);
    int find(int i);
    void uniao(int i, int j, double pesoAresta);
    
    // Getters para o algoritmo de segmentação usar
    int getTamanho(int i);
    double getMaxPesoInterno(int i);

private:
    std::vector<ElementoConjunto> elementos;
};