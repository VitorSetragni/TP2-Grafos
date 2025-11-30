//#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

// Define apenas se ainda não foi definido no main ou outro lugar
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/std/stb_image.h"
#endif

#include "../Grafo/Lista/GrafoLista.hpp"

using namespace std;

/**
 * Calcula a distância Euclidiana entre dois pixels RGB
 * @param img Ponteiro para o array de dados da imagem
 * @param idx1 Índice linear do primeiro pixel
 * @param idx2 Índice linear do segundo pixel
 * @return A distância euclidiana (double) convertida para o tipo do peso.
 */
double calcularPesoEuclidiano(unsigned char* img, int idx1, int idx2) {
    // Como a imagem tem 3 canais, multiplicamos o índice linear por 3
    int p1 = idx1 * 3;
    int p2 = idx2 * 3;

    double r = static_cast<double>(img[p1]) - img[p2];
    double g = static_cast<double>(img[p1 + 1]) - img[p2 + 1];
    double b = static_cast<double>(img[p1 + 2]) - img[p2 + 2];

    return std::sqrt(r*r + g*g + b*b);
}

// GrafoMatriz* gerarGrafoImagemReal(string nomeArquivo) {
//     cout << "\n--- Carregando Imagem Real (Matriz): " << nomeArquivo << " ---\n";

//     int largura, altura, canais;
//     unsigned char* img = stbi_load(nomeArquivo.c_str(), &largura, &altura, &canais, 1);

//     if (img == nullptr) {
//         cout << "[ERRO] Nao foi possivel abrir a imagem.\n";
//         return nullptr;
//     }

//     int totalVertices = largura * altura;

//     GrafoMatriz* novoGrafo = new GrafoMatriz(totalVertices, true, true, true, false, false);

//     cout << "Gerando Matriz... (" << largura << "x" << altura << ")\n";

//     for (int y = 0; y < altura; y++) {
//         for (int x = 0; x < largura; x++) {
//             int u = y * largura + x;
//             int valorPixel = img[u];


//             if (x + 1 < largura) {
//                 int v = y * largura + (x + 1);
//                 int peso = abs(valorPixel - img[v]) + 1; // +1 para evitar peso 0
//                 novoGrafo->adicionarAresta(u, v, peso);
//                 novoGrafo->adicionarAresta(v, u, peso); // Volta
//             }


//             if (y + 1 < altura) {
//                 int v = (y + 1) * largura + x;
//                 int peso = abs(valorPixel - img[(y+1)*largura + x]) + 1; // +1 para evitar peso 0
//                 novoGrafo->adicionarAresta(u, v, peso);
//                 novoGrafo->adicionarAresta(v, u, peso); // Volta
//             }
//         }
//     }
//     stbi_image_free(img);
//     cout << "Grafo Matriz pronto!\n";
//     return novoGrafo;
// }

GrafoLista* gerarGrafoImagemRealLista(string nomeArquivo) {
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
    GrafoLista* novoGrafo = new GrafoLista(false, false, true, true, false, false, totalVertices);

    cout << "Gerando Lista com pesos RGB Euclidianos... (" << largura << "x" << altura << ")\n";

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            // Índice do vértice atual na malha (0 a totalVertices-1)
            int u = y * largura + x;

            // --- Vizinho da DIREITA ---
            if (x + 1 < largura) {
                int v = y * largura + (x + 1);
                
                double peso = calcularPesoEuclidiano(img, u, v);

                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
            }

            // --- Vizinho de BAIXO ---
            if (y + 1 < altura) {
                int v = (y + 1) * largura + x;
                
                double peso = calcularPesoEuclidiano(img, u, v);

                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
            }
        }
    }

    stbi_image_free(img);
    cout << "Grafo Lista pronto!\n";
    return novoGrafo;
}