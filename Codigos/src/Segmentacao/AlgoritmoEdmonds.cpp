// //#pragma once

// #include <vector>
// #include <iostream>
// #include <algorithm>
// #include <map>
// #include <limits>
// #include <fstream>
// #include <cstdlib>
// #include <filesystem>


// #include "../Grafo/Lista/GrafoLista.hpp"
// #include "../Grafo/Matriz/GrafoMatriz.hpp"

// using namespace std;


// struct ArestaEdmonds {
//     int u, v, peso, idOriginal;
// };

// struct ResultadoEdmonds {
//     int custoTotal;
//     vector<ArestaEdmonds> arestasEscolhidas;
// };


// void salvarImagemSegmentada(int largura, int altura, vector<ArestaEdmonds>& arestas, string nomeArquivo) {
//     cout << "\n--------------------------------------------------" << endl;
//     cout << "Tentando salvar imagem em: " << nomeArquivo << endl;

//     int LIMIAR_CORTE = 30;

//     // Estrutura para busca (DFS/BFS) nos componentes
//     vector<vector<int>> adj(largura * altura);
//     for (const auto& a : arestas) {
//         if (a.peso < LIMIAR_CORTE) {
//             adj[a.u].push_back(a.v);
//             adj[a.v].push_back(a.u);
//         }
//     }

//     int n = largura * altura;
//     vector<int> componente(n, -1);
//     int numComponentes = 0;
//     vector<vector<int>> cores;

//     for (int i = 0; i < n; i++) {
//         if (componente[i] == -1) {
//             numComponentes++;
//             cores.push_back({rand() % 255, rand() % 255, rand() % 255});

//             vector<int> fila;
//             fila.push_back(i);
//             componente[i] = numComponentes - 1;

//             int head = 0;
//             while(head < fila.size()){
//                 int u = fila[head++];
//                 for(int v : adj[u]){
//                     if(componente[v] == -1){
//                         componente[v] = numComponentes - 1;
//                         fila.push_back(v);
//                     }
//                 }
//             }
//         }
//     }


//     ofstream imgFile(nomeArquivo);


//     if (!imgFile.is_open()) {
//         cout << "[ERRO FATAL] O Windows bloqueou a criacao do arquivo!" << endl;
//         cout << "Motivo: Permissao negada ou pasta inexistente." << endl;
//         cout << "Tente rodar o Code::Blocks como Administrador ou mude a pasta." << endl;
//         return;
//     }

//     imgFile << "P3\n" << largura << " " << altura << "\n255\n";

//     for (int y = 0; y < altura; y++) {
//         for (int x = 0; x < largura; x++) {
//             int id = y * largura + x;
//             int compID = componente[id];
//             imgFile << cores[compID][0] << " " << cores[compID][1] << " " << cores[compID][2] << " ";
//         }
//         imgFile << "\n";
//     }
//     imgFile.close();

//     cout << "SUCESSO! Arquivo salvo." << endl;

//     try {
//         cout << "Localizacao: " << std::filesystem::current_path() << "\\" << nomeArquivo << endl;
//     } catch (...) {
//         cout << "Localizacao: Na mesma pasta do executavel." << endl;
//     }
//     cout << "--------------------------------------------------" << endl;
// }


// ResultadoEdmonds executarEdmonds(int numVertices, int raiz, vector<ArestaEdmonds>& arestas) {
//     ResultadoEdmonds resultado;
//     resultado.custoTotal = 0;


//     vector<int> menorIn(numVertices, -1);
//     vector<int> minPeso(numVertices, 2147483647);

//     for (int i = 0; i < arestas.size(); i++) {
//         int u = arestas[i].u;
//         int v = arestas[i].v;
//         int w = arestas[i].peso;

//         if (u == v || v == raiz) continue;

//         if (w < minPeso[v]) {
//             minPeso[v] = w;
//             menorIn[v] = i;
//         }
//     }

//     for (int i = 0; i < numVertices; i++) {
//         if (i != raiz && menorIn[i] == -1) {
//             return {-1, {}};
//         }
//     }


//     vector<int> grupo(numVertices, -1);
//     vector<int> visitado(numVertices, -1);
//     vector<bool> noCiclo(numVertices, false);
//     int contadorCiclo = 0;

//     for (int i = 0; i < numVertices; i++) {
//         if (i == raiz) continue;
//         int v = i;
//         while (v != raiz && visitado[v] != i && grupo[v] == -1) {
//             visitado[v] = i;
//             v = arestas[menorIn[v]].u;
//         }
//         if (v != raiz && grupo[v] == -1) {
//             int u = v;
//             while (grupo[u] == -1) {
//                 grupo[u] = contadorCiclo;
//                 noCiclo[u] = true;
//                 u = arestas[menorIn[u]].u;
//                 if (u == v) break;
//             }
//             contadorCiclo++;
//         }
//     }

//     if (contadorCiclo == 0) {
//         for (int i = 0; i < numVertices; i++) {
//             if (i != raiz) {
//                 resultado.arestasEscolhidas.push_back(arestas[menorIn[i]]);
//                 resultado.custoTotal += arestas[menorIn[i]].peso;
//             }
//         }
//         return resultado;
//     }


//     int numVerticesContraidos = 0;
//     vector<int> novosIds(numVertices);
//     for (int i = 0; i < numVertices; i++) {
//         if (noCiclo[i]) novosIds[i] = numVertices - contadorCiclo + grupo[i];
//         else novosIds[i] = numVerticesContraidos++;
//     }

//     int totalNovosVertices = numVerticesContraidos + contadorCiclo;
//     vector<ArestaEdmonds> novasArestas;

//     for (const auto& aresta : arestas) {
//         int u = aresta.u;
//         int v = aresta.v;
//         int novoU = novosIds[u];
//         int novoV = novosIds[v];

//         if (novoU != novoV) {
//             int novoPeso = aresta.peso;
//             if (noCiclo[v]) novoPeso -= minPeso[v];
//             novasArestas.push_back({novoU, novoV, novoPeso, aresta.idOriginal});
//         }
//     }


//     ResultadoEdmonds resultadoRecursivo = executarEdmonds(totalNovosVertices, novosIds[raiz], novasArestas);
//     if (resultadoRecursivo.custoTotal == -1) return {-1, {}};

//     vector<bool> cicloResolvido(contadorCiclo, false);
//     for (const auto& arestaRec : resultadoRecursivo.arestasEscolhidas) {
//         ArestaEdmonds arestaOriginal;
//         bool achou = false;
//         for(auto& a : arestas) {
//             if(a.idOriginal == arestaRec.idOriginal) {
//                 arestaOriginal = a;
//                 achou = true;
//                 break;
//             }
//         }
//         if(achou) {
//              resultado.arestasEscolhidas.push_back(arestaOriginal);
//              if (noCiclo[arestaOriginal.v]) cicloResolvido[grupo[arestaOriginal.v]] = true;
//         }
//     }

//     for (int i = 0; i < numVertices; i++) {
//         if (i != raiz && noCiclo[i]) {
//             bool conflito = false;
//             for(auto& escolhida : resultado.arestasEscolhidas) {
//                 if(escolhida.v == i) { conflito = true; break; }
//             }
//             if(!conflito) resultado.arestasEscolhidas.push_back(arestas[menorIn[i]]);
//         }
//     }

//     resultado.custoTotal = 0;
//     for(auto& a : resultado.arestasEscolhidas) resultado.custoTotal += a.peso;

//     return resultado;
// }



// // Ponte para LISTA
// void resolverEdmondsNoSeuGrafo(GrafoLista& grafo, int idRaiz) {
//     int n = grafo.getQuantidadeVertices();
//     vector<ArestaEdmonds> listaArestas;
//     int idCount = 0;

//     for (int u = 0; u < n; u++) {
//         if (u >= grafo.listaPrincipal.size()) break;
//         for (const auto& verticeDestino : grafo.listaPrincipal[u].arestas) {
//             int v = verticeDestino.getId();
//             int peso = verticeDestino.getPeso();
//             listaArestas.push_back({u, v, peso, idCount++});
//         }
//     }

//     cout << "\nRodando Edmonds (Lista)... Raiz: " << idRaiz << endl;
//     ResultadoEdmonds res = executarEdmonds(n, idRaiz, listaArestas);

//     if (res.custoTotal == -1) {
//         cout << "Erro: Grafo desconexo ou raiz invalida.\n";
//     } else {
//         cout << "--- Resultado Encontrado ---\n";
//         cout << "Custo Total: " << res.custoTotal << endl;


//         salvarImagemSegmentada(50, 34, res.arestasEscolhidas, "Resultado_Lista.ppm");
//     }
// }

// // Ponte para MATRIZ
// void resolverEdmondsNoGrafoMatriz(GrafoMatriz& grafo, int idRaiz) {
//     int n = grafo.getQuantidadeVertices();
//     vector<ArestaEdmonds> listaArestas;
//     int idCount = 0;

//     for (int u = 0; u < n; u++) {
//         for (int v = 0; v < n; v++) {
//             if (grafo.existeAresta(u, v)) {
//                 int peso = grafo.getPeso(u, v);
//                 listaArestas.push_back({u, v, peso, idCount++});
//             }
//         }
//     }

//     cout << "\nRodando Edmonds (Matriz)... Raiz: " << idRaiz << endl;
//     ResultadoEdmonds res = executarEdmonds(n, idRaiz, listaArestas);

//     if (res.custoTotal == -1) {
//         cout << "Erro: Grafo desconexo ou raiz invalida.\n";
//     } else {
//         cout << "--- Resultado Encontrado ---\n";
//         cout << "Custo Total: " << res.custoTotal << endl;

//         salvarImagemSegmentada(50, 34, res.arestasEscolhidas, "Resultado_Matriz.ppm");
//     }
// }
