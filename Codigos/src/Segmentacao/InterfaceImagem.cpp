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

#include "ISegmentador.hpp"

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
    double g = rgb_origem[1] - rgb_final[1];
    double b = rgb_origem[2] - rgb_final[2];

    return sqrt(r*r + g*g + b*b);
}

vector<double> getRBG(unsigned char* img, int idx1){
    int p1 = idx1 * 3;

    double r = static_cast<double>(img[p1]);
    double g = static_cast<double>(img[p1 + 1]);
    double b = static_cast<double>(img[p1 + 2]);

    vector<double> rgb = {r,g,b};
    return rgb;
}

// Usado na leitura da imagem para o grafo
double criarRGBunico(vector<double> rgb){
    // Garante que não ultrapasse 255 por segurança
    long long r = static_cast<long long>(rgb[0]) % 1000;
    long long g = static_cast<long long>(rgb[1]) % 1000;
    long long b = static_cast<long long>(rgb[2]) % 1000;

    return (double)(r * 1000000 + g * 1000 + b);
}

// Usado para pintar o grafo
double encodeRGBunico(Pixel p) {
    long long r = p.r;
    long long g = p.g;
    long long b = p.b;
    return (double)(r * 1000000 + g * 1000 + b);
}

// CORREÇÃO CRÍTICA: Decodifica usando a mesma base 1000
Pixel decodeRGBunico(double valor) {
    // Converte para inteiro longo para operar
    long long v = static_cast<long long>(valor);
    
    Pixel p;
    
    // Extrai o Blue
    p.b = static_cast<unsigned char>(v % 1000);
    
    // Remove o B e extrai o Green
    v /= 1000;
    p.g = static_cast<unsigned char>(v % 1000);
    
    // Remove o Green e o que sobra é o Red
    v /= 1000;
    p.r = static_cast<unsigned char>(v);
    
    return p;
}

// double encodeRGBunico(Pixel p) {
//     return p.r * 1000000 + p.b * 1000 + p.b * 1;
// }

// Pixel decodeRGBunico(double rgbUnico){
//     int r = floor(rgbUnico / 1000000.0);
//     int g = floor((rgbUnico - r*1000000.0) / 1000.0);
//     int b = rgbUnico - r*1000000.0 - g*1000.0;

//     return Pixel{(unsigned char)r, (unsigned char)g, (unsigned char)b};
// }

// GrafoLista* grafoFromImagem(string nomeArquivo, bool isDirecionado) {
//     cout << "\n--- Carregando Imagem Real (Lista): " << nomeArquivo << " ---\n";

//     int largura, altura, canaisOriginais;
    
//     // Forçamos o carregamento com 3 canais (RGB)
//     // O último parâmetro '3' garante que teremos R, G, B
//     unsigned char* img = stbi_load(nomeArquivo.c_str(), &largura, &altura, &canaisOriginais, 3);

//     if (img == nullptr) {
//         cout << "[ERRO] Nao foi possivel abrir a imagem.\n";
//         return nullptr;
//     }

//     int totalVertices = largura * altura;

//     // Instancia o grafo
//     GrafoLista* novoGrafo = new GrafoLista(false, isDirecionado, true, true, false, false, 0);

//     cout << "Gerando Lista com pesos RGB Euclidianos... (" << largura << "x" << altura << ")\n";

//     for (int y = 0; y < altura; y++) {
//         for (int x = 0; x < largura; x++) {
//             // Índice do vértice atual na malha (0 a totalVertices-1)
//             int u = y * largura + x;
//             vector<double> rgb_u = getRBG(img,u);
//             double unico = criarRGBunico(rgb_u);
//             novoGrafo->adicionarVertice(Vertice(u,false,true,unico,""));

//             // Vizinho da DIREITA
//             if (x + 1 < largura) {
//                 int v = y * largura + (x + 1);

//                 vector<double> rgb_v = getRBG(img,v);                
//                 double peso = calcularPesoEuclidiano(rgb_u,rgb_v);
//                 novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
//                 if(isDirecionado){
//                     novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
//                 }
//             }

//             // Vizinho de BAIXO
//             if (y + 1 < altura) {
//                 int v = (y + 1) * largura + x;
                
//                 vector<double> rgb_v = getRBG(img,v);
                
//                 double peso = calcularPesoEuclidiano(rgb_u,rgb_v);

//                 novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                
//                 if(isDirecionado){
//                     novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
//                 }
//             }
//         }
//     }

//     stbi_image_free(img);
//     cout << "Grafo Lista pronto!\n";
//     return novoGrafo;
// }

// GrafoLista* grafoFromImagem(string nomeArquivo, bool isDirecionado) {
//     cout << "\n--- Carregando Imagem Real (Lista): " << nomeArquivo << " ---\n";

//     int largura, altura, canaisOriginais;
//     unsigned char* img = stbi_load(nomeArquivo.c_str(), &largura, &altura, &canaisOriginais, 3);

//     if (img == nullptr) {
//         cout << "[ERRO] Nao foi possivel abrir a imagem.\n";
//         return nullptr;
//     }

//     // Inicializa grafo vazio
//     GrafoLista* novoGrafo = new GrafoLista(
//         false, isDirecionado, true, true, false, false, 0
//     );

//     cout << "Gerando Vertices...\n";

//     // Cria apenas os vértices
//     for (int y = 0; y < altura; y++) {
//         for (int x = 0; x < largura; x++) {
//             int u = y * largura + x;
//             vector<double> rgb_u = getRBG(img, u);
//             double unico = criarRGBunico(rgb_u);
            
//             // Adiciona o vértice
//             novoGrafo->adicionarVertice(Vertice(u, false, true, unico, ""));
//         }
//     }

//     cout << "Gerando Arestas...\n";

//     // Cria arestas agora que todos os vizinhos existem
//     for (int y = 0; y < altura; y++) {
//         for (int x = 0; x < largura; x++) {
//             int u = y * largura + x;
//             vector<double> rgb_u = getRBG(img, u);

//             // Vizinho da DIREITA
//             if (x + 1 < largura) {
//                 int v = y * largura + (x + 1);
//                 vector<double> rgb_v = getRBG(img, v);
//                 double peso = calcularPesoEuclidiano(rgb_u, rgb_v);

//                 novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                
//                 if (isDirecionado) {
//                     novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
//                 }
//             }

//             // Vizinho de BAIXO
//             if (y + 1 < altura) {
//                 int v = (y + 1) * largura + x;
//                 vector<double> rgb_v = getRBG(img, v);
//                 double peso = calcularPesoEuclidiano(rgb_u, rgb_v);

//                 novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                
//                 if (isDirecionado) {
//                     novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
//                 }
//             }
//         }
//     }

//     stbi_image_free(img);
//     cout << "Grafo Lista pronto! Vertices: " << novoGrafo->getQuantidadeVertices() << endl;
    
//     // Debug essencial: Verificar se arestas foram criadas
//     cout << "Arestas Totais: " << novoGrafo->getQuantidadeArestas() << endl;

//     return novoGrafo;
// }

GrafoLista* grafoFromImagem(string nomeArquivo, bool isDirecionado) {
    cout << "\n--- Carregando Imagem Real (Lista): " << nomeArquivo << " ---\n";

    int largura, altura, canaisOriginais;
    unsigned char* img = stbi_load(nomeArquivo.c_str(), &largura, &altura, &canaisOriginais, 3);

    if (img == nullptr) {
        cout << "[ERRO] Nao foi possivel abrir a imagem.\n";
        return nullptr;
    }

    GrafoLista* novoGrafo = new GrafoLista(
        false, isDirecionado, true, true, false, false, 0
    );

    cout << "Gerando Vertices..." << endl;
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int u = y * largura + x;
            vector<double> rgb_u = getRBG(img, u);
            double unico = criarRGBunico(rgb_u);
            novoGrafo->adicionarVertice(Vertice(u, false, true, unico, ""));
        }
    }
    // CHECKPOINT 1
    cout << "Vertices criados: " << novoGrafo->getQuantidadeVertices() << endl;

    cout << "Gerando Arestas..." << endl;
    int arestasAdicionadas = 0;

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            int u = y * largura + x;
            vector<double> rgb_u = getRBG(img, u);

            // Vizinho da DIREITA
            if (x + 1 < largura) {
                int v = y * largura + (x + 1);
                vector<double> rgb_v = getRBG(img, v);
                double peso = calcularPesoEuclidiano(rgb_u, rgb_v);
                
                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                arestasAdicionadas++; 

                if (!isDirecionado) {
                    novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
                }
            }
            // Vizinho de BAIXO
            if (y + 1 < altura) {
                int v = (y + 1) * largura + x;
                vector<double> rgb_v = getRBG(img, v);
                double peso = calcularPesoEuclidiano(rgb_u, rgb_v);

                novoGrafo->adicionarAresta(Vertice(u, false, true), Vertice(v, false, true), peso);
                arestasAdicionadas++;

                if (isDirecionado) {
                    novoGrafo->adicionarAresta(Vertice(v, false, true), Vertice(u, false, true), peso);
                }
            }
        }
    }

    stbi_image_free(img);
    cout << "Grafo Lista pronto!" << endl;
    cout << "Tentativas de adicao de arestas (Loop): " << arestasAdicionadas << endl;
    cout << "Arestas reais no grafo: " << novoGrafo->getQuantidadeArestas() << endl;

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
        cout << "Erro ao abrir arquivo: " << nomeArquivo << endl;
        return;
    }

    // Cabeçalho PPM P6
    out << "P6\n" << largura << " " << altura << "\n255\n";

    // Escrita segura byte a byte para evitar problemas de struct padding
    for (const auto& p : pixels) {
        out.put(p.r);
        out.put(p.g);
        out.put(p.b);
    }

    out.close();
}

void saveImageFromGrafo(string nomeArquivo, GrafoLista* grafo, int largura, int altura){
    if (!grafo) {
        cout << "[ERRO CRITICO] O Grafo a ser pintado é nulo!" << endl;
        return; 
    }
    vector<Pixel> pixels = extrairPixelsDoGrafo(grafo, largura, altura);
    salvarPPM(nomeArquivo,largura,altura,pixels);
}

GrafoLista* gerarGrafoPintado(GrafoLista* grafoOriginal, ResultadoSegmentacao& resultado) {
    int numVertices = grafoOriginal->getQuantidadeVertices();
    int numComponentes = resultado.numComponentes;

    // Acumula as cores originais por segmento
    vector<AcumuladorCor> acumuladores(numComponentes);

    for (int i = 0; i < numVertices; i++) {
        // Obtém a cor original do pixel i
        double pesoOriginal = grafoOriginal->listaPrincipal[i].vertice.getPeso();

        Pixel corOriginal = decodeRGBunico(pesoOriginal);

        // Descobre a qual segmento este pixel pertence
        int idComponente = resultado.componentes[i];

        // Acumula
        acumuladores[idComponente].adicionar(corOriginal);
    }

    // Calcula a cor média final para cada segmento
    vector<Pixel> paletaCores(numComponentes);
    for (int c = 0; c < numComponentes; c++) {
        paletaCores[c] = acumuladores[c].calcularMedia();
    }

    // Criar o novo grafo (cópia estrutural, mas com pesos atualizados)
    
    // GrafoLista* grafoPintado = new GrafoLista(
    //     false, // simples
    //     false, // direcionado
    //     true,  // verticePonderado
    //     true,  // arestaPonderada
    //     false, // verticeRotulado
    //     false, // arestaRotulada
    //     0
    // );

    // // Configura vértices com a cor média
    // for (int i = 0; i < numVertices; i++) {
    //     int idComponente = resultado.componentes[i];

    //     if (idComponente >= 0 && idComponente < numComponentes) {
    //         Pixel corMedia = paletaCores[idComponente];

    //         double novoPesoCor = encodeRGBunico(corMedia);
            
    //         grafoPintado->listaPrincipal[i].vertice.setPeso(novoPesoCor);
    //     }
    // }

    // Cria o novo grafo
    GrafoLista* grafoPintado = new GrafoLista(
        false, // simples
        false, // direcionado
        true,  // verticePonderado
        true,  // arestaPonderada
        false, // verticeRotulado
        false, // arestaRotulada
        0
    );

    // Configura vértices
    for (int i = 0; i < numVertices; i++) {
        int idComponente = resultado.componentes[i];
        double novoPesoCor = 0.0;

        if (idComponente >= 0 && idComponente < numComponentes) {
            Pixel corMedia = paletaCores[idComponente];

            novoPesoCor = encodeRGBunico(corMedia);
        }

        // Adiciona o vértice explicitamente com ID 'i'
        grafoPintado->adicionarVertice(Vertice(i, false, true, novoPesoCor, ""));
    }

    // Verifica se o grafo foi criado corretamente
    if (grafoPintado->getQuantidadeVertices() != numVertices) {
        cout << "[ERRO] O construtor do GrafoLista nao criou os vertices solicitados." << endl;
        return grafoPintado;
    }

    return grafoPintado;
}

GrafoLista* gerarGrafoPintadoAleatorio(GrafoLista* grafoOriginal, ResultadoSegmentacao& resultado) {
    if (!grafoOriginal) {
        cout << "[ERRO CRITICO] O Grafo a ser pintado é nulo!" << endl;
        return nullptr; 
    }

    int numVertices = grafoOriginal->getQuantidadeVertices();
    
    // Verifica se a segmentação foi válida
    if (resultado.componentes.size() != static_cast<size_t>(numVertices)) {
        cout << "[ERRO CRITICO] O tamanho do resultado da segmentacao (" 
             << resultado.componentes.size() << ") difere do numero de vertices da imagem (" 
             << numVertices << ")." << endl;
        // Retorna nulo para não crashar
        return nullptr; 
    }

    int numComponentes = resultado.numComponentes;
    
    // Verifica se há componentes
    if (numComponentes <= 0) {
        cout << "[AVISO] Nenhum componente detectado." << endl;
        return new GrafoLista(false, false, true, true, false, false, numVertices);
    }

    // Gera uma paleta de cores aleatórias
    vector<Pixel> paletaCores(numComponentes);
    for (int c = 0; c < numComponentes; c++) {
        paletaCores[c] = {
            static_cast<unsigned char>(rand() % 256),
            static_cast<unsigned char>(rand() % 256),
            static_cast<unsigned char>(rand() % 256)
        };
    }

    // Cria o novo grafo
    GrafoLista* grafoPintado = new GrafoLista(
        false, // simples
        false, // direcionado
        true,  // verticePonderado
        true,  // arestaPonderada
        false, // verticeRotulado
        false, // arestaRotulada
        0
    );

    // Configura vértices
    for (int i = 0; i < numVertices; i++) {
        int idComponente = resultado.componentes[i];
        double novoPesoCor = 0.0;

        if (idComponente >= 0 && idComponente < numComponentes) {
            Pixel corAleatoria = paletaCores[idComponente];
            novoPesoCor = encodeRGBunico(corAleatoria);
        }

        // Adiciona o vértice explicitamente com ID 'i'
        grafoPintado->adicionarVertice(Vertice(i, false, true, novoPesoCor, ""));
    }

    // Verifica se o grafo foi criado corretamente
    if (grafoPintado->getQuantidadeVertices() != numVertices) {
        cout << "[ERRO] O construtor do GrafoLista nao criou os vertices solicitados." << endl;
        return grafoPintado;
    }

    return grafoPintado;
}