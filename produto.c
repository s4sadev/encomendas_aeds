#include <stdio.h>
#include <string.h>
#include "produto.h"

static Produto produtos[MAX_PRODUTOS];
static int qtdProdutos = 0;

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

static int lerFloat(float *dest) {
    int c;

    if (scanf("%f", dest) != 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 0;
    }
    return 1;
}

static int buscarIndiceProduto(int id) {
    int i;

    for (i = 0; i < qtdProdutos; i++) {
        if (produtos[i].id == id) {
            return i;
        }
    }
    return -1;
}

static int proximoIdProduto(void) {
    int i;
    int maior = 0;

    for (i = 0; i < qtdProdutos; i++) {
        if (produtos[i].id > maior) {
            maior = produtos[i].id;
        }
    }
    return maior + 1;
}

void cadastrarProduto(void) {
    Produto *p;
    float preco;
    int estoque;

    if (qtdProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    char nome[50];

    printf("Nome: ");
    lerTexto(nome, (int)sizeof(nome));

    printf("Preco: ");
    if (!lerFloat(&preco) || preco < 0) {
        printf("Preco invalido.\n");
        return;
    }

    printf("Estoque: ");
    if (!lerInteiro(&estoque) || estoque < 0) {
        printf("Estoque invalido.\n");
        return;
    }

    p = &produtos[qtdProdutos];
    p->id = proximoIdProduto();
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    p->preco = preco;
    p->estoque = estoque;
    qtdProdutos++;
    printf("Produto cadastrado com id %d.\n", p->id);
}

void listarProdutos(void) {
    int i;

    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (i = 0; i < qtdProdutos; i++) {
        printf("ID: %d | Nome: %s | Preco: %.2f | Estoque: %d\n",
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

void atualizarProduto(void) {
    int id;
    int indice;
    float preco;
    int estoque;

    printf("ID do produto: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndiceProduto(id);
    if (indice < 0) {
        printf("Produto nao encontrado.\n");
        return;
    }

    char nome[50];

    printf("Novo nome: ");
    lerTexto(nome, (int)sizeof(nome));

    printf("Novo preco: ");
    if (!lerFloat(&preco) || preco < 0) {
        printf("Preco invalido.\n");
        return;
    }

    printf("Novo estoque: ");
    if (!lerInteiro(&estoque) || estoque < 0) {
        printf("Estoque invalido.\n");
        return;
    }

    strncpy(produtos[indice].nome, nome, sizeof(produtos[indice].nome) - 1);
    produtos[indice].nome[sizeof(produtos[indice].nome) - 1] = '\0';
    produtos[indice].preco = preco;
    produtos[indice].estoque = estoque;
    printf("Produto atualizado.\n");
}

void removerProduto(void) {
    int id;
    int indice;
    int i;

    printf("ID do produto: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndiceProduto(id);
    if (indice < 0) {
        printf("Produto nao encontrado.\n");
        return;
    }

    for (i = indice; i < qtdProdutos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }
    qtdProdutos--;
    printf("Produto removido.\n");
}

int produtoExiste(int id) {
    return buscarIndiceProduto(id) >= 0;
}

int baixarEstoque(int id, int qtd) {
    int indice = buscarIndiceProduto(id);

    if (indice < 0 || qtd <= 0 || produtos[indice].estoque < qtd) {
        return 0;
    }

    produtos[indice].estoque -= qtd;
    return 1;
}

void devolverEstoque(int id, int qtd) {
    int indice = buscarIndiceProduto(id);

    if (indice < 0 || qtd <= 0) {
        return;
    }

    produtos[indice].estoque += qtd;
}

void menuProduto(void) {
    int sub;

    printf("Voce esta no menu de PRODUTOS. Selecione uma opcao:\n");
    printf("[1] Criar produto\n");
    printf("[2] Editar produto\n");
    printf("[3] Remover produto\n");
    printf("[4] Listar produtos\n");
    printf("[5] Voltar\n");
    if (!lerInteiro(&sub)) {
        printf("Entrada invalida.\n");
        return;
    }

    if (sub == 1) {
        cadastrarProduto();
    } else if (sub == 2) {
        atualizarProduto();
    } else if (sub == 3) {
        removerProduto();
    } else if (sub == 4) {
        listarProdutos();
    }
}

void salvarProdutos(void) {
}

void carregarProdutos(void) {
}
