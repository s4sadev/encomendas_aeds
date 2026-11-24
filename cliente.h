#ifndef CLIENTE_H
#define CLIENTE_H

#include "tipos.h"

void cliente_cadastrar(void);
void cliente_listar(void);
void cliente_buscar(void);
void cliente_atualizar(void);
void cliente_remover(void);

Cliente    *cliente_buscar_por_id(int id);
const char *cliente_nome_por_id(int id);


void cliente_carregar(void);
int cliente_salvar(void);

#endif
