#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "chainlist.h"

typedef struct _battlefield{
    int initialRange,
        jumpRange,
        numberOfJumps,
        initialPower,
        currentPlayerCount;
    double powerReduction;
    Chain *players;
    ChainList *paths;
} Battlefield;

Battlefield* new_battlefield(int initialRange, int jumpRange, int numberOfJumps, int initialPower, double powerReduction);
int add_player(Battlefield *battlefield, Player *player);
void print_players(Battlefield *battlefield);
void calculate_total_healing(ChainList *list, int initialPower, double powerReductionCoefficient);
void reset(Chain *players);
void find_and_print_best_healing_path(ChainList *paths);
void itialize_neighbors(Battlefield *bf);
Chain *find_players_in_initial_range(Battlefield *bf);

#endif