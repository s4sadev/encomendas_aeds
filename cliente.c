#include <stdio.h>
#include <string.h>
#include "cliente.h"
#include "encomenda.h"
#include "utils.h"

static Cliente clientes[MAX_CLIENTES];
static int total_clientes = 0;
static int proximo_id = 1;

void cliente_carregar(void)
{
    FILE *arquivo = fopen(ARQ_CLIENTES, "rb");
    int quantidade, id_seguinte;

    if (arquivo == NULL) return; /* primeira execucao: ainda nao ha arquivo */

    if (fread(&quantidade, sizeof(int), 1, arquivo) != 1 ||
        fread(&id_seguinte, sizeof(int), 1, arquivo) != 1 ||
        quantidade < 0 || quantidade > MAX_CLIENTES ||
        fread(clientes, sizeof(Cliente), (size_t)quantidade, arquivo) != (size_t)quantidade) {
        printf("Aviso: arquivo ARQ_CLIENTES invalido ou incompleto. Dados nao carregados.\n");
        fclose(arquivo);
        return;
    }

    total_clientes = quantidade;
    proximo_id = id_seguinte > 0 ? id_seguinte : 1;
    fclose(arquivo);
}

int cliente_salvar(void)
{
    FILE *arquivo = fopen(ARQ_CLIENTES, "wb");
    int sucesso = 1;

    if (arquivo == NULL) {
        printf("Erro ao salvar ARQ_CLIENTES.\n");
        return 0;
    }

    if (fwrite(&total_clientes, sizeof(int), 1, arquivo) != 1 ||
        fwrite(&proximo_id, sizeof(int), 1, arquivo) != 1 ||
        fwrite(clientes, sizeof(Cliente), (size_t)total_clientes, arquivo) != (size_t)total_clientes)
        sucesso = 0;

    if (fclose(arquivo) != 0) sucesso = 0;
    if (!sucesso) printf("Erro ao gravar ARQ_CLIENTES.\n");
    return sucesso;
}


Cliente *cliente_buscar_por_id(int id)
{
    int i;

    for (i = 0; i < total_clientes; i++)
        if (clientes[i].ativo && clientes[i].id == id) return &clientes[i];
    return NULL;
}

const char *cliente_nome_por_id(int id)
{
    int i;

    for (i = 0; i < total_clientes; i++)
        if (clientes[i].id == id) return clientes[i].nome;
    return "?";
}

static int cpf_ja_cadastrado(const char *cpf)
{
    int i;

    for (i = 0; i < total_clientes; i++)
        if (clientes[i].ativo && strcmp(clientes[i].cpf, cpf) == 0) return 1;
    return 0;
}

static Cliente *pedir_cliente(void)
{
    Cliente *c = cliente_buscar_por_id(ler_inteiro("ID do cliente: "));

    if (c == NULL) printf("Cliente nao encontrado!\n");
    return c;
}

static void exibir_cliente(const Cliente *c)
{
    printf(" [%d] %s | CPF: %s | Tel: %s\n", c->id, c->nome, c->cpf, c->telefone);
    printf("     Endereco: %s\n", c->endereco);
}

void cliente_cadastrar(void)
{
    Cliente novo;

    if (total_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
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
    ler_texto_obrigatorio("Endereco: ", novo.endereco, TAM_ENDERECO);

    novo.id = proximo_id++;
    novo.ativo = 1;
    clientes[total_clientes++] = novo;
    printf("Cliente cadastrado! ID: %d\n", novo.id);
}

void cliente_listar(void)
{
    int i, qtd = 0;

    for (i = 0; i < total_clientes; i++) {
        if (clientes[i].ativo) {
            exibir_cliente(&clientes[i]);
            qtd++;
        }
    }
    if (qtd == 0) printf("Nenhum cliente cadastrado.\n");
}

void cliente_buscar(void)
{
    char termo[TAM_NOME];
    int i, qtd = 0;

    ler_texto_obrigatorio("Buscar (parte do nome ou CPF): ", termo, TAM_NOME);
    for (i = 0; i < total_clientes; i++) {
        if (clientes[i].ativo &&
            (contem_texto(clientes[i].nome, termo) || contem_texto(clientes[i].cpf, termo))) {
            exibir_cliente(&clientes[i]);
            qtd++;
        }
    }
    if (qtd == 0) printf("Nenhum cliente encontrado.\n");
}

void cliente_atualizar(void)
{
    Cliente *c = pedir_cliente();

    if (c == NULL) return;

    printf("Enter mantem o valor atual (CPF nao pode ser alterado).\n");
    atualizar_texto("Nome", c->nome, TAM_NOME);
    atualizar_texto("Telefone", c->telefone, TAM_TELEFONE);
    atualizar_texto("Endereco", c->endereco, TAM_ENDERECO);
    printf("Cliente atualizado!\n");
}

void cliente_remover(void)
{
    Cliente *c = pedir_cliente();

    if (c == NULL) return;

    if (encomenda_cliente_em_andamento(c->id)) {
        printf("Cliente possui encomendas em andamento! Remocao cancelada.\n");
        return;
    }
    if (!confirmar("Confirmar remocao (s/n)? ")) {
        printf("Remocao cancelada.\n");
        return;
    }
    c->ativo = 0;
    printf("Cliente removido!\n");
}
