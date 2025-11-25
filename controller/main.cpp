#include "../model/colaborador.h"
#include "../model/io.h"
#include "../model/utils.h"
#include "../view/cores.h"
#include "../view/view.h"
#include <iostream>
#include <string>
#include <vector>


// --- Configurações da Aplicação ---
const std::string NOME_FICHEIRO_DADOS = "rh_dados.txt";
const int CHAVE_CIFRA = 3;

int main() {
  // A nossa "base de dados" em memória
  std::vector<Colaborador> listaColaboradores;

  // Tenta carregar os dados do ficheiro ao iniciar
  // Se o ficheiro não existir ou estiver vazio, inicia com lista vazia
  carregarDados(listaColaboradores, NOME_FICHEIRO_DADOS, CHAVE_CIFRA);

  int opcao = -1;
  // Loop principal da aplicação
  while (true) {
    limparEcra(); // Limpa a consola para mostrar o menu
    exibirMenu();

    opcao = lerInteiro(""); // A mensagem já está no menu

    // Processa a opção escolhida pelo utilizador
    switch (opcao) {
    case 1:
      listarColaboradores(listaColaboradores);
      break;
    case 2:
      adicionarColaborador(listaColaboradores);
      break;
    case 3:
      marcarAusencia(listaColaboradores);
      break;
    case 4:
      // Visualizar calendário (pede nome/ID dentro da função)
      visualizarCalendarioColaborador(listaColaboradores);
      break;
    case 5:
      // Buscar colaborador (reutiliza a função de visualizar calendário que faz
      // busca) Nota: Poderia ser uma função separada apenas para mostrar dados
      visualizarCalendarioColaborador(listaColaboradores);
      break;
    case 6: {
      std::string termo = lerString("Digite o nome ou ID do colaborador: ");
      Colaborador *col = nullptr;
      try {
        int id = std::stoi(termo);
        col = buscarColaboradorPorId(listaColaboradores, id);
      } catch (...) {
        col = buscarColaboradorPorNome(listaColaboradores, termo);
      }
      if (col)
        gerirFormacoes(*col);
      else
        std::cout << COR_ERRO << "Colaborador não encontrado." << COR_RESET
                  << std::endl;
      break;
    }
    case 7: {
      std::string termo = lerString("Digite o nome ou ID do colaborador: ");
      Colaborador *col = nullptr;
      try {
        int id = std::stoi(termo);
        col = buscarColaboradorPorId(listaColaboradores, id);
      } catch (...) {
        col = buscarColaboradorPorNome(listaColaboradores, termo);
      }
      if (col)
        gerirNotas(*col);
      else
        std::cout << COR_ERRO << "Colaborador não encontrado." << COR_RESET
                  << std::endl;
      break;
    }
    case 8:
      relatorioMensal(listaColaboradores);
      break;
    case 9:
      estatisticasDepartamento(listaColaboradores);
      break;
    case 10:
      dashboardResumido(listaColaboradores);
      break;
    case 11:
      exportarDados(listaColaboradores);
      break;
    case 0:
      // Salva os dados antes de sair
      guardarDados(listaColaboradores, NOME_FICHEIRO_DADOS, CHAVE_CIFRA);
      std::cout << COR_SAIR << "A sair do programa. Adeus!" << COR_RESET
                << std::endl;
      return 0;
    default:
      std::cout << COR_ERRO << "Opção inválida. Tente novamente." << COR_RESET
                << std::endl;
      break;
    }
    std::cout << "\n"
              << COR_PROMPT << "Pressione Enter para continuar..." << COR_RESET;
    std::cin.get(); // Espera por um novo 'Enter'
  }

  return 0;
}