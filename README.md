# Trabalho Processos ⚖️📊

Bem-vindo ao repositório **Trabalho Processos**!  
Este projeto em C implementa o Tipo Abstrato de Dados (TAD) **Processo** para ler, processar e ordenar dados de processos eleitorais. Ele cumpre os seguintes itens:

- **Leitura de CSV**: Extrai os atributos de cada processo (como `id`, `numero`, `data_ajuizamento`, `id_classe`, `id_assunto` e `ano_eleicao`), tratando atributos multivalorados delimitados por `{}`.
- **Ordenação**:
  - Ordena em ordem crescente pelo atributo `id`.
  - Ordena em ordem decrescente pela `data_ajuizamento`.
- **Contagens & Listagens**:
  - Conta quantos processos estão vinculados a um determinado `id_classe`.
  - Identifica quantos `id_assuntos` únicos há na base de dados.
  - Lista os processos que possuem mais de um assunto.
- **Cálculo**:
  - Indica há quantos dias cada processo está em tramitação (diferença entre a data de ajuizamento e a data atual).

---

## 📋 Requisitos do Projeto

Este projeto foi desenvolvido atendendo a todas as seguintes especificações:

- Implementação do TAD **Processo** usando uma `struct`.
- Organização dos dados em vetores de structs.
- Utilização de funções próprias para ordenação (sem funções de bibliotecas externas para essa finalidade).
- Código organizado em **3 arquivos**:
  - `main.c` – Contém a função `main` e a lógica de execução.
  - `processo.c` – Implementa as funções de processamento e ordenação dos dados.
  - `processo.h` – Cabeçalho com a definição do TAD e os protótipos das funções.
- Salva os resultados das ordenações em arquivos CSV com cabeçalho.

---

## 🚀 Como Compilar e Executar

### Pré-requisitos

- **Compilador C** (ex.: GCC – MinGW para Windows)
- **Git** (opcional, para clonar o repositório)

### Passos

1. **Clone o repositório** (caso ainda não o tenha feito):

   ```bash
   git clone https://github.com/seunome/trabalho_processos.git
   cd trabalho_processos
