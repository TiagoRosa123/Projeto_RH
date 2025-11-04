#include "view.h"
#include <iostream>
#include <iomanip>
#include "cores.h"

void imprimirCalendario(int ano, int mes, const std::map<std::string, char>& marcacoes) {
    const std::string nomesMeses[] = {
        "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    std::cout << "\n   " << nomesMeses[mes - 1] << " " << ano << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << " Dom Seg Ter Qua Qui Sex Sab" << std::endl;

    // Implementação do calendário (já existente)
    std::cout << "\n-----------------------------" << std::endl;
    std::cout << "[F] = Férias, [X] = Falta" << std::endl;
}

void exibirMenu() {
    std::cout << "\n" << COR_TITULO << "--- Mini-Sistema de RH ---" << COR_RESET << std::endl;
    std::cout << COR_OPCAO << "1." << COR_RESET << " Adicionar Colaborador" << std::endl;
    std::cout << COR_OPCAO << "2." << COR_RESET << " Marcar/Desmarcar Ausência (Férias/Falta)" << std::endl;
    std::cout << COR_OPCAO << "3." << COR_RESET << " Listar Colaboradores" << std::endl;
    std::cout << COR_OPCAO << "4." << COR_RESET << " Visualizar Calendário Mensal de Colaborador" << std::endl;
    std::cout << COR_SAIR << "5." << COR_RESET << " Guardar e Sair" << std::endl;
    std::cout << "\nEscolha uma opção: ";
}