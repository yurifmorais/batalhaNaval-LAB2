#ifndef _funcoes_H_
#define _funcoes_H_
//#include "funcoes.c"

int imprime_menu();

int recebe_e_verifica_linhas();

int recebe_e_verifica_colunas();

char** cria_aloca_matriz(int m, int n);

void preenche_matriz(char** matriz, int m, int n);

bool verifica_disponibilidade_local(char** tab_back, int cor_m, int cor_n,  int tam_embarcacao, int orientacao, int m, int n);

void sorteia_posicao_embarcacao(char** tab_back, int m, int n, int qtd_embarcacao, char letra, int tam_embarcacao);

void recebe_embarcacoes(char** matriz_um, char** matriz_dois, int m, int n);

bool verifica_jogada_valida(int m, int n, int coordenada_linha, int coordenada_coluna);

bool ataque(char** matriz_back, char** matriz_impressa, int m, int n, int jogador);

bool verifica_jogada_computador(char** matriz_back, char** matriz_impressa, int linha, int coluna);

bool jogada_computador(char** matriz_back, char** matriz_impressa, int m, int n, int *seq, int *linha_atac, int *coluna_atac);
                      
int verifica_vidas(char** matriz, int m, int n);

void imprime_matriz(char **matriz, int m, int n, int jogador);

void jogo(int op_jogo, char** tabuleiro_um, char** tabuleiro_dois, char** tabuleiro_um_back, char** tabuleiro_dois_back, int m, int n);

void tempo_decorrido(double t_inicio);

void libera_matriz(char** matriz, int m);

#endif