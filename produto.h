#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 100
#define ARQ_PRODUTOS "produtos.dat"

typedef struct {
    int id;
    char nome[50];
    float preco;
    int estoque;
} Produto;

void cadastrarProduto(void);
void listarProdutos(void);
void atualizarProduto(void);
void removerProduto(void);
int  produtoExiste(int id);              // usada por pedido.c 
int  baixarEstoque(int id, int qtd);     // 1 = ok, 0 = estoque insuficiente 
void devolverEstoque(int id, int qtd);   // usada ao cancelar pedido 
void salvarProdutos(void);
void carregarProdutos(void);
void menuProduto(void);

#endif
