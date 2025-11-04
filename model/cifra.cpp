#include "cifra.h"

// Implementação da Cifra de César
// Caracteres acentuados ou especiais não serão cifrados.

std::string cifrar(const std::string& texto, int chave) {
    std::string resultado = "";
    for (char c : texto) {
        if (c >= 'a' && c <= 'z') {
            // (c - 'a') dá a posição 0-25. Soma a chave, % 26 para dar a volta, + 'a' para voltar a char.
            resultado += (char)('a' + (c - 'a' + chave) % 26);
        } else if (c >= 'A' && c <= 'Z') {
            resultado += (char)('A' + (c - 'A' + chave) % 26);
        } else {
            // Mantém caracteres que não são letras (espaços, números, etc.)
            resultado += c;
        }
    }
    return resultado;
}

std::string decifrar(const std::string& textoCifrado, int chave) {
    std::string resultado = "";
    for (char c : textoCifrado) {
        if (c >= 'a' && c <= 'z') {
            // (c - 'a') dá a posição 0-25. Subtrai a chave.
            // (+ 26) garante que o resultado é positivo antes do módulo.
            resultado += (char)('a' + (c - 'a' - chave + 26) % 26);
        } else if (c >= 'A' && c <= 'Z') {
            resultado += (char)('A' + (c - 'A' - chave + 26) % 26);
        } else {
            resultado += c;
        }
    }
    return resultado;
}
