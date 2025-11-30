#ifndef INTERFACEIMAGEM_HPP
#define INTERFACEIMAGEM_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "../../libs/std/stb_image.h"
#include "../Grafo/Lista/GrafoLista.hpp"


struct Pixel {
    unsigned char r, g, b;
};

double calcularPesoEuclidiano(vector<double> rgb_origem, vector<double> rgb_final);

vector<double> getRBG(unsigned char* img, int idx1);
double criarRGBunico(vector<double> rgb);

Pixel decodeRGBunico(double rgbUnico);

GrafoLista* GrafoFromImagem(string nomeArquivo, bool isDirecionado);

vector<Pixel> extrairPixelsDoGrafo(GrafoLista* grafo, int largura, int altura);

void salvarPPM(const string& nomeArquivo, int largura, int altura, const vector<Pixel>& pixels);

void SaveImageFromGrafo(string nomeArquivo, GrafoLista* grafo, int largura, int altura);
#endif