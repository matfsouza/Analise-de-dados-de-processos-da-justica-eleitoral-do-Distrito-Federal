#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "processo.h"

void limpar_token(char *token)
{
    if (!token)
        return;
    char *src = token, *dst = token;
    while (*src)
    {
        if (*src != '"' && *src != '\n' && *src != '\r')
            *dst++ = *src;
        src++;
    }
    *dst = '\0';
}

int carregar_processos(const char *nome_arquivo, Processo processos[], int *n)
{
    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp)
    {
        perror("Erro ao abrir o arquivo de entrada");
        return 0;
    }

    char linha[1024];
    int linha_atual = 0;
    *n = 0;

    while (fgets(linha, sizeof(linha), fp))
    {
        if (linha_atual == 0)
        {
            if (strncmp(linha, "\xEF\xBB\xBF", 3) == 0)
                memmove(linha, linha + 3, strlen(linha + 3) + 1);
        }

        if (linha_atual++ == 0)
            continue;

        Processo p = {0};
        char *token;

        token = strtok(linha, ",");
        if (!token)
            continue;
        limpar_token(token);
        p.id = atoi(token);

        token = strtok(NULL, ",");
        if (!token)
            continue;
        limpar_token(token);
        strncpy(p.numero, token, MAX_NUMERO - 1);
        p.numero[MAX_NUMERO - 1] = '\0';

        token = strtok(NULL, ",");
        if (!token)
            continue;
        limpar_token(token);
        strncpy(p.data_ajuizamento, token, 10);
        p.data_ajuizamento[10] = '\0';

        token = strtok(NULL, ",");
        if (!token)
            continue;
        limpar_token(token);
        sscanf(token, "{%d}", &p.id_classe);

        token = strtok(NULL, ",");
        if (!token)
            continue;
        limpar_token(token);
        p.qtd_assuntos = 0;
        if (token[0] == '{')
        {
            char *ptr = token + 1;
            while (*ptr && *ptr != '}')
            {
                int id;
                if (sscanf(ptr, "%d", &id) == 1 && p.qtd_assuntos < MAX_ASSUNTOS)
                    p.id_assuntos[p.qtd_assuntos++] = id;
                while (*ptr && *ptr != ',' && *ptr != '}')
                    ptr++;
                if (*ptr == ',')
                    ptr++;
            }
        }

        token = strtok(NULL, ",");

        processos[(*n)++] = p;
        if (*n >= MAX_PROCESSOS)
        {
            printf("Limite de processos (%d) atingido.\n", MAX_PROCESSOS);
            break;
        }
    }

    fclose(fp);
    printf("Fim de carregar_processos: %d processos carregados.\n", *n);
    return 1;
}

void ordenar_por_id(Processo processos[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (processos[i].id > processos[j].id)
            {
                Processo tmp = processos[i];
                processos[i] = processos[j];
                processos[j] = tmp;
            }
}

void ordenar_por_data(Processo processos[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp(processos[i].data_ajuizamento, processos[j].data_ajuizamento) < 0)
            {
                Processo tmp = processos[i];
                processos[i] = processos[j];
                processos[j] = tmp;
            }
}

int contar_por_classe(Processo processos[], int n, int id_classe)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        if (processos[i].id_classe == id_classe)
            count++;
    return count;
}

int contar_assuntos_unicos(Processo processos[], int n)
{
    int mapa[10000] = {0}, total = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < processos[i].qtd_assuntos; j++)
        {
            int id = processos[i].id_assuntos[j];
            if (!mapa[id])
            {
                mapa[id] = 1;
                total++;
            }
        }
    return total;
}

void listar_multiplos_assuntos(Processo processos[], int n)
{
    printf("Processos com múltiplos assuntos:\n");
    for (int i = 0; i < n; i++)
    {
        if (processos[i].qtd_assuntos > 1)
        {
            printf("ID: %d | Número: %s | Assuntos: ", processos[i].id, processos[i].numero);
            for (int j = 0; j < processos[i].qtd_assuntos; j++)
            {
                printf("%d", processos[i].id_assuntos[j]);
                if (j < processos[i].qtd_assuntos - 1)
                    printf(", ");
            }
            printf("\n");
        }
    }
}

int calcular_dias_tramitacao(Processo *p)
{
    struct tm data = {0};
    int ano, mes, dia;
    if (sscanf(p->data_ajuizamento, "%d-%d-%d", &ano, &mes, &dia) != 3)
        return -1;
    data.tm_year = ano - 1900;
    data.tm_mon = mes - 1;
    data.tm_mday = dia;
    time_t t1 = mktime(&data);
    if (t1 == -1)
        return -1;
    time_t t2 = time(NULL);
    return (int)(difftime(t2, t1) / (60 * 60 * 24));
}

void salvar_csv(const char *nome_arquivo, Processo processos[], int n)
{
    FILE *fp = fopen(nome_arquivo, "w");
    if (!fp)
    {
        perror("Erro ao abrir arquivo CSV para escrita");
        printf("Não foi possível abrir %s para escrita.\n", nome_arquivo);
        return;
    }
    fprintf(fp, "id,numero,data_ajuizamento,id_classe,id_assuntos\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d,%s,%s,{%d},\"{", processos[i].id, processos[i].numero,
                processos[i].data_ajuizamento, processos[i].id_classe);
        for (int j = 0; j < processos[i].qtd_assuntos; j++)
        {
            fprintf(fp, "%d", processos[i].id_assuntos[j]);
            if (j < processos[i].qtd_assuntos - 1)
                fprintf(fp, ",");
        }
        fprintf(fp, "}\"");
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Arquivo %s salvo com sucesso.\n", nome_arquivo);
}