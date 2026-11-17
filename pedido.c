#include <stdio.h>
#include <string.h>
#include "pedido.h"
#include "cliente.h"
#include "produto.h"

static Pedido pedidos[MAX_PEDIDOS];
static int qtdPedidos = 0;

static void lerTexto(char *dest, int tam) {
    int c;
    size_t n;

    if (fgets(dest, tam, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    if (dest[0] == '\n') {
        if (fgets(dest, tam, stdin) == NULL) {
            dest[0] = '\0';
            return;
        }
    }
    n = strlen(dest);
    if (n > 0 && dest[n - 1] == '\n') {
        dest[n - 1] = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

static int lerInteiro(int *dest) {
    int c;

    if (scanf("%d", dest) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 0;
    }
    return 1;
}

static int buscarIndicePedido(int id) {
    int i;

    for (i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id == id) {
            return i;
        }
    }
    return -1;
}

static int proximoIdPedido(void) {
    int i;
    int maior = 0;

    for (i = 0; i < qtdPedidos; i++) {
        if (pedidos[i].id > maior) {
            maior = pedidos[i].id;
        }
    }
    return maior + 1;
}

void cadastrarPedido(void) {
    int idCliente;
    int idProduto;
    int quantidade;
    Pedido *p;

    if (qtdPedidos >= MAX_PEDIDOS) {
        printf("Limite de pedidos atingido.\n");
        return;
    }

    printf("ID do cliente: ");
    if (!lerInteiro(&idCliente)) {
        printf("Entrada invalida.\n");
        return;
    }
    if (!clienteExiste(idCliente)) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("ID do produto: ");
    if (!lerInteiro(&idProduto)) {
        printf("Entrada invalida.\n");
        return;
    }
    if (!produtoExiste(idProduto)) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Quantidade: ");
    if (!lerInteiro(&quantidade) || quantidade <= 0) {
        printf("Quantidade invalida.\n");
        return;
    }

    if (!baixarEstoque(idProduto, quantidade)) {
        printf("Estoque insuficiente.\n");
        return;
    }

    p = &pedidos[qtdPedidos];
    p->id = proximoIdPedido();
    p->idCliente = idCliente;
    p->idProduto = idProduto;
    p->quantidade = quantidade;
    printf("Data (dd/mm/aaaa): ");
    lerTexto(p->data, (int)sizeof(p->data));
    qtdPedidos++;
    printf("Pedido cadastrado com id %d.\n", p->id);
}

void listarPedidos(void) {
    int i;

    if (qtdPedidos == 0) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    for (i = 0; i < qtdPedidos; i++) {
        printf("ID: %d | Cliente: %d | Produto: %d | Quantidade: %d | Data: %s\n",
               pedidos[i].id, pedidos[i].idCliente, pedidos[i].idProduto,
               pedidos[i].quantidade, pedidos[i].data);
    }
}

void cancelarPedido(void) {
    int id;
    int indice;
    int i;

    printf("ID do pedido: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndicePedido(id);
    if (indice < 0) {
        printf("Pedido nao encontrado.\n");
        return;
    }

    devolverEstoque(pedidos[indice].idProduto, pedidos[indice].quantidade);
    for (i = indice; i < qtdPedidos - 1; i++) {
        pedidos[i] = pedidos[i + 1];
    }
    qtdPedidos--;
    printf("Pedido cancelado.\n");
}

int pedidoExiste(int id) {
    return buscarIndicePedido(id) >= 0;
}

void menuPedido(void) {
    int sub;

    printf("Voce esta no menu de PEDIDOS. Selecione uma opcao:\n");
    printf("[1] Criar pedido\n");
    printf("[2] Cancelar pedido\n");
    printf("[3] Listar pedidos\n");
    printf("[4] Voltar\n");
    if (!lerInteiro(&sub)) {
        printf("Entrada invalida.\n");
        return;
    }

    if (sub == 1) {
        cadastrarPedido();
    } else if (sub == 2) {
        cancelarPedido();
    } else if (sub == 3) {
        listarPedidos();
    }
}

void salvarPedidos(void) {
}

void carregarPedidos(void) {
}
