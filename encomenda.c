#include <stdio.h>
#include <string.h>
#include "encomenda.h"
#include "cliente.h"
#include "entregador.h"
#include "utils.h"

static Encomenda encomendas[MAX_ENCOMENDAS];
static int total_encomendas = 0;
static int proximo_id = 1;

void encomenda_carregar(void)
{
    FILE *arquivo = fopen(ARQ_ENCOMENDAS, "rb");
    int quantidade, id_seguinte;

    if (arquivo == NULL) return; /* primeira execucao: ainda nao ha arquivo */

    if (fread(&quantidade, sizeof(int), 1, arquivo) != 1 ||
        fread(&id_seguinte, sizeof(int), 1, arquivo) != 1 ||
        quantidade < 0 || quantidade > MAX_ENCOMENDAS ||
        fread(encomendas, sizeof(Encomenda), (size_t)quantidade, arquivo) != (size_t)quantidade) {
        printf("Aviso: arquivo ARQ_ENCOMENDAS invalido ou incompleto. Dados nao carregados.\n");
        fclose(arquivo);
        return;
    }

    total_encomendas = quantidade;
    proximo_id = id_seguinte > 0 ? id_seguinte : 1;
    fclose(arquivo);
}

int encomenda_salvar(void)
{
    FILE *arquivo = fopen(ARQ_ENCOMENDAS, "wb");
    int sucesso = 1;

    if (arquivo == NULL) {
        printf("Erro ao salvar ARQ_ENCOMENDAS.\n");
        return 0;
    }

    if (fwrite(&total_encomendas, sizeof(int), 1, arquivo) != 1 ||
        fwrite(&proximo_id, sizeof(int), 1, arquivo) != 1 ||
        fwrite(encomendas, sizeof(Encomenda), (size_t)total_encomendas, arquivo) != (size_t)total_encomendas)
        sucesso = 0;

    if (fclose(arquivo) != 0) sucesso = 0;
    if (!sucesso) printf("Erro ao gravar ARQ_ENCOMENDAS.\n");
    return sucesso;
}


static const char *status_para_texto(StatusEncomenda status)
{
    switch (status) {
        case STATUS_REGISTRADA:  return "Registrada";
        case STATUS_EM_TRANSITO: return "Em transito";
        case STATUS_ENTREGUE:    return "Entregue";
        case STATUS_CANCELADA:   return "Cancelada";
    }
    return "Desconhecido";
}

static int esta_finalizada(const Encomenda *e)
{
    return e->status == STATUS_ENTREGUE || e->status == STATUS_CANCELADA;
}

static Encomenda *buscar_por_id(int id)
{
    int i;

    for (i = 0; i < total_encomendas; i++)
        if (encomendas[i].ativo && encomendas[i].id == id) return &encomendas[i];
    return NULL;
}

static Encomenda *pedir_encomenda(void)
{
    Encomenda *e = buscar_por_id(ler_inteiro("ID da encomenda: "));

    if (e == NULL) printf("Encomenda nao encontrada!\n");
    return e;
}

static int pedir_status(StatusEncomenda *status)
{
    int opcao;

    printf("1 - Registrada\n2 - Em transito\n3 - Entregue\n4 - Cancelada\n");
    opcao = ler_inteiro("Status: ");
    if (opcao < STATUS_REGISTRADA || opcao > STATUS_CANCELADA) {
        printf("Status invalido!\n");
        return 0;
    }
    *status = (StatusEncomenda)opcao;
    return 1;
}

static void exibir_encomenda(const Encomenda *e)
{
    const char *entregador = "(nao atribuido)";

    if (e->id_entregador != 0) entregador = entregador_nome_por_id(e->id_entregador);

    printf(" [%d] %s | %.2f kg | frete R$ %.2f | %s\n",
           e->id, e->descricao, e->peso_kg, e->valor_frete, status_para_texto(e->status));
    printf("     Cliente: %s | Entregador: %s\n", cliente_nome_por_id(e->id_cliente), entregador);
    printf("     Destino: %s\n", e->endereco_destino);
    printf("     Postagem: ");
    exibir_data(e->data_postagem);
    printf(" | Entrega: ");
    exibir_data(e->data_entrega);
    printf("\n");
}

static void exibir_total(int qtd)
{
    if (qtd == 0) printf("Nenhuma encomenda encontrada.\n");
    else printf("Total: %d encomenda(s)\n", qtd);
}

void encomenda_registrar(void)
{
    Encomenda nova;

    if (total_encomendas >= MAX_ENCOMENDAS) {
        printf("Limite de encomendas atingido!\n");
        return;
    }

    memset(&nova, 0, sizeof(nova));
    nova.id_cliente = ler_inteiro("ID do cliente: ");
    if (cliente_buscar_por_id(nova.id_cliente) == NULL) {
        printf("Cliente nao encontrado! Registro cancelado.\n");
        return;
    }
    ler_texto_obrigatorio("Descricao: ", nova.descricao, TAM_DESCRICAO);
    ler_texto_obrigatorio("Endereco de destino: ", nova.endereco_destino, TAM_ENDERECO);
    nova.peso_kg = ler_float("Peso (kg): ");
    nova.valor_frete = ler_float("Valor do frete: ");
    nova.data_postagem = ler_data("Data de postagem (dd/mm/aaaa): ");

    nova.id = proximo_id++;
    nova.id_entregador = 0;
    nova.status = STATUS_REGISTRADA;
    nova.ativo = 1;
    encomendas[total_encomendas++] = nova;
    printf("Encomenda registrada! ID: %d\n", nova.id);
}

void encomenda_atribuir_entregador(void)
{
    Encomenda *e = pedir_encomenda();
    int id_entregador;

    if (e == NULL) return;
    if (esta_finalizada(e)) {
        printf("Encomenda ja finalizada (%s)!\n", status_para_texto(e->status));
        return;
    }

    id_entregador = ler_inteiro("ID do entregador: ");
    if (entregador_buscar_por_id(id_entregador) == NULL) {
        printf("Entregador nao encontrado!\n");
        return;
    }
    e->id_entregador = id_entregador;
    printf("Entregador atribuido!\n");
}

void encomenda_atualizar_status(void)
{
    Encomenda *e = pedir_encomenda();
    int opcao;

    if (e == NULL) return;
    if (esta_finalizada(e)) {
        printf("Encomenda ja finalizada (%s)!\n", status_para_texto(e->status));
        return;
    }

    printf("1 - Em transito\n2 - Cancelada\n(para entregue, use Registrar entrega)\n");
    opcao = ler_inteiro("Novo status: ");
    if (opcao == 1) {
        if (e->id_entregador == 0) {
            printf("Atribua um entregador antes de colocar em transito!\n");
            return;
        }
        e->status = STATUS_EM_TRANSITO;
    } else if (opcao == 2) {
        e->status = STATUS_CANCELADA;
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    printf("Status atualizado: %s\n", status_para_texto(e->status));
}

void encomenda_registrar_entrega(void)
{
    Encomenda *e = pedir_encomenda();
    Data data;

    if (e == NULL) return;
    if (e->status != STATUS_EM_TRANSITO) {
        printf("So e possivel entregar uma encomenda em transito!\n");
        return;
    }

    data = ler_data("Data da entrega (dd/mm/aaaa): ");
    if (comparar_datas(data, e->data_postagem) < 0) {
        printf("A entrega nao pode ser antes da postagem!\n");
        return;
    }
    e->data_entrega = data;
    e->status = STATUS_ENTREGUE;
    printf("Entrega registrada!\n");
}

void encomenda_buscar(void)
{
    Encomenda *e = pedir_encomenda();

    if (e != NULL) exibir_encomenda(e);
}

void encomenda_listar(void)
{
    int i, qtd = 0;

    for (i = 0; i < total_encomendas; i++) {
        if (encomendas[i].ativo) {
            exibir_encomenda(&encomendas[i]);
            qtd++;
        }
    }
    exibir_total(qtd);
}

void encomenda_relatorio_por_cliente(void)
{
    int id, i, qtd = 0;

    id = ler_inteiro("ID do cliente: ");
    if (cliente_buscar_por_id(id) == NULL) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("Encomendas de %s:\n", cliente_nome_por_id(id));
    for (i = 0; i < total_encomendas; i++) {
        if (encomendas[i].ativo && encomendas[i].id_cliente == id) {
            exibir_encomenda(&encomendas[i]);
            qtd++;
        }
    }
    exibir_total(qtd);
}

void encomenda_relatorio_por_entregador(void)
{
    int id, i, qtd = 0;

    id = ler_inteiro("ID do entregador: ");
    if (entregador_buscar_por_id(id) == NULL) {
        printf("Entregador nao encontrado!\n");
        return;
    }

    printf("Encomendas de %s:\n", entregador_nome_por_id(id));
    for (i = 0; i < total_encomendas; i++) {
        if (encomendas[i].ativo && encomendas[i].id_entregador == id) {
            exibir_encomenda(&encomendas[i]);
            qtd++;
        }
    }
    exibir_total(qtd);
}

void encomenda_relatorio_por_status(void)
{
    StatusEncomenda status;
    int i, qtd = 0;

    if (!pedir_status(&status)) return;

    printf("Encomendas com status %s:\n", status_para_texto(status));
    for (i = 0; i < total_encomendas; i++) {
        if (encomendas[i].ativo && encomendas[i].status == status) {
            exibir_encomenda(&encomendas[i]);
            qtd++;
        }
    }
    exibir_total(qtd);
}

int encomenda_cliente_em_andamento(int id_cliente)
{
    int i;

    for (i = 0; i < total_encomendas; i++)
        if (encomendas[i].ativo && encomendas[i].id_cliente == id_cliente &&
            !esta_finalizada(&encomendas[i]))
            return 1;
    return 0;
}

int encomenda_entregador_em_andamento(int id_entregador)
{
    int i;

    for (i = 0; i < total_encomendas; i++)
        if (encomendas[i].ativo && encomendas[i].id_entregador == id_entregador &&
            !esta_finalizada(&encomendas[i]))
            return 1;
    return 0;
}
