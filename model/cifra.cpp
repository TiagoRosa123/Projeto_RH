#include "cifra.h"

// Implementação da Cifra de César
// Caracteres acentuados ou especiais não serão cifrados.

std::string cifrar(const std::string &texto, int chave) {
  std::string resultado = "";
  for (char c : texto) {
    if (c >= 'a' && c <= 'z') {
      // (c - 'a') converte para índice 0-25
      // Soma a chave para deslocar
      // % 26 garante que o valor fica entre 0-25 (rotação)
      // + 'a' converte de volta para caractere ASCII
      resultado += (char)('a' + (c - 'a' + chave) % 26);
    } else if (c >= 'A' && c <= 'Z') {
      // Mesma lógica para letras maiúsculas
      resultado += (char)('A' + (c - 'A' + chave) % 26);
    } else if (c >= '0' && c <= '9') {
      // Cifra números 0-9 (módulo 10)
      resultado += (char)('0' + (c - '0' + chave) % 10);
    } else {
      // Mantém caracteres que não são letras nem números (pontuação, espaços)
      resultado += c;
    }
  }
  return resultado;
}

std::string decifrar(const std::string &textoCifrado, int chave) {
  std::string resultado = "";
  for (char c : textoCifrado) {
    if (c >= 'a' && c <= 'z') {
      // Subtrai a chave para reverter o deslocamento
      // + 26 garante que o resultado da subtração não seja negativo antes do
      // módulo
      resultado += (char)('a' + (c - 'a' - chave + 26) % 26);
    } else if (c >= 'A' && c <= 'Z') {
      resultado += (char)('A' + (c - 'A' - chave + 26) % 26);
    } else if (c >= '0' && c <= '9') {
      // Decifra números 0-9 (+ 10 para garantir não negativo)
      resultado += (char)('0' + (c - '0' - chave + 10) % 10);
    } else {
      resultado += c;
    }
  }
  return resultado;
}
