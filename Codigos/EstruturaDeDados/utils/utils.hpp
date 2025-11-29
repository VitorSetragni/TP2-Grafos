#ifndef UTILS_HPP
#define UTILS_HPP

/**
 * @file utils.hpp
 * @brief Declarações utilitárias para algoritmos de busca em grafos.
 *
 * Este arquivo contém declarações de estruturas usadas pelos algoritmos de busca,
 * como enumerações de estados de vértice e variáveis globais compartilhadas.
 */

/**
 * @enum cores
 * Enumeração que representa os estados de visitação dos vértices:
 * - BRANCO: não visitado
 * - VERMELHO: visitado, mas não processado
 * - PRETO: totalmente processado
 */
enum cores {
    BRANCO,
    VERMELHO,
    PRETO
};

/**
 * @brief Variável global para rastrear o tempo nos algoritmos de busca.
 */
extern int tempo;

#endif // UTILS_HPP
