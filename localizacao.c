#include <stdio.h>
#include <string.h>
#include "localizacao.h"
#include "utils.h"

static Localizacao localizacoes[MAX_LOCALIZACOES];
static int total_localizacoes = 0;
static int proximo_id = 1;

void localizacao_carregar(void)
{
    FILE *arquivo = fopen(ARQ_LOCALIZACOES, "rb");
    int quantidade, id_seguinte;

    if (arquivo == NULL) return; /* primeira execucao: ainda nao ha arquivo */

    if (fread(&quantidade, sizeof(int), 1, arquivo) != 1 ||
        fread(&id_seguinte, sizeof(int), 1, arquivo) != 1 ||
        quantidade < 0 || quantidade > MAX_LOCALIZACOES ||
        fread(localizacoes, sizeof(Localizacao), (size_t)quantidade, arquivo) != (size_t)quantidade) {
        printf("Aviso: arquivo ARQ_LOCALIZACOES invalido ou incompleto. Dados nao carregados.\n");
        fclose(arquivo);
        return;
    }

    total_localizacoes = quantidade;
    proximo_id = id_seguinte > 0 ? id_seguinte : 1;
    fclose(arquivo);
}

int localizacao_salvar(void)
{
    FILE *arquivo = fopen(ARQ_LOCALIZACOES, "wb");
    int sucesso = 1;

    if (arquivo == NULL) {
        printf("Erro ao salvar ARQ_LOCALIZACOES.\n");
        return 0;
    }

    if (fwrite(&total_localizacoes, sizeof(int), 1, arquivo) != 1 ||
        fwrite(&proximo_id, sizeof(int), 1, arquivo) != 1 ||
        fwrite(localizacoes, sizeof(Localizacao), (size_t)total_localizacoes, arquivo) != (size_t)total_localizacoes)
        sucesso = 0;

    if (fclose(arquivo) != 0) sucesso = 0;
    if (!sucesso) printf("Erro ao gravar ARQ_LOCALIZACOES.\n");
    return sucesso;
}


static Localizacao *buscar_por_id(int id)
{
    int i;

    for (i = 0; i < total_localizacoes; i++)
        if (localizacoes[i].ativo && localizacoes[i].id == id) return &localizacoes[i];
    return NULL;
}

static Localizacao *pedir_localizacao(void)
{
    Localizacao *l = buscar_por_id(ler_inteiro("ID da localizacao: "));

    if (l == NULL) printf("Localizacao nao encontrada!\n");
    return l;
}

static void exibir_localizacao(const Localizacao *l)
{
    printf(" [%d] %s | %s\n", l->id, l->nome, l->endereco);
}

void localizacao_cadastrar(void)
{
    Localizacao nova;

    if (total_localizacoes >= MAX_LOCALIZACOES) {
        printf("Limite de localizacoes atingido!\n");
        return;
    }

    memset(&nova, 0, sizeof(nova));
    ler_texto_obrigatorio("Nome: ", nova.nome, TAM_NOME);
    ler_texto_obrigatorio("Endereco: ", nova.endereco, TAM_ENDERECO);

    nova.id = proximo_id++;
    nova.ativo = 1;
    localizacoes[total_localizacoes++] = nova;
    printf("Localizacao cadastrada! ID: %d\n", nova.id);
}

void localizacao_listar(void)
{
    int i, qtd = 0;

    for (i = 0; i < total_localizacoes; i++) {
        if (localizacoes[i].ativo) {
            exibir_localizacao(&localizacoes[i]);
            qtd++;
        }
    }
    if (qtd == 0) printf("Nenhuma localizacao cadastrada.\n");
}

void localizacao_buscar(void)
{
    char termo[TAM_NOME];
    int i, qtd = 0;

    ler_texto_obrigatorio("Buscar (parte do nome ou endereco): ", termo, TAM_NOME);
    for (i = 0; i < total_localizacoes; i++) {
        if (localizacoes[i].ativo &&
            (contem_texto(localizacoes[i].nome, termo) ||
             contem_texto(localizacoes[i].endereco, termo))) {
            exibir_localizacao(&localizacoes[i]);
            qtd++;
        }
    }
    if (qtd == 0) printf("Nenhuma localizacao encontrada.\n");
}

void localizacao_atualizar(void)
{
    Localizacao *l = pedir_localizacao();

    if (l == NULL) return;

    printf("Enter mantem o valor atual.\n");
    atualizar_texto("Nome", l->nome, TAM_NOME);
    atualizar_texto("Endereco", l->endereco, TAM_ENDERECO);
    printf("Localizacao atualizada!\n");
}

void localizacao_remover(void)
{
    Localizacao *l = pedir_localizacao();

    if (l == NULL) return;

    if (!confirmar("Confirmar remocao (s/n)? ")) {
        printf("Remocao cancelada.\n");
        return;
    }
    l->ativo = 0;
    printf("Localizacao removida!\n");
}
