#ifndef SEGMENTADOREDMONDS_HPP
#define SEGMENTADOREDMONDS_HPP

#include "../../Grafo/Lista/GrafoLista.hpp"
#include "../ISegmentador.hpp"
#include <vector>

class SegmentadorMSA : public ISegmentador {
public:
    // Segmenta usando Edmonds
    ResultadoSegmentacao segmentar(GrafoLista* grafo, double k, int minSize) override;

private:
    struct ArestaEdmonds {
        int u;          // Origem
        int v;          // Destino
        double peso;
        int idOriginal; // Rastreio
    };

    // Núcleo recursivo do Edmonds
    static std::vector<int> executarEdmondsRecursivo(int numVertices, int raiz, std::vector<ArestaEdmonds>& arestas, int nivel);

    // BFS leve para marcar componentes finais
    static void bfsMarcarComponente(const std::vector<std::vector<int>>& adj, int raiz, int idComponente, std::vector<int>& mapa, std::vector<bool>& visitado);
};

#endif