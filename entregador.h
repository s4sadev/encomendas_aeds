#ifndef ENTREGADOR_H
#define ENTREGADOR_H

#include "tipos.h"

void entregador_cadastrar(void);
void entregador_listar(void);
void entregador_buscar(void);
void entregador_atualizar(void);
void entregador_remover(void);

Entregador *entregador_buscar_por_id(int id);
const char *entregador_nome_por_id(int id);


void entregador_carregar(void);
int entregador_salvar(void);

#endif
