#ifndef ENTREGA_H
#define ENTREGA_H

#define MAX_ENTREGAS 500
#define ARQ_ENTREGAS "entregas.dat"

typedef struct {
    int id;
    int idPedido;       // referencia a Pedido 
    int idEntregador;   // referencia a Entregador
    int status;         // 0 = pendente, 1 = entregue
} Entrega;

void cadastrarEntrega(void);
void listarEntregas(void);
void marcarEntregue(void);
void salvarEntregas(void);
void carregarEntregas(void);
void menuEntrega(void);

#endif
