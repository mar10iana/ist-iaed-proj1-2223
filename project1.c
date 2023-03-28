/* iaed-23 - ist199528 - project1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"

int main()
{
    char input[BUFSIZ];

    lista_carreiras *topo_c = NULL;
    lista_paragens *topo_p = NULL;

    /* Aloca memoria para o topo da lista de carreiras */
    topo_c = (lista_carreiras*) malloc(sizeof(lista_carreiras));
    erro_alocacao_c(topo_c);
    topo_c->prox_c = NULL;

    /* Aloca memoria para o topo da lista de paragens */
    topo_p = (lista_paragens*) malloc(sizeof(lista_paragens));
    erro_alocacao_p(topo_p);
    topo_p->prox_p = NULL;

    while(1){

        /* Le os dados inseridos pelo utilizador e armazena na variavel input */
        fgets(input, sizeof(input), stdin);

        /* Substitui o caractere "\n" por '\0' */
        input[strcspn(input, "\n")] = '\0';

        /* Avalia a primeira letra do input e chama a funcao correspondente a 
        esse comando. */
        if(input[0] == 'q')
            break; /* Interrompe o loop */

        else if(input[0] == 'c')
            comandos_c(input, topo_c);
            
        else if(input[0] == 'p')
            comandos_p(input, topo_p);

        else if(input[0] == 'l')
            comandos_l(input,topo_c, topo_p);

        else if(input[0] == 'i')
            comandos_i(topo_c, topo_p);
    }
    
    free_lista_carreiras(topo_c);
    free_lista_paragens(topo_p);

    return 0;
}

