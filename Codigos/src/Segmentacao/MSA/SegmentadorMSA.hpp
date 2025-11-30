#pragma once
#include "../ISegmentador.hpp"

class SegmentadorMSA : public ISegmentador {
    public:
        ResultadoSegmentacao segmentar(GrafoLista* grafo, double k, int minSize = 0) override {        
            return ResultadoSegmentacao();
        }
    
    private:
        void adicionarRaizVirtual(GrafoLista* g) const;
};