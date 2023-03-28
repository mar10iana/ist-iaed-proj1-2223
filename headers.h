#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CARREIRA_MAX 21
#define PARAGEM_MAX 51
#define NUM_CARREIRAS 200
#define NUM_PARAGENS 10000
#define INVERSO 8

typedef struct {
    double latitude;
    double longitude;
    char nome[PARAGEM_MAX];
    int num_carreiras;
}paragem_struct;

typedef struct lista_paragens{
    paragem_struct paragem;
    struct lista_paragens* prox_p;
}lista_paragens;

typedef struct {
    paragem_struct origem;
    paragem_struct destino;
    lista_paragens *paragens;
    double custo_total;
    double duracao_total;
    int numero_paragens;
    char nome[CARREIRA_MAX];
}carreira_struct;

typedef struct lista_carreiras{
    carreira_struct carreira;
    struct lista_carreiras* prox_c;
}lista_carreiras;


void erro_alocacao_c(lista_carreiras *topo);
void erro_alocacao_p(lista_paragens *topo);
void comandos_c(char input[BUFSIZ], lista_carreiras *topo);
lista_carreiras * adiciona_carreira(char nome[CARREIRA_MAX], 
    lista_carreiras *topo);
lista_carreiras * cria_carreira(char nome[CARREIRA_MAX]);
void imprime_carreiras(lista_carreiras *topo);
int procura_carreira(char nome[CARREIRA_MAX], lista_carreiras *topo);
void imprime_paragens(lista_paragens *topo);
void comandos_p(char input[BUFSIZ], lista_paragens *topo);
int procura_paragem(char nome[PARAGEM_MAX], lista_paragens *topo);
void imprime_coord(char nome[PARAGEM_MAX], lista_paragens *topo);
lista_paragens * adiciona_paragem(char nome[PARAGEM_MAX], double latitude, 
    double longitude, lista_paragens *topo);
lista_paragens * cria_paragem(char nome[PARAGEM_MAX], double latitude, 
    double longitude);
void comandos_l(char input[BUFSIZ], lista_carreiras *topo_c, 
    lista_paragens *topo_p);
void adicionar_ligacao(char carreira[CARREIRA_MAX], char origem[PARAGEM_MAX], 
    char destino[PARAGEM_MAX], double custo, double duracao, 
    lista_carreiras *topo_c, lista_paragens *topo_p);
int verifica_carreira_nova(char carreira[CARREIRA_MAX], 
    char paragem[PARAGEM_MAX], lista_carreiras* topo);
lista_paragens * update_paragem(char nome[PARAGEM_MAX], lista_paragens * topo);
paragem_struct return_paragem(char nome[PARAGEM_MAX], lista_paragens *topo);
lista_paragens* cria_lista_paragens(paragem_struct paragem);
lista_carreiras * update_carreira(char nome[CARREIRA_MAX], 
    lista_carreiras * topo, double custo, double duracao, 
    paragem_struct origem, paragem_struct destino);
void imprime_paragens_da_carreira(char nome[CARREIRA_MAX], 
    lista_carreiras * topo);
int aspas(char input[BUFSIZ]);
int conta_palavras(char input[BUFSIZ]);
void comandos_i(lista_carreiras *topo_c, lista_paragens *topo_p);
void imprime_carreiras_intersecao(char nome[PARAGEM_MAX], 
    lista_carreiras *topo_c);
void ordena(char **vetor, int tamanho);
void imprime_inverso(char nome[CARREIRA_MAX], lista_carreiras * topo);
void inverte(char **strings, int n);
int verifica_abrv_inverso(char palavra[7]);
void free_lista_carreiras(lista_carreiras *topo_c);
void free_lista_paragens(lista_paragens *topo_p);
lista_carreiras* cria_lista_carreiras(carreira_struct carreira);
int strcasecmp(const char *s1, const char *s2);
int verifica_aspas_no_meio(char input[BUFSIZ]);

#endif
