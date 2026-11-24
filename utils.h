#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

int   ler_texto(const char *rotulo, char *destino, int tamanho);
void  ler_texto_obrigatorio(const char *rotulo, char *destino, int tamanho);
void  atualizar_texto(const char *rotulo, char *campo, int tamanho);
int   ler_inteiro(const char *rotulo);
float ler_float(const char *rotulo);
Data  ler_data(const char *rotulo);
int   confirmar(const char *pergunta);

int  cpf_valido(const char *cpf);
int  data_valida(Data d);
int  comparar_datas(Data a, Data b);
void exibir_data(Data d);
int  contem_texto(const char *texto, const char *trecho);

#endif
