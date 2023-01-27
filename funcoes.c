#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "funcoes.h"

int imprime_menu()
{
    int op_jogo = 0;
    printf("\n----------BATALHA NAVAL----------\n\n");
    printf("-> MENU:");
    printf("\n\t1. Dois jogadores");
    printf("\n\t2. Um jogador vs CPU (JOGADOR 2)\n"); 
    do
    {
        printf("\tOpcao(1 ou 2): ");
        scanf("%d", &op_jogo);
    } while (op_jogo != 1 && op_jogo != 2);
    printf("\n\t-> INFORMACOES SOBRE O TABULEIRO: \n\t\t'~' = MAR |||| '*' = BOMBA NO MAR |||| '&' BOMBA NA EMBARCACAO\n");
    return op_jogo;
}

int recebe_e_verifica_linhas()
{   
    printf("\n-> CONFIGURACAO DO TABULEIRO:\n");
    int qtd_linhas;
    do
    {
        printf("\t-Informe a quantidade de linhas: ");
        scanf("%d", &qtd_linhas);
        if(qtd_linhas < 2) printf("\t >>A quantidade de linhas deve ser maior do que 1!<<\n");
    } while (qtd_linhas < 2);
    
    return qtd_linhas;
}

int recebe_e_verifica_colunas()
{   
    int qtd_colunas;
    do
    {
        printf("\t-Informe a quantidade de colunas: ");
        scanf("%d", &qtd_colunas);
        if(qtd_colunas < 2) printf("\t >>A quantidade de colunas deve ser maior do que 1!<<\n");
    } while (qtd_colunas < 2);

    return qtd_colunas;
}

char** cria_aloca_matriz(int m, int n)
{
    char** matriz = (char**) malloc(m * sizeof(char*));
    for (int i = 0; i < m; i++) matriz[i] = (char*) malloc(n * sizeof(char));

    if (!matriz)
    {
        printf("Falha na alocacao de memoria!\nEncerrando o programa.");
        exit(1);
    }
    else return matriz;
}

void preenche_matriz(char** matriz, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++) matriz[i][j] = '~';                  
    }
}

bool verifica_disponibilidade_local(char** tab_back, int cor_m, int cor_n,  int tam_embarcacao, int orientacao, int m, int n)
{   
    int cont = 0;

    if (tab_back[cor_m][cor_n] == '~')
    {   
        switch (orientacao)
        {
            case 0:
                for (int i = cor_n; i < n; i++)
                { 
                    if ((tab_back[cor_m][i]) != '~') break;
                    else cont++;
                }
            break;
                
            case 1:
                for (int i = cor_m; i < m; i++)
                { 
                    if ((tab_back[i][cor_n]) != '~') break;
                    else cont++;
                }
            break;
        }    
    }

    if (cont >= tam_embarcacao) return true;
    else return false;
}

void sorteia_posicao_embarcacao(char** tab_back, int m, int n, int qtd_embarcacao, char letra, int tam_embarcacao)
{                             
    int limite_m = m;
    int limite_n = n;
    int cor_m=0, cor_n=0, cont, orientacao, tentativas=0;
    int i=0, j;
    
    while (i < qtd_embarcacao)
    {
        cont = 0;
        orientacao = (rand() % 2); //orientacao: 0 = horizontal //// 1 = vertical 
        cor_m = (rand() % limite_m);
        cor_n = (rand() % limite_n);
        
        if (verifica_disponibilidade_local(tab_back, cor_m, cor_n, tam_embarcacao, orientacao, m, n))
        {
            switch (orientacao)
            {
                case 0:
                    while (cont < tam_embarcacao)
                    {
                        j = cor_n + cont;
                        tab_back[cor_m][j] = letra;
                        cont++;                      
                    }
                    i++;
                break;

                case 1:
                    while (cont < tam_embarcacao)
                    {
                        j = cor_m + cont;
                        tab_back[j][cor_n] = letra;
                        cont++;                      
                    }
                    i++; 
                break;           
            }
        }
        tentativas++;
        if (tentativas > 150)
        {
            printf("\t\nFalha ao sortear posicao das barcos! Tente com menos embacacoes ou em um tabuleiro maior!");
            exit(1);
        }
    }
}

void recebe_embarcacoes(char** matriz_um, char** matriz_dois, int m, int n)
{
    int tam_tabuleiro = m * n;
    int total_embarcacoes = 0, qtd_porta_avioes, qtd_submarinos, qtd_navio_tanque, qtd_contra_torpedeiros;

    printf("\n-> CONFIGURACAO DAS EMBARCACOES:\n");
    do
    {
        printf("\tInforme a quantidade de porta-avioes: ");
        scanf("%d", &qtd_porta_avioes);         
        printf("\tInforme a quantidade de navios-tanque: ");
        scanf("%d", &qtd_navio_tanque); 
        printf("\tInforme a quantidade de contratorpedeiros: ");
        scanf("%d", &qtd_contra_torpedeiros);
        printf("\tInforme a quantidade de submarinos:");
        scanf("%d", &qtd_submarinos);
        
        sorteia_posicao_embarcacao(matriz_um, m, n, qtd_porta_avioes, 'P', 5);
        sorteia_posicao_embarcacao(matriz_dois, m, n, qtd_porta_avioes, 'P', 5);
        sorteia_posicao_embarcacao(matriz_um, m, n, qtd_navio_tanque, 'N', 4);
        sorteia_posicao_embarcacao(matriz_dois, m, n, qtd_navio_tanque, 'N', 4);
        sorteia_posicao_embarcacao(matriz_um, m, n, qtd_contra_torpedeiros, 'C', 3);
        sorteia_posicao_embarcacao(matriz_dois, m, n, qtd_contra_torpedeiros, 'C', 3);
        sorteia_posicao_embarcacao(matriz_um, m, n, qtd_submarinos, 'S', 2);         
        sorteia_posicao_embarcacao(matriz_dois, m, n, qtd_submarinos, 'S', 2);
          
        total_embarcacoes = qtd_porta_avioes + qtd_submarinos + qtd_navio_tanque + qtd_contra_torpedeiros;
        if (total_embarcacoes < 1) printf("\t >>A quantidade de embarcacoes deve ser maior que zero!<<\n");   
    } while (total_embarcacoes < 1);
}

bool verifica_jogada_valida(int m, int n, int coordenada_linha, int coordenada_coluna)
{
    if (coordenada_linha < m && coordenada_linha >= 0 && coordenada_coluna < n && coordenada_coluna >= 0) return true;
    else return false;
}

bool ataque(char** matriz_back, char** matriz_impressa, int m, int n, int jogador)
{                           
    int linha_atacada, coluna_atacada;
    printf("\n\t-> Vez de Jogador %d: ", jogador);
    printf("\n\t-> Informe as coordenadas de ataque");
    printf("\n\t-> Linha: ");
    scanf("%d", &linha_atacada);
    printf("\t-> Coluna: ");
    scanf("%d", &coluna_atacada);
    if (verifica_jogada_valida(m, n, linha_atacada, coluna_atacada))
    {        
        if (matriz_back[linha_atacada][coluna_atacada] != '~' && matriz_impressa[linha_atacada][coluna_atacada] == '~')
        {
            matriz_impressa[linha_atacada][coluna_atacada] = '&';
            return true;
        }
        else if (matriz_impressa[linha_atacada][coluna_atacada] != '~' )
        {
            printf("\n\t-> VOCE JA JOGOU AI! TENTE NOVAMENTE!");
            ataque(matriz_back, matriz_impressa, m, n, jogador);
        }
        else
        {
            matriz_impressa[linha_atacada][coluna_atacada] = '*'; 
            return false;
        } 
    }
    else
    {
        printf("\n\t-> POSICAO INVALIDA! TENTE NOVAMENTE!");
        ataque(matriz_back, matriz_impressa, m, n, jogador);
    }
}

bool verifica_jogada_computador(char** matriz_back, char** matriz_impressa, int linha, int coluna)
{
    if (matriz_back[linha][coluna] != '~' && matriz_impressa[linha][coluna] == '~') return true; 
    else return false;       
}

bool jogada_computador(char** matriz_back, char** matriz_impressa, int m, int n, int *seq, int *linha_atac, int *coluna_atac) 
{
    int linha_atacada = *linha_atac;
    int coluna_atacada = *coluna_atac;
    
    if (*seq == 0)
    {
        do
        {
            linha_atacada = (rand() % m);
            coluna_atacada = (rand() % n); 
        } while (matriz_impressa[linha_atacada][coluna_atacada] != '~');
    }
   
    else if (*seq > 0) 
    {        
        if (verifica_jogada_valida(m, n, linha_atacada, coluna_atacada+1) && matriz_impressa[linha_atacada][coluna_atacada+1] == '~') coluna_atacada++; //para direita
        else if (verifica_jogada_valida(m, n, linha_atacada+1, coluna_atacada) && matriz_impressa[linha_atacada+1][coluna_atacada] == '~') linha_atacada++; //baixo
        else if (verifica_jogada_valida(m, n, linha_atacada, coluna_atacada-1) && matriz_impressa[linha_atacada][coluna_atacada-1] == '~') coluna_atacada--; //esquerda
        else if (verifica_jogada_valida(m, n, linha_atacada-1, coluna_atacada) && matriz_impressa[linha_atacada-1][coluna_atacada] == '~') linha_atacada--; //cima

        else
        {
            printf("\ncaiu no else!\n");/////*
            do
            {
                linha_atacada = (rand() % m);
                coluna_atacada = (rand() % n); 
            } while (matriz_impressa[linha_atacada][coluna_atacada] != '~');
        }
    }

    printf("\n\t-> Vez de COMPUTADOR:");
    printf("\n\t-> Coordenadas de ataque");
    printf("\n\t-> Linha: %d", linha_atacada);
    printf("\t-> Coluna: %d", coluna_atacada);

    if (verifica_jogada_valida(m, n, linha_atacada, coluna_atacada))
    {        
        if (verifica_jogada_computador(matriz_back, matriz_impressa, linha_atacada, coluna_atacada))
        {
            matriz_impressa[linha_atacada][coluna_atacada] = '&';
            *seq++;
            *linha_atac = linha_atacada;
            *coluna_atac = coluna_atacada; 
            return true;
        }
        else if (matriz_impressa[linha_atacada][coluna_atacada] != '~' )
        {
            printf("\n\t-> VOCE JA JOGOU AI! TENTE NOVAMENTE!");
            jogada_computador(matriz_back, matriz_impressa, m, n, seq, linha_atac, coluna_atac);  
        }
        else
        {
            matriz_impressa[linha_atacada][coluna_atacada] = '*'; 
            return false;
        } 
    }      
}

int verifica_vidas(char** matriz, int m, int n)
{
    int vidas = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {   
            if (matriz[i][j] == 'P'|| matriz[i][j] == 'N' || matriz[i][j] == 'C' || matriz[i][j] == 'S') vidas++;  
        }               
    }
    return vidas;
}
  
void imprime_matriz(char **matriz, int m, int n, int jogador)
{
    printf("\t\n\nTABULEIRO JOGADOR %d:", jogador);

    printf("\n\n");
    printf("Linha:      \n");
    for (int x = 0; x < m; x++) 
    {
        if (x < 10 ) printf("    0%d ->   ", x);
        else printf("    %d ->   ", x);

        for (int y = 0; y < n; y++) printf("%c  ", matriz[x][y]);
        printf("\n");
    }
  
    printf("\n\t    ");
    for (int t=0; t <n; t++) printf("^  ");
    printf("\n\t    ");
    for (int t=0; t <n; t++) printf("'  ");
    
    printf("\nColuna:   ");
    for (int j = 0; j < n; j++)
    { 
      if (j < 10) printf(" 0%d", j);
      else printf(" %d", j);
    }
    printf("\n");
}

void jogo(int op_jogo, char** tabuleiro_um, char** tabuleiro_dois, char** tabuleiro_um_back, char** tabuleiro_dois_back, int m, int n)
{         

    int vidas_jogador_um = verifica_vidas(tabuleiro_um_back, m, n);
    int vidas_jogador_dois = verifica_vidas(tabuleiro_dois_back, m, n);
    int player = (rand() % 2) + 1; 
    int seq = 0, linha_a, coluna_a; 
    int *ptSeq = &seq;
    int *ptLinha = &linha_a;
    int *ptColuna = &coluna_a;

    printf("\n-------------------------------------------------------");
    printf("\n-> O JOGADOR %d FOI SORTEADO PARA COMECAR A PARTIDA!", player);
    printf("\n-> VIDAS JOGADOR UM: %d -- VIDAS JOGADOR DOIS: %d", vidas_jogador_um, vidas_jogador_dois);
    imprime_matriz(tabuleiro_um, m, n, 1);
    imprime_matriz(tabuleiro_dois, m, n, 2);

    do
    {
        if (op_jogo == 1)
        {
            if (player == 1)
            {
                if (ataque(tabuleiro_dois_back, tabuleiro_dois, m, n, 1))
                {
                    vidas_jogador_dois--;
                    printf("\t\n-> NA MOSCA! ACERTAMOS UMA EMBARCACAO DO JOGADOR DOIS.");
                }
                else
                {
                    player = 2;
                    printf("\t\n-> NAO FOI DESSA VEZ! NA PROXIMA SEJA MAIS PRECISO.");
                }
            }
            else 
            {
                if (ataque(tabuleiro_um_back, tabuleiro_um, m, n, 2))
                {
                    vidas_jogador_um--;
                    printf("\t\n-> NA MOSCA! ACERTAMOS UMA EMBARCACAO DO JOGADOR UM.");
                }
                else
                {
                    player = 1;
                    printf("\t\n-> NAO FOI DESSA VEZ! NA PROXIMA SEJA MAIS PRECISO.");
                }
            }
        }
        
        else
        {
            if (player == 1)
            {
                if (ataque(tabuleiro_dois_back, tabuleiro_dois, m, n, 1))
                {
                    vidas_jogador_dois--;
                    printf("\t\n-> NA MOSCA! ACERTAMOS UMA EMBARCACAO DO COMPUTADOR.");
                }
                else
                {
                    player = 2;
                    printf("\t\n-> NAO FOI DESSA VEZ! NA PROXIMA SEJA MAIS PRECISO.");
                }
            }
            else 
            {                           
                if (jogada_computador(tabuleiro_um_back, tabuleiro_um, m, n, ptSeq, ptLinha, ptColuna))
                {
                    vidas_jogador_um--;
                    printf("\t\n-> NA MOSCA! O COMPUTADOR ACERTOU SUA EMBARCACAO.");
                    seq++;
                }
                else
                {
                    player = 1;
                    printf("\t\n-> NAO FOI DESSA VEZ! NA PROXIMA SEJA MAIS PRECISO.");
                }
            }
        }       
        printf("\n-------------------------------------------------------");
        imprime_matriz(tabuleiro_um, m, n, 1);
        imprime_matriz(tabuleiro_dois, m, n, 2);
        printf("\n-------------------------------------------------------\n");
        printf("-> VIDAS JOGADOR UM: %d -- VIDAS JOGADOR DOIS: %d\n", vidas_jogador_um, vidas_jogador_dois);

    } while (vidas_jogador_um > 0 && vidas_jogador_dois > 0);
    
    if (vidas_jogador_um > 0) printf("\t\n\t -> PARABENS JOGADOR 1, VOCE VENCEU!\n");
    else printf("\t\n\t -> PARABENS JOGADOR 2, VOCE VENCEU!\n");
}

void tempo_decorrido(double t_inicio)
{
    clock_t fim = clock();
    printf("\t\n-> TEMPO DECORRIDO DURANTE A PARTIDA: %.2f SEGUNDOS\n", (double)(fim - t_inicio) / CLOCKS_PER_SEC);    
}

void libera_matriz(char** matriz, int m)
{
    for (int i = 0; i < m; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}