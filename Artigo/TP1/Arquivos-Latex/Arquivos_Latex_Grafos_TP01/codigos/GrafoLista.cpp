#include <algorithm>
#include <iostream>
#include <forward_list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <queue>

#include "../IGrafo.cpp"

using namespace std;

// Classe de Vertice genérica

class Vertice {
    int id;  // cada vertice precisa de um identificador único, caso não tenha rotulo
    int peso;
    string rotulo;

   public:
    // Variaveis de controle
    bool rotulado;
    bool ponderado;

    /**
     *   Construtor Vazio de Vertice
     *
     *   @return Vertice com id e peso 0, rotulo vazio e não rotulado e ponderado
     */
    Vertice() : Vertice(0, false, false, 0, "") {
    }

    /**
     *   Construtor de Vértice sem peso e rotulo
     *
     *   @param id Inteiro que define o id do vértice
     *   @param rotulado Boleano que determina se o vértice é rotulado ou não
     *   @param ponderado Boleano que determina se o vértice é ponderado ou não
     */
    Vertice(int id, bool rotulado, bool ponderado) : Vertice(id, rotulado, ponderado, 0, "") {
    }

    /**
     *   Construtor de Vértice com peso e rotulo
     *
     *   @param id Inteiro que define o id do vértice
     *   @param peso Inteiro que define o peso
     *   @param rotulo String que define o rotulo
     */
    Vertice(int id, int peso, string rotulo) : Vertice(id, true, true, peso, rotulo) {
    }

    /**
     *   Construtor de Vértice sem peso e rotulo
     *
     *   @param id Inteiro que define o id do vértice
     *   @param rotulado Boleano que determina se o vértice é rotulado ou não
     *   @param ponderado Boleano que determina se o vértice é ponderado ou não
     *   @param peso Inteiro que define o peso
     *   @param rotulo String que define o rotulo
     */
    Vertice(int id, bool rotulado, bool ponderado, int peso, string rotulo) {
        this->id = id;
        this->peso = peso;
        this->rotulo = rotulo;
        this->rotulado = rotulado;
        this->ponderado = ponderado;
    }

    /**
     *   Construtor de Vértice de cópia
     *
     *   @param v Vertice a ser copiado
     */
    Vertice(Vertice const &v) {
        this->peso = v.peso;
        this->rotulo = v.rotulo;
        this->ponderado = v.ponderado;
        this->rotulado = v.rotulado;
        setId(v.id);
    }

    void setPeso(int p) {
        this->peso = p;
    }

    void setRotulo(string r) {
        this->rotulo = r;
    }

    void setId(int id) {
        this->id = id;
    }

    int const getId() const {
        return this->id;
    }

    int const getPeso() const {
        return this->peso;
    }

    string getRotulo() const {
        return this->rotulo;
    }

    bool operator==(const Vertice &other) const {
        return this->id == other.id;
    }

    bool operator<(const Vertice &other) const {
        return this->id < other.id;
    }

    string toString() const {
        std::ostringstream oss;
        if (ponderado && rotulado) {
            oss << " [" << getId() << ", " << getPeso() << ", " << getRotulo() << "]";
        } else if (ponderado) {
            oss << " [" << getId() << ", " << getPeso() << "]";
        } else if (rotulado) {
            oss << " [" << getId() << ", " << getRotulo() << "]";
        } else {
            oss << " [" << getId() << "]";
        }
        return oss.str();
    }
};

/* A classe NoVertice representa o Vertice da forward_lista principal,
na qual cada posição possui um vertice e a forward_lista de vizinhos (suas arestas)

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

class NoVertice {
   public:
    Vertice vertice;
    forward_list<Vertice> arestas;

    // Variavéis de controle
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    bool verticeRotulado;
    bool arestaRotulada;

    /**
     *   Construtor de NoVertice Vazio
     */
    NoVertice() : NoVertice(false, false, false, false, 0) {
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
    NoVertice(bool verticePonderado, bool arestaPonderada, bool verticeRotulado,
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
    NoVertice(bool verticePonderado, bool arestaPonderada, bool verticeRotulado,
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
    NoVertice(bool arestaPonderada, bool arestaRotulada, Vertice v)
        : NoVertice(v.ponderado, arestaPonderada, v.rotulado, arestaRotulada, v.getId(),
                    v.getPeso(), v.getRotulo()) {
    }

    void appendAresta(const Vertice &v) {
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
    void adicionarAresta(Vertice v) {
        appendAresta(v);
    }

    /**
     *   Adiciona uma Aresta conectando o vértice desse Nó com o v, adicionado peso na aresta
     *
     *   @param v Vertice destino da aresta
     *   @param peso Inteiro do peso a ser adicionado
     */
    void adicionarAresta(Vertice v, int peso) {
        v.setPeso(peso);
        appendAresta(v);
    }

    /**
     *   Adiciona uma Aresta conectando o vértice desse Nó com o v, adicionado rotulo na aresta
     *
     *   @param v Vertice destino da aresta
     *   @param rotulo String do rotulo a ser adicionado
     */
    void adicionarAresta(Vertice v, string rotulo) {
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
    void adicionarAresta(Vertice v, int peso, string rotulo) {
        v.setPeso(peso);
        v.setRotulo(rotulo);
        appendAresta(v);
    }

    /**
     *   Remove uma Aresta conectada o vértice desse Nó com v, caso exista
     *
     *   @param v Vertice destino da aresta a ser removida
     */
    void removerAresta(Vertice v) {
        // if(existeAresta(v)) <-- Vale a pena testar aqui?
        this->arestas.remove(v);
    }

    /**
     *   Testa se aresta existe
     *
     *   @param v Vertice destino da aresta
     *   @return Verdadeiro caso exista
     */
    bool existeAresta(Vertice v) {
        bool existe = false;
        for (std::forward_list<Vertice>::iterator it = arestas.begin(); it != arestas.end(); ++it)
            if (*it == v) {
                existe = true;
            }
        return existe;
    }

    forward_list<Vertice> getArestas() {
        return this->arestas;
    }

    int getId() const {
        return vertice.getId();
    }

    /**
     *   Transforma Nó vértice em uma string
     *
     *   @param v Vertice destino da aresta
     *   @return Verdadeiro caso exista
     */
    string toString() {
        string forward_lista = to_string(vertice.getId());
        forward_lista += " |";
        for (auto const &aresta : this->arestas) {
            forward_lista += ' ' + aresta.toString();
        }
        forward_lista += '\n';
        return forward_lista;
    }
};

/*
O grafo forward_lista é formado por um vector (array contínuo) de Nós vértices.
Esse grafo pode conter as seguintes características:
    + Simples ou Não simples
    + Direcionado ou não direcionado
    + Vértices e/ou arestas ponderados ou não ponderados
    + Vértices e/ou arestas rotulados ou não rotulados

Representação gráfica:

     +-> listaPrincipal<NoVertice>
     |
+----|------------------------------------------------------+
|    |     |                                                |
|    0     | forward_list<Vertice> arestas -> 1 -> 2 -> ...         |
|          |                                                |
|    1     | forward_list<Vertice> arestas -> 4 -> 0 -> ...         |
|          |                                                |
|    2     | forward_list<Vertice> arestas -> 3 -> 2 -> ...         |
|          |                                                |
|   ...    |                    ...                         |
+----------|------------------------------------------------+

*/

class GrafoLista : public IGrafo<Vertice> {
   private:
    // --- Busca em Profundidade (helper recursivo) ---
    void dfsRec_(int uId, std::vector<char>& visitado, std::vector<Vertice>& ordem) const {
        // Segurança: ignorar IDs fora do range atual
        if (uId < 0 || uId > ultimoId) return;
        if (visitado[uId]) return;

        visitado[uId] = 1;
        ordem.push_back(listaPrincipal.at(uId).vertice); // vértice canônico

        // Percorre vizinhos pelo id armazenado nas arestas
        const auto& adj = listaPrincipal.at(uId).arestas;
        for (const auto& aresta : adj) {
            int v = aresta.getId();
            // Só segue se o id é válido e o vértice realmente existe hoje
            if (validarVertice(aresta) && !visitado[v] && existeVertice(aresta)) {
                dfsRec_(v, visitado, ordem);
            }
        }
    }


   public:
    vector<NoVertice> listaPrincipal;
    int numVertices;
    int numArestas;
    int ultimoId;

    // Variavéis de controle
    bool simples;
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;
    bool verticeRotulado;
    bool arestaRotulada;

    /**
     *   Construtor de GrafoLista com n vértices (com peso e rotulos zerados)
     *
     *   @param simples Boleano que determina se o grafo é simples ou não
     *   @param direcionado Boleano que determina se o grafo é direcionado ou não
     *   @param vPonderado Boleano que determina se o vértice é ponderado ou não
     *   @param aPonderada Boleano que determina se a aresta é pondearda ou não
     *   @param vRotulado Boleano que determina se o vértice é rotulado ou não
     *   @param aRotulada Boleano que determina se a aresta é rotulada ou não
     *   @param quantidadeVerticesInicial inteiro
     */
    GrafoLista(bool simples, bool direcionado, bool vPonderado, bool aPonderada, bool vRotulado,
               bool aRotulada, int quantidadeVerticesInicial) {
        this->ultimoId = -1;
        this->numArestas = 0;
        this->numVertices = 0;
        this->simples = simples;
        this->direcionado = direcionado;
        this->verticePonderado = vPonderado;
        this->arestaPonderada = aPonderada;
        this->verticeRotulado = vRotulado;
        this->arestaRotulada = aRotulada;
        NoVertice v1 = NoVertice(this->verticePonderado, this->arestaPonderada,
                                 this->verticeRotulado, this->arestaRotulada, 0);

        for (int i = 0; i < quantidadeVerticesInicial; i++) {
            adicionarVertice(v1.vertice);
        }
    }

    /**
     *   Construtor de Grafo inicializado com 1 único vértice
     *
     *   @param simples Boleano que determina se o grafo é simples ou não
     *   @param direcionado Boleano que determina se o grafo é direcionado ou não
     *   @param vPonderado Boleano que determina se o vértice é ponderado ou não
     *   @param aPonderada Boleano que determina se a aresta é pondearda ou não
     *   @param vRotulado Boleano que determina se o vértice é rotulado ou não
     *   @param aRotulada Boleano que determina se a aresta é rotulada ou não
     *   @param quantidadeVerticesInicial inteiro
     */
    GrafoLista(bool simples, bool direcionado, bool vPonderado, bool aPonderada, bool vRotulado,
               bool aRotulada)
        : GrafoLista(simples, direcionado, vPonderado, aPonderada, vRotulado, aRotulada, 1) {
    }

    // Metodos de manipulação

    /**
     *   Adiciona mais um vértice no Grafo
     *
     *   @param v Vertice a ser adicionado
     *   @return se ação foi concluida ou não
     */
    bool adicionarVertice(Vertice v) override {
        NoVertice vertice =
            NoVertice(this->verticePonderado, this->arestaPonderada, this->verticeRotulado,
                      this->arestaRotulada, ++ultimoId, v.getPeso(), v.getRotulo());
        listaPrincipal.push_back(vertice);
        numVertices++;
        return true;
    }

    /**
     *   Adiciona mais um vértice no Grafo
     *
     *   @param v Vertice a ser adicionado
     *   @param rotulo String a ser definida como rotulo do vértice
     *   @return se ação foi concluida ou não
     */
    bool adicionarVertice(Vertice v, string rotulo) {
        bool status = false;
        NoVertice vertice =
            NoVertice(this->verticePonderado, this->arestaPonderada, this->verticeRotulado,
                      this->arestaRotulada, ++ultimoId, 0, rotulo);
        if (this->verticeRotulado) {
            listaPrincipal.push_back(vertice);
            numVertices++;
            status = true;
        }
        return status;
    }

    /**
     *   Adiciona mais um vértice no Grafo
     *
     *   @param v Vertice a ser adicionado
     *   @param peso Inteiro a ser adicionado como peso do vértice
     *   @return se ação foi concluida ou não
     */
    bool adicionarVertice(Vertice v, int peso) {
        bool status = false;
        NoVertice vertice =
            NoVertice(this->verticePonderado, this->arestaPonderada, this->verticeRotulado,
                      this->arestaRotulada, ++ultimoId, peso, "");
        if (this->verticeRotulado) {
            listaPrincipal.push_back(vertice);
            numVertices++;
            status = true;
        }
        return status;
    }

    /**
     *   Adiciona mais um vértice no Grafo
     *
     *   @param v Vertice a ser adicionado
     *   @param peso Inteiro a ser adicionado como peso do vértice
     *   @param rotulo String a ser definida como rotulo do vértice
     *   @return se ação foi concluida ou não
     */
    bool adicionarVertice(Vertice v, int peso, string rotulo) {
        bool status = false;
        NoVertice vertice =
            NoVertice(this->verticePonderado, this->arestaPonderada, this->verticeRotulado,
                      this->arestaRotulada, ++ultimoId, peso, "");
        if (this->verticeRotulado) {
            listaPrincipal.push_back(vertice);
            numVertices++;
            status = true;
        }
        return status;
    }

    /**
     *   Remove um vértice no Grafo, caso o vértice esteja presente, assim como as arestas
     * conectadas
     *
     *   @param v Vertice a ser removido
     *   @return se ação foi concluida ou não
     */
    bool removerVertice(Vertice v) override {
        NoVertice vertice = NoVertice(this->arestaPonderada, this->arestaRotulada, v);
        int pos = procurarVertice(v);
        bool status = true;
        if (pos != -1) {
            // Remover todas as arestas que conectavam com v
            vector<Vertice> arestasRemover = procurarAresta(v);
            for (int i = 0; i < arestasRemover.size(); i++) {
                removerAresta(arestasRemover.at(i), v);
            }

            // Remover NoVertice da forward_lista Principal
            listaPrincipal.erase(listaPrincipal.begin() + pos);
            numVertices -= 1;
        } else {
            status = false;
            cout << "Vértice " << v.toString() << " não está no grafo";
        }
        return status;
    }

    /**
     *   Adiciona uma aresta no grafo
     *
     *   @param origem Vertice de partida da aresta
     *   @param destino Vertice de destino da aresta
     *   @return se ação foi concluida ou não
     */
    bool adicionarAresta(Vertice origem, Vertice destino) override {
        bool status = false;
        if (validarVertice(destino) && validarVertice(origem)) {
            NoVertice &procura = listaPrincipal.at(origem.getId());
            procura.adicionarAresta(destino);

            if (!direcionado) {
                NoVertice &procuraDestino = listaPrincipal.at(destino.getId());
                procuraDestino.adicionarAresta(origem);
            }

            status = true;
            numArestas++;
        } else {
            cout << "Vértices não válidos" << endl;
        }
        return status;
    }

    /**
     *   Adiciona uma aresta com peso no grafo
     *
     *   @param origem Vertice de partida da aresta
     *   @param destino Vertice de destino da aresta
     *   @param peso Inteiro do peso a ser adicionado
     *   @return se ação foi concluida ou não
     */
    bool adicionarAresta(Vertice origem, Vertice destino, int peso) override {
        return adicionarAresta(origem, destino, peso, "");
    }

    /**
     *   Adiciona uma aresta com rotulo no grafo
     *
     *   @param origem Vertice de partida da aresta
     *   @param destino Vertice de destino da aresta
     *   @param rotulo String do rotulo a ser adicionado
     *   @return se ação foi concluida ou não
     */
    bool adicionarAresta(Vertice origem, Vertice destino, string rotulo) {
        return adicionarAresta(origem, destino, 0, rotulo);
    }

    /**
     *   Adiciona uma aresta com peso e rotulo no grafo
     *
     *   @param origem Vertice de partida da aresta
     *   @param destino Vertice de destino da aresta
     *   @param peso Inteiro do peso a ser adicionado
     *   @param rotulo String do rotulo a ser adicionado
     *   @return se ação foi concluida ou não
     */
    bool adicionarAresta(Vertice origem, Vertice destino, int peso, string rotulo) {
        bool status = false;
        if (validarVertice(destino) && validarVertice(origem)) {
            NoVertice &procura = listaPrincipal.at(origem.getId());

            destino.ponderado = arestaPonderada;
            destino.rotulado = arestaRotulada;

            // cout << "(Grafo forward_lista) Inserindo:" << origem.toString() << " : " <<destino.toString()
            // << endl;

            procura.adicionarAresta(destino, peso, rotulo);

            if (!direcionado) {
                procura = listaPrincipal.at(destino.getId());
                procura.adicionarAresta(origem, peso, rotulo);
            }

            status = true;
            numArestas++;
        }
        return status;
    }

    /**
     *   Remove uma aresta do Grafo, caso exista
     *
     *   @param origem Vertice de partida da aresta
     *   @param destino Vertice de destino da aresta
     *   @return se ação foi concluida ou não
     */
    bool removerAresta(Vertice origem, Vertice destino) override {
        bool status = false;
        if (existeAresta(origem, destino)) {
            NoVertice &procura = listaPrincipal.at(origem.getId());
            procura.removerAresta(destino);

            if (!direcionado) {
                NoVertice &procura = listaPrincipal.at(destino.getId());
                procura.removerAresta(origem);
            }

            status = true;
            numArestas--;
        } else {
            cout << "A aresta não existe" << endl;
        }
        return status;
    }

    /**
     *   Coleta os vértices vizinhos de um dado vértice
     *
     *   @param v Vertice a ter seus vizinhos coletados
     *   @return Vector<Vertice> dos vizinhos
     */
    vector<Vertice> getVizinhos(Vertice v) const override {
        if (direcionado) {
            vector<Vertice> v1 = fechoTransitivoInverso(v);
            vector<Vertice> v2 = fechoTransitivoDireto(v);
            vector<Vertice> resultado;

            sort(v1.begin(), v1.end());
            sort(v2.begin(), v2.end());

            set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(resultado));

            return resultado;
        } else {
            return fechoTransitivoDireto(v);
        }
    }

    /**
     *   Coleta os vértices descendentes de um dado vértice
     *
     *   @param v Vertice a ter seus descendentes coletados
     *   @return Vector<Vertice> dos descendentes
     */
    vector<Vertice> fechoTransitivoDireto(Vertice v) const override {
        NoVertice procura = listaPrincipal.at(v.getId());
        forward_list<Vertice> descendentes_forward_list = procura.getArestas();
        vector<Vertice> descendentes;

        // Caso tenha algum calor extra, pegar o valor do vértice e não da aresta
        if (arestaPonderada || arestaRotulada) {
            for (auto const &aresta : descendentes_forward_list) {
                int pos = procurarVertice(aresta);
                descendentes.push_back(listaPrincipal.at(pos).vertice);
            }
        } else {
            // Conversao de forward_list para vector
            vector<Vertice> descendentes{std::begin(descendentes_forward_list),
                                         std::end(descendentes_forward_list)};
        }
        return descendentes;
    }

    /**
     *   Coleta os vértices ancestrais de um dado vértice
     *
     *   @param v Vertice a ter seus ancestrais coletados
     *   @return Vector<Vertice> dos ancestrais
     */
    vector<Vertice> fechoTransitivoInverso(Vertice v) const override {
        vector<Vertice> ancestrais;
        NoVertice procura;
        for (int i = 0; i < listaPrincipal.size(); i++) {
            procura = listaPrincipal.at(i);
            forward_list<Vertice> arestas_forward_list = procura.getArestas();
            for (std::forward_list<Vertice>::iterator it = arestas_forward_list.begin(); it != arestas_forward_list.end();
                 ++it) {
                if (*it == v) {
                    ancestrais.push_back(procura.vertice);
                }
            }
        }

        return ancestrais;
    }

    // Metodos de validacao

    /**
     *   Valida um dado vértice.
     *
     *   @param v Vertice a ser validado
     *   @return Verdadeiro caso vértice seja válido
     */
    bool validarVertice(Vertice v) const {
        return (0 <= v.getId() && v.getId() <= ultimoId);
    }

    /**
     *   Determina se certo Vértice existe no grafo
     *
     *   @param v Vertice a ser testado
     *   @return Verdadeiro caso exista
     */
    bool existeVertice(Vertice v) const override {
        Vertice verticeProcurar = Vertice();
        int i = 0;

        // testar se vértice está nos limites de vértices já criados
        bool achou = validarVertice(v);
        if (achou) {
            // Se estiver no limite, ter certeza se está dentre os atuais
            achou = false;
            while (i != listaPrincipal.size() && !achou) {
                verticeProcurar = listaPrincipal.at(i).vertice;
                if (verticeProcurar == v) {
                    achou = true;
                }
                i++;
            }
        }
        return achou;
    }

    /**
     *   Determina se certa Aresta existe no grafo
     *
     *   @param origem Vertice de partida da aresta
     *   @param destino Vertice de destino da aresta
     *   @return Verdadeiro se aresta existir
     */
    bool existeAresta(Vertice origem, Vertice destino) const override {
        bool achou = false;
        if (validarVertice(destino) && validarVertice(origem)) {
            NoVertice procura = listaPrincipal.at(origem.getId());
            achou = procura.existeAresta(destino);
        }
        return achou;
    }

    /**
     *   Procura certo Vértice no grafo
     *
     *   @param v Vertice a ser procurado
     *   @return Inteiro de sua posição no grafo, caso não exista retorna -1
     */
    int procurarVertice(Vertice v) const {
        int i = 0;
        int achou = -1;
        while (i != listaPrincipal.size() && achou == -1) {
            Vertice verticeProcurar = listaPrincipal.at(i).vertice;
            // cout << verticeProcurar.toString();
            if (verticeProcurar == v) {
                achou = i;
            }
            i++;
        }
        return achou;
    }

    /**
     *   Procura todas as arestas cujo destino é o Vertice destino
     *
     *   @param destino Vertice destino das arestas desejadas
     *   @return Vector<Vertice> de Vertices que possuam alguma aresta com Vertice Destino
     */
    vector<Vertice> procurarAresta(Vertice v) {
        vector<Vertice> listaVerticesComAresta;
        int i = 0;
        int achou = -1;
        if (existeVertice(v)) {
            while (i != listaPrincipal.size()) {
                NoVertice &noVerticeProcurar = listaPrincipal.at(i);
                for (std::forward_list<Vertice>::iterator it = noVerticeProcurar.arestas.begin();
                     it != noVerticeProcurar.arestas.end(); ++it) {
                    if (*it == v) {  // Caso há aresta com v
                        listaVerticesComAresta.push_back(noVerticeProcurar.vertice);
                    }
                }
                i++;
            }
        }

        return listaVerticesComAresta;
    }

    // Metodos de capacidade

    int getQuantidadeVertices() const override {
        return numVertices;
    }

    int getQuantidadeArestas() const override {
        return numArestas;
    }

    vector<NoVertice> getlistaPrincipal() const {
        return this->listaPrincipal;
    }

    // Outros metodos

    /**
     *   Imprime o grafo inteiro
     */
    void imprimir() const override {
        string str = "";
        int tam_max = to_string(abs(ultimoId)).size();
        std::ostringstream oss;

        cout << "------- forward_lista de Adjacências --------" << endl;
        for (int i = 0; i < listaPrincipal.size(); i++) {
            const NoVertice &v = listaPrincipal.at(i);
            if (verticePonderado && verticeRotulado) {
                oss << i << " [" << v.vertice.getId() << ", " << v.vertice.getPeso() << ", "
                    << v.vertice.getRotulo() << "]";
            } else if (verticePonderado) {
                oss << i << " [" << v.vertice.getId() << ", " << v.vertice.getPeso() << "]";
            } else if (verticeRotulado) {
                oss << i << " [" << v.vertice.getId() << ", " << v.vertice.getRotulo() << "]";
            } else {
                oss << i << " [" << v.vertice.getId() << "]";
            }

            str = oss.str();
            // alinhar valores
            for (int i = 0; i < tam_max - to_string(abs(v.getId())).size(); i++) str += " ";
            str += " ->";
            cout << str;

            str = "";
            oss.str("");
            oss.clear();

            for (const auto &aresta : v.arestas) {
                oss << ' ' << aresta.toString();
                str += oss.str();
                oss.str("");
                oss.clear();
            }
            str += '\n';
            cout << str;
        }

        cout << "-------------------------------------";
        cout << endl << "Características: " << endl;

        cout << "Direcionado? ";
        this->direcionado ? (cout << "Sim") : (cout << "Não");
        cout << endl;

        cout << "Ponderado? ";
        if (verticePonderado && arestaPonderada) {
            cout << "Vértices e Arestas";
        } else if (verticePonderado) {
            cout << "Vértices";
        } else if (arestaPonderada) {
            cout << "Arestas";
        } else {
            cout << "Não";
        }
        cout << endl;

        cout << "Rotulado? ";
        if (verticeRotulado && arestaRotulada) {
            cout << "Vértices e Arestas";
        } else if (verticeRotulado) {
            cout << "Vértices";
        } else if (arestaRotulada) {
            cout << "Arestas";
        } else {
            cout << "Não";
        }
        cout << endl;
        cout << "-------------------------------------" << endl << endl;
    }
    /**
     *   Imprime o forward_lista de vertices
     *   @param vertices Vector de vertices a ser mostrada
     */
    void imprimir(vector<Vertice> vertices) const {
        for (auto const &i : vertices) {
            cout << i.toString() << " ";
        }
        cout << endl << endl;
    }

    /**
     *   Busca em largura (Breadth-First Search)
     *
     *   Retorna a ordem de visita dos vértices a partir de 'origem'.
     *   Explora primeiro todos os vértices do mesmo nível antes de ir para o próximo.
     *
     *   @param origem Vértice inicial da busca
     *   @return Vector<Vertice> na ordem de visita
     *   @throws std::invalid_argument Se o vértice de origem não existir
     */
    std::vector<Vertice> buscaEmLargura(const Vertice& origem) const {
        if (!existeVertice(origem)) {
            throw std::invalid_argument("Origem inexistente no grafo.");
        }

        std::vector<Vertice> ordem;
        std::vector<char> visitado(ultimoId + 1, 0);
        std::queue<int> q;

        int s = origem.getId();
        visitado[s] = 1;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            ordem.push_back(listaPrincipal.at(u).vertice);

            const auto& adj = listaPrincipal.at(u).arestas;
            for (const auto& aresta : adj) {
                int v = aresta.getId();
                if (validarVertice(aresta) && !visitado[v] && existeVertice(aresta)) {
                    visitado[v] = 1;
                    q.push(v);
                }
            }
        }
        return ordem;
    }

    /**
     *   Busca em largura para encontrar o menor caminho em número de arestas
     *
     *   Retorna vetor vazio se não houver caminho entre 'origem' e 'destino'.
     *
     *   @param origem Vértice inicial
     *   @param destino Vértice final
     *   @return Vector<Vertice> representando o menor caminho, ou vazio se não houver caminho
     *   @throws std::invalid_argument Se origem ou destino não existirem
     */
    std::vector<Vertice> caminhoEmLargura(const Vertice& origem, const Vertice& destino) const {
        if (!existeVertice(origem) || !existeVertice(destino)) {
            throw std::invalid_argument("Origem e/ou destino inexistente(s) no grafo.");
        }

        std::vector<char> visitado(ultimoId + 1, 0);
        std::vector<int> pai(ultimoId + 1, -1);
        std::queue<int> q;

        int s = origem.getId();
        int t = destino.getId();

        visitado[s] = 1; 
        q.push(s);

        bool achou = false;

        while (!q.empty() && !achou) {
            int u = q.front(); q.pop();
            const auto& adj = listaPrincipal.at(u).arestas;
            for (const auto& aresta : adj) {
                int v = aresta.getId();
                if (validarVertice(aresta) && !visitado[v] && existeVertice(aresta)) {
                    visitado[v] = 1;
                    pai[v] = u;
                    if (v == t) {
                        achou = true;
                        break;
                    }
                    q.push(v);
                }
            }
        }

        if (!achou) return {};

        std::vector<Vertice> caminho;
        for (int atual = t; atual != -1; atual = pai[atual]) {
            caminho.push_back(listaPrincipal.at(atual).vertice);
        }
        std::reverse(caminho.begin(), caminho.end());
        return caminho;
    }

    /**
     *   Busca em profundidade recursiva (Depth-First Search)
     *
     *   Explora o mais profundamente possível antes de voltar.
     *
     *   @param origem Vértice inicial da busca
     *   @return Vector<Vertice> na ordem de visita
     *   @throws std::invalid_argument Se o vértice de origem não existir
     */
    std::vector<Vertice> buscaEmProfundidade(const Vertice& origem) const {
        if (!existeVertice(origem)) {
            throw std::invalid_argument("Origem inexistente no grafo.");
        }

        std::vector<Vertice> ordem;
        std::vector<char> visitado(ultimoId + 1, 0);
        dfsRec_(origem.getId(), visitado, ordem);
        return ordem;
    }

    /**
     *   Busca em profundidade cobrindo todos os componentes do grafo
     *
     *   Garante que todos os vértices do grafo sejam visitados,
     *   inclusive os desconexos do vértice de origem.
     *
     *   @param origem Vértice inicial
     *   @return Vector<Vertice> com todos os vértices visitados
     */
    std::vector<Vertice> buscaEmProfundidadeCompleta(const Vertice& origem) const {
        std::vector<Vertice> ordem;
        std::vector<char> visitado(ultimoId + 1, 0);

        if (existeVertice(origem)) {
            dfsRec_(origem.getId(), visitado, ordem);
        }

        for (const auto& no : listaPrincipal) {
            int id = no.getId();
            if (id >= 0 && id <= ultimoId && !visitado[id] && existeVertice(no.vertice)) {
                dfsRec_(id, visitado, ordem);
            }
        }
        return ordem;
    }

    int getUltimoId() const {
        return ultimoId;
    }
};

void TesteNaoDirecionado() {
    cout << endl << ">>>> Grafo Não direcionado" << endl << endl;

    GrafoLista g = GrafoLista(false, false, false, false, false, false);
    Vertice v1 = Vertice(1, false, false);
    Vertice v2 = Vertice(2, false, false);
    Vertice v3 = Vertice(3, false, false);
    Vertice v4 = Vertice(4, false, false);

    g.adicionarVertice(v1);
    g.adicionarVertice(v2);
    g.adicionarVertice(v3);
    g.adicionarVertice(v4);

    g.adicionarAresta(v1, v2);
    g.adicionarAresta(v3, v4);
    g.imprimir();

    cout << "Removendo aresta" << v1.toString() << " :" << v2.toString() << endl;
    g.removerAresta(v1, v2);
    g.imprimir();

    cout << "Removendo vértice" << v4.toString() << endl;
    g.removerVertice(v4);
    g.imprimir();
}
void TesteDirecionado() {
    cout << endl << "Grafo Direcionado" << endl << endl;
    GrafoLista g = GrafoLista(false, true, false, false, false, false);
    g.imprimir();
    Vertice v = Vertice(1, false, false);
    for (int i = 0; i < 11; i++) {
        v.setId(i + 1);
        g.adicionarVertice(v);
    }

    for (int i = 0; i < g.numVertices; i++) {
        v.setId(i);
        for (int x = 0; x < g.numVertices; x++) {
            Vertice a = Vertice(v);
            a.setId(x);
            g.adicionarAresta(v, a);
        }
    }
    g.imprimir();
}
void TestePonderado() {
    cout << endl << "Grafo Ponderado" << endl << endl;
    GrafoLista g1 = GrafoLista(false, true, true, true, false, false);
    g1.imprimir();

    Vertice v1 = Vertice(1, false, true);
    for (int i = 0; i < 11; i++) {
        v1.setId(i + 1);
        v1.setPeso(i * v1.getId());
        g1.adicionarVertice(v1);
    }
    g1.imprimir();

    Vertice origem = g1.getlistaPrincipal().at(0).vertice;
    Vertice destino = g1.getlistaPrincipal().at(5).vertice;

    g1.adicionarAresta(origem, destino, 10);

    for (const auto &origem : g1.getlistaPrincipal()) {
        for (int x = 5; x < g1.numVertices; x++) {
            Vertice a = Vertice(origem.vertice);
            a.setId(x);
            g1.adicionarAresta(origem.vertice, a, rand() % 1000);
        }
    }

    g1.imprimir();

    g1.removerAresta(origem, destino);
    g1.imprimir();
}
void TesteRotulado() {
    cout << endl << "Grafo Rotulado" << endl << endl;

    GrafoLista gr = GrafoLista(true, true, false, false, true, true);
    Vertice vr1 = Vertice(1, true, false);
    Vertice vr2 = Vertice(2, true, false);
    Vertice vr3 = Vertice(3, true, false);
    Vertice vr4 = Vertice(4, true, false);

    vr1.setRotulo("Cor");
    vr2.setRotulo("Fruta");
    vr3.setRotulo("?");
    vr4.setRotulo("Sei la mano");

    gr.adicionarVertice(vr1);
    gr.adicionarVertice(vr2);
    gr.adicionarVertice(vr3);

    for (const auto &origem : gr.getlistaPrincipal()) {
        for (int x = 0; x < gr.numVertices; x++) {
            Vertice a = Vertice(origem.vertice);
            a.setId(x);
            gr.adicionarAresta(origem.vertice, a, "Abacate");
        }
        cout << endl;
    }

    gr.imprimir();

    cout << "Remover o aresta " << vr1.toString() << " : " << vr3.toString() << endl;
    gr.removerAresta(vr1, vr3);
    gr.imprimir();

    gr.removerAresta(vr1, vr1);
    gr.removerAresta(vr3, vr3);

    vector<Vertice> fti = gr.fechoTransitivoInverso(vr1);
    cout << "Fecho Transitivo Inverso do " << vr1.toString() << endl;
    gr.imprimir(fti);

    vector<Vertice> ftd = gr.fechoTransitivoDireto(vr1);
    cout << "Fecho Transitivo Direto do " << vr1.toString() << endl;
    gr.imprimir(ftd);

    gr.adicionarVertice(vr4);
    gr.imprimir();
    vector<Vertice> vizinhos = gr.getVizinhos(vr1);
    cout << "Vizinhos de" << vr1.toString() << endl;
    gr.imprimir(vizinhos);
}

// Extrai IDs de um vetor de Vertice
static vector<int> idsOf(const vector<Vertice>& vs) {
    vector<int> ids;
    ids.reserve(vs.size());
    for (const auto& v : vs) ids.push_back(v.getId());
    return ids;
}

// Compara vetores de ids; imprime detalhe se falhar
static bool expectEqualIds(const string& testName, const vector<int>& got, const vector<int>& expected) {
    if (got == expected) {
        cout << "[PASS] " << testName << "\n";
        return true;
    } else {
        cout << " [FAIL] " << testName << "\n";
        cout << "  Esperado: ";
        for (int x : expected) cout << x << ' ';
        cout << "\n  Obtido : ";
        for (int x : got) cout << x << ' ';
        cout << "\n";
        return false;
    }
}

static int failures = 0;
static void check(const string& name, const vector<int>& got, const vector<int>& expected) {
    if (!expectEqualIds(name, got, expected)) ++failures;
}

// Helper que cria n vértices no grafo e retorna os objetos Vertice corretos (com os ids reais)
static vector<Vertice> criarVertices(GrafoLista& g, int n) {
    Vertice dummy(0,false,false);
    vector<Vertice> res;
    for (int i = 0; i < n; ++i) {
        g.adicionarVertice(dummy);
        int id = g.getUltimoId(); // usa id real atribuído pelo grafo
        res.emplace_back(id, false, false);
    }
    return res;
}

void testeBfsOrdemCaminho() {
    GrafoLista g(false,false,false,false,false,false);
    auto vs = criarVertices(g, 4); // cria 4 vértices, ids reais consecutivos

    g.adicionarAresta(vs[0], vs[1]);
    g.adicionarAresta(vs[1], vs[2]);
    g.adicionarAresta(vs[2], vs[3]);

    auto ordemBFS = g.buscaEmLargura(vs[0]);
    check("BFS - ordem linear", idsOf(ordemBFS),
          {vs[0].getId(), vs[1].getId(), vs[2].getId(), vs[3].getId()});

    auto caminho = g.caminhoEmLargura(vs[0], vs[3]);
    check("BFS - caminho mínimo", idsOf(caminho),
          {vs[0].getId(), vs[1].getId(), vs[2].getId(), vs[3].getId()});
}

void testeDfsOrdemRecursiva() {
    GrafoLista g(false,false,false,false,false,false);
    auto vs = criarVertices(g, 5); // ids consecutivos

    g.adicionarAresta(vs[0], vs[1]); // 0 -> 1
    g.adicionarAresta(vs[0], vs[2]); // 0 -> 2
    g.adicionarAresta(vs[1], vs[3]); // 1 -> 3
    g.adicionarAresta(vs[1], vs[4]); // 1 -> 4

    auto ordemDFS = g.buscaEmProfundidade(vs[0]);
    // Esperado: 0,1,3,4,2 (seguindo ordem de inserção)
    check("DFS recursiva - ordem esperada", idsOf(ordemDFS),
          {vs[0].getId(), vs[1].getId(), vs[3].getId(), vs[4].getId(), vs[2].getId()});
}

void testeComponentesDesconexosDfsCompleta() {
    GrafoLista g(false,false,false,false,false,false);
    auto vs = criarVertices(g, 5); // ids consecutivos

    // componente 1-2-3
    g.adicionarAresta(vs[0], vs[1]);
    g.adicionarAresta(vs[1], vs[2]);
    // componente 4-5
    g.adicionarAresta(vs[3], vs[4]);

    auto ordemCompleta = g.buscaEmProfundidadeCompleta(vs[0]);
    // Esperado: todos os vértices, incluindo componentes desconexos
    check("DFS completa (componentes desconexos)", idsOf(ordemCompleta),
     {vs[0].getId(), vs[1].getId(), vs[2].getId(), 0, vs[3].getId(), vs[4].getId()});
}

void testeCiclo() {
    GrafoLista g(false,false,false,false,false,false);
    auto vs = criarVertices(g, 3);

    g.adicionarAresta(vs[0], vs[1]);
    g.adicionarAresta(vs[1], vs[2]);
    g.adicionarAresta(vs[2], vs[0]);

    auto ordemBFS = g.buscaEmLargura(vs[0]);
    check("BFS em ciclo", idsOf(ordemBFS),
          {vs[0].getId(), vs[1].getId(), vs[2].getId()});

    auto ordemDFS = g.buscaEmProfundidade(vs[0]);
    check("DFS em ciclo", idsOf(ordemDFS),
          {vs[0].getId(), vs[1].getId(), vs[2].getId()});
}

void testeSelfLoop() {
    GrafoLista g(false,false,false,false,false,false);
    auto vs = criarVertices(g, 2);

    g.adicionarAresta(vs[0], vs[0]); // self-loop
    g.adicionarAresta(vs[0], vs[1]);

    auto ordemBFS = g.buscaEmLargura(vs[0]);
    check("BFS com self-loop", idsOf(ordemBFS),
          {vs[0].getId(), vs[1].getId()});

    auto ordemDFS = g.buscaEmProfundidade(vs[0]);
    check("DFS com self-loop", idsOf(ordemDFS),
          {vs[0].getId(), vs[1].getId()});
}

void testeVerticeIsolado() {
    GrafoLista g(false,false,false,false,false,false);
    auto vs = criarVertices(g, 1);

    auto ordemBFS = g.buscaEmLargura(vs[0]);
    check("BFS - vértice isolado", idsOf(ordemBFS),
          {vs[0].getId()});

    auto ordemDFS = g.buscaEmProfundidade(vs[0]);
    check("DFS - vértice isolado", idsOf(ordemDFS),
          {vs[0].getId()});
}

void testeExcecaoVerticeInexistente() {
    GrafoLista g(false,false,false,false,false,false);
    Vertice v999(999,false,false);
    bool lancou = false;
    try {
        auto r = g.buscaEmLargura(v999);
    } catch (const std::invalid_argument&) {
        lancou = true;
    }
    if (lancou) cout << "[PASS] Exceção para vértice inexistente\n";
    else { cout << "[FAIL] Esperava exceção para vértice inexistente\n"; ++failures; }
}

int main() {
    TesteDirecionado();
    TesteNaoDirecionado();
    TestePonderado();
    TesteRotulado();

     cout << "=== Iniciando testes BFS/DFS ===\n";

    testeBfsOrdemCaminho();
    testeDfsOrdemRecursiva();
    testeComponentesDesconexosDfsCompleta();
    testeCiclo();
    testeSelfLoop();
    testeVerticeIsolado();
    testeExcecaoVerticeInexistente();

    if (failures == 0) {
        cout << "\n== TODOS OS TESTES PASSARAM ==\n";
        return 0;
    } else {
        cout << "\n== FALHARAM " << failures << " TESTE(S) ==\n";
        return 2;
    }
    return 0;
}