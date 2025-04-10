# Trabalho Processos ⚖️📊

Olá! Seja bem-vindo(a) ao repositório **Trabalho Processos**! Este projeto foi desenvolvido em C para demonstrar a manipulação de dados de processos eleitorais utilizando o conceito de Tipo Abstrato de Dados (TAD). Aqui, o código realiza diversas operações de leitura, processamento e ordenação dos dados de processos de forma totalmente manual — sem o uso de funções avançadas de bibliotecas para ordenação ou busca — deixando o projeto organizado, modular e com um toque de criatividade! 😄

---

## O Projeto

Neste projeto, o programa realiza as seguintes operações:

- **Leitura do CSV:**  
  O programa lê um arquivo CSV (exceto o cabeçalho) que contém os atributos:
  - **`id`**: Identificador do processo.
  - **`numero`**: Número do processo.
  - **`data_ajuizamento`**: Data em que o processo foi iniciado.
  - **`id_classe`**: Classe vinculada ao processo.
  - **`id_assunto`**: Assunto vinculado ao processo – este campo pode conter múltiplos valores, delimitados por chaves `{}`.
  - **`ano_eleicao`**: Ano da eleição que ensejou o processo.

- **Ordenações:**  
  - Ordena os processos em ordem **crescente** pelo atributo `id` e salva o resultado no arquivo `ordenado_por_id.csv`.
  - Ordena os processos em ordem **decrescente** pela `data_ajuizamento` e salva o resultado no arquivo `ordenado_por_data.csv`.

- **Contagens e Listagens:**  
  - Conta quantos processos estão associados a um determinado `id_classe` (por exemplo, 327).
  - Conta quantos `id_assuntos` únicos existem na base.
  - Lista todos os processos que possuem mais de um assunto.

- **Cálculo de Tramitação:**  
  - Calcula há quantos dias cada processo está em tramitação, ou seja, a diferença entre a data de ajuizamento e a data atual.

---

## Estrutura do Projeto

O código foi organizado em três arquivos, seguindo as diretrizes do TAD, para manter o projeto bem modularizado:

trabalho_processos/ 
├── main.c # Função principal e coordenação das operações 
├── processo.c # Implementação do TAD Processo e das funções de manipulação 
├── processo.h # Cabeçalho com a definição da struct Processo e os protótipos das funções 
├── processo_043_202409032338.csv # Arquivo CSV com os dados dos processos (entrada) 
└── README.md # Este arquivo, com todas as informações sobre o projeto


Cada operação (ordenar, contar, listar e calcular dias) foi implementada em uma função específica, garantindo que o código seja claro e fácil de manter.
