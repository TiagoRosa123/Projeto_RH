#include <iostream>
#include <vector>
#include <string>
#include <limits> 

#include "../model/colaborador.h"
#include "../model/io.h"
#include "../view/view.h"
#include "../view/cores.h" 

// --- Configurações da Aplicação ---
const std::string NOME_FICHEIRO_DADOS = "rh_dados.txt";
const int CHAVE_CIFRA = 3;

// Função auxiliar para limpar o buffer de entrada
void limparInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // A nossa "base de dados" em memória
    std::vector<Colaborador> listaColaboradores;

    // Tenta carregar os dados do ficheiro ao iniciar
    carregarDados(listaColaboradores, NOME_FICHEIRO_DADOS, CHAVE_CIFRA);

    int opcao = 0;
    while (true) {
        exibirMenu();
        
        // Validação básica da entrada
        while (!(std::cin >> opcao)) { 
            std::cout << COR_ERRO << "Opção inválida. Por favor, digite um número (1-5): " << COR_RESET;
            std::cin.clear(); 
            limparInput();   
        }

        switch (opcao) {
            case 1:
                adicionarColaborador(listaColaboradores);
                break;
            case 2:
                marcarAusencia(listaColaboradores);
                break;
            case 3:
                listarColaboradores(listaColaboradores);
                break;              
            case 4:
                visualizarCalendarioColaborador(listaColaboradores);
                break;
            case 5:
                guardarDados(listaColaboradores, NOME_FICHEIRO_DADOS, CHAVE_CIFRA);
                std::cout << COR_SAIR << "A sair do programa. Adeus!" << COR_RESET << std::endl;
                return 0;
            default:
                std::cout << COR_ERRO << "Opção inválida. Tente novamente." << COR_RESET << std::endl;
                break;
        }
        std::cout << "\n" << COR_PROMPT << "Pressione Enter para continuar..." << COR_RESET;
        limparInput(); 
        std::cin.get(); // Espera por um novo 'Enter'
    }

    return 0; 
}