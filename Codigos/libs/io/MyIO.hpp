#ifndef MYIO_HPP
#define MYIO_HPP

#include <string>

/**
 * Lê um número inteiro dentro de um intervalo.
 * @param mensagem Texto exibido ao usuário.
 * @param limiteInferior Valor mínimo permitido.
 * @param limiteSuperior Valor máximo permitido.
 * @return Inteiro válido.
 */
int lerInteiro(const std::string& mensagem, int limiteInferior, int limiteSuperior);

/**
 * Lê um número decimal (double).
 * @param mensagem Texto exibido ao usuário.
 * @return Double válido.
 */
double lerDouble(const std::string& mensagem);

/**
 * Lê uma resposta booleana (S/N ou Y/N).
 * @param mensagem Texto exibido ao usuário.
 * @return true para S/s/Y/y, false para N/n.
 */
bool lerBoolean(const std::string& mensagem);

/**
 * Lê um texto não vazio.
 * @param mensagem Texto exibido ao usuário.
 * @return String válida.
 */
std::string lerRotulo(const std::string& mensagem);

/**
 * Alias para lerRotulo — lê uma string não vazia.
 */
std::string lerString(const std::string& mensagem);

#endif // MYIO_HPP
