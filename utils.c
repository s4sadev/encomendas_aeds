#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define TAM_LINHA 128

static void limpar_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_texto(const char *rotulo, char *destino, int tamanho)
{
    size_t len;

    printf("%s", rotulo);
    if (fgets(destino, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada.\n");
        exit(0);
    }

    len = strlen(destino);
    if (len > 0 && destino[len - 1] == '\n') destino[len - 1] = '\0';
    else limpar_buffer();

    return (int)strlen(destino);
}

void ler_texto_obrigatorio(const char *rotulo, char *destino, int tamanho)
{
    while (ler_texto(rotulo, destino, tamanho) == 0)
        printf("Campo obrigatorio!\n");
}

void atualizar_texto(const char *rotulo, char *campo, int tamanho)
{
    char prompt[TAM_LINHA * 2];
    char entrada[TAM_LINHA];

    if (tamanho > TAM_LINHA) tamanho = TAM_LINHA;
    snprintf(prompt, sizeof(prompt), "%s [%s]: ", rotulo, campo);

    if (ler_texto(prompt, entrada, tamanho) > 0)
        strcpy(campo, entrada);
}

int ler_inteiro(const char *rotulo)
{
    char linha[32];
    char extra;
    int valor;

    while (1) {
        ler_texto(rotulo, linha, sizeof(linha));
        if (sscanf(linha, "%d %c", &valor, &extra) == 1) return valor;
        printf("Numero invalido!\n");
    }
}

float ler_float(const char *rotulo)
{
    char linha[32];
    char extra;
    float valor;
    char *virgula;

    while (1) {
        ler_texto(rotulo, linha, sizeof(linha));
        virgula = strchr(linha, ',');
        if (virgula != NULL) *virgula = '.';
        if (sscanf(linha, "%f %c", &valor, &extra) == 1 && valor >= 0) return valor;
        printf("Valor invalido!\n");
    }
}

static int dias_no_mes(int mes, int ano)
{
    static const int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)) return 29;
    return dias[mes - 1];
}

int data_valida(Data d)
{
    if (d.ano < 1900 || d.ano > 2100) return 0;
    if (d.mes < 1 || d.mes > 12) return 0;
    return d.dia >= 1 && d.dia <= dias_no_mes(d.mes, d.ano);
}

Data ler_data(const char *rotulo)
{
    char linha[32];
    char extra;
    Data d = {0, 0, 0};

    while (1) {
        ler_texto(rotulo, linha, sizeof(linha));
        if (sscanf(linha, "%d/%d/%d %c", &d.dia, &d.mes, &d.ano, &extra) == 3 && data_valida(d))
            return d;
        printf("Data invalida! Use dd/mm/aaaa.\n");
    }
}

int comparar_datas(Data a, Data b)
{
    if (a.ano != b.ano) return a.ano - b.ano;
    if (a.mes != b.mes) return a.mes - b.mes;
    return a.dia - b.dia;
}

void exibir_data(Data d)
{
    if (d.ano == 0) printf("--/--/----");
    else printf("%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

int confirmar(const char *pergunta)
{
    char resposta[8];

    ler_texto(pergunta, resposta, sizeof(resposta));
    return resposta[0] == 's' || resposta[0] == 'S';
}

int cpf_valido(const char *cpf)
{
    int digitos = 0;

    for (; *cpf != '\0'; cpf++) {
        if (isdigit((unsigned char)*cpf)) digitos++;
        else if (*cpf != '.' && *cpf != '-') return 0;
    }
    return digitos == 11;
}

int contem_texto(const char *texto, const char *trecho)
{
    size_t tam_texto = strlen(texto);
    size_t tam_trecho = strlen(trecho);
    size_t i, j;

    for (i = 0; i + tam_trecho <= tam_texto; i++) {
        for (j = 0; j < tam_trecho; j++)
            if (tolower((unsigned char)texto[i + j]) != tolower((unsigned char)trecho[j])) break;
        if (j == tam_trecho) return 1;
    }
    return 0;
}
