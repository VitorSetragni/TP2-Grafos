#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/std/stb_image.h"


#include "../Matriz/GrafoMatriz.hpp"
#include "../Lista/GrafoLista.hpp"

using namespace std;


GrafoMatriz* gerarGrafoImagemReal(string nomeArquivo) {
    cout << "\n--- Carregando Imagem Real (Matriz): " << nomeArquivo << " ---\n";

    int largura, altura, canais;
    unsigned char* img = stbi_load(nomeArquivo.c_str(), &largura, &altura, &canais, 1);

    if (img == nullptr) {
        cout << "[ERRO] Nao foi possivel abrir a imagem.\n";
        return nullptr;
    }

    int totalVertices = largura * altura;

    GrafoMatriz* novoGrafo = new GrafoMatriz(totalVertices, true, true, true, false, false);

    cout << "Gerando Matriz... (" << largura << "x" << altura << ")\n";

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int u = y * largura + x;
            int valorPixel = img[u];


            if (x + 1 < largura) {
                int v = y * largura + (x + 1);
                int peso = abs(valorPixel - img[v]) + 1; // +1 para evitar peso 0
                novoGrafo->adicionarAresta(u, v, peso);
                novoGrafo->adicionarAresta(v, u, peso); // Volta
            }


            if (y + 1 < altura) {
                int v = (y + 1) * largura + x;
                int peso = abs(valorPixel - img[(y+1)*largura + x]) + 1; // +1 para evitar peso 0
                novoGrafo->adicionarAresta(u, v, peso);
                novoGrafo->adicionarAresta(v, u, peso); // Volta
            }
        }
    }
    stbi_image_free(img);
    cout << "Grafo Matriz pronto!\n";
    return novoGrafo;
}


// ---------------------------------------------------------
GrafoLista* gerarGrafoImagemRealLista(string nomeArquivo) {
    cout << "\n--- Carregando Imagem Real (Lista): " << nomeArquivo << " ---\n";

    int largura, altura, canais;
    unsigned char* img = stbi_load(nomeArquivo.c_str(), &largura, &altura, &canais, 1);

    if (img == nullptr) {
        cout << "[ERRO] Nao foi possivel abrir a imagem.\n";
        return nullptr;
    }

    int totalVertices = largura * altura;

    GrafoLista* novoGrafo = new GrafoLista(false, true, true, true, false, false, totalVertices);

    cout << "Gerando Lista... (" << largura << "x" << altura << ")\n";

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int u = y * largura + x;
            int valorPixel = img[u];

            // Vizinho da DIREITA
            if (x + 1 < largura) {
                int v = y * largura + (x + 1);
                int peso = abs(valorPixel - img[v]) + 1;


                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
            }

            // Vizinho de BAIXO
            if (y + 1 < altura) {
                int v = (y + 1) * largura + x;
                int peso = abs(valorPixel - img[(y+1)*largura + x]) + 1;

                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
            }
        }
    }
    stbi_image_free(img);
    cout << "Grafo Lista pronto!\n";
    return novoGrafo;
}
