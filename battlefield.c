#include "battlefield.h"

Battlefield *new_battlefield(int initialRange, int jumpRange, int numberOfJumps, int initialPower, double powerReduction)
{
    Battlefield *bf = (Battlefield *)malloc(sizeof(Battlefield));
    bf->initialRange = initialRange;
    bf->jumpRange = jumpRange;
    bf->numberOfJumps = numberOfJumps;
    bf->initialPower = initialPower;
    bf->powerReduction = powerReduction;
    bf->currentPlayerCount = 0;
    bf->players = new_chain();
    bf->paths = new_chain_list();
    return bf;
}

void print_players(Battlefield *battlefield)
{
    print_chain(battlefield->players);
}

int add_player(Battlefield *battlefield, Player *player)
{
    add_node_to_chain(battlefield->players, new_chain_node(player));
    battlefield->currentPlayerCount++;
    return battlefield->currentPlayerCount;
}

void calculate_total_healing(ChainList *list, int initialPower, double powerReductionCoefficient)
{
    ChainListNode *outer = list->head;
    while (outer != NULL)
    {
        int initial = initialPower;
        outer->chain->totalHealing = 0;
        ChainNode *iter = outer->chain->head;
        while (iter != NULL)
        {
            int maxHealthCanBeHealed = iter->player->maxHealth - iter->player->currentHealth;
            if (maxHealthCanBeHealed > initial)
            {
                iter->heal = initial;
                outer->chain->totalHealing += initial;
            }
            else
            {
                iter->heal = maxHealthCanBeHealed;
                outer->chain->totalHealing += maxHealthCanBeHealed;
            }
            initial = rint(initial * (1.0 - powerReductionCoefficient));
            iter = iter->next;
        }
        outer = outer->next;
    }
}

void reset(Chain *players){
    ChainNode *iter = players->head;
    while (iter != NULL)
    {
        iter->player->prev = NULL;
        iter->player->visited = 1;
        iter = iter->next;  
    }
}

void find_and_print_best_healing_path(ChainList *paths){
    if(paths->head == NULL) return;
    Chain *best = paths->head->chain;
    ChainListNode *outer = paths->head->next;
    while (outer != NULL)
    {
        if(outer->chain->totalHealing > best->totalHealing)
            best = outer->chain;
        outer = outer->next;
    }
    ChainNode *inner = best->head;
    while(inner != NULL){
        printf("%s %d\n", inner->player->nickname, inner->heal);
        inner = inner->next;
    }
    printf("Total_Healing: %d\n", best->totalHealing);
}

void itialize_neighbors(Battlefield *bf)
{
    ChainNode *outer = bf->players->head;
    while (outer != NULL)
    {
        ChainNode *inner = bf->players->head;
        while (inner != NULL)
        {
            if (strcmp(outer->player->nickname, inner->player->nickname) != 0 && player_has_neighbour(outer->player, inner->player) != 1 && distance(outer->player->position, inner->player->position) <= (double)bf->jumpRange)
            {
                add_node_to_chain(outer->player->neighbors, new_chain_node(inner->player));
                add_node_to_chain(inner->player->neighbors, new_chain_node(outer->player));
            }
            inner = inner->next;
        }
        outer = outer->next;
    }
    return;
}

Chain *find_players_in_initial_range(Battlefield *bf)
{
    Chain *chain = new_chain();
    Player *healer = bf->players->head->player;
    add_node_to_chain(chain, new_chain_node(healer));
    ChainNode *iter = bf->players->head->next;
    while (iter != NULL)
    {
        if (distance(healer->position, iter->player->position) <= (double)bf->initialRange)
        {
            add_node_to_chain(chain, new_chain_node(iter->player));
        }
        iter = iter->next;
    }
    return chain;
}
