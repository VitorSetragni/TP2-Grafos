#pragma once

#include "../ISegmentador.hpp"
#include <vector>
#include <algorithm>

class SegmentadorMST : public ISegmentador {
public:
    ResultadoSegmentacao segmentar(GrafoLista* grafo, double k, int minSize = 0) override;

private:
    struct ArestaSimples {
        int u, v;
        double peso;

        // Operador < para o sort funcionar
        bool operator<(const ArestaSimples& outra) const {
            return peso < outra.peso;
        }
    };

    // Métodos auxiliares
    double calcularMInt(double maxC1, int tamC1, double maxC2, int tamC2, double k);

    // Agora o compilador já conhece "ArestaSimples"
    std::vector<ArestaSimples> buscarListaDeArestasOrdenadas(GrafoLista* grafo);    

    GrafoLista* kruskalCondicional(GrafoLista* grafoEntrada, double k);
};