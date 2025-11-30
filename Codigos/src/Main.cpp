#include <iostream>
#include <string>

#include "./Visao/MenuImageSegmentation.cpp" 
#include "./Visao/MenuGrafoManager.cpp" 

#include "../libs/io/io.hpp"
#include "Segmentacao/InterfaceImagem.hpp"
#include "Segmentacao/ISegmentador.hpp"
#include "Segmentacao/MST/SegmentadorMST.hpp"
#include "Segmentacao/MSA/SegmentadorTarjan.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    GrafoLista* grafoImagem = grafoFromImagem("assets/input/elefantes.jpeg", false);

    SegmentadorMST meuSegmentador;

    for (int i = 1; i <= 20; i++) {
        ResultadoSegmentacao resultado = meuSegmentador.segmentar(grafoImagem, i * 50, 100);

        GrafoLista* grafoPintado = gerarGrafoPintado(grafoImagem, resultado, 200);

        stringstream outputPath;
        
        outputPath << "assets/output/MST/MST_elefantes_" << (i * 50) << ".ppm";

        saveImageFromGrafo(outputPath.str(), grafoPintado, 275, 183);
    }

    // GrafoLista* grafoImagem = grafoFromImagem("assets/input/gatos.png", false);

    // SegmentadorMST meuSegmentador;

    // for (int i = 1; i <= 20; i++) {
    //     ResultadoSegmentacao resultado = meuSegmentador.segmentar(grafoImagem, i * 50, 100);

    //     GrafoLista* grafoPintado = gerarGrafoPintado(grafoImagem, resultado, 200);

    //     stringstream outputPath;
        
    //     outputPath << "assets/output/MST_gatos_" << (i * 50) << ".ppm";

    //     saveImageFromGrafo(outputPath.str(), grafoPintado, 888, 489);
    // }

    // GrafoLista* grafoImagem = grafoFromImagem("assets/input/gatos.png", true);

    // SegmentadorTarjan meuSegmentador;

    // for (int i = 1; i <= 10; i++) {
    //     ResultadoSegmentacao resultado = meuSegmentador.segmentar(grafoImagem, i * 10, 100);

    //     GrafoLista* grafoPintado = gerarGrafoPintado(grafoImagem, resultado);

    //     stringstream outputPath;
        
    //     outputPath << "assets/output/MSA/gatos_" << (i * 10) << ".ppm";

    //     saveImageFromGrafo(outputPath.str(), grafoPintado, 888, 489);
    // }

    // GrafoLista* grafoImagem = grafoFromImagem("assets/input/gatos.jpg", false);

    // SegmentadorMST meuSegmentador;

    // cout << "Numero de vertices: " << grafoImagem->getQuantidadeVertices() << endl;
    // ResultadoSegmentacao resultado = meuSegmentador.segmentar(grafoImagem, 0.0, 100);

    // //GrafoLista* grafoPintado = gerarGrafoPintado(grafoImagem, resultado);
    // GrafoLista* grafoPintado = gerarGrafoPintadoAleatorio(grafoPintado, resultado);

    // saveImageFromGrafo("assets/output/gatos.ppm", grafoImagem, 2560, 1463);

    // try {
    //     int opcaoPrincipal = 0;

    //     cout << "---------------------------------------------" << endl;
    //     cout << "--- Bem vindo aos TPs de Teoria dos Grafos ---"<< endl;
    //     cout << "---------------------------------------------" << endl;
    //     cout << "--------------- Integrantes: ----------------" << endl
    //          << "---------- Augusto Stambassi Duarte ---------" << endl
    //          << "---------- Davi Cândido de Almeida ----------" << endl
    //          << "-------  Gabriela de Assis dos Reis ---------" << endl
    //          << "-------- Lucas Carneiro Nassau Malta --------" << endl
    //          << "------------- João Pedro Torres -------------" << endl
    //          << "------------ Vitor Leite Setragni -----------" << endl;
    //     cout << "---------------------------------------------" << endl;
 
    //     do {
    //         cout << "\n> Menu Principal (Geral)" << endl << endl;
    //         cout << "Escolha o módulo:" << endl;
    //         cout << "1) Testar Implementação de Grafo (TP1 - CRUD/Buscas)" << endl;
    //         cout << "2) Segmentação de Imagem via MST (TP2)" << endl;
    //         cout << "0) Sair" << endl << endl;

    //         opcaoPrincipal = lerInteiro("Opção: ", 0, 2);

    //         switch (opcaoPrincipal) {
    //             case 1:
    //                 (new MenuGrafoManager())->menu();
    //                 break;
                
    //             case 2:
    //                 (new MenuImageSegmentation())->menu();
    //                 break;
                
    //             case 0:
    //                 cout << "\nSaindo da aplicação..." << endl;
    //                 break;
                
    //             default:
    //                 cout << "\nOpção inválida." << endl;
    //                 break;
    //         }
    //     } while (opcaoPrincipal != 0);

    // } catch (exception& e) {
    //     cout << "Erro crítico na main: " << e.what() << endl;
    // }

    return 0;
}