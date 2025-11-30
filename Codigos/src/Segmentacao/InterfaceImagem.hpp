#ifndef INTERFACEIMAGEM_HPP
#define INTERFACEIMAGEM_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "../../libs/std/stb_image.h"
#include "../Grafo/Lista/GrafoLista.hpp"
#include "ISegmentador.hpp"


struct Pixel {
    unsigned char r, g, b;
};

// Estrutura auxiliar para acumular médias
struct AcumuladorCor {
    long long sumR = 0;
    long long sumG = 0;
    long long sumB = 0;
    int count = 0;

    void adicionar(Pixel p) {
        sumR += p.r;
        sumG += p.g;
        sumB += p.b;
        count++;
    }

    Pixel calcularMedia() {
        if (count == 0) return {0, 0, 0};
        return {
            static_cast<unsigned char>(sumR / count),
            static_cast<unsigned char>(sumG / count),
            static_cast<unsigned char>(sumB / count)
        };
    }
};

double calcularPesoEuclidiano(vector<double> rgb_origem, vector<double> rgb_final);

vector<double> getRBG(unsigned char* img, int idx1);
double criarRGBunico(vector<double> rgb);

Pixel decodeRGBunico(double rgbUnico);

GrafoLista* grafoFromImagem(string nomeArquivo, bool isDirecionado);

vector<Pixel> extrairPixelsDoGrafo(GrafoLista* grafo, int largura, int altura);

void salvarPPM(const string& nomeArquivo, int largura, int altura, const vector<Pixel>& pixels);

void SaveImageFromGrafo(string nomeArquivo, GrafoLista* grafo, int largura, int altura);

GrafoLista* gerarGrafoPintado(GrafoLista* grafoOriginal, ResultadoSegmentacao& resultado);

GrafoLista* gerarGrafoPintadoAleatorio(GrafoLista* grafoOriginal, ResultadoSegmentacao& resultado);
#endif