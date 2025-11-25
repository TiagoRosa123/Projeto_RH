#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <map>
#include <string>
#include <vector>


struct Formacao {
  std::string nome_curso;     ///< Nome do curso ou formação
  std::string data_conclusao; ///< Data de conclusão (formato string)
};

struct Nota {
  std::string texto; ///< Conteúdo da nota ou observação
  std::string data;  ///< Data de criação da nota
};

struct Colaborador {
  int id;                   ///< Identificador único do colaborador
  std::string nome;         ///< Nome completo do colaborador
  std::string departamento; ///< Departamento ao qual pertence

  // Usamos um mapa para armazenar apenas os dias com marcações
  // Chave: "YYYY-MM-DD", Valor: 'F' (Férias) ou 'X' (Falta)
  std::map<std::string, char> marcacoes;

  std::vector<Formacao> formacoes; ///< Histórico de formações
  std::vector<Nota> notas;         ///< Notas e observações sobre o colaborador
};

/**
 * @brief Procura um colaborador pelo nome na lista.
 * @param colaboradores A lista de todos os colaboradores.
 * @param nome O nome a procurar.
 * @return Um ponteiro para o Colaborador se encontrado, ou nullptr se não.
 */
Colaborador *buscarColaboradorPorNome(std::vector<Colaborador> &colaboradores,
                                      const std::string &nome);

/**
 * @brief Procura um colaborador pelo ID na lista.
 * @param colaboradores A lista de todos os colaboradores.
 * @param id O ID a procurar.
 * @return Um ponteiro para o Colaborador se encontrado, ou nullptr se não.
 */
Colaborador *buscarColaboradorPorId(std::vector<Colaborador> &colaboradores,
                                    int id);

/**
 * @brief Adiciona um novo colaborador à lista, verificando duplicados.
 * @param colaboradores A lista de todos os colaboradores.
 */
void adicionarColaborador(std::vector<Colaborador> &colaboradores);

/**
 * @brief Lista todos os colaboradores registados.
 * @param colaboradores A lista de todos os colaboradores.
 */
void listarColaboradores(const std::vector<Colaborador> &colaboradores);

/**
 * @brief Permite marcar ou desmarcar uma ausência (férias/falta) para um
 * colaborador.
 * @param colaboradores A lista de todos os colaboradores.
 */
void marcarAusencia(std::vector<Colaborador> &colaboradores);

/**
 * @brief Mostra o calendário mensal de um colaborador específico.
 * @param colaboradores A lista de todos os colaboradores.
 */
void visualizarCalendarioColaborador(std::vector<Colaborador> &colaboradores);

/**
 * @brief Menu para gerir formações de um colaborador.
 */
void gerirFormacoes(Colaborador &colaborador);

/**
 * @brief Menu para gerir notas de um colaborador.
 */
void gerirNotas(Colaborador &colaborador);

/**
 * @brief Gera relatórios mensais de férias e faltas.
 */
void relatorioMensal(const std::vector<Colaborador> &colaboradores);

/**
 * @brief Mostra estatísticas por departamento.
 */
void estatisticasDepartamento(const std::vector<Colaborador> &colaboradores);

/**
 * @brief Mostra um dashboard resumido.
 */
void dashboardResumido(const std::vector<Colaborador> &colaboradores);

/**
 * @brief Exporta dados de um colaborador ou departamento.
 */
void exportarDados(const std::vector<Colaborador> &colaboradores);

#endif // COLABORADOR_H