#include "colaborador.h"
#include "calendario.h" 
#include "calendario.h" 
#include "../view/view.h"
#include <iostream>
#include <limits>

// Função auxiliar para limpar o buffer de entrada
void limparBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Colaborador* buscarColaboradorPorNome(std::vector<Colaborador>& colaboradores, const std::string& nome) {
    for (Colaborador& col : colaboradores) {
        if (col.nome == nome) {
            return &col;
        }
    }
    return nullptr;
}

void adicionarColaborador(std::vector<Colaborador>& colaboradores) {
    std::string nome;
    std::cout << "Digite o nome do novo colaborador: ";
    limparBufferEntrada();
    std::getline(std::cin, nome);

    if (buscarColaboradorPorNome(colaboradores, nome) != nullptr) {
        std::cout << "Erro: Já existe um colaborador com esse nome." << std::endl;
        char resposta;
        std::cout << "Deseja continuar e adicionar mesmo assim? (s/n): ";
        std::cin >> resposta;
        if (resposta != 's' && resposta != 'S') {
            std::cout << "Adição cancelada." << std::endl;
            return;
        }
    }

    Colaborador novoColaborador;
    novoColaborador.nome = nome;
    colaboradores.push_back(novoColaborador);
    std::cout << "Colaborador '" << nome << "' adicionado com sucesso!" << std::endl;
}

void listarColaboradores(const std::vector<Colaborador>& colaboradores) {
    std::cout << "\n--- Lista de Colaboradores ---" << std::endl;
    if (colaboradores.empty()) {
        std::cout << "Nenhum colaborador registado." << std::endl;
    } else {
        for (size_t i = 0; i < colaboradores.size(); ++i) {
            std::cout << i + 1 << ". " << colaboradores[i].nome << std::endl;
        }
    }
    std::cout << "--------------------------------" << std::endl;
}

void marcarAusencia(std::vector<Colaborador>& colaboradores) {
    std::string nome;
    std::cout << "Digite o nome do colaborador: ";
    limparBufferEntrada();
    std::getline(std::cin, nome);

    Colaborador* col = buscarColaboradorPorNome(colaboradores, nome);
    if (col == nullptr) {
        std::cout << "Erro: Colaborador não encontrado." << std::endl;
        return;
    }

    int ano, mes, dia;
    std::cout << "Digite o Ano (ex: 2024): ";
    while (!(std::cin >> ano)) {
        std::cout << "Entrada inválida. Digite o Ano: ";
        std::cin.clear();
        limparBufferEntrada();
    }
    std::cout << "Digite o Mês (1-12): ";
     while (!(std::cin >> mes) || mes < 1 || mes > 12) {
        std::cout << "Entrada inválida. Digite o Mês (1-12): ";
        std::cin.clear();
        limparBufferEntrada();
    }
    std::cout << "Digite o Dia (1-31): ";
    while (!(std::cin >> dia)) {
        std::cout << "Entrada inválida. Digite o Dia: ";
        std::cin.clear();
        limparBufferEntrada();
    }


    if (!isDataValida(ano, mes, dia)) {
        std::cout << "Erro: Data inválida (" << dia << "/" << mes << "/" << ano << ")." << std::endl;
        return;
    }

    int diaSemana = getDiaDaSemana(ano, mes, dia);
    if (diaSemana == 0 || diaSemana == 6) { // 0=Domingo, 6=Sábado
        std::cout << "Erro: Não é permitido marcar ausências ao fim de semana." << std::endl;
        return;
    }

    char tipo;
    std::cout << "Tipo de marcação (F - Férias, X - Falta, D - Desmarcar): ";
    std::cin >> tipo;
    tipo = std::toupper(tipo);

    std::string chaveData = formatarData(ano, mes, dia);

    if (tipo == 'D') {
        if (col->marcacoes.count(chaveData)) {
            col->marcacoes.erase(chaveData);
            std::cout << "Marcação removida com sucesso para " << chaveData << "." << std::endl;
        } else {
            std::cout << "Nenhuma marcação encontrada para remover nesse dia." << std::endl;
        }
    } else if (tipo == 'F' || tipo == 'X') {
        col->marcacoes[chaveData] = tipo;
        std::cout << "Marcação (" << tipo << ") registada com sucesso para " << chaveData << "." << std::endl;
    } else {
        std::cout << "Erro: Tipo de marcação inválido." << std::endl;
    }
}

void visualizarCalendarioColaborador(std::vector<Colaborador>& colaboradores) {
    std::string nome;
    std::cout << "Digite o nome do colaborador: ";
    limparBufferEntrada();
    std::getline(std::cin, nome);

    Colaborador* col = buscarColaboradorPorNome(colaboradores, nome);
    if (col == nullptr) {
        std::cout << "Erro: Colaborador não encontrado." << std::endl;
        return;
    }

    int ano, mes;
    std::cout << "Digite o Ano (ex: 2024): ";
     while (!(std::cin >> ano)) {
        std::cout << "Entrada inválida. Digite o Ano: ";
        std::cin.clear();
        limparBufferEntrada();
    }
    std::cout << "Digite o Mês (1-12): ";
    while (!(std::cin >> mes) || mes < 1 || mes > 12) {
        std::cout << "Entrada inválida. Digite o Mês (1-12): ";
        std::cin.clear();
        limparBufferEntrada();
    }


    std::cout << "\n--- Calendário de " << col->nome << " para " << mes << "/" << ano << " ---" << std::endl;
    imprimirCalendario(ano, mes, col->marcacoes);
}
