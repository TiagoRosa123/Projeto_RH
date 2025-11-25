#include "view.h"
#include "../model/calendario.h"
#include "cores.h"
#include <iomanip>
#include <iostream>


void imprimirCalendario(int ano, int mes,
                        const std::map<std::string, char> &marcacoes) {
  const std::string nomesMeses[] = {
      "Janeiro", "Fevereiro", "Março",    "Abril",   "Maio",     "Junho",
      "Julho",   "Agosto",    "Setembro", "Outubro", "Novembro", "Dezembro"};

  std::cout << "\n   " << nomesMeses[mes - 1] << " " << ano << std::endl;
  std::cout << "-----------------------------" << std::endl;
  std::cout << " Dom Seg Ter Qua Qui Sex Sab" << std::endl;

  int dias = diasNoMes(ano, mes);
  int diaSemana = getDiaDaSemana(ano, mes, 1); // 0=Dom, 1=Seg, ...

  // Espaços iniciais para alinhar o primeiro dia do mês
  for (int i = 0; i < diaSemana; ++i) {
    std::cout << "    ";
  }

  for (int dia = 1; dia <= dias; ++dia) {
    std::string dataStr = formatarData(ano, mes, dia);

    // Verifica se há marcação para o dia atual
    if (marcacoes.count(dataStr)) {
      char tipo = marcacoes.at(dataStr);
      // Aplica cor dependendo do tipo de marcação
      if (tipo == 'F')
        std::cout << COR_FERIAS;
      else if (tipo == 'X')
        std::cout << COR_FALTA;

      std::cout << std::setw(3) << tipo << COR_RESET << " ";
    } else {
      std::cout << std::setw(3) << dia << " ";
    }

    // Quebra de linha no Sábado (diaSemana 6)
    if ((diaSemana + 1) % 7 == 0) {
      std::cout << std::endl;
    }
    diaSemana++;
  }
  std::cout << std::endl;
}

void exibirMenu() {
  std::cout << "\n"
            << COR_TITULO << "=============================" << std::endl;
  std::cout << "      RH AVANÇADO" << std::endl;
  std::cout << "=============================" << COR_RESET << std::endl;

  // Exibe as opções com cores para destaque
  std::cout << COR_OPCAO << "1." << COR_RESET << " Listar colaboradores"
            << std::endl;
  std::cout << COR_OPCAO << "2." << COR_RESET << " Adicionar colaborador"
            << std::endl;
  std::cout << COR_OPCAO << "3." << COR_RESET << " Marcar férias/faltas"
            << std::endl;
  std::cout << COR_OPCAO << "4." << COR_RESET
            << " Visualizar calendário do colaborador" << std::endl;
  std::cout << COR_OPCAO << "5." << COR_RESET
            << " Buscar colaborador por ID ou nome" << std::endl;
  std::cout << COR_OPCAO << "6." << COR_RESET
            << " Gerir formações/cursos de um colaborador" << std::endl;
  std::cout << COR_OPCAO << "7." << COR_RESET
            << " Gerir notas/observações de um colaborador" << std::endl;
  std::cout << COR_OPCAO << "8." << COR_RESET << " Relatórios mensais"
            << std::endl;
  std::cout << COR_OPCAO << "9." << COR_RESET
            << " Estatísticas por departamento" << std::endl;
  std::cout << COR_OPCAO << "10." << COR_RESET << " Dashboard resumido"
            << std::endl;
  std::cout << COR_OPCAO << "11." << COR_RESET << " Exportar dados"
            << std::endl;
  std::cout << COR_SAIR << "0." << COR_RESET << " Guardar e Sair" << std::endl;
  std::cout << "-----------------------------" << std::endl;
  std::cout << "Escolha uma opção: ";
}