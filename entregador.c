#include <stdio.h>
#include <string.h>
#include "entregador.h"
#include "encomenda.h"
#include "utils.h"

static Entregador entregadores[MAX_ENTREGADORES];
static int total_entregadores = 0;
static int proximo_id = 1;

void entregador_carregar(void)
{
    FILE *arquivo = fopen(ARQ_ENTREGADORES, "rb");
    int quantidade, id_seguinte;

    if (arquivo == NULL) return; /* primeira execucao: ainda nao ha arquivo */

    if (fread(&quantidade, sizeof(int), 1, arquivo) != 1 ||
        fread(&id_seguinte, sizeof(int), 1, arquivo) != 1 ||
        quantidade < 0 || quantidade > MAX_ENTREGADORES ||
        fread(entregadores, sizeof(Entregador), (size_t)quantidade, arquivo) != (size_t)quantidade) {
        printf("Aviso: arquivo ARQ_ENTREGADORES invalido ou incompleto. Dados nao carregados.\n");
        fclose(arquivo);
        return;
    }

    total_entregadores = quantidade;
    proximo_id = id_seguinte > 0 ? id_seguinte : 1;
    fclose(arquivo);
}

int entregador_salvar(void)
{
    FILE *arquivo = fopen(ARQ_ENTREGADORES, "wb");
    int sucesso = 1;

    if (arquivo == NULL) {
        printf("Erro ao salvar ARQ_ENTREGADORES.\n");
        return 0;
    }

    if (fwrite(&total_entregadores, sizeof(int), 1, arquivo) != 1 ||
        fwrite(&proximo_id, sizeof(int), 1, arquivo) != 1 ||
        fwrite(entregadores, sizeof(Entregador), (size_t)total_entregadores, arquivo) != (size_t)total_entregadores)
        sucesso = 0;

    if (fclose(arquivo) != 0) sucesso = 0;
    if (!sucesso) printf("Erro ao gravar ARQ_ENTREGADORES.\n");
    return sucesso;
}


Entregador *entregador_buscar_por_id(int id)
{
    int i;

    for (i = 0; i < total_entregadores; i++)
        if (entregadores[i].ativo && entregadores[i].id == id) return &entregadores[i];
    return NULL;
}

const char *entregador_nome_por_id(int id)
{
    int i;

    for (i = 0; i < total_entregadores; i++)
        if (entregadores[i].id == id) return entregadores[i].nome;
    return "?";
}

static int cpf_ja_cadastrado(const char *cpf)
{
    int i;

    for (i = 0; i < total_entregadores; i++)
        if (entregadores[i].ativo && strcmp(entregadores[i].cpf, cpf) == 0) return 1;
    return 0;
}

static Entregador *pedir_entregador(void)
{
    Entregador *e = entregador_buscar_por_id(ler_inteiro("ID do entregador: "));

    if (e == NULL) printf("Entregador nao encontrado!\n");
    return e;
}

static void exibir_entregador(const Entregador *e)
{
    printf(" [%d] %s | CPF: %s | Tel: %s | Placa: %s\n",
           e->id, e->nome, e->cpf, e->telefone, e->placa_veiculo);
}

void entregador_cadastrar(void)
{
    Entregador novo;

    if (total_entregadores >= MAX_ENTREGADORES) {
        printf("Limite de entregadores atingido!\n");
        return;
    }

    memset(&novo, 0, sizeof(novo));
    ler_texto_obrigatorio("Nome: ", novo.nome, TAM_NOME);
    ler_texto_obrigatorio("CPF: ", novo.cpf, TAM_CPF);
    if (!cpf_valido(novo.cpf)) {
        printf("CPF invalido! Cadastro cancelado.\n");
        return;
    }
    if (cpf_ja_cadastrado(novo.cpf)) {
        printf("CPF ja cadastrado! Cadastro cancelado.\n");
        return;
    }
    ler_texto_obrigatorio("Telefone: ", novo.telefone, TAM_TELEFONE);
    ler_texto_obrigatorio("Placa do veiculo: ", novo.placa_veiculo, TAM_PLACA);

    novo.id = proximo_id++;
    novo.ativo = 1;
    entregadores[total_entregadores++] = novo;
    printf("Entregador cadastrado! ID: %d\n", novo.id);
}

void entregador_listar(void)
{
    int i, qtd = 0;

    for (i = 0; i < total_entregadores; i++) {
        if (entregadores[i].ativo) {
            exibir_entregador(&entregadores[i]);
            qtd++;
        }
    }
    if (qtd == 0) printf("Nenhum entregador cadastrado.\n");
}

void entregador_buscar(void)
{
    char termo[TAM_NOME];
    int i, qtd = 0;

    ler_texto_obrigatorio("Buscar (parte do nome, CPF ou placa): ", termo, TAM_NOME);
    for (i = 0; i < total_entregadores; i++) {
        if (entregadores[i].ativo &&
            (contem_texto(entregadores[i].nome, termo) ||
             contem_texto(entregadores[i].cpf, termo) ||
             contem_texto(entregadores[i].placa_veiculo, termo))) {
            exibir_entregador(&entregadores[i]);
            qtd++;
        }
    }
    if (qtd == 0) printf("Nenhum entregador encontrado.\n");
}

void entregador_atualizar(void)
{
    Entregador *e = pedir_entregador();

    if (e == NULL) return;

    printf("Enter mantem o valor atual (CPF nao pode ser alterado).\n");
    atualizar_texto("Nome", e->nome, TAM_NOME);
    atualizar_texto("Telefone", e->telefone, TAM_TELEFONE);
    atualizar_texto("Placa", e->placa_veiculo, TAM_PLACA);
    printf("Entregador atualizado!\n");
}

void entregador_remover(void)
{
    Entregador *e = pedir_entregador();

    if (e == NULL) return;

    if (encomenda_entregador_em_andamento(e->id)) {
        printf("Entregador possui encomendas em andamento! Remocao cancelada.\n");
        return;
    }
    if (!confirmar("Confirmar remocao (s/n)? ")) {
        printf("Remocao cancelada.\n");
        return;
    }
    e->ativo = 0;
    printf("Entregador removido!\n");
}
