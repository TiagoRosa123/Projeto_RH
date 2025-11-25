#include "utils.h"
#include "../view/cores.h"
#include <cstdlib> // Para system()
#include <iostream>
#include <limits>


void limparBuffer() {
  // Ignora todos os caracteres até encontrar uma nova linha
  // Útil para limpar o buffer após ler números e antes de ler strings
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void limparEcra() {
#ifdef _WIN32
  std::system("cls"); // Comando para Windows
#else
  std::system("clear"); // Comando para Linux/macOS
#endif
}

int lerInteiro(const std::string &mensagem) {
  int valor;
  std::cout << mensagem;
  // Tenta ler um inteiro. Se falhar (ex: utilizador digitou letras), entra no
  // loop
  while (!(std::cin >> valor)) {
    std::cout << COR_ERRO
              << "Entrada inválida. Por favor, digite um número: " << COR_RESET;
    std::cin.clear(); // Limpa o estado de erro do cin
    limparBuffer();   // Remove a entrada inválida do buffer
    std::cout << mensagem;
  }
  limparBuffer(); // Limpa o buffer após ler o número para consumir o '\n'
  return valor;
}

std::string lerString(const std::string &mensagem) {
  std::string texto;
  std::cout << mensagem;
  std::getline(std::cin, texto);
  return texto;
}
