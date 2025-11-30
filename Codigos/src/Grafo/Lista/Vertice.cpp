#include "Vertice.hpp"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Classe de Vertice genérica

/**
 *   Construtor Vazio de Vertice
 *
 *   @return Vertice com id e peso 0, rotulo vazio e não rotulado e ponderado
 */
Vertice::Vertice() : Vertice(0, false, false, 0, "") {
}

/**
 *   Construtor de Vértice sem peso e rotulo
 *
 *   @param id Inteiro que define o id do vértice
 *   @param rotulado Boleano que determina se o vértice é rotulado ou não
 *   @param ponderado Boleano que determina se o vértice é ponderado ou não
 */
Vertice::Vertice(int id, bool rotulado, bool ponderado) : Vertice(id, rotulado, ponderado, 0, "") {
}

/**
 *   Construtor de Vértice com peso e rotulo
 *
 *   @param id Inteiro que define o id do vértice
 *   @param peso Inteiro que define o peso
 *   @param rotulo String que define o rotulo
 */
Vertice::Vertice(int id, double peso, string rotulo) : Vertice(id, true, true, peso, rotulo) {
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
Vertice::Vertice(int id, bool rotulado, bool ponderado, double peso, string rotulo) {
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
Vertice::Vertice(Vertice const &v) {
    this->peso = v.peso;
    this->rotulo = v.rotulo;
    this->ponderado = v.ponderado;
    this->rotulado = v.rotulado;
    setId(v.id);
}

void Vertice::setPeso(int p) {
    this->peso = p;
}

void Vertice::setRotulo(string r) {
    this->rotulo = r;
}

void Vertice::setId(int id) {
    this->id = id;
}

int Vertice::getId() const {
    return this->id;
}

double Vertice::getPeso() const {
    return this->peso;
}

string Vertice::getRotulo() const {
    return this->rotulo;
}

bool Vertice::operator==(const Vertice &other) const {
    return this->id == other.id;
}

bool Vertice::operator<(const Vertice &other) const {
    return this->id < other.id;
}

string Vertice::toString() const {
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
