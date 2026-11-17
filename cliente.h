#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_CLIENTES 100
#define ARQ_CLIENTES "clientes.dat"

typedef struct {
    int id;
    char nome[50];
    char telefone[20];
} Cliente;

void cadastrarCliente(void);
void listarClientes(void);
void atualizarCliente(void);
void removerCliente(void);
int  clienteExiste(int id);      // usada por pedido.c
void salvarClientes(void);
void carregarClientes(void);
void menuCliente(void);

#endif
