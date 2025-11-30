#pragma once

#include "../Grafo/Lista/GrafoLista.hpp"
#include <vector>
#include <map>

// Estrutura simples para retornar o resultado
struct ResultadoSegmentacao {
    // Mapeia ID do Vértice (Pixel) -> ID do Componente (Região)
    std::vector<int> componentes;
    
    // Quantos componentes (árvores) foram gerados
    int numComponentes;
};

class ISegmentador {
public:
    virtual ~ISegmentador() = default;

    /**
     * @param grafo O grafo da imagem (lista de adjacências).
     * @param k Parâmetro de escala (threshold) para o critério de segmentação.
     * @param minSize Tamanho mínimo para um componente ser aceito (opcional, usado para pós-processamento).
     */
    virtual ResultadoSegmentacao segmentar(GrafoLista* grafo, double k, int minSize = 0) = 0;
};