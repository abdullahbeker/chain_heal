#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "battlefield.h"
#include "coordinate.h"
#include "player.h"

#define LINE_LENGTH 512
#define NN_LENGTH 256

int dfs(ChainNode *start, int nthHop, Battlefield *bf)
{
    nthHop++;
    start->player->visited = 0;
    ChainNode *iter = start->player->neighbors->head;
    while (iter != NULL && nthHop < bf->numberOfJumps)
    {
        if (iter->player->visited != 0)
        {
            iter->player->prev = start->player;
            dfs(iter, nthHop, bf);
        }
        if (iter->next == NULL)
            break;
        iter = iter->next;
    }
    int hasANeighbourToGo = 1;
    ChainNode *inner = start->player->neighbors->head;
    while(inner != NULL){
        if(inner->player->visited == 1) hasANeighbourToGo = 0;
        inner = inner->next;
    }
    if(nthHop == bf->numberOfJumps || (nthHop < bf->numberOfJumps && hasANeighbourToGo == 1)){
        Chain *path = new_chain();
        Player *outer = start->player;
        while (outer != NULL)
        {
            prepend_node_to_chain(path, new_chain_node(outer));
            outer = outer->prev;
        }
        add_node_to_chain_list(bf->paths, new_chain_list_node(path));
    }
    nthHop--;
    start->player->visited = 1;
    return 0;
}

int main(int argc, char **argv)
{
    int xPosition,
        yPosition,
        currentHealth,
        maxHealth;
    char nickname[NN_LENGTH];
    Battlefield *bf = new_battlefield(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atof(argv[5]));
    while (scanf("%d %d %d %d %s", &xPosition, &yPosition, &currentHealth, &maxHealth, nickname) == 5)
    {
        add_player(bf, new_player(strdup(nickname), maxHealth, currentHealth, xPosition, yPosition));
    }
    initialize_neighbors(bf);
    Chain *playersInInitialRange = find_players_in_initial_range(bf);
    ChainNode *iter = playersInInitialRange->head;
    while (iter != NULL)
    {
        dfs(iter, 0, bf);
        reset(bf->players);
        iter = iter->next;
    }
    calculate_total_healing(bf->paths, bf->initialPower, bf->powerReduction);
    find_and_print_best_healing_path(bf->paths);

    free_chain_list(bf->paths);
    free_only_chain(bf->players);
    free(bf);
    return EXIT_SUCCESS;
}
