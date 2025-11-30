//#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

// Define apenas se ainda não foi definido no main ou outro lugar

#include "../../libs/std/stb_image.h"

#include "../Grafo/Lista/GrafoLista.hpp"

#include "InterfaceImagem.hpp"

using namespace std;

/**
 * Calcula a distância Euclidiana entre dois pixels RGB
 * @param img Ponteiro para o array de dados da imagem
 * @param idx1 Índice linear do primeiro pixel
 * @param idx2 Índice linear do segundo pixel
 * @return A distância euclidiana (double) convertida para o tipo do peso.
 */
double calcularPesoEuclidiano(vector<double> rgb_origem, vector<double> rgb_final) {
    // Como a imagem tem 3 canais, multiplicamos o índice linear por 3
    double r = rgb_origem[0] - rgb_final[0];
    double g = rgb_origem[1] - rgb_final[0];
    double b = rgb_origem[2] - rgb_final[0];

    return std::sqrt(r*r + g*g + b*b);
}

vector<double> getRBG(unsigned char* img, int idx1){
    int p1 = idx1 * 3;

    double r = static_cast<double>(img[p1]);
    double g = static_cast<double>(img[p1 + 1]);
    double b = static_cast<double>(img[p1 + 2]);

    vector<double> rgb = {r,g,b};
    return rgb;
}

double criarRGBunico(vector<double> rgb){
    double rgbUnico;
    rgbUnico = rgb[0]*1000000 + rgb[1]*1000+ rgb[2] * 1;

    return rgbUnico;
}

Pixel decodeRGBunico(double rgbUnico){
    int r = floor(rgbUnico / 1000000.0);
    int g = floor((rgbUnico - r*1000000.0) / 1000.0);
    int b = rgbUnico - r*1000000.0 - g*1000.0;

    return Pixel{(unsigned char)r, (unsigned char)g, (unsigned char)b};

}

GrafoLista* GrafoFromImagem(string nomeArquivo, bool isDirecionado) {
    cout << "\n--- Carregando Imagem Real (Lista): " << nomeArquivo << " ---\n";

    int largura, altura, canaisOriginais;
    
    // Forçamos o carregamento com 3 canais (RGB)
    // O último parâmetro '3' garante que teremos R, G, B
    unsigned char* img = stbi_load(nomeArquivo.c_str(), &largura, &altura, &canaisOriginais, 3);

    if (img == nullptr) {
        cout << "[ERRO] Nao foi possivel abrir a imagem.\n";
        return nullptr;
    }

    int totalVertices = largura * altura;

    // Instancia o grafo
    GrafoLista* novoGrafo = new GrafoLista(false, isDirecionado, true, true, false, false);

    cout << "Gerando Lista com pesos RGB Euclidianos... (" << largura << "x" << altura << ")\n";

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            // Índice do vértice atual na malha (0 a totalVertices-1)
            int u = y * largura + x;
            vector<double> rgb_u = getRBG(img,u);
            double unico = criarRGBunico(rgb_u);
            novoGrafo->adicionarVertice(Vertice(u,false,true,unico,""));

            // --- Vizinho da DIREITA ---
            if (x + 1 < largura) {
                int v = y * largura + (x + 1);

                vector<double> rgb_v = getRBG(img,v);                
                double peso = calcularPesoEuclidiano(rgb_u,rgb_v);
                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                if(isDirecionado){
                    novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
                }
            }

            // --- Vizinho de BAIXO ---
            if (y + 1 < altura) {
                int v = (y + 1) * largura + x;
                
                vector<double> rgb_v = getRBG(img,v);
                
                double peso = calcularPesoEuclidiano(rgb_u,rgb_v);

                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                
                if(isDirecionado){
                    novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
                }
            }
        }
    }

    stbi_image_free(img);
    cout << "Grafo Lista pronto!\n";
    return novoGrafo;
}

vector<Pixel> extrairPixelsDoGrafo(GrafoLista* grafo, int largura, int altura) {
    int total = largura * altura;
    vector<Pixel> pixels(total);

    for (int v = 0; v < total; v++) {
        Vertice vertice = grafo->getVertice(v);
        Pixel p = decodeRGBunico(vertice.getPeso());
        pixels[v] = p;
    }

    return pixels;
}


void salvarPPM(const string& nomeArquivo, int largura, int altura, const vector<Pixel>& pixels) {
    ofstream out(nomeArquivo, ios::binary);
    if (!out.is_open()) {
        throw runtime_error("Erro ao abrir arquivo para escrita");
    }

    // Cabeçalho PPM binário (P6)
    out << "P6\n" << largura << " " << altura << "\n255\n";

    // Escreve os bytes RGB
    out.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * 3);

    out.close();
}

void SaveImageFromGrafo(string nomeArquivo, GrafoLista* grafo, int largura, int altura){
    vector<Pixel> pixels = extrairPixelsDoGrafo(grafo, largura, altura);
    salvarPPM(nomeArquivo,largura,altura,pixels);
}


