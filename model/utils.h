#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @brief Limpa o buffer de entrada (std::cin).
 */
void limparBuffer();

/**
 * @brief Limpa o ecrã da consola.
 */
void limparEcra();

/**
 * @brief Lê um número inteiro da entrada padrão com validação.
 * @param mensagem Mensagem a exibir antes de ler.
 * @return O número inteiro lido.
 */
int lerInteiro(const std::string& mensagem);

/**
 * @brief Lê uma linha de texto da entrada padrão.
 * @param mensagem Mensagem a exibir antes de ler.
 * @return A string lida.
 */
std::string lerString(const std::string& mensagem);

#endif // UTILS_H
