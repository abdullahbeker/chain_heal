#include "player.h"

Player *new_player(char *nickname, int maxHealth, int currentHealth, int xPosition, int yPosition)
{
    Player *p = (Player *)malloc(sizeof(Player));
    p->neighbors = new_chain();
    p->prev = NULL;
    p->visited = 1;
    p->nickname = nickname;
    p->currentHealth = currentHealth;
    p->maxHealth = maxHealth;
    p->position = new_coordinate(xPosition, yPosition);
    return p;
}

ChainNode *new_chain_node(Player *player)
{
    ChainNode *cn = (ChainNode *)malloc(sizeof(ChainNode));
    cn->player = player;
    cn->next = NULL;
    cn->prev = NULL;
    return cn;
}

Chain *new_chain()
{
    Chain *c = (Chain *)malloc(sizeof(Chain));
    c->numberOfPlayers = 0;
    c->head = NULL;
    c->totalHealing = 0;
    return c;
}

void prepend_node_to_chain(Chain *chain, ChainNode *cn)
{
    if (chain->head == NULL)
    {
        chain->head = cn;
        chain->numberOfPlayers++;
        return;
    }
    cn->next = chain->head;
    chain->head->prev = cn;
    chain->head = cn;
    return;
}

void add_node_to_chain(Chain *chain, ChainNode *cn)
{
    if (chain->head == NULL)
    {
        chain->head = cn;
        chain->numberOfPlayers++;
        return;
    }
    ChainNode *iter = chain->head;
    while (iter->next != NULL)
    {
        iter = iter->next;
    }
    iter->next = cn;
    cn->prev = iter;
    chain->numberOfPlayers++;
    return;
}

void print_chain(Chain *chain)
{
    if (chain->head == NULL)
        return;
    ChainNode *iter = chain->head;
    printf("---------------------------------\n");
    do
    {
        printf("player: %s\ncurrent and max health: %d - %d\nneighbours:\n", iter->player->nickname, iter->player->currentHealth, iter->player->maxHealth);
        ChainNode *inner = iter->player->neighbors->head;
        while (inner != NULL)
        {
            printf("%s\n", inner->player->nickname);
            inner = inner->next;
        }
        iter = iter->next;
        printf("---------------------------------\n");
    } while (iter != NULL);
}

void free_chain(Chain *chain)
{
    if (chain->head == NULL)
    {
        free(chain);
        return;
    }
    ChainNode *iter;
    while (chain->head != NULL)
    {
        iter = chain->head->next;
        free(chain->head);
        chain->head = iter;
    }
    free(chain);
}

Player *chain_nth(Chain *chain, int nth)
{
    ChainNode *iter = chain->head;
    for (nth; nth > 0; nth--)
    {
        iter = iter->next;
    }
    return iter->player;
}

int player_has_neighbour(Player *player, Player *neighbour)
{
    ChainNode *iter = player->neighbors->head;
    while (iter != NULL)
    {
        if (strcmp(iter->player->nickname, neighbour->nickname) == 0)
            return 1;
        iter = iter->next;
    }
    return 0;
}

Player *chain_at(Chain *chain, int at)
{
    if (chain->head == NULL)
        return NULL;
    ChainNode *iter = chain->head;
    for (at; at > 0; at--)
    {
        iter = iter->next;
    }
    return iter->player;
}
