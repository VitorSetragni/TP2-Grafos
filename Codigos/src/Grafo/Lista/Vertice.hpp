#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <string>

class Vertice {
private:
    int id;
    double peso;
    std::string rotulo;

public:
    bool rotulado;
    bool ponderado;

    Vertice();
    Vertice(int id, bool rotulado, bool ponderado);
    Vertice(int id, double peso, std::string rotulo);
    Vertice(int id, bool rotulado, bool ponderado, double peso, std::string rotulo);
    Vertice(const Vertice& v);

    void setPeso(int p);
    void setRotulo(std::string r);
    void setId(int id);

    int getId() const;
    double getPeso() const;
    std::string getRotulo() const;

    bool operator==(const Vertice& other) const;
    bool operator<(const Vertice& other) const;

    std::string toString() const;
};

#endif
