#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <vector>
#include <map>


struct Colaborador {
    std::string nome;
    // Usamos um mapa para armazenar apenas os dias com marcações
    // Chave: "YYYY-MM-DD", Valor: 'F' (Férias) ou 'X' (Falta)
    std::map<std::string, char> marcacoes;
};

/**
 * @brief Procura um colaborador pelo nome na lista.
 * @param colaboradores A lista de todos os colaboradores.
 * @param nome O nome a procurar.
 * @return Um ponteiro para o Colaborador se encontrado, ou nullptr se não.
 */
Colaborador* buscarColaboradorPorNome(std::vector<Colaborador>& colaboradores, const std::string& nome);

/**
 * @brief Adiciona um novo colaborador à lista, verificando duplicados.
 * @param colaboradores A lista de todos os colaboradores.
 */
void adicionarColaborador(std::vector<Colaborador>& colaboradores);

/**
 * @brief Lista todos os colaboradores registados.
 * @param colaboradores A lista de todos os colaboradores.
 */
void listarColaboradores(const std::vector<Colaborador>& colaboradores);

/**
 * @brief Permite marcar ou desmarcar uma ausência (férias/falta) para um colaborador.
 * @param colaboradores A lista de todos os colaboradores.
 */
void marcarAusencia(std::vector<Colaborador>& colaboradores);

/**
 * @brief Mostra o calendário mensal de um colaborador específico.
 * @param colaboradores A lista de todos os colaboradores.
 */
void visualizarCalendarioColaborador(std::vector<Colaborador>& colaboradores);


#endif // COLABORADOR_H