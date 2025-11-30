# TP2 — Segmentação de Imagens com Grafos 🖼️

## 🎯 Objetivo

Desenvolvimento e avaliação experimental de métodos de **segmentação de imagens baseados em grafos**. O projeto utiliza a infraestrutura de grafos desenvolvida anteriormente para implementar duas abordagens distintas:

1.  **Árvores Geradoras Mínimas (MST)**: Utilizando o método de **Felzenszwalb e Huttenlocher** em grafos não direcionados.
2.  **Arborescências Geradoras Mínimas (MSA)**: Utilizando o algoritmo de **Edmonds (Chu-Liu)** em grafos direcionados.

O objetivo central é comparar o desempenho computacional e as características visuais das regiões geradas por essas duas abordagens.

-----

## 👨‍🎓 Integrantes da equipe

  - **Augusto Stambassi Duarte** — *Adaptação da biblioteca de grafos e modelagem de imagens em grafos e vice-versa*
  - **Davi Cândido de Almeida** — *Implementação do algoritmo de Edmonds (MSA) e interface de visualização*
  - **Gabriela de Assis dos Reis** — *Implementação e validação do segmentador em (MSA)*
  - **João Pedro Torres** — *Validação de variantes, análise de experimentos e documentação*
  - **Lucas Carneiro Nassau Malta** — *Implementação do algoritmo de Kruskal (MST)* e Interface de Segementadores
  - **Vitor Leite Setragni** — *Interface de visualização, análise de experimentos e documentação*

## 👩‍🏫 Professor responsável

  - *Silvio Jamil Ferzoli Guimaraes*

-----

## 🧠 Fundamentação e Modelagem

A imagem é modelada como um **grafo ponderado** onde cada pixel é um vértice.

  - **Arestas:** Conectam pixels adjacentes (vizinhança-4: direita e abaixo).
  - **Pesos:** Definidos pela **distância euclidiana** entre os vetores de cor RGB dos pixels vizinhos.
  - **Direcionalidade:**
      - **MST:** Aresta única não direcionada entre $(u, v)$.
      - **MSA:** Arestas direcionadas $(u, v)$ e $(v, u)$ para permitir o fluxo direcionado.

### Algoritmos Implementados

1.  **MST (Kruskal):** Baseado em Kruskal. Decide iterativamente a fusão de componentes comparando o peso da aresta com a variação interna dos componentes ($Int(C)$). É eficiente e preserva bordas.
2.  **MSA (Edmonds):** Seleciona a aresta de menor custo de entrada para cada vértice. Se ciclos são formados, eles são contraídos em super-vértices recursivamente até formar uma arborescência válida enraizada.

-----

## 🗂 Estrutura do Projeto

A estrutura foi estendida a partir do TP1 para suportar o módulo de segmentação:

```sh
├── Makefile                         # Compilador
├── assets/
│   ├── input/                       # Coloque suas imagens de entrada aqui
│   └── output/                      # As imagens geradas serão salvas aqui
├── bin/ 
├── libs/                            # Bibliotecas externas
├── build/                           # Objetos de compilação (.o) 
└── src/
    ├─ Grafo/                        # Infraestrutura base de Grafos
    │   ├─ GrafoLista.cpp            # Grafo via lista de adjacências (base do projeto)
    │   ├─ Vertice.hpp               # Identificador, peso e rótulo do pixel
    │   └─ NoVertice.hpp             # Nó da lista encadeada
    │
    ├─ Segmentacao/                  # Módulo de Segmentação
    │   ├─ InterfaceImagem.cpp       # Carregamento (stb_image) e conversão Imagem <-> Grafo
    │   ├─ ISegmentador.hpp          # Interface comum (contrato) para os algoritmos
    │   ├─ MST/
    │   │   └─ SegmentadorMST.cpp    # Implementação de Kruskal
    │   └─ MSA/
    │       └─ SegmentadorMSA.cpp    # Implementação de Edmonds
    │
    ├─ libs/
    │   └─ std/stb_image.h           # Bibliotecas para leitura de imagens RGB
    │
    ├─ Visao/
    │   ├─ MenuGrafoManager.cpp      # Interface de Operações em Grafo
    │   ├─ MenuLista/Matriz.cpp      # Interface de Operações em Grafo Lista e Matriz
    │   └─ MenuImageSegmentation.cpp # Interface de Operações em Segmentação de Imagem      
    │                  
    │
    └─ main.cpp                      # Programa principal
```

-----

### 📋 Pré-requisitos

  * **Compilador:** É necessário ter o **GCC versão 13 ou superior** instalado.
  * **Ferramenta:** `make` instalado no sistema.


### 🚀 Como Compilar e Executar

Abra o terminal na raiz do projeto e utilize os comandos abaixo:

1.  **Compilar o projeto:**
    O `Makefile` irá encontrar automaticamente todos os arquivos `.cpp`, criar as pastas necessárias dentro de `build/` e gerar o executável na pasta `bin/`.

    ```bash
    make
    ```

2.  **Executar o programa:**
    Após a compilação bem-sucedida, o executável estará disponível na pasta `bin`.

    ```bash
    ./bin/programa
    ```

### 🛠️ Comandos Adicionais

  * **Limpar arquivos temporários e executável:**
    Remove a pasta `build` e o arquivo gerado em `bin`.

    ```bash
    make clean
    ```

  * **Recompilar tudo do zero (Clean + Build):**
    Útil se você fez alterações profundas e quer garantir uma compilação limpa.

    ```bash
    make re
    ```

-----

## 📊 Comparativo: MST vs. MSA

Conforme os experimentos realizados no artigo:

| Característica | MST (Kruskal) | MSA (Edmonds) |
| :--- | :--- | :--- |
| **Complexidade** | Quase linear (rápido) | Quadrática $O(nm)$ (mais lento) |
| **Formato dos Segmentos** | Regiões compactas e coesas | Regiões alongadas e orientadas |
| **Dependência de Raiz** | Não | Sim (estrutura hierárquica) |
| **Preservação de Bordas** | Alta | Moderada |

> **Conclusão:** A MST é superior em eficiência e fidelidade de bordas para tarefas gerais, enquanto a MSA oferece propriedades estruturais únicas úteis para análises que exigem hierarquia ou direcionalidade.

-----

## 📄 Licença e Disponibilidade

Este projeto foi desenvolvido para a disciplina de Grafos da PUC Minas.
Os códigos e análises estão disponíveis no repositório oficial: [GitHub - TP2-Grafos](https://www.google.com/search?q=https://github.com/VitorSetragni/TP2-Grafos).