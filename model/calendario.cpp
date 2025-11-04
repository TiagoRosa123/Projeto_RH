#include "calendario.h"
#include "../view/view.h"
#include <iostream>
#include <iomanip> // Para std::setw
#include <ctime>   // Para calcular o dia da semana
#include <sstream> // Para formatarData

bool isBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int ano, int mes) {
    if (mes == 2) {
        return isBissexto(ano) ? 29 : 28;
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    } else {
        return 31;
    }
}

bool isDataValida(int ano, int mes, int dia) {
    if (ano < 1900 || ano > 2100) return false; 
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > diasNoMes(ano, mes)) return false;
    return true;
}

int getDiaDaSemana(int ano, int mes, int dia) {
    std::tm time_in = {0, 0, 0, dia, mes - 1, ano - 1900};
    
    // mktime normaliza a data e preenche os outros campos
    std::time_t time_temp = std::mktime(&time_in);
    
    // localtime converte para a estrutura tm local
    const std::tm* time_out = std::localtime(&time_temp);
    
    // tm_wday é 0=Domingo, 1=Segunda, ..., 6=Sábado
    return time_out->tm_wday;
}

std::string formatarData(int ano, int mes, int dia) {
    std::ostringstream oss;
    oss << ano << "-" 
        << std::setw(2) << std::setfill('0') << mes << "-"
        << std::setw(2) << std::setfill('0') << dia;
    return oss.str();
}
