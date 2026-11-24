#ifndef TIPOS_H
#define TIPOS_H

#define TAM_NOME       75
#define TAM_CPF        15
#define TAM_TELEFONE   16
#define TAM_ENDERECO   100
#define TAM_DESCRICAO  80
#define TAM_PLACA      10

#define MAX_CLIENTES      100
#define MAX_ENTREGADORES   50
#define MAX_LOCALIZACOES   50
#define MAX_ENCOMENDAS    200

#define ARQ_CLIENTES      "clientes.dat"
#define ARQ_ENTREGADORES  "entregadores.dat"
#define ARQ_LOCALIZACOES  "localizacoes.dat"
#define ARQ_ENCOMENDAS    "encomendas.dat"

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef enum {
    STATUS_REGISTRADA = 1,
    STATUS_EM_TRANSITO,
    STATUS_ENTREGUE,
    STATUS_CANCELADA
} StatusEncomenda;

typedef struct {
    int  id;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char telefone[TAM_TELEFONE];
    char endereco[TAM_ENDERECO];
    int  ativo;
} Cliente;

typedef struct {
    int  id;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char telefone[TAM_TELEFONE];
    char placa_veiculo[TAM_PLACA];
    int  ativo;
} Entregador;

typedef struct {
    int  id;
    char nome[TAM_NOME];
    char endereco[TAM_ENDERECO];
    int  ativo;
} Localizacao;

typedef struct {
    int  id;
    int  id_cliente;
    int  id_entregador;
    char descricao[TAM_DESCRICAO];
    char endereco_destino[TAM_ENDERECO];
    float peso_kg;
    float valor_frete;
    Data data_postagem;
    Data data_entrega;
    StatusEncomenda status;
    int  ativo;
} Encomenda;

#endif
