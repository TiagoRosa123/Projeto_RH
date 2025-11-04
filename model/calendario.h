#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <map>
#include <string>

/**
 * @brief Verifica se um ano é bissexto.
 */
bool isBissexto(int ano);

/**
 * @brief Retorna o número de dias num determinado mês/ano.
 */
int diasNoMes(int ano, int mes);

/**
 * @brief Verifica se uma data (ano, mes, dia) é válida.
 */
bool isDataValida(int ano, int mes, int dia);

/**
 * @brief Retorna o dia da semana para uma data.
 * @return 0=Domingo, 1=Segunda, ..., 6=Sábado.
 */
int getDiaDaSemana(int ano, int mes, int dia);

/**
 * @brief Imprime um calendário mensal na consola, mostrando marcações.
 * @param ano O ano a exibir.
 * @param mes O mês a exibir.
 * @param marcacoes O mapa de marcações (YYYY-MM-DD -> char) do colaborador.
 */
void imprimirCalendario(int ano, int mes, const std::map<std::string, char>& marcacoes);

/**
 * @brief Formata uma data (ano, mes, dia) para a string "YYYY-MM-DD".
 */
std::string formatarData(int ano, int mes, int dia);

#endif // CALENDARIO_H
