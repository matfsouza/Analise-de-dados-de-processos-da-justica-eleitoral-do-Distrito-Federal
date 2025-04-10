#ifndef PROCESSO_H
#define PROCESSO_H

#define MAX_PROCESSOS 1000
#define MAX_NUMERO 32
#define MAX_ASSUNTOS 10

typedef struct
{
    int id;
    char numero[MAX_NUMERO];
    char data_ajuizamento[11];
    int id_classe;
    int id_assuntos[MAX_ASSUNTOS];
    int qtd_assuntos;
} Processo;

void limpar_token(char *token);
int carregar_processos(const char *nome_arquivo, Processo processos[], int *n);
void ordenar_por_id(Processo processos[], int n);
void ordenar_por_data(Processo processos[], int n);
int contar_por_classe(Processo processos[], int n, int id_classe);
int contar_assuntos_unicos(Processo processos[], int n);
void listar_multiplos_assuntos(Processo processos[], int n);
int calcular_dias_tramitacao(Processo *p);
void salvar_csv(const char *nome_arquivo, Processo processos[], int n);

#endif