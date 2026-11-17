#include <stdio.h>
#include <string.h>
#include "cliente.h"

static Cliente clientes[MAX_CLIENTES];
static int qtdClientes = 0;

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

static int buscarIndiceCliente(int id) {
    int i;

    for (i = 0; i < qtdClientes; i++) {
        if (clientes[i].id == id) {
            return i;
        }
    }
    return -1;
}

static int proximoIdCliente(void) {
    int i;
    int maior = 0;

    for (i = 0; i < qtdClientes; i++) {
        if (clientes[i].id > maior) {
            maior = clientes[i].id;
        }
    }
    return maior + 1;
}

void cadastrarCliente(void) {
    Cliente *c;

    if (qtdClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    c = &clientes[qtdClientes];
    c->id = proximoIdCliente();
    printf("Nome: ");
    lerTexto(c->nome, (int)sizeof(c->nome));
    printf("Telefone: ");
    lerTexto(c->telefone, (int)sizeof(c->telefone));
    qtdClientes++;
    printf("Cliente cadastrado com id %d.\n", c->id);
}

void listarClientes(void) {
    int i;

    if (qtdClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for (i = 0; i < qtdClientes; i++) {
        printf("ID: %d | Nome: %s | Telefone: %s\n",
               clientes[i].id, clientes[i].nome, clientes[i].telefone);
    }
}

void atualizarCliente(void) {
    int id;
    int indice;

    printf("ID do cliente: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndiceCliente(id);
    if (indice < 0) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Novo nome: ");
    lerTexto(clientes[indice].nome, (int)sizeof(clientes[indice].nome));
    printf("Novo telefone: ");
    lerTexto(clientes[indice].telefone, (int)sizeof(clientes[indice].telefone));
    printf("Cliente atualizado.\n");
}

void removerCliente(void) {
    int id;
    int indice;
    int i;

    printf("ID do cliente: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndiceCliente(id);
    if (indice < 0) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    for (i = indice; i < qtdClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    qtdClientes--;
    printf("Cliente removido.\n");
}

int clienteExiste(int id) {
    return buscarIndiceCliente(id) >= 0;
}

void menuCliente(void) {
    int sub;

    printf("Voce esta no menu de CLIENTES. Selecione uma opcao:\n");
    printf("[1] Criar cliente\n");
    printf("[2] Editar cliente\n");
    printf("[3] Remover cliente\n");
    printf("[4] Listar clientes\n");
    printf("[5] Voltar\n");
    if (!lerInteiro(&sub)) {
        printf("Entrada invalida.\n");
        return;
    }

    if (sub == 1) {
        cadastrarCliente();
    } else if (sub == 2) {
        atualizarCliente();
    } else if (sub == 3) {
        removerCliente();
    } else if (sub == 4) {
        listarClientes();
    }
}

void salvarClientes(void) {
}

void carregarClientes(void) {
}
