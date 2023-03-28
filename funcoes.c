#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers.h"

/*-----------------------------------------------------------------------------
| Nome da funcao: erro_alocacao_memoria_c
| Tipo: void
| Argumentos: lista_carreiras *topo1
| Funcao: Funcao responsavel por testar a alocacao de memoria.
+----------------------------------------------------------------------------*/

void erro_alocacao_c(lista_carreiras *topo){
    if (topo == NULL)
        exit (-1);
}

/*-----------------------------------------------------------------------------
| Nome da funcao: erro_alocacao_memoria_p
| Tipo: void
| Argumentos: lista_paragens *topo1
| Funcao: Funcao responsavel por testar a alocacao de memoria.
+----------------------------------------------------------------------------*/

void erro_alocacao_p(lista_paragens *topo){
    if (topo == NULL)
        exit (-1);
}

/*-----------------------------------------------------------------------------
| Nome da funcao: comandos_c
| Tipo: int
| Argumentos: char input[BUFSIZ], lista_carreiras *topo
| Funcao: Funcao responsavel por lidar com os comandos das carreiras. 
+----------------------------------------------------------------------------*/

void comandos_c(char input[BUFSIZ], lista_carreiras *topo){
    
    char command = '\0';
    char nome[CARREIRA_MAX];
    char inverso[INVERSO];
    int i=0;

    /* Se o input tem apenas um caractere, imprime todas as carreiras */
    if(strlen(input) == 1)
        imprime_carreiras(topo);
    
    /* Verifica se o input tem duas palavras */
    else if(conta_palavras(input) == 2){

        /* Le o comando e o nome da carreira */
        i = sscanf(input, "%c %s", &command, nome);

        /* Se a leitura foi bem sucedida, verifica se a carreira ja esta na 
        lista */
        if(i == 2){

            /* Se a carreira estiver na lista, imprime as paragens associadas 
            a carreira */
            if(procura_carreira(nome, topo) == 1)
                imprime_paragens_da_carreira(nome, topo);

            /* Se a carreira nao estiver na lista, adiciona-a */
            else
                topo = adiciona_carreira(nome, topo);
        }
    }

    /* Verifica se o input tem tres palavras */
    else if(conta_palavras(input) == 3){

        /* Le o comando, o nome da carreira e a opcao de inversao */
        i = sscanf(input, "%c %s %s", &command, nome, inverso);

        /* Se a leitura foi bem sucedida e opcao de inversao for valida, 
        imprime lista de carreiras invertida */
        if(i == 3){

            if(verifica_abrv_inverso(inverso)==1){

                if(procura_carreira(nome, topo) == 1)
                    imprime_inverso(nome, topo);
                else
                    topo = adiciona_carreira(nome, topo);
            }

            /* Se a opcao de inversao nao for valida, imprime uma mensagem de 
            erro */
            else
                printf("incorrect sort option.\n");
        }
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: adiciona_carreira
| Tipo: lista_carreiras *
| Argumentos: char nome
| Funcao: Funcao responsavel por adicionar uma nova carreira a lista.
+----------------------------------------------------------------------------*/

lista_carreiras * adiciona_carreira(char nome[CARREIRA_MAX], 
    lista_carreiras *topo){

    lista_carreiras *novo = NULL;
    lista_carreiras *aux = NULL;
    int contador = 0;
    
    /* Cria uma nova estrutura com a carreira a ser adicionada */
    novo = cria_carreira(nome);

    /* Inicializa o auxiliar como o topo da lista */          
    aux = topo;

    /* Percorre a lista ate chegar ao ultimo elemento e incrementa o contador */
    while (aux -> prox_c != NULL){
        aux = aux -> prox_c;
        contador ++;
    }

    /* Se o numero maximo de carreiras nao foi atingido, adiciona a nova
    estrutura no fim da lista */
    if(contador < NUM_CARREIRAS)
        aux -> prox_c = novo;

    /* Retorna o ponteiro para o inicio da lista atualizada */
    return topo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: cria_carreira
| Tipo: lista_carreiras *
| Argumentos: char nome[CARREIRA_MAX]
| Funcao: Funcao responsavel por criar um novo elemento da lista de carreiras
+----------------------------------------------------------------------------*/

lista_carreiras* cria_carreira(char nome[CARREIRA_MAX]){

    carreira_struct carreira;
    lista_carreiras* novo;
    lista_paragens* topo_p = NULL;
    paragem_struct indef;

    /* Inicializa a paragem indefinida */
    strcpy(indef.nome, "indef");
    indef.latitude = 0;
    indef.longitude = 0;

    /* Aloca memoria para o topo da lista de paragens da carreira */
    topo_p = (lista_paragens*) malloc(sizeof(lista_paragens));
    erro_alocacao_p(topo_p);
    topo_p->prox_p = NULL;

    /* Preenche a estrutura da carreira */
    strcpy(carreira.nome, nome);
    carreira.paragens = topo_p;
    carreira.origem = indef;
    carreira.destino = indef;
    carreira.custo_total = 0;
    carreira.duracao_total = 0;
    carreira.numero_paragens = 0;

    /* Associa a estrutura carreira a lista de carreiras */
    novo = cria_lista_carreiras(carreira);

    /* Retorna o ponteiro para o elemento da lista de carreiras criado */
    return novo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: cria_lista_carreiras
| Tipo: lista_carreiras*
| Argumentos: carreira_struct carreira
| Funcao: Funcao responsavel por associar a estrutura carreira a uma estrutura 
| lista de carreiras.
+----------------------------------------------------------------------------*/

lista_carreiras* cria_lista_carreiras(carreira_struct carreira){

    lista_carreiras* novo;
    
    /* Aloca memoria para o novo elemento da lista de carreiras */
    novo = (lista_carreiras*) malloc(sizeof(lista_carreiras));
    erro_alocacao_c(novo);

    /* Associa a estrutura carreira a uma estrutura lista de carreiras */
    novo->carreira = carreira;
    novo->prox_c = NULL;

    /* Retorna o ponteiro para o elemento da lista de carreiras criado */
    return novo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: imprime_carreiras
| Tipo: void
| Argumentos: lista_carreiras *topo
| Funcao: Funcao responsavel por imprimir as informaçoes de todas as carreiras 
| existentes na lista.
+----------------------------------------------------------------------------*/

void imprime_carreiras(lista_carreiras *topo){

    lista_carreiras *aux = topo->prox_c;

    /* Percorre a lista de carreiras */
    while(aux!=NULL){

        /* Imprime informacoes de uma carreira sem origem e destino definidos*/
        if(strcmp(aux->carreira.destino.nome, "indef") == 0)
            printf("%s %d %.2f %.2f\n", 
                aux->carreira.nome, aux->carreira.numero_paragens, 
                aux->carreira.custo_total, aux->carreira.duracao_total);
        
        /* Imprime informações de uma carreira com origem e destino definidos*/
        else
            printf("%s %s %s %d %.2f %.2f\n",
                aux->carreira.nome, aux->carreira.origem.nome,
                aux->carreira.destino.nome, aux->carreira.numero_paragens, 
                aux->carreira.custo_total, aux->carreira.duracao_total);

        aux = aux -> prox_c;
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: procura_carreira
| Tipo: int
| Argumentos: char nome[CARREIRA_MAX], lista_carreiras *topo
| Funcao: Funcao responsavel por verificar se uma carreira com o nome fornecido 
| existe na lista de carreiras. Retorna 1 caso exista e 0 caso contrario.
+----------------------------------------------------------------------------*/

int procura_carreira(char nome[CARREIRA_MAX], lista_carreiras *topo){

    lista_carreiras *aux = topo;

    /* Percorre a lista de carreiras */
    while(aux != NULL){
        
        if(strcmp(aux->carreira.nome, nome) == 0)
            return 1;
        
        aux = aux -> prox_c;
    }
    return 0;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: comandos_p
| Tipo: void
| Argumentos: char input[BUFSIZ], lista_paragens *topo
| Funcao: Funcao responsavel por lidar com os comandos das paragens.
+----------------------------------------------------------------------------*/

void comandos_p(char input[BUFSIZ], lista_paragens *topo){
    
    char command = '\0';
    char nome[PARAGEM_MAX];
    double latitude = 0;
    double longitude = 0;
    int i=0;

    /* Se o input tem apenas um caractere, imprime todas as paragens */
    if(strlen(input) == 1)
        imprime_paragens(topo);

    /* Verifica que nao ha palavras com aspas no meio */
    if(verifica_aspas_no_meio(input)!=1)
        return;

    /* Verifica se o input tem duas palavras */
    if(conta_palavras(input) == 2){

        /* Se nao ha aspas no comando, le normalmente */
        if(aspas(input)==0)
            i = sscanf(input, "%c %s", &command, nome);
        
        /* Se ha aspas no comando, le com sscanf para uma string delimitada 
        por aspas */
        else
            i = sscanf(input, "%c \"%[^\"]\"", &command, nome);

        /* Se leitura foi bem sucedida, verifica se a paragem ja esta na 
        lista */
        if(i == 2){

            /* Se a paragem estiver na lista, imprime as suas coordenadas */
            if(procura_paragem(nome, topo) == 1)
                imprime_coord(nome, topo);

            /* Se a paragem nao estiver na lista, emite uma mensagem de erro */
            else
                printf("%s: no such stop.\n", nome);
        }
    }

    /* Verifica se o input tem quatro palavras */
    if(conta_palavras(input) == 4){

        /* Se nao ha aspas no comando, le normalmente */
        if(aspas(input)==0)
            i = sscanf(input, "%c %s %lf %lf", 
                &command, nome, &latitude, &longitude);
        
        /* Se ha aspas no comando, le com scanf para uma string delimitada 
        por aspas */
        else
            i = sscanf(input, "%c \"%[^\"]\" %lf %lf", 
                &command, nome, &latitude, &longitude);
        
        /* Se leitura foi bem sucedida, verifica se a paragem ja esta na 
        lista */
        if(i == 4){

            /* Se a paragem estiver na lista, emite uma mensagem de erro */
            if(procura_paragem(nome, topo) == 1)
                printf("%s: stop already exists.\n", nome);

            /* Se a paragem nao estiver na lista, adiciona-a */
            else
                adiciona_paragem(nome, latitude, longitude, topo);
        }
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: procura_paragens
| Tipo: int
| Argumentos: char nome[PARAGEM_MAX], lista_paragens *topo
| Funcao: Funcao responsavel por verificar se uma paragem com o nome fornecido 
| existe na lista de paragens. Retorna 1 caso exista e 0 caso contrario.
+----------------------------------------------------------------------------*/

int procura_paragem(char nome[PARAGEM_MAX], lista_paragens *topo){

    lista_paragens *aux = topo;

    /* Percorre a lista de paragens */
    while(aux != NULL){

        if(strcmp(aux->paragem.nome, nome) == 0)
            return 1;
        
        aux = aux -> prox_p;
    }
    return 0;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: imprime_coord
| Tipo: void
| Argumentos: char nome[PARAGEM_MAX], lista_paragens *topo
| Funcao: Funcao responsavel por imprimir as coordenadas paragem com o nome 
| fornecido.
+----------------------------------------------------------------------------*/

void imprime_coord(char nome[PARAGEM_MAX], lista_paragens *topo){

    lista_paragens *aux = topo;

    /* Percorre a lista de paragens */
    while(aux != NULL){

        /* Se encontrar a paragem com o nome desejado, imprime as suas 
        coordenadas */
        if(strcmp(aux->paragem.nome, nome) == 0){
            printf("%16.12f %16.12f\n", 
                aux->paragem.latitude, aux->paragem.longitude);
            break;
        }
        aux = aux -> prox_p;
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: imprime_paragens
| Tipo: void
| Argumentos: lista_paragens *topo
| Funcao: Funcao responsavel por imprimir as informacoes de todas as paragens
| da lista.
+----------------------------------------------------------------------------*/

void imprime_paragens(lista_paragens *topo){

    lista_paragens *aux = topo->prox_p;

    /* Percorre a lista de paragens */
    while(aux != NULL){

        /* Imprime informacoes da paragem*/
        printf("%s: %16.12f %16.12f %d\n", aux->paragem.nome, 
            aux->paragem.latitude, aux->paragem.longitude, 
            aux->paragem.num_carreiras);

        aux = aux -> prox_p;
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: adiciona_paragem
| Tipo: lista_paragens *
| Argumentos: char nome
| Funcao: Funcao responsavel por adicionar uma nova paragem a lista
+----------------------------------------------------------------------------*/

lista_paragens * adiciona_paragem(char nome[PARAGEM_MAX], double latitude, 
    double longitude, lista_paragens *topo){

    lista_paragens *novo = NULL;
    lista_paragens *aux = NULL;
    int contador = 0;

    /* Cria uma nova estrutura com a paragem a ser adicionada */
    novo = cria_paragem(nome, latitude, longitude);

    /* Inicializa o auxiliar como o topo da lista */      
    aux = topo;

    /* Percorre a lista ate chegar ao ultimo elemento e incrementa o contador */
    while (aux -> prox_p != NULL){
        aux = aux -> prox_p;
        contador ++;
    }

    /* Se o numero maximo de paragens nao foi atingido, adiciona a nova
    estrutura no fim da lista */
    if(contador < NUM_PARAGENS)    
        aux -> prox_p = novo;

    /* Retorna o ponteiro para o inicio da lista atualizada */
    return topo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: cria_paragem
| Tipo: lista_paragens *
| Argumentos: char nome[paragem_MAX]
| Funcao: Funcao responsavel por criar um novo elemento da lista de paragens
+----------------------------------------------------------------------------*/

lista_paragens* cria_paragem(char nome[PARAGEM_MAX], double latitude,
    double longitude){

    paragem_struct paragem;
    lista_paragens* novo;

    /* Preenche a estrutura da paragem */
    strcpy(paragem.nome, nome);
    paragem.latitude = latitude;
    paragem.longitude = longitude;
    paragem.num_carreiras = 0;

    /* Associa a estrutura paragem a uma estrutura lista de paragens */
    novo = cria_lista_paragens(paragem);

    /* Retorna o ponteiro para o elemento da lista de paragens criado */
    return novo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: cria_lista_paragens
| Tipo: lista_paragens*
| Argumentos: paragem_struct paragem
| Funcao: Funcao responsavel por associar a estrutura paragem a uma estrutura 
| lista de paragens
+----------------------------------------------------------------------------*/

lista_paragens* cria_lista_paragens(paragem_struct paragem){

    lista_paragens* novo;
    
    /* Aloca memoria para o novo elemento da lista de paragens */
    novo = (lista_paragens*) malloc(sizeof(lista_paragens));
    erro_alocacao_p(novo);

    /* Associa a estrutura paragem a uma estrutura lista de paragens */
    novo->paragem = paragem;
    novo->prox_p = NULL;

    /* Retorna o ponteiro para o elemento da lista de paragens criado */
    return novo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: comandos_l
| Tipo: void
| Argumentos: char input[BUFSIZ], lista_carreiras *topo_c, 
| lista_paragens *topo_p
| Funcao: Funcao responsavel por lidar com os comandos das ligacoes
+----------------------------------------------------------------------------*/

void comandos_l(char input[BUFSIZ], lista_carreiras *topo_c, 
    lista_paragens *topo_p){
    
    char command = '\0';
    char carreira[CARREIRA_MAX];
    char origem[PARAGEM_MAX];
    char destino[PARAGEM_MAX];
    double custo = 0;
    double duracao = 0;
    int i=0;

    /* Se nao ha aspas no comando, le normalmente */
    if(aspas(input)==0)
        i = sscanf(input, "%c %s %s %s %lf %lf", &command, carreira, origem,
            destino, &custo, &duracao);
    
    /* Verifica que nao ha palavras com aspas no meio */
    if(verifica_aspas_no_meio(input)!=1)
        return;

    /* Se ha aspas no comando, le com sscanf para uma string delimitada 
    por aspas na posicao de origem */
    else if(aspas(input)==2){
        i = sscanf(input, "%c %s \"%[^\"]\" %s %lf %lf", &command, carreira, 
            origem, destino, &custo, &duracao);

        /* Caso a leitura nao tenha sido bem-sucedida, le com sscanf para uma 
        string delimitada por aspas na posicao de destino */
        if(i!=6)
            i = sscanf(input, "%c %s %s \"%[^\"]\" %lf %lf", &command, carreira, 
            origem, destino, &custo, &duracao);
    }

    /* Se o input contem quatro aspas, faz a leitura do input com aspas */
    else if(aspas(input) == 4){
        i = sscanf(input, "%c %s \"%[^\"]\" \"%[^\"]\" %lf %lf", &command, 
            carreira, origem, destino, &custo, &duracao);
    }

    /* Verifica se o input foi lido corretamente */
    if(i == 6){

        /* Verifica se a carreira existe */
        if(procura_carreira(carreira, topo_c)!=1)
            printf("%s: no such line.\n", carreira);
        
        /* Verifica se a paragem de origem existe */
        else if(procura_paragem(origem, topo_p)!=1)
            printf("%s: no such stop.\n", origem);
        
        /* Verifica se a paragem de destino existe */
        else if(procura_paragem(destino, topo_p)!=1)
            printf("%s: no such stop.\n", destino);    

        /* Verifica se o custo e a duração são positivos */
        else if(custo < 0 || duracao < 0)
            printf("negative cost or duration.\n");

        /* Adiciona a ligacao */
        else if(strcmp(origem, destino)!=0)
            adicionar_ligacao(carreira, origem, destino, custo, duracao, 
                topo_c, topo_p);
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: adicionar_ligacao
| Tipo: void
| Argumentos: char carreira[CARREIRA_MAX], char origem[PARAGEM_MAX], 
|    char destino[PARAGEM_MAX], double custo, double duracao, 
|    lista_carreiras *topo_c, lista_paragens *topo_p
| Funcao: Funcao responsavel por atualizar as carreiras e paragens tendo em 
| conta a informacao da ligacao.
+----------------------------------------------------------------------------*/

void adicionar_ligacao(char carreira[CARREIRA_MAX], char origem[PARAGEM_MAX], 
    char destino[PARAGEM_MAX], double custo, double duracao, 
    lista_carreiras *topo_c, lista_paragens *topo_p){

    paragem_struct origem_p;
    paragem_struct destino_p;
    
    /* Verifica se a paragem de origem ja existe na carreira.
    Se nao existir, atualiza a lista de paragens */
    if(verifica_carreira_nova(carreira, origem, topo_c) == 0)
        topo_p = update_paragem(origem, topo_p);
    
    /* Verifica se a paragem de destino ja existe na carreira.
    Se nao existir, atualiza a lista de paragens */
    if(verifica_carreira_nova(carreira, destino, topo_c) == 0)
        topo_p = update_paragem(destino, topo_p);

    /* Obtem as estruturas das paragens de origem e destino */
    origem_p = return_paragem(origem, topo_p);
    destino_p = return_paragem(destino, topo_p);

    /* Atualiza a carreira com a nova ligação */
    topo_c = update_carreira(carreira, topo_c, custo, duracao, 
        origem_p, destino_p);
}

/*-----------------------------------------------------------------------------
| Nome da funcao: verfica_carreira_nova
| Tipo: int
| Argumentos: char nome[PARAGEM_MAX], lista_paragens * topo
| Funcao: Funcao responsavel por verificar se uma determinada carreira ja 
| possui uma determinada paragem associada a ela.
| Retorna 1 caso a paragem ja esteja associada a uma carreira e 0 caso
| contrario.
+----------------------------------------------------------------------------*/

int verifica_carreira_nova(char carreira[CARREIRA_MAX], 
    char paragem[PARAGEM_MAX], lista_carreiras* topo){

    lista_carreiras * aux = topo;        
    lista_paragens *aux_p = NULL;

    /* Percorre a lista de carreiras */
    while (aux != NULL){

        if(strcmp(aux->carreira.nome, carreira)==0){
            
            /* Começa a percorrer a lista de paragens da carreira */
            aux_p = aux->carreira.paragens->prox_p;

            while (aux_p!=NULL){
                
                /* Verifica se a paragem já existe na carreira */
                if(strcmp(aux_p->paragem.nome, paragem)==0)
                    return 1;
                
                aux_p = aux_p->prox_p;
            }       
        }
        aux = aux->prox_c;
    }
    return 0;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: update_paragem
| Tipo: lista_paragens *
| Argumentos: char nome[PARAGEM_MAX], lista_paragens * topo
| Funcao: Funcao responsavel por incrementar o numero de carreiras de uma 
| paragem
+----------------------------------------------------------------------------*/

lista_paragens * update_paragem(char nome[PARAGEM_MAX], lista_paragens * topo){

    lista_paragens *aux = topo;

    /* Percorre a lista de paragens */
    while(aux != NULL){
    
        if(strcmp(aux-> paragem.nome, nome) == 0){

            /* Incrementa o numero de carreiras que passam na paragem */
            aux->paragem.num_carreiras ++;
            break;
        }
        aux = aux -> prox_p;
    }

    /* Retorna o ponteiro para o inicio da lista atualizada */
    return topo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: return_paragem
| Tipo: paragem_struct
| Argumentos: char nome[PARAGEM_MAX], lista_paragens * topo
| Funcao: Funcao responsavel por retornar a paragem correspondente ao nome 
| fornecido
+----------------------------------------------------------------------------*/

paragem_struct return_paragem(char nome[PARAGEM_MAX], lista_paragens *topo){

    lista_paragens *aux = topo;
    paragem_struct novo;

    /* Percorre a lista de paragens */
    while(1){

        /* Verifica se a carreira correspondente a pretendida */
        if(strcmp(aux-> paragem.nome, nome) == 0){
            novo = aux->paragem;
            break;
        }
        aux = aux -> prox_p;
    }

    /* Retorna a paragem pretendida */
    return novo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: update_carreira
| Tipo: lista_carreiras*
| Argumentos: char nome[CARREIRA_MAX], lista_carreiras * topo, 
| double custo, double duracao, paragem_struct origem, paragem_struct destino
| Funcao: Funcao responsavel por atualizar as informacoes da carreira em funcao
| da nova ligacao
+----------------------------------------------------------------------------*/

lista_carreiras * update_carreira(char nome[CARREIRA_MAX], 
    lista_carreiras * topo, double custo, double duracao, 
    paragem_struct origem, paragem_struct destino){

    lista_carreiras *aux = topo;
    lista_paragens *aux_p;
    lista_paragens *ant_p;

    lista_paragens *novo_origem;
    lista_paragens *novo_destino;

    /* Percorre a lista de carreiras */
    while(aux != NULL){

        if(strcmp(aux->carreira.nome, nome) == 0){

            /* Se a origem da carreira ainda não foi definida, atualiza a 
            carreira com a nova origem e destino */
            if(strcmp(aux->carreira.origem.nome, "indef")==0){

                /* Atualiza o custo e duracao da carreira */
                aux->carreira.custo_total += custo;
                aux->carreira.duracao_total += duracao;

                /* Cria novas estruturas listas de paragens para a origem
                e destino */
                novo_origem = cria_lista_paragens(origem);
                novo_destino = cria_lista_paragens(destino);

                /* Define a origem e o destino da carreira como a nova origem 
                e destino */
                aux->carreira.origem = origem;
                aux->carreira.destino = destino;

                /* Define a primeira paragem da carreira como a nova origem e
                a segunda paragem como o novo destino */
                aux->carreira.paragens->prox_p = novo_origem;
                novo_origem->prox_p = novo_destino;

                /* Define o numero total de paragens como 2 */
                aux->carreira.numero_paragens = 2;
            }
            /* Se o destino da carreira e igual a origem da nova ligacao,
            atualiza a carreira com a nova paragem de destino */
            else if(strcmp(aux->carreira.destino.nome, origem.nome)==0){

                /* Atualiza o custo e duracao da carreira */
                aux->carreira.custo_total += custo;
                aux->carreira.duracao_total += duracao;

                /* Cria uma nova estruturas listas de paragens para o destino*/
                novo_destino = cria_lista_paragens(destino);

                /* Percorre a lista de paragens da carreira ate chegar a 
                ultima paragem e adiciona o novo destino ao final */
                aux_p = aux->carreira.paragens;

                while(aux_p->prox_p != NULL)
                    aux_p = aux_p -> prox_p;
                
                aux_p -> prox_p = novo_destino;
                
                /* Define o destino da carreira como o novo destino */
                aux->carreira.destino = destino;
                /* Incrementa o numero total de paragens */
                aux->carreira.numero_paragens ++;
            }

            /* Se a origem da carreira e igual ao destino da nova ligacao,
            atualiza a carreira com a nova paragem de origem */
            else if(strcmp(aux->carreira.origem.nome, destino.nome)==0){

                /* Atualiza o custo e duracao da carreira */
                aux->carreira.custo_total += custo;
                aux->carreira.duracao_total += duracao;

                /* Cria uma nova estruturas listas de paragens para a origem*/
                novo_origem = cria_lista_paragens(origem);

                /* Define a nova origem como a primeira paragem da carreira e 
                atualiza a segunda paragem como a antiga primeira paragem */
                aux_p = aux->carreira.paragens;
                ant_p = aux->carreira.paragens->prox_p;

                aux_p->prox_p = novo_origem;
                novo_origem->prox_p = ant_p;

                /* Define a origem da carreira como a nova origem */
                aux->carreira.origem = origem;
                /* Incrementa o numero total de paragens */
                aux->carreira.numero_paragens ++;
            }
            /* Caso contrario, imprime uma mensagem de erro */
            else
                printf("link cannot be associated with bus line.\n");

        }
        aux = aux -> prox_c;
    }
    /* Retorna o ponteiro para o inicio da lista atualizada */
    return topo;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: imprime_paragens_da_carreira
| Tipo: void
| Argumentos: char nome[CARREIRA_MAX], lista_carreiras * topo
| Funcao: Funcao responsavel por imprimir as paragens de uma carreira
+----------------------------------------------------------------------------*/


void imprime_paragens_da_carreira(char nome[CARREIRA_MAX], 
    lista_carreiras * topo){

    lista_carreiras *aux_c = topo->prox_c;
    lista_paragens *aux_p = NULL;

    /* Percorre a lista de carreiras */
    while(aux_c!=NULL){

        /* Verifica se a carreira existe e tem paragens associadas */
        if(strcmp(aux_c->carreira.nome, nome)==0 && 
            strcmp(aux_c->carreira.destino.nome, "indef") != 0){

            /* Percorre a lista de paragens da carreira */
            aux_p = aux_c->carreira.paragens->prox_p;

            while(aux_p->prox_p != NULL){

                /* Imprime o nome das paragens */
                printf("%s, ", aux_p->paragem.nome);

                aux_p = aux_p->prox_p;
            }
            /* Imprime o nome da ultima paragem */
            printf("%s\n", aux_p->paragem.nome);
        }  
        aux_c = aux_c -> prox_c;
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: verifica_aspas_no_meio
| Tipo: int
| Argumentos: char input[BUFSIZ]
| Funcao: Funcao responsavel por verificar que as aspas no meio do input estão 
| sempre precedidas ou seguidas por um espaço.
+----------------------------------------------------------------------------*/

int verifica_aspas_no_meio(char input[BUFSIZ]){
    
    int i = 1;
    int tamanho = strlen(input);

    for (i = 1; i < tamanho - 1; i++){
        if (input[i] == '"'){ 
            if (input[i-1] != ' ' && input[i+1] != ' ')
                return 0;
        }
    }
    return 1;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: aspas
| Tipo: int
| Argumentos: char input[BUFSIZ]
| Funcao: Funcao responsavel por retornar o numero de aspas presentes no input
+----------------------------------------------------------------------------*/

int aspas(char input[BUFSIZ]){

    int contador = 0;
    int i = 0;

    /* Percorre o input e incrementa o contador sempre que encontrar aspas */
    for (i = 0; input[i] != '\0'; i++){
        if (input[i] == '"')
            contador++;   
    }
    /* Retorna o numero de aspas */
    return contador;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: conta_palavras
| Tipo: int
| Argumentos: char input[BUFSIZ]
| Funcao: Funcao responsavel por retornar o numero de palavras presentes no 
| input
+----------------------------------------------------------------------------*/

int conta_palavras(char input[BUFSIZ]){

    int contador = 0;
    int dentro_palavra = 0, dentro_aspas = 0;
    int i = 0;

    /* Percorre o input */
    for (i = 0; input[i] != '\0'; i++){

        /* Se o caractere for aspas, modifica o valor do identificador dentro 
        de aspas */
        if (input[i] == '"') {
            dentro_aspas = !dentro_aspas;

        /* Se e um espaço ou tabulação e nao esta dentro de aspas, altera
        o valor do identificador dentro de palavra para 0 */
        } else if ((input[i] == ' ' || input[i] == '\t') && !dentro_aspas){
            dentro_palavra = 0;

        /* Caso contrario, incrementa o contador e altera o valor do 
        identificador dentro de palavra para 1 */
        } else{
            if (!dentro_palavra){
                contador ++;
                dentro_palavra = 1;
            }
        }
    }
    /* Retorna o numero de palavras */
    return contador;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: comandos_i
| Tipo: void
| Argumentos: lista_carreiras *topo_c, lista_paragens *topo_p
| Funcao: Funcao responsavel por imprimir as informacoes das paragens que estao 
| presentes em mais de uma carreira
+----------------------------------------------------------------------------*/

void comandos_i(lista_carreiras *topo_c, lista_paragens *topo_p){
    
    lista_paragens *aux_p = topo_p->prox_p;

    /* Percorre a lista de paragens */
    while(aux_p!= NULL){

        /* Verifica se a paragem esta presente em mais do que uma carreira */
        if(aux_p->paragem.num_carreiras > 1){

            /* Imprime o nome e o numero de carreiras da paragem */
            printf("%s %d: ",aux_p->paragem.nome, aux_p->paragem.num_carreiras);
            /* Imprime o nome das carreiras que contem a paragem */
            imprime_carreiras_intersecao(aux_p->paragem.nome, topo_c);
        }           
        aux_p = aux_p -> prox_p;
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: imprime_carreiras_intersecao
| Tipo: void
| Argumentos: lista_carreiras *topo_c, lista_paragens *topo_p
| Funcao: Funcao responsavel por imprimir o nome das carreiras que contem a 
| paragem
+----------------------------------------------------------------------------*/

void imprime_carreiras_intersecao(char nome[PARAGEM_MAX], 
    lista_carreiras *topo_c){
    
    lista_carreiras *aux_c = topo_c->prox_c;
    lista_paragens *aux_p = NULL;
    char *nome_carreiras[NUM_CARREIRAS];
    int i = 0, j=0, k=0;

    /* Aloca memoria para as strings de nomes de carreiras */
    for (k = 0; k < NUM_CARREIRAS; k++){
        nome_carreiras[k] = malloc(sizeof(char) * CARREIRA_MAX);
    }   

    /* Percorre a lista de carreiras */
    while(aux_c != NULL){

        /* Percorre a lista de paragens da carreira */
        aux_p = aux_c->carreira.paragens->prox_p;

        while (aux_p!=NULL){

            /* Verifica se a carreira contem a paragem */
            if (strcmp(aux_p->paragem.nome, nome) == 0){
                /* Adiciona o nome da carreira ao array */
                strcpy(nome_carreiras[i], aux_c->carreira.nome);
                i++;
                break;
            }
            aux_p = aux_p->prox_p;
        }
        aux_c = aux_c -> prox_c;
    }

    /* Organiza o array por ordem alfabetica */
    ordena(nome_carreiras, i);

    /* Imprime as carreiras envolvidas na intersecao */
    while (j < i-1){
        printf("%s ", nome_carreiras[j]);
        j++;
    }
    printf("%s\n", nome_carreiras[i-1]);

    /* Liberta a memoria alocada */
    for (k = 0; k < NUM_CARREIRAS; k++){
        free(nome_carreiras[k]);
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: strcasecmp
| Tipo: int
| Argumentos: const char *s1, const char *s2
| Funcao: Funcao responsavel por comparar duas strings sem diferenciacao entre 
| letras maiusculas e minusculas.
| Retorna a diferenca entre os caracteres ou 0 se as strings forem iguais.
+----------------------------------------------------------------------------*/

int strcasecmp(const char *s1, const char *s2) {
    int i;
    char c1, c2;

    /* Percorre as duas strings */
    for (i = 0; s1[i] && s2[i]; i++) {
        /* Converte os caracteres para minusculos */
        c1 = tolower(s1[i]);
        c2 = tolower(s2[i]);
        /* Compara os caracteres em minusculo */
        if (c1 != c2) {
            /* Retorna a diferenca entre os caracteres caso sejam diferentes */
            return (c1 - c2);
        }
    }
    /* Retorna a diferenca entre os ultimos caracteres comparados 
    ou 0 caso as strings tenham o mesmo tamanho */
    return (s1[i] - s2[i]);
}

/*-----------------------------------------------------------------------------
| Nome da funcao: ordena
| Tipo: void
| Argumentos: char **vetor, int tamanho
| Funcao: Funcao responsavel por ordernar as strings do array por ordem
| alfabetica.
+----------------------------------------------------------------------------*/

void ordena(char **vetor, int tamanho){

    int i = 0, j = 0;
    int indice_menor = 0;
    char *temp;

    /* Percorre o vetor */
    for (i = 0; i < tamanho-1; i++){

        /* Encontra o indice do menor elemento no restante do vetor */
        indice_menor = i;
        for (j = i+1; j < tamanho; j++){

            /* Comparar as strings e encontrar o menor elemento */
            if (strcasecmp(vetor[j], vetor[indice_menor]) < 0){
                indice_menor = j;
            }
        }

        /* Troca o menor elemento com o primeiro elemento nao ordenado */
        if (indice_menor != i){
            temp = vetor[i];
            vetor[i] = vetor[indice_menor];
            vetor[indice_menor] = temp;
        }
    }
}


/*-----------------------------------------------------------------------------
| Nome da funcao: imprime_inverso
| Tipo: void
| Argumentos: char nome[CARREIRA_MAX], lista_carreiras *topo
| Funcao: Funcao responsavel por imprimir as paragens de uma carreira pela
| ordem inversa.
+----------------------------------------------------------------------------*/

void imprime_inverso(char nome[CARREIRA_MAX], lista_carreiras * topo){

    lista_carreiras *aux_c = topo->prox_c;
    lista_paragens *aux_p = NULL;
    char *nome_paragens[NUM_PARAGENS];
    int i = 0, j=0;

    /* Percorre a lista de carreiras */
    while(aux_c!=NULL){

        /* Verifica se a carreira existe e tem paragens associadas */
        if(strcmp(aux_c->carreira.nome, nome)==0 && 
            strcmp(aux_c->carreira.destino.nome, "indef") != 0){

            /* Percorre a lista de paragens da carreira */
            aux_p = aux_c->carreira.paragens->prox_p;

            while(aux_p != NULL){
                /* Adiciona o nome da paragem ao array */
                nome_paragens[i] = aux_p->paragem.nome;
                i++;
                aux_p = aux_p->prox_p;
            }
        }  
        aux_c = aux_c -> prox_c;
    }
    /* Verifica se a carreira tem paragens associadas */
    if(i!=0){

        /* Inverte a ordem do array */
        inverte(nome_paragens, i);

        /* Imprime o nome das paragens pela ordem inversa */
        while (j < i-1){
            printf("%s, ", nome_paragens[j]);
            j++;
        }
        printf("%s\n", nome_paragens[i-1]);
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: inverte
| Tipo: void
| Argumentos: char **strings, int n
| Funcao: Funcao responsavel por inverter a ordem do array
+----------------------------------------------------------------------------*/

void inverte(char **strings, int n){

    int i = 0;
    char *temp;

    /* Percorre o array ate o meio, trocando a posicao das strings. */
    for(i = 0; i < n / 2; i++){
        temp = strings[i];
        strings[i] = strings[n - 1 - i];
        strings[n - 1 - i] = temp;
    }
}

/*-----------------------------------------------------------------------------
| Nome da funcao: verifica_abrv_inverso
| Tipo: int
| Argumentos: char palavra[INVERSO]
| Funcao: Funcao responsavel por verificar se a palavra fornecida corresponde 
| a palavra "inverso" ou um prefixo de tamanho pelo menos 3 da mesma.
| Retorna 1 se sim e 0 caso contrario.
+----------------------------------------------------------------------------*/

int verifica_abrv_inverso(char palavra[INVERSO]){

    char inverso[] = "inverso";
    int tamanho = strlen(palavra);
    int i = 0, count = 0;

    /* Verifica se o tamanha da palavra e inferior a 3. Se sim, retorna 0 */
    if(tamanho < 3)
        return 0;

    /* Percorre a palavra fornecida */
    for(i = 0; i < tamanho; i++){    
        /* Compara cada caractere da palavra com o caracter correspondente da 
        palavra "inverso" */  
        if(palavra[i] == inverso[i])
            /* Incrementa o contador */
            count ++;
    }
    /* Se o numero de caracteres correspondentes for igual ao numero de 
    caracteres da palavra recebida, retorna 1 */
    if(count == tamanho)
        return 1;
    /* Caso contrario, retorna 0 */
    else
        return 0;
}

/*-----------------------------------------------------------------------------
| Nome da funcao: free_lista_carreiras
| Tipo: void
| Argumentos: lista_carreiras *topo_c
| Funcao: Funcao responsavel por desalocar a memoria de cada elemento da lista
| de carreiras
+----------------------------------------------------------------------------*/

void free_lista_carreiras(lista_carreiras *topo_c){

    lista_carreiras *aux_c = topo_c->prox_c;
    
    /* Percorre a lista de carreiras e desaloca a memoria alocada para cada
    elemento */
    while (aux_c != NULL) {
        lista_carreiras *prox_c = aux_c->prox_c;
        /* Percorre a lista de paragens da carreira e desaloca a memoria 
        alocada para a lista de paragens da carreira atual */
        free_lista_paragens(aux_c->carreira.paragens);
        free(aux_c);
        aux_c = prox_c;
    }
    /* Liberta o topo */
    free(topo_c);
}

/*-----------------------------------------------------------------------------
| Nome da funcao: free_lista_paragens
| Tipo: void
| Argumentos: lista_paragens *topo_p
| Funcao: Funcao responsavel por desalocar a memoria de cada elemento da lista
| de paragens.
+----------------------------------------------------------------------------*/

void free_lista_paragens(lista_paragens *topo_p){

    lista_paragens *aux_p = topo_p->prox_p;
    /* Percorre a lista de paragens e desaloca a memoria alocada para cada
    elemento*/
    while (aux_p != NULL){
        lista_paragens *prox_p = aux_p->prox_p;
        free(aux_p);
        aux_p = prox_p;
    }
    /* Liberta o topo */
    free(topo_p);
}
