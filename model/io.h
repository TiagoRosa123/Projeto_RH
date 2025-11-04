#ifndef IO_H
#define IO_H

#include "colaborador.h"
#include <string>
#include <vector>

/**
 * @brief Guarda a lista de colaboradores num ficheiro.
 * Os nomes são encriptados.
 * @param colaboradores A lista de colaboradores.
 * @param nomeFicheiro O nome do ficheiro onde guardar.
 * @param chaveCifra A chave para encriptar os nomes.
 * @return true se guardou com sucesso, false caso contrário.
 */
bool guardarDados(const std::vector<Colaborador>& colaboradores, const std::string& nomeFicheiro, int chaveCifra);

/**
 * @brief Carrega a lista de colaboradores de um ficheiro.
 * Os nomes são desencriptados.
 * @param colaboradores A lista (vazia) onde carregar os dados.
 * @param nomeFicheiro O nome do ficheiro de onde ler.
 * @param chaveCifra A chave para desencriptar os nomes.
 * @return true se carregou com sucesso, false caso contrário.
 */
bool carregarDados(std::vector<Colaborador>& colaboradores, const std::string& nomeFicheiro, int chaveCifra);


#endif // IO_H
