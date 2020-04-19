#ifndef CHAINLIST_H
#define CHAINLIST_H

#include "player.h"

typedef struct _chainlistnode ChainListNode;
struct _chainlistnode{
    Chain *chain;
    ChainListNode *prev;
    ChainListNode *next;
};

typedef struct _chainlist{
    int numberOfChains;
    ChainListNode *head;
} ChainList;

ChainListNode* new_chain_list_node(Chain *chain);
ChainList* new_chain_list();
void add_node_to_chain_list(ChainList *list, ChainListNode *node);
void print_chain_list(ChainList *list);
void free_chain_list(ChainList *list);

#endif