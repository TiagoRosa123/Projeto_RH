#ifndef CIFRA_H
#define CIFRA_H

#include <string>

/**
 * @brief Encripta um texto usando a Cifra de César.
 * @param texto O texto original.
 * @param chave O desvio (shift) a aplicar.
 * @return O texto cifrado.
 */
std::string cifrar(const std::string& texto, int chave);

/**
 * @brief Desencripta um texto cifrado com a Cifra de César.
 * @param textoCifrado O texto encriptado.
 * @param chave O desvio (shift) usado para cifrar.
 * @return O texto original.
 */
std::string decifrar(const std::string& textoCifrado, int chave);

#endif // CIFRA_H
