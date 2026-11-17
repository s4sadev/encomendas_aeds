#include <stdio.h>
#include "produto.h"
#include "pedido.h"
#include "entregador.h"
#include "cliente.h"
#include "entrega.h"

static int lerOpcao(int *op) {
    int c;
    int lido = scanf("%d", op);

    if (lido == EOF) {
        *op = 0;
        return 1;
    }
    if (lido != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 0;
    }
    return 1;
}

int main(void) {
    int op = -1;

    while (op != 0) {
        printf("\nOla! Por favor, selecione a opcao que deseja:\n");
        printf("[1] Produto\n");
        printf("[2] Pedido\n");
        printf("[3] Entregador\n");
        printf("[4] Cliente\n");
        printf("[5] Entrega\n");
        printf("[0] Encerrar\n");

        if (!lerOpcao(&op)) {
            printf("Entrada invalida.\n");
            op = -1;
            continue;
        }

        if (op == 1) {
            menuProduto();
        } else if (op == 2) {
            menuPedido();
        } else if (op == 3) {
            menuEntregador();
        } else if (op == 4) {
            menuCliente();
        } else if (op == 5) {
            menuEntrega();
        } else if (op != 0) {
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}
