#ifndef PEDIDO_H
#define PEDIDO_H

#define MAX_PEDIDOS 500
#define ARQ_PEDIDOS "pedidos.dat"

typedef struct {
    int id;
    int idCliente;      // referencia a Cliente 
    int idProduto;      // referencia a Produto 
    int quantidade;
    char data[11];      // dd/mm/aaaa 
} Pedido;

void cadastrarPedido(void);
void listarPedidos(void);
void cancelarPedido(void);
int  pedidoExiste(int id);       // usada por entrega.c
void salvarPedidos(void);
void carregarPedidos(void);
void menuPedido(void);

#endif
