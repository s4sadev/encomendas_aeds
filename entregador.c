#include <stdio.h>
#include <string.h>
#include "entregador.h"

static Entregador entregadores[MAX_ENTREGADORES];
static int qtdEntregadores = 0;

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

static int buscarIndiceEntregador(int id) {
    int i;

    for (i = 0; i < qtdEntregadores; i++) {
        if (entregadores[i].id == id) {
            return i;
        }
    }
    return -1;
}

static int proximoIdEntregador(void) {
    int i;
    int maior = 0;

    for (i = 0; i < qtdEntregadores; i++) {
        if (entregadores[i].id > maior) {
            maior = entregadores[i].id;
        }
    }
    return maior + 1;
}

void cadastrarEntregador(void) {
    Entregador *e;

    if (qtdEntregadores >= MAX_ENTREGADORES) {
        printf("Limite de entregadores atingido.\n");
        return;
    }

    e = &entregadores[qtdEntregadores];
    e->id = proximoIdEntregador();
    printf("Nome: ");
    lerTexto(e->nome, (int)sizeof(e->nome));
    printf("Telefone: ");
    lerTexto(e->telefone, (int)sizeof(e->telefone));
    qtdEntregadores++;
    printf("Entregador cadastrado com id %d.\n", e->id);
}

void listarEntregadores(void) {
    int i;

    if (qtdEntregadores == 0) {
        printf("Nenhum entregador cadastrado.\n");
        return;
    }

    for (i = 0; i < qtdEntregadores; i++) {
        printf("ID: %d | Nome: %s | Telefone: %s\n",
               entregadores[i].id, entregadores[i].nome, entregadores[i].telefone);
    }
}

void atualizarEntregador(void) {
    int id;
    int indice;

    printf("ID do entregador: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndiceEntregador(id);
    if (indice < 0) {
        printf("Entregador nao encontrado.\n");
        return;
    }

    printf("Novo nome: ");
    lerTexto(entregadores[indice].nome, (int)sizeof(entregadores[indice].nome));
    printf("Novo telefone: ");
    lerTexto(entregadores[indice].telefone, (int)sizeof(entregadores[indice].telefone));
    printf("Entregador atualizado.\n");
}

void removerEntregador(void) {
    int id;
    int indice;
    int i;

    printf("ID do entregador: ");
    if (!lerInteiro(&id)) {
        printf("Entrada invalida.\n");
        return;
    }

    indice = buscarIndiceEntregador(id);
    if (indice < 0) {
        printf("Entregador nao encontrado.\n");
        return;
    }

    for (i = indice; i < qtdEntregadores - 1; i++) {
        entregadores[i] = entregadores[i + 1];
    }
    qtdEntregadores--;
    printf("Entregador removido.\n");
}

int entregadorExiste(int id) {
    return buscarIndiceEntregador(id) >= 0;
}

void menuEntregador(void) {
    int sub;

    printf("Voce esta no menu de ENTREGADORES. Selecione uma opcao:\n");
    printf("[1] Criar entregador\n");
    printf("[2] Editar entregador\n");
    printf("[3] Remover entregador\n");
    printf("[4] Listar entregadores\n");
    printf("[5] Voltar\n");
    if (!lerInteiro(&sub)) {
        printf("Entrada invalida.\n");
        return;
    }

    if (sub == 1) {
        cadastrarEntregador();
    } else if (sub == 2) {
        atualizarEntregador();
    } else if (sub == 3) {
        removerEntregador();
    } else if (sub == 4) {
        listarEntregadores();
    }
}

void salvarEntregadores(void) {
}

void carregarEntregadores(void) {
}
