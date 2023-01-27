#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "funcoes.h"
/*
YURI FONSECA DE MORAIS - 202020637
yfmorais@inf.ufsm.br

LABORATORIO DE PROGRAMACAO 2
BATALHA NAVAL 
*/
int main()
{
    clock_t inicio = clock();
    srand (time(NULL));
    int opcao_jogo, linhas, colunas;

    opcao_jogo = imprime_menu();
    linhas = recebe_e_verifica_linhas();
    colunas = recebe_e_verifica_colunas();

    char** tabuleiro = cria_aloca_matriz(linhas, colunas);
    char** tabuleiro_dois = cria_aloca_matriz(linhas, colunas);
    char** tabuleiro_back = cria_aloca_matriz(linhas, colunas);
    char** tabuleiro_back_dois = cria_aloca_matriz(linhas, colunas);

    preenche_matriz(tabuleiro, linhas, colunas);
    preenche_matriz(tabuleiro_dois, linhas, colunas);
    preenche_matriz(tabuleiro_back, linhas, colunas);
    preenche_matriz(tabuleiro_back_dois, linhas, colunas);
    recebe_embarcacoes(tabuleiro_back, tabuleiro_back_dois, linhas, colunas);

    jogo(opcao_jogo, tabuleiro, tabuleiro_dois, tabuleiro_back, tabuleiro_back_dois, linhas, colunas);

    libera_matriz(tabuleiro, linhas);
    libera_matriz(tabuleiro_dois, linhas);
    libera_matriz(tabuleiro_back, linhas);
    libera_matriz(tabuleiro_back_dois, linhas);
    tempo_decorrido(inicio);
    return 0;
}