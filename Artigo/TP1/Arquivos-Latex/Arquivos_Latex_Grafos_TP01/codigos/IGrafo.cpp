#include <vector>

using namespace std;

template <typename TVertice>
class IGrafo {
   public:
    virtual ~IGrafo() = default;

    // Métodos para obter o tamanho do grafo
    virtual int getQuantidadeVertices() const = 0;
    virtual int getQuantidadeArestas() const = 0;

    // Métodos para manipulação
    virtual bool adicionarVertice(TVertice v) = 0;
    virtual bool adicionarAresta(TVertice origem, TVertice destino, int peso) = 0;
    virtual bool adicionarAresta(TVertice origem, TVertice destino) = 0;

    // Métodos para remoção
    virtual bool removerVertice(TVertice v) = 0;
    virtual bool removerAresta(TVertice origem, TVertice destino) = 0;

    // Métodos de checagem
    virtual bool existeVertice(TVertice v) const = 0;
    virtual bool existeAresta(TVertice origem, TVertice destino) const = 0;

    // Métodos para obter adjacências
    virtual vector<TVertice> getVizinhos(TVertice v) const = 0;
    virtual vector<TVertice> fechoTransitivoDireto(TVertice v) const = 0;
    virtual vector<TVertice> fechoTransitivoInverso(TVertice v) const = 0;

    // Método para visualização
    virtual void imprimir() const = 0;
};