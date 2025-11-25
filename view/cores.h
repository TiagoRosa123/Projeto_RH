#ifndef CORES_H
#define CORES_H

#include <string>

// Códigos de escape ANSI para cores no terminal
inline const std::string COR_RESET = "\033[0m";
inline const std::string COR_TITULO = "\033[1;36m";  // Cyan brilhante
inline const std::string COR_OPCAO = "\033[1;33m";   // Amarelo brilhante
inline const std::string COR_SAIR = "\033[1;32m";    // Verde brilhante
inline const std::string COR_ERRO = "\033[1;31m";    // Vermelho brilhante
inline const std::string COR_PROMPT = "\033[2;37m";  // Cinza
inline const std::string COR_SUCESSO = "\033[1;32m"; // Verde
inline const std::string COR_AVISO = "\033[1;33m";   // Amarelo
inline const std::string COR_FERIAS = "\033[1;33m";  // Amarelo
inline const std::string COR_FALTA = "\033[1;31m";   // Vermelho

#endif