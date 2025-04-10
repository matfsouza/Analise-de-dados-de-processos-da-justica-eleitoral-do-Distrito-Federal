#include <stdio.h>
#include <direct.h> // Para _getcwd em Windows
#include "processo.h"

int main(void)
{
    Processo processos[MAX_PROCESSOS];
    int n = 0;
    char cwd[1024];

    if (_getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Diretório de trabalho atual: %s\n", cwd);
    else
        printf("Não foi possível recuperar o diretório de trabalho.\n");

    printf("Iniciando leitura do arquivo 'processo_043_202409032338.csv'...\n");
    if (!carregar_processos("processo_043_202409032338.csv", processos, &n))
    {
        printf("Falha ao carregar o arquivo.\n");
        return 1;
    }
    printf("Foram carregados %d processos.\n", n);

    // Operação 1: Ordenar por ID e salvar em arquivo CSV
    printf("Ordenando por ID...\n");
    ordenar_por_id(processos, n);
    salvar_csv("ordenado_por_id.csv", processos, n);

    // Operação 2: Ordenar por data de ajuizamento (ordem decrescente) e salvar em arquivo CSV
    printf("Ordenando por data de ajuizamento...\n");
    ordenar_por_data(processos, n);
    salvar_csv("ordenado_por_data.csv", processos, n);

    // Operação 3: Contar processos de um determinado id_classe (exemplo: 327)
    int classe = 327;
    printf("Contagem de processos da classe %d: %d\n", classe, contar_por_classe(processos, n, classe));

    // Operação 4: Contar assuntos únicos
    printf("Total de assuntos únicos: %d\n", contar_assuntos_unicos(processos, n));

    // Operação 5: Listar os processos que possuem múltiplos assuntos
    listar_multiplos_assuntos(processos, n);

    // Operação 6: Calcular os dias de tramitação para cada processo
    printf("Dias de tramitação de cada processo:\n");
    for (int i = 0; i < n; i++)
    {
        int dias = calcular_dias_tramitacao(&processos[i]);
        printf("ID: %d | Dias: %d\n", processos[i].id, dias);
    }

    printf("Fim do programa.\n");
    return 0;
}