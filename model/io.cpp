#include "io.h"
#include "cifra.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Formato do Ficheiro (por linha):
// NOME_CIFRADO;ID;DEPT;MARCACOES;FORMACOES;NOTAS
// MARCACOES: DATA:TIPO,DATA:TIPO
// FORMACOES: NOME|DATA,NOME|DATA
// NOTAS: TEXTO|DATA,TEXTO|DATA

bool guardarDados(const std::vector<Colaborador> &colaboradores,
                  const std::string &nomeFicheiro, int chaveCifra) {
  std::ofstream ficheiro(nomeFicheiro);
  if (!ficheiro.is_open()) {
    std::cerr << "Erro: Não foi possível abrir o ficheiro " << nomeFicheiro
              << " para escrita." << std::endl;
    return false;
  }

  for (const Colaborador &col : colaboradores) {
    // 1. Nome Cifrado (para proteção básica de dados)
    ficheiro << cifrar(col.nome, chaveCifra) << ";";
    // 2. ID
    ficheiro << col.id << ";";
    // 3. Departamento
    ficheiro << col.departamento << ";";

    // 4. Marcações (Formato: DATA:TIPO,DATA:TIPO)
    bool primeira = true;
    for (const auto &par : col.marcacoes) {
      if (!primeira)
        ficheiro << ",";
      ficheiro << par.first << ":" << par.second;
      primeira = false;
    }
    ficheiro << ";";

    // 5. Formações (Formato: NOME|DATA,NOME|DATA)
    primeira = true;
    for (const auto &f : col.formacoes) {
      if (!primeira)
        ficheiro << ",";
      ficheiro << f.nome_curso << "|" << f.data_conclusao;
      primeira = false;
    }
    ficheiro << ";";

    // 6. Notas (Formato: TEXTO|DATA,TEXTO|DATA)
    primeira = true;
    for (const auto &n : col.notas) {
      if (!primeira)
        ficheiro << ",";
      ficheiro << n.texto << "|" << n.data;
      primeira = false;
    }
    ficheiro << "\n";
  }

  ficheiro.close();
  std::cout << "Dados guardados com sucesso em " << nomeFicheiro << std::endl;
  return true;
}

bool carregarDados(std::vector<Colaborador> &colaboradores,
                   const std::string &nomeFicheiro, int chaveCifra) {
  std::ifstream ficheiro(nomeFicheiro);
  if (!ficheiro.is_open()) {
    std::cerr << "Aviso: Ficheiro " << nomeFicheiro
              << " não encontrado. A iniciar sem dados." << std::endl;
    return false;
  }

  colaboradores.clear();
  std::string linha;

  while (std::getline(ficheiro, linha)) {
    if (linha.empty())
      continue;

    std::stringstream ssLinha(linha);
    std::string segmento;
    Colaborador col;

    // 1. Nome (Desencripta ao ler)
    if (std::getline(ssLinha, segmento, ';')) {
      col.nome = decifrar(segmento, chaveCifra);
    }

    // 2. ID
    if (std::getline(ssLinha, segmento, ';')) {
      try {
        col.id = std::stoi(segmento);
      } catch (...) {
        col.id = 0; // Fallback em caso de erro de conversão
      }
    }

    // 3. Departamento
    if (std::getline(ssLinha, segmento, ';')) {
      col.departamento = segmento;
    }

    // 4. Marcações (Parse da lista separada por vírgulas)
    if (std::getline(ssLinha, segmento, ';')) {
      std::stringstream ssMarcacoes(segmento);
      std::string item;
      while (std::getline(ssMarcacoes, item, ',')) {
        size_t pos = item.find(':');
        if (pos != std::string::npos) {
          std::string data = item.substr(0, pos);
          char tipo = item[pos + 1];
          col.marcacoes[data] = tipo;
        }
      }
    }

    // 5. Formações
    if (std::getline(ssLinha, segmento, ';')) {
      std::stringstream ssFormacoes(segmento);
      std::string item;
      while (std::getline(ssFormacoes, item, ',')) {
        size_t pos = item.find('|');
        if (pos != std::string::npos) {
          Formacao f;
          f.nome_curso = item.substr(0, pos);
          f.data_conclusao = item.substr(pos + 1);
          col.formacoes.push_back(f);
        }
      }
    }

    // 6. Notas
    if (std::getline(ssLinha, segmento, ';')) {
      std::stringstream ssNotas(segmento);
      std::string item;
      while (std::getline(ssNotas, item, ',')) {
        size_t pos = item.find('|');
        if (pos != std::string::npos) {
          Nota n;
          n.texto = item.substr(0, pos);
          n.data = item.substr(pos + 1);
          col.notas.push_back(n);
        }
      }
    }

    colaboradores.push_back(col);
  }

  ficheiro.close();
  std::cout << "Dados carregados com sucesso de " << nomeFicheiro << std::endl;
  return true;
}
