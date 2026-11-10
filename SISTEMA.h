#ifndef SISTEMA_H //sarah
#define SISTEMA_H

// 
#define TAM_NOME 50
#define TAM_CPF 15
#define TAM_CNH 15
#define TAM_DATA 11
#define TAM_ENDERECO 100


// CADASTROS BASICOS

typedef struct {
    int idCliente;        
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
} Cliente;

typedef struct {
    int idProduto;              
    char nome[TAM_NOME];
    float preco;
} Produto;

typedef struct {
    int idEntregador;           
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char cnh[TAM_CNH];
} Entregador;

// OPERAÇÕES

typedef struct {
    int idPedido;               
    int idCliente;              
    char data[TAM_DATA];         
    float valorTotal;
    int status;                 // ???? 1=Pendente, 2=Em Processamento, 3=Concluído, 4=Cancelado 
} Pedido;

typedef struct {
    int idPedido;               // vincula pedido
    int idProduto;              // vincula produto
    int quantidade;
    float precoUnitario;
    float precoTotal;
} ItemPedido;

typedef struct {
    int idEntrega;              
    int idPedido;               // vincula pedido
    int idEntregador;           // vincula entregador
    char endereco[TAM_ENDERECO];
    int status;                 // ??? 1=Em Separação, 2=Em Trânsito, 3=Entregue
} Entrega;

#endif 

