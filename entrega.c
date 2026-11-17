#include <stdio.h>
#include "entrega.h"
#include "pedido.h"
#include "entregador.h"

static Entrega entregas[MAX_ENTREGAS];
static int qtdEntregas = 0;

static int lerInteiro(int *dest) {
    int c;

    if (scanf("%d", dest) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 0;
    }
    return 1;
}

static int buscarIndiceEntrega(int id) {
    int i;

    for (i = 0; i < qtdEntregas; i++) {
        if (entregas[i].id == id) {
            return i;
        }
    }
    return -1;
}

static int proximoIdEntrega(void) {
    int i;
    int maior = 0;

    for (i = 0; i < qtdEntregas; i++) {
        if (entregas[i].id > maior) {
            maior = entregas[i].id;
        }
    }
    return maior + 1;
}

void cadastrarEntrega(void) {
    int idPedido;
    int idEntregador;
    Entrega *e;

    if (qtdEntregas >= MAX_ENTREGAS) {
        printf("Limite de entregas atingido.\n");
        return;
    }

    printf("ID do pedido: ");
    if (!lerInteiro(&idPedido)) {
        printf("Entrada invalida.\n");
        return;
    }
    if (!pedidoExiste(idPedido)) {
        printf("Pedido nao encontrado.\n");
        return;
    }

    printf("ID do entregador: ");
    if (!lerInteiro(&idEntregador)) {
        printf("Entrada invalida.\n");
        return;
    }
    if (!entregadorExiste(idEntregador)) {
        printf("Entregador nao encontrado.\n");
        return;
    }

    e = &entregas[qtdEntregas];
    e->id = proximoIdEntrega();
    e->idPedido = idPedido;
    e->idEntregador = idEntregador;
    e->status = 0;
    qtdEntregas++;
    printf("Entrega cadastrada com id %d (pendente).\n", e->id);
}

void listarEntregas(void) {
    int i;

    if (qtdEntregas == 0) {
        printf("Nenhuma entrega cadastrada.\n");
        return;
    }

    for (i = 0; i < qtdEntregas; i++) {
        printf("ID: %d | Pedido: %d | Entregador: %d | Status: %s\n",
               entregas[i].id, entregas[i].idPedido, entregas[i].idEntregador,
               entregas[i].status == 1 ? "Entregue" : "Pendente");
    }
}

void marcarEntregue(void) {
    int id;
    int indice;

    printf("ID da entrega: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndiceEntrega(id);
    if (indice < 0) {
        printf("Entrega nao encontrada.\n");
        return;
    }

    entregas[indice].status = 1;
    printf("Entrega marcada como entregue.\n");
}

void menuEntrega(void) {
    int sub;

    printf("Voce esta no menu de ENTREGAS. Selecione uma opcao:\n");
    printf("[1] Criar entrega\n");
    printf("[2] Marcar como entregue\n");
    printf("[3] Listar entregas\n");
    printf("[4] Voltar\n");
    if (!lerInteiro(&sub)) {
        printf("Entrada invalida.\n");
        return;
    }

    if (sub == 1) {
        cadastrarEntrega();
    } else if (sub == 2) {
        marcarEntregue();
    } else if (sub == 3) {
        listarEntregas();
    }
}

void salvarEntregas(void) {
}

void carregarEntregas(void) {
}
