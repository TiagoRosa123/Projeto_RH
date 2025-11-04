#include "io.h"
#include "cifra.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Formato do Ficheiro (por linha):
// NOME_CIFRADO;DATA1:TIPO1,DATA2:TIPO2,DATA3:TIPO3...
// Exemplo:
// Mdvfl Sdqwr;2024-10-28:F,2024-10-29:F,2024-11-01:X
// (Nome "Joao Pinto" cifrado com chave 3)

bool guardarDados(const std::vector<Colaborador>& colaboradores, const std::string& nomeFicheiro, int chaveCifra) {
    std::ofstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o ficheiro " << nomeFicheiro << " para escrita." << std::endl;
        return false;
    }

    for (const Colaborador& col : colaboradores) {
        // Encripta o nome antes de guardar
        ficheiro << cifrar(col.nome, chaveCifra) << ";";

        // Guarda as marcações (formato "DATA:TIPO,DATA:TIPO")
        bool primeiraMarcacao = true;
        for (const auto& par : col.marcacoes) {
            // auto& par é um std::pair<std::string, char>
            if (!primeiraMarcacao) {
                ficheiro << ",";
            }
            ficheiro << par.first << ":" << par.second;
            primeiraMarcacao = false;
        }
        ficheiro << "\n";
    }

    ficheiro.close();
    std::cout << "Dados guardados com sucesso em " << nomeFicheiro << std::endl;
    return true;
}

bool carregarDados(std::vector<Colaborador>& colaboradores, const std::string& nomeFicheiro, int chaveCifra) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        std::cerr << "Aviso: Ficheiro " << nomeFicheiro << " não encontrado. A iniciar sem dados." << std::endl;
        return false;
    }

    colaboradores.clear(); 
    std::string linha;

    while (std::getline(ficheiro, linha)) {
        if (linha.empty()) continue;

        std::stringstream ssLinha(linha);
        std::string segmento;
        Colaborador col;

        // 1. Ler o nome cifrado (até ao ';')
        std::getline(ssLinha, segmento, ';');
        // Desencripta o nome ao carregar
        col.nome = decifrar(segmento, chaveCifra);

        // 2. Ler a string de marcações (o resto da linha)
        std::getline(ssLinha, segmento);
        if (!segmento.empty()) {
            std::stringstream ssMarcacoes(segmento);
            std::string marcacaoStr;

            // Divide a string de marcações por ','
            while (std::getline(ssMarcacoes, marcacaoStr, ',')) {
                std::stringstream ssPar(marcacaoStr);
                std::string data;
                std::string tipoStr;

                // Divide "YYYY-MM-DD:TIPO" por ':'
                std::getline(ssPar, data, ':');
                std::getline(ssPar, tipoStr);

                if (!data.empty() && !tipoStr.empty()) {
                    col.marcacoes[data] = tipoStr[0];
                }
            }
        }
        
        colaboradores.push_back(col);
    }

    ficheiro.close();
    std::cout << "Dados carregados com sucesso de " << nomeFicheiro << std::endl;
    return true;
}
