# **Mini-Sistema de RH em C++**

Este projeto é uma aplicação de consola robusta para gestão de recursos humanos, permitindo gerir colaboradores, férias, faltas, formações e notas internas, com persistência segura de dados.

## **Funcionalidades**

### **Gestão de Colaboradores**

- **CRUD Completo**: Adicionar, listar e pesquisar colaboradores (por Nome ou ID).
- **Validação**: Verificação de duplicados e validação de dados de entrada.

### **Gestão de Ausências**

- **Marcação**: Marcar Férias (F) ou Faltas (X) num dia específico.
- **Calendário Visual**: Visualização mensal com indicação de dias úteis, fins de semana e marcações (F/X).
- **Regras de Negócio**:
  - Proibição de marcações em fins de semana.
  - Aviso de conflito de férias (se outro colega do mesmo departamento já tiver férias no mesmo dia).

### **Funcionalidades Avançadas**

- **Formações**: Adicionar e gerir cursos/certificações por colaborador.
- **Notas/Observações**: Registar notas internas sobre o desempenho ou ocorrências.
- **Relatórios**:
  - **Relatório Mensal**: Resumo de férias e faltas por colaborador num mês específico.
  - **Estatísticas por Departamento**: Totais de ausências agrupados por departamento.
  - **Dashboard Resumido**: Visão geral do mês com saldo de dias de férias restantes.
- **Exportação**: Exportar todos os dados (Calendário, Formações, Notas) para um ficheiro CSV (`exportacao.csv`).

### **Segurança e Persistência**

- **Encriptação Total**: Todos os dados sensíveis (Nomes, IDs, Departamentos, Notas, etc.) são encriptados no ficheiro `rh_dados.txt` usando uma cifra personalizada (baseada em César + deslocamento numérico).
- **Persistência Automática**: Os dados são carregados ao iniciar e guardados ao sair.

## **Estrutura dos Ficheiros**

O projeto segue uma arquitetura MVC (Model-View-Controller):

- **`controller/`**:
  - `main.cpp`: Ponto de entrada, gere o fluxo principal e menus.
- **`model/`**:
  - `colaborador.h/.cpp`: Lógica principal (Colaborador, Formações, Notas).
  - `calendario.h/.cpp`: Manipulação de datas.
  - `io.h/.cpp`: Persistência de dados (Save/Load).
  - `cifra.h/.cpp`: Algoritmos de encriptação.
  - `utils.h/.cpp`: Funções utilitárias (Input seguro, limpeza de ecrã).
- **`view/`**:
  - `view.h/.cpp`: Interface de consola (Impressão de calendários, menus).
  - `cores.h`: Códigos ANSI para cores na consola.

## **Compilação e Execução**

Para compilar o projeto, navegue até à pasta raiz e execute o seguinte comando (certifique-se de incluir todos os ficheiros `.cpp`):

```bash
g++ -std=c++17 -Wall -g controller/main.cpp model/colaborador.cpp model/calendario.cpp model/io.cpp model/cifra.cpp model/utils.cpp view/view.cpp -o rh_avancado
```

Depois, execute:

**Windows:**

```bash
mini_rh.exe
```

**Linux/Mac:**

```bash
./mini_rh
```

## **Utilização**

1.  Ao iniciar, o sistema carrega os dados existentes (se houver).
2.  Use o menu numérico para navegar.
3.  Para adicionar dados de teste, use a opção **2** (Adicionar Colaborador).
4.  Para ver o calendário, use a opção **4**.
5.  Para gerir formações ou notas, use as opções **6** ou **7**.
6.  Para sair e guardar, escolha a opção **0**.
