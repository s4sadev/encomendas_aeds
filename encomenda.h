#ifndef ENCOMENDA_H
#define ENCOMENDA_H

#include "tipos.h"

void encomenda_registrar(void);
void encomenda_atribuir_entregador(void);
void encomenda_atualizar_status(void);
void encomenda_registrar_entrega(void);
void encomenda_buscar(void);

void encomenda_listar(void);
void encomenda_relatorio_por_cliente(void);
void encomenda_relatorio_por_entregador(void);
void encomenda_relatorio_por_status(void);

int encomenda_cliente_em_andamento(int id_cliente);
int encomenda_entregador_em_andamento(int id_entregador);


void encomenda_carregar(void);
int encomenda_salvar(void);

#endif
