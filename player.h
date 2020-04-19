#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <string.h>
#include "coordinate.h"
#include "math.h"

typedef struct _player Player;
typedef struct _chainNode ChainNode;
typedef struct _chain Chain;

struct _player{
    Coordinate *position;
    int maxHealth,
        currentHealth;
    char *nickname;
    Chain *neighbors;
    int visited;
    Player *prev;
};

struct _chainNode{
    int heal;
    Player *player;
    ChainNode *prev;
    ChainNode *next;
};

struct _chain{
    int numberOfPlayers,
        totalHealing;
    ChainNode *head;
};

Player* new_player(char* nickname, int maxHealth, int currentHealth, int xPosition, int yPosition);
ChainNode* new_chain_node(Player *player);
Chain* new_chain();
void add_node_to_chain(Chain *chain, ChainNode *cn);
void prepend_node_to_chain(Chain *chain, ChainNode *cn);
void print_chain(Chain *chain);
void free_chain(Chain *chain);
void free_only_chain(Chain *chain);
int player_has_neighbour(Player *player, Player *neighbour);
Player *chain_at(Chain *, int);

#endif