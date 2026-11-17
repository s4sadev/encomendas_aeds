#ifndef ENTREGADOR_H
#define ENTREGADOR_H

#define MAX_ENTREGADORES 50
#define ARQ_ENTREGADORES "entregadores.dat"

typedef struct {
    int id;
    char nome[50];
    char telefone[20];
} Entregador;

void cadastrarEntregador(void);
void listarEntregadores(void);
void atualizarEntregador(void);
void removerEntregador(void);
int  entregadorExiste(int id);   // usada por entrega.c
void salvarEntregadores(void);
void carregarEntregadores(void);
void menuEntregador(void);

#endif
