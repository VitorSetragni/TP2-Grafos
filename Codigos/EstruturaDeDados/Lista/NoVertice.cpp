#include "NoVertice.hpp"

#include <forward_list>
#include <string>

#include "Vertice.hpp"
using namespace std;

/* A classe NoVertice representa o Vertice da lista principal,
na qual cada posição possui um vertice e a lista de vizinhos (suas arestas)

Representação gráfica:

                        Nó Vértice
+-----------------------------------------------------------+
|          |                                                |
|  Vertice | forward_list<Vertice> arestas -> V1 -> V2 -> ... -> Vn |
|     |    |  |                                             |
+-----|----|--|---------------------------------------------+
      |       +-> Cada Vertice u em aresta tem os atributos da aresta (Vertice - u)
      +-> Vertice com todos os atributos

*/
/**
 *   Construtor de NoVertice Vazio
 */
NoVertice::NoVertice() : NoVertice(false, false, false, false, 0) {
}

/**
 *   Construtor de NoVértice sem peso e rotulo
 *
 *   @param verticePonderado Boleano que determina se o vértice é ponderado ou não
 *   @param arestaPonderada Boleano que determina se o aresta é ponderada ou não
 *   @param verticeRotulado Boleano que determina se o vértice é rotulado ou não
 *   @param arestaRotulada Boleano que determina se o aresta é rotulada ou não
 *   @param id Inteiro que define o id do vértice
 */
NoVertice::NoVertice(bool verticePonderado, bool arestaPonderada, bool verticeRotulado,
                     bool arestaRotulada, int id) {
    this->verticePonderado = verticePonderado;
    this->arestaPonderada = arestaPonderada;
    this->verticeRotulado = verticeRotulado;
    this->arestaRotulada = arestaRotulada;
    this->vertice = Vertice(id, verticePonderado, verticeRotulado);
    forward_list<Vertice> arestas = {};
}

/**
 *   Construtor de NoVértice com peso e rotulo
 *
 *   @param verticePonderado Boleano que determina se o vértice é ponderado ou não
 *   @param arestaPonderada Boleano que determina se o aresta é ponderada ou não
 *   @param verticeRotulado Boleano que determina se o vértice é rotulado ou não
 *   @param arestaRotulada Boleano que determina se o aresta é rotulada ou não
 *   @param id Inteiro que define o id do vértice
 *   @param peso Inteiro que define o peso do vértice
 *   @param rotulo String que define o rotulo do vértice
 */
NoVertice::NoVertice(bool verticePonderado, bool arestaPonderada, bool verticeRotulado,
                     bool arestaRotulada, int id, int peso, string rotulo) {
    this->verticePonderado = verticePonderado;
    this->arestaPonderada = arestaPonderada;
    this->verticeRotulado = verticeRotulado;
    this->arestaRotulada = arestaRotulada;
    this->vertice = Vertice(id, verticePonderado, verticeRotulado, peso, rotulo);
    forward_list<Vertice> arestas = {};
}

/**
 *   Construtor de NoVértice copiando um Vértice
 *
 *   @param arestaPonderada Boleano que determina se o aresta é ponderada ou não
 *   @param arestaRotulada Boleano que determina se a aresta é rotulada ou não
 *   @param v Vértice a ser copiado
 */
NoVertice::NoVertice(bool arestaPonderada, bool arestaRotulada, Vertice v)
    : NoVertice(v.ponderado, arestaPonderada, v.rotulado, arestaRotulada, v.getId(), v.getPeso(),
                v.getRotulo()) {
}

void NoVertice::appendAresta(const Vertice &v) {
    if (arestas.empty()) {
        arestas.push_front(v);
    } else {
        auto prev = arestas.before_begin();
        for (auto it = arestas.begin(); it != arestas.end(); ++it) ++prev;
        arestas.insert_after(prev, v);
    }
}

/**
 *   Adiciona uma Aresta conectando o vértice desse Nó com o v
 *
 *   @param v Vertice destino da aresta
 */
void NoVertice::adicionarAresta(Vertice v) {
    appendAresta(v);
}

/**
 *   Adiciona uma Aresta conectando o vértice desse Nó com o v, adicionado peso na aresta
 *
 *   @param v Vertice destino da aresta
 *   @param peso Inteiro do peso a ser adicionado
 */
void NoVertice::adicionarAresta(Vertice v, int peso) {
    v.setPeso(peso);
    appendAresta(v);
}

/**
 *   Adiciona uma Aresta conectando o vértice desse Nó com o v, adicionado rotulo na aresta
 *
 *   @param v Vertice destino da aresta
 *   @param rotulo String do rotulo a ser adicionado
 */
void NoVertice::adicionarAresta(Vertice v, string rotulo) {
    v.setRotulo(rotulo);
    appendAresta(v);
}

/**
 *   Adiciona uma Aresta conectando o vértice desse Nó com o v, adicionado peso e rotulo na
 * aresta
 *
 *   @param v Vertice destino da aresta
 *   @param peso Inteiro do peso a ser adicionado
 *   @param rotulo String do rotulo a ser adicionado
 */
void NoVertice::adicionarAresta(Vertice v, int peso, string rotulo) {
    v.setPeso(peso);
    v.setRotulo(rotulo);
    appendAresta(v);
}

/**
 *   Remove uma Aresta conectada o vértice desse Nó com v, caso exista
 *
 *   @param v Vertice destino da aresta a ser removida
 */
void NoVertice::removerAresta(Vertice v) {
    // if(existeAresta(v)) <-- Vale a pena testar aqui?
    this->arestas.remove(v);
}

/**
 *   Testa se aresta existe
 *
 *   @param v Vertice destino da aresta
 *   @return Verdadeiro caso exista
 */
bool NoVertice::existeAresta(Vertice v) {
    bool existe = false;
    for (std::forward_list<Vertice>::iterator it = arestas.begin(); it != arestas.end(); ++it)
        if (*it == v) {
            existe = true;
        }
    return existe;
}

forward_list<Vertice> NoVertice::getArestas() {
    return this->arestas;
}

int NoVertice::getId() const {
    return vertice.getId();
}

/**
 *   Transforma Nó vértice em uma string
 *
 *   @param v Vertice destino da aresta
 *   @return Verdadeiro caso exista
 */
string NoVertice::toString() {
    string lista = to_string(vertice.getId());
    lista += " |";
    for (auto const &aresta : this->arestas) {
        lista += ' ' + aresta.toString();
    }
    lista += '\n';
    return lista;
}
