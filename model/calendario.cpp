#include "calendario.h"
#include <ctime>   // Para calcular o dia da semana
#include <iomanip> // Para std::setw
#include <iostream>
#include <sstream> // Para formatarData

bool isBissexto(int ano) {
  // Um ano é bissexto se for divisível por 4 e não por 100, ou se for divisível
  // por 400
  return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int ano, int mes) {
  if (mes == 2) {
    // Fevereiro tem 29 dias em anos bissextos e 28 em anos comuns
    return isBissexto(ano) ? 29 : 28;
  } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    // Abril, Junho, Setembro, Novembro têm 30 dias
    return 30;
  } else {
    // Os restantes têm 31 dias
    return 31;
  }
}

bool isDataValida(int ano, int mes, int dia) {
  if (ano < 1900 || ano > 2100)
    return false; // Limite de anos para o sistema
  if (mes < 1 || mes > 12)
    return false; // Mês inválido
  if (dia < 1 || dia > diasNoMes(ano, mes))
    return false; // Dia inválido para o mês/ano
  return true;
}

int getDiaDaSemana(int ano, int mes, int dia) {
  // Configura a estrutura tm com a data fornecida
  std::tm time_in = {0, 0, 0, dia, mes - 1, ano - 1900};

  // mktime normaliza a data e calcula o dia da semana
  std::time_t time_temp = std::mktime(&time_in);

  // localtime converte para a estrutura tm local (necessário após mktime)
  const std::tm *time_out = std::localtime(&time_temp);

  // tm_wday retorna 0 para Domingo, 1 para Segunda, etc.
  return time_out->tm_wday;
}

std::string formatarData(int ano, int mes, int dia) {
  std::ostringstream oss;
  // Formata para YYYY-MM-DD com zeros à esquerda se necessário
  oss << ano << "-" << std::setw(2) << std::setfill('0') << mes << "-"
      << std::setw(2) << std::setfill('0') << dia;
  return oss.str();
}
