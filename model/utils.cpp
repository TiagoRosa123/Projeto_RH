#include "utils.h"
#include "../view/cores.h"
#include <iostream>
#include <limits>
#include <cstdlib> // Para system()

void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void limparEcra() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

int lerInteiro(const std::string& mensagem) {
    int valor;
    std::cout << mensagem;
    while (!(std::cin >> valor)) {
        std::cout << COR_ERRO << "Entrada inválida. Por favor, digite um número: " << COR_RESET;
        std::cin.clear();
        limparBuffer();
        std::cout << mensagem;
    }
    limparBuffer(); // Limpa o buffer após ler o número
    return valor;
}

std::string lerString(const std::string& mensagem) {
    std::string texto;
    std::cout << mensagem;
    std::getline(std::cin, texto);
    return texto;
}
