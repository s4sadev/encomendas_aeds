#include <stdio.h>
#include "tipos.h"
#include "cliente.h"
#include "entregador.h"
#include "localizacao.h"
#include "encomenda.h"

static void exibir_titulo(const char *titulo)
{
    printf("\n  %s\n", titulo);
}

static int ler_opcao(void)
{
    char linha[32];
    int opcao;

    printf("Opcao: ");
    if (fgets(linha, sizeof(linha), stdin) == NULL) return 0;
    if (sscanf(linha, "%d", &opcao) != 1) return -1;
    return opcao;
}

static void menu_clientes(void)
{
    int opcao;

    do {
        exibir_titulo("CLIENTES");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Voltar\n");
        opcao = ler_opcao();

        switch (opcao) {
            case 1: cliente_cadastrar(); break;
            case 2: cliente_listar();    break;
            case 3: cliente_buscar();    break;
            case 4: cliente_atualizar(); break;
            case 5: cliente_remover();   break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

static void menu_entregadores(void)
{
    int opcao;

    do {
        exibir_titulo("ENTREGADORES");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Voltar\n");
        opcao = ler_opcao();

        switch (opcao) {
            case 1: entregador_cadastrar(); break;
            case 2: entregador_listar();    break;
            case 3: entregador_buscar();    break;
            case 4: entregador_atualizar(); break;
            case 5: entregador_remover();   break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

static void menu_localizacoes(void)
{
    int opcao;

    do {
        exibir_titulo("LOCALIZACOES");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Voltar\n");
        opcao = ler_opcao();

        switch (opcao) {
            case 1: localizacao_cadastrar(); break;
            case 2: localizacao_listar();    break;
            case 3: localizacao_buscar();    break;
            case 4: localizacao_atualizar(); break;
            case 5: localizacao_remover();   break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

static void menu_cadastros(void)
{
    int opcao;

    do {
        exibir_titulo("CADASTROS");
        printf("1 - Clientes\n");
        printf("2 - Entregadores\n");
        printf("3 - Localizacoes\n");
        printf("0 - Voltar\n");
        opcao = ler_opcao();

        switch (opcao) {
            case 1: menu_clientes();     break;
            case 2: menu_entregadores(); break;
            case 3: menu_localizacoes(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

static void menu_rotinas(void)
{
    int opcao;

    do {
        exibir_titulo("ROTINAS");
        printf("1 - Registrar encomenda\n");
        printf("2 - Atribuir entregador\n");
        printf("3 - Atualizar status da encomenda\n");
        printf("4 - Registrar entrega\n");
        printf("5 - Buscar encomenda\n");
        printf("0 - Voltar\n");
        opcao = ler_opcao();

        switch (opcao) {
            case 1: encomenda_registrar();           break;
            case 2: encomenda_atribuir_entregador(); break;
            case 3: encomenda_atualizar_status();    break;
            case 4: encomenda_registrar_entrega();   break;
            case 5: encomenda_buscar();              break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

static void menu_relatorios(void)
{
    int opcao;

    do {
        exibir_titulo("RELATORIOS");
        printf("1 - Encomendas - cliente\n");
        printf("2 - Encomendas - entregador\n");
        printf("3 - Encomendas - status\n");
        printf("4 - Todas as encomendas\n");
        printf("0 - Voltar\n");
        opcao = ler_opcao();

        switch (opcao) {
            case 1: encomenda_relatorio_por_cliente();    break;
            case 2: encomenda_relatorio_por_entregador(); break;
            case 3: encomenda_relatorio_por_status();     break;
            case 4: encomenda_listar();                   break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

int main(void)
{
    int opcao;

    /* Recupera os dados persistidos antes de exibir o menu. */
    cliente_carregar();
    entregador_carregar();
    localizacao_carregar();
    encomenda_carregar();

    do {
        exibir_titulo("SISTEMA DE EMPRESA DE ENCOMENDAS");
        printf("1 - Cadastros\n");
        printf("2 - Rotinas\n");
        printf("3 - Relatorios\n");
        printf("0 - Sair\n");
        opcao = ler_opcao();

        switch (opcao) {
            case 1: menu_cadastros();  break;
            case 2: menu_rotinas();    break;
            case 3: menu_relatorios(); break;
            case 0:
                /* Grava todos os cadastros e encomendas antes de encerrar. */
                {
                    int salvou_clientes = cliente_salvar();
                    int salvou_entregadores = entregador_salvar();
                    int salvou_localizacoes = localizacao_salvar();
                    int salvou_encomendas = encomenda_salvar();

                    if (salvou_clientes && salvou_entregadores &&
                        salvou_localizacoes && salvou_encomendas)
                        printf("Dados salvos. Sistema encerrado\n");
                    else
                        printf("Sistema encerrado, mas houve erro ao salvar os dados.\n");
                }
                break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
