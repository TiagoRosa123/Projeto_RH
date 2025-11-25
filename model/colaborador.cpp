#include "colaborador.h"
#include "../view/cores.h"
#include "../view/view.h"
#include "calendario.h"
#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>

Colaborador *buscarColaboradorPorNome(std::vector<Colaborador> &colaboradores,
                                      const std::string &nome) {
  // Itera sobre a lista de colaboradores para encontrar o nome correspondente
  for (Colaborador &col : colaboradores) {
    if (col.nome == nome) {
      return &col; // Retorna ponteiro para o colaborador encontrado
    }
  }
  return nullptr; // Retorna nullptr se não encontrar
}

Colaborador *buscarColaboradorPorId(std::vector<Colaborador> &colaboradores,
                                    int id) {
  // Itera sobre a lista de colaboradores para encontrar o ID correspondente
  for (Colaborador &col : colaboradores) {
    if (col.id == id) {
      return &col; // Retorna ponteiro para o colaborador encontrado
    }
  }
  return nullptr; // Retorna nullptr se não encontrar
}

void adicionarColaborador(std::vector<Colaborador> &colaboradores) {
  std::string nome = lerString("Digite o nome do novo colaborador: ");

  // Verifica se já existe um colaborador com o mesmo nome
  if (buscarColaboradorPorNome(colaboradores, nome) != nullptr) {
    std::cout << COR_ERRO << "Erro: Já existe um colaborador com esse nome."
              << COR_RESET << std::endl;
    char resposta;
    std::cout << "Deseja continuar e adicionar mesmo assim? (s/n): ";
    std::cin >> resposta;
    limparBuffer();
    if (resposta != 's' && resposta != 'S') {
      std::cout << "Adição cancelada." << std::endl;
      return;
    }
  }

  int id = lerInteiro("Digite o ID do colaborador: ");

  // Verifica se já existe um colaborador com o mesmo ID (não permitido
  // duplicados)
  if (buscarColaboradorPorId(colaboradores, id) != nullptr) {
    std::cout << COR_ERRO << "Erro: Já existe um colaborador com esse ID."
              << COR_RESET << std::endl;
    return;
  }

  std::string departamento = lerString("Digite o departamento: ");

  // Cria e preenche o novo colaborador
  Colaborador novoColaborador;
  novoColaborador.nome = nome;
  novoColaborador.id = id;
  novoColaborador.departamento = departamento;

  // Adiciona à lista
  colaboradores.push_back(novoColaborador);
  std::cout << COR_SUCESSO << "Colaborador '" << nome
            << "' adicionado com sucesso!" << COR_RESET << std::endl;
}

void listarColaboradores(const std::vector<Colaborador> &colaboradores) {
  std::cout << "\n--- Lista de Colaboradores ---" << std::endl;
  if (colaboradores.empty()) {
    std::cout << "Nenhum colaborador registado." << std::endl;
  } else {
    for (const auto &col : colaboradores) {
      std::cout << "ID: " << col.id << " | Nome: " << col.nome
                << " | Dept: " << col.departamento << std::endl;
    }
  }
  std::cout << "--------------------------------" << std::endl;
}

void marcarAusencia(std::vector<Colaborador> &colaboradores) {
  std::string nome = lerString("Digite o nome do colaborador: ");

  Colaborador *col = buscarColaboradorPorNome(colaboradores, nome);
  if (col == nullptr) {
    std::cout << COR_ERRO << "Erro: Colaborador não encontrado." << COR_RESET
              << std::endl;
    return;
  }

  // Solicita a data da ausência
  int ano = lerInteiro("Digite o Ano (ex: 2024): ");
  int mes = lerInteiro("Digite o Mês (1-12): ");
  while (mes < 1 || mes > 12) {
    std::cout << COR_ERRO << "Mês inválido." << COR_RESET << std::endl;
    mes = lerInteiro("Digite o Mês (1-12): ");
  }
  int dia = lerInteiro("Digite o Dia (1-31): ");

  // Valida a data
  if (!isDataValida(ano, mes, dia)) {
    std::cout << COR_ERRO << "Erro: Data inválida (" << dia << "/" << mes << "/"
              << ano << ")." << COR_RESET << std::endl;
    return;
  }

  // Verifica se é fim de semana
  int diaSemana = getDiaDaSemana(ano, mes, dia);
  if (diaSemana == 0 || diaSemana == 6) { // 0=Domingo, 6=Sábado
    std::cout << COR_ERRO
              << "Erro: Não é permitido marcar ausências ao fim de semana."
              << COR_RESET << std::endl;
    return;
  }

  std::string chaveData = formatarData(ano, mes, dia);

  // Solicita o tipo de marcação
  char tipo;
  std::cout << "Tipo de marcação (F - Férias, X - Falta, D - Desmarcar): ";
  std::cin >> tipo;
  limparBuffer();
  tipo = std::toupper(tipo);

  // Se for férias, verifica conflitos com outros colaboradores do mesmo
  // departamento
  if (tipo == 'F') {
    for (const auto &outroCol : colaboradores) {
      if (outroCol.departamento == col->departamento &&
          outroCol.nome != col->nome) {
        if (outroCol.marcacoes.count(chaveData) &&
            outroCol.marcacoes.at(chaveData) == 'F') {
          std::cout
              << COR_AVISO << "AVISO: O colaborador " << outroCol.nome
              << " (mesmo departamento) já tem férias marcadas para este dia."
              << COR_RESET << std::endl;
          std::cout << "Deseja continuar? (s/n): ";
          char resp;
          std::cin >> resp;
          limparBuffer();
          if (resp != 's' && resp != 'S')
            return;
        }
      }
    }
  }

  // Processa a marcação ou desmarcação
  if (tipo == 'D') {
    if (col->marcacoes.count(chaveData)) {
      col->marcacoes.erase(chaveData);
      std::cout << COR_SUCESSO << "Marcação removida com sucesso para "
                << chaveData << "." << COR_RESET << std::endl;
    } else {
      std::cout << "Nenhuma marcação encontrada para remover nesse dia."
                << std::endl;
    }
  } else if (tipo == 'F' || tipo == 'X') {
    col->marcacoes[chaveData] = tipo;
    std::cout << COR_SUCESSO << "Marcação (" << tipo
              << ") registada com sucesso para " << chaveData << "."
              << COR_RESET << std::endl;
  } else {
    std::cout << COR_ERRO << "Erro: Tipo de marcação inválido." << COR_RESET
              << std::endl;
  }
}

void visualizarCalendarioColaborador(std::vector<Colaborador> &colaboradores) {
  std::string termo = lerString("Digite o nome ou ID do colaborador: ");

  Colaborador *col = nullptr;
  try {
    int id = std::stoi(termo);
    col = buscarColaboradorPorId(colaboradores, id);
  } catch (...) {
    col = buscarColaboradorPorNome(colaboradores, termo);
  }

  if (col == nullptr) {
    std::cout << COR_ERRO << "Erro: Colaborador não encontrado." << COR_RESET
              << std::endl;
    return;
  }

  std::cout << "ID: " << col->id << " | Nome: " << col->nome
            << " | Dept: " << col->departamento << std::endl;

  int ano = lerInteiro("Digite o Ano (ex: 2024): ");
  int mes = lerInteiro("Digite o Mês (1-12): ");
  while (mes < 1 || mes > 12) {
    std::cout << COR_ERRO << "Mês inválido." << COR_RESET << std::endl;
    mes = lerInteiro("Digite o Mês (1-12): ");
  }

  std::cout << "\n--- Calendário de " << col->nome << " para " << mes << "/"
            << ano << " ---" << std::endl;
  imprimirCalendario(ano, mes, col->marcacoes);
}

void gerirFormacoes(Colaborador &colaborador) {
  int opcao;
  do {
    std::cout << "\n--- FORMACOES / CURSOS DE " << colaborador.nome << " ---"
              << std::endl;
    std::cout << "1. Listar formações" << std::endl;
    std::cout << "2. Adicionar formação" << std::endl;
    std::cout << "3. Remover formação" << std::endl;
    std::cout << "0. Voltar" << std::endl;

    opcao = lerInteiro("Escolha uma opção: ");

    switch (opcao) {
    case 1:
      if (colaborador.formacoes.empty())
        std::cout << "Nenhuma formação registada." << std::endl;
      else {
        for (size_t i = 0; i < colaborador.formacoes.size(); ++i) {
          std::cout << i + 1 << ". " << colaborador.formacoes[i].nome_curso
                    << " (" << colaborador.formacoes[i].data_conclusao << ")"
                    << std::endl;
        }
      }
      break;
    case 2: {
      Formacao f;
      f.nome_curso = lerString("Nome do curso: ");
      f.data_conclusao = lerString("Data de conclusão: ");
      colaborador.formacoes.push_back(f);
      std::cout << COR_SUCESSO << "Formação adicionada!" << COR_RESET
                << std::endl;
      break;
    }
    case 3: {
      int idx = lerInteiro("Número da formação a remover: ");
      if (idx > 0 && idx <= (int)colaborador.formacoes.size()) {
        colaborador.formacoes.erase(colaborador.formacoes.begin() + idx - 1);
        std::cout << COR_SUCESSO << "Formação removida!" << COR_RESET
                  << std::endl;
      } else {
        std::cout << COR_ERRO << "Índice inválido." << COR_RESET << std::endl;
      }
      break;
    }
    case 0:
      break;
    default:
      std::cout << COR_ERRO << "Opção inválida." << COR_RESET << std::endl;
    }
  } while (opcao != 0);
}

void gerirNotas(Colaborador &colaborador) {
  int opcao;
  do {
    std::cout << "\n--- NOTAS / OBSERVAÇÕES DE " << colaborador.nome << " ---"
              << std::endl;
    std::cout << "1. Listar notas" << std::endl;
    std::cout << "2. Adicionar nota" << std::endl;
    std::cout << "3. Remover nota" << std::endl;
    std::cout << "0. Voltar" << std::endl;

    opcao = lerInteiro("Escolha uma opção: ");

    switch (opcao) {
    case 1:
      if (colaborador.notas.empty())
        std::cout << "Nenhuma nota registada." << std::endl;
      else {
        for (size_t i = 0; i < colaborador.notas.size(); ++i) {
          std::cout << i + 1 << ". [" << colaborador.notas[i].data << "] "
                    << colaborador.notas[i].texto << std::endl;
        }
      }
      break;
    case 2: {
      Nota n;
      n.texto = lerString("Texto da nota: ");
      n.data = lerString("Data: ");
      colaborador.notas.push_back(n);
      std::cout << COR_SUCESSO << "Nota adicionada!" << COR_RESET << std::endl;
      break;
    }
    case 3: {
      int idx = lerInteiro("Número da nota a remover: ");
      if (idx > 0 && idx <= (int)colaborador.notas.size()) {
        colaborador.notas.erase(colaborador.notas.begin() + idx - 1);
        std::cout << COR_SUCESSO << "Nota removida!" << COR_RESET << std::endl;
      } else {
        std::cout << COR_ERRO << "Índice inválido." << COR_RESET << std::endl;
      }
      break;
    }
    case 0:
      break;
    default:
      std::cout << COR_ERRO << "Opção inválida." << COR_RESET << std::endl;
    }
  } while (opcao != 0);
}

void relatorioMensal(const std::vector<Colaborador> &colaboradores) {
  int mes = lerInteiro("Mês (1-12): ");
  int ano = lerInteiro("Ano: ");

  std::cout << "\n--- Relatório Mensal (" << mes << "/" << ano << ") ---"
            << std::endl;
  std::cout << std::left << std::setw(20) << "Nome" << std::setw(10) << "Férias"
            << std::setw(10) << "Faltas" << std::endl;

  for (const auto &col : colaboradores) {
    int ferias = 0;
    int faltas = 0;
    // Cria prefixo para filtrar as marcações do mês/ano selecionado
    std::string prefixo =
        std::to_string(ano) + "-" + (mes < 10 ? "0" : "") + std::to_string(mes);

    // Conta férias e faltas
    for (const auto &par : col.marcacoes) {
      if (par.first.find(prefixo) == 0) {
        if (par.second == 'F')
          ferias++;
        else if (par.second == 'X')
          faltas++;
      }
    }
    std::cout << std::left << std::setw(20) << col.nome << std::setw(10)
              << ferias << std::setw(10) << faltas << std::endl;
  }
}

void estatisticasDepartamento(const std::vector<Colaborador> &colaboradores) {
  std::map<std::string, std::pair<int, int>> stats; // Dept -> {Ferias, Faltas}

  // Agrega estatísticas por departamento
  for (const auto &col : colaboradores) {
    for (const auto &par : col.marcacoes) {
      if (par.second == 'F')
        stats[col.departamento].first++;
      else if (par.second == 'X')
        stats[col.departamento].second++;
    }
  }

  std::cout << "\n--- Estatísticas por Departamento ---" << std::endl;
  std::string deptMaisAusencias;
  int maxAusencias = -1;

  // Exibe os resultados e encontra o departamento com mais ausências
  for (const auto &par : stats) {
    int total = par.second.first + par.second.second;
    std::cout << "Departamento: " << par.first
              << " | Férias: " << par.second.first
              << " | Faltas: " << par.second.second << std::endl;

    if (total > maxAusencias) {
      maxAusencias = total;
      deptMaisAusencias = par.first;
    }
  }
  if (!deptMaisAusencias.empty()) {
    std::cout << "Departamento com mais ausências: " << deptMaisAusencias
              << " (" << maxAusencias << ")" << std::endl;
  }
}

void dashboardResumido(const std::vector<Colaborador> &colaboradores) {
  int mes = lerInteiro("Mês (1-12): ");
  int ano = lerInteiro("Ano: ");

  std::cout << "\n--- Dashboard Resumido (" << mes << "/" << ano << ") ---"
            << std::endl;
  std::cout << std::left << std::setw(20) << "Nome" << std::setw(10) << "Férias"
            << std::setw(10) << "Faltas" << std::setw(15) << "Dias Restantes"
            << std::endl;

  for (const auto &col : colaboradores) {
    int feriasMes = 0;
    int faltasMes = 0;
    int feriasAno = 0;

    std::string prefixoMes =
        std::to_string(ano) + "-" + (mes < 10 ? "0" : "") + std::to_string(mes);
    std::string prefixoAno = std::to_string(ano);

    for (const auto &par : col.marcacoes) {
      if (par.first.find(prefixoMes) == 0) {
        if (par.second == 'F')
          feriasMes++;
        else if (par.second == 'X')
          faltasMes++;
      }
      if (par.first.find(prefixoAno) == 0 && par.second == 'F') {
        feriasAno++;
      }
    }
    int diasRestantes = 22 - feriasAno;
    std::cout << std::left << std::setw(20) << col.nome << std::setw(10)
              << feriasMes << std::setw(10) << faltasMes << std::setw(15)
              << diasRestantes << std::endl;
  }
}

void exportarDados(const std::vector<Colaborador> &colaboradores) {
  std::ofstream ficheiro("exportacao.csv");
  if (!ficheiro.is_open()) {
    std::cout << COR_ERRO << "Erro ao criar ficheiro de exportação."
              << COR_RESET << std::endl;
    return;
  }

  // Exporta dados do calendário
  ficheiro << "--- CALENDARIO ---\n";
  ficheiro << "ID;Nome;Departamento;Data;Tipo\n";
  for (const auto &col : colaboradores) {
    for (const auto &par : col.marcacoes) {
      ficheiro << col.id << ";" << col.nome << ";" << col.departamento << ";"
               << par.first << ";" << par.second << "\n";
    }
  }

  // Exporta dados de formações
  ficheiro << "\n--- FORMACOES ---\n";
  ficheiro << "ID;Nome;Curso;DataConclusao\n";
  for (const auto &col : colaboradores) {
    for (const auto &f : col.formacoes) {
      ficheiro << col.id << ";" << col.nome << ";" << f.nome_curso << ";"
               << f.data_conclusao << "\n";
    }
  }

  // Exporta notas
  ficheiro << "\n--- NOTAS ---\n";
  ficheiro << "ID;Nome;Nota;Data\n";
  for (const auto &col : colaboradores) {
    for (const auto &n : col.notas) {
      ficheiro << col.id << ";" << col.nome << ";" << n.texto << ";" << n.data
               << "\n";
    }
  }

  ficheiro.close();
  std::cout
      << COR_SUCESSO
      << "Dados exportados para 'exportacao.csv' (incluindo formações e notas)."
      << COR_RESET << std::endl;
}
