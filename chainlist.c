#include "chainlist.h"

ChainListNode* new_chain_list_node(Chain *chain){
    ChainListNode *node = (ChainListNode*) malloc(sizeof(ChainListNode));
    node->prev = NULL;
    node->next = NULL;
    node->chain = chain;
    return node;
}

ChainList* new_chain_list(){
    ChainList *list = (ChainList*) malloc(sizeof(ChainList));
    list->head = NULL;
    list->numberOfChains = 0;
    return list;
}

void add_node_to_chain_list(ChainList *list, ChainListNode *node){
    if(list->head == NULL){
        list->head = node;
        list->numberOfChains++; 
        return;
    }
    ChainListNode *iter = list->head;
    while(iter->next != NULL){
        iter = iter->next;
    }
    iter->next = node;
    node->prev = iter;
    list->numberOfChains++;
    return;
}

void print_chain_list(ChainList *list){
    ChainListNode *iter = list->head;
    while(iter != NULL){
        ChainNode *inner = iter->chain->head;
        while(inner != NULL){
            printf("-> %s ", inner->player->nickname);
            inner = inner->next;
        }
        printf("- total healing available: %d\n", iter->chain->totalHealing);
        iter = iter->next;
    }
}

void free_chain_list(ChainList *list){
    if(list->head == NULL) {
        free(list);
        return;
    }
    ChainListNode * iter = list->head;
    ChainListNode * next;
    while(iter != NULL){
        free_chain(iter->chain);
        next = iter->next;
        free(iter);
        iter = next;
    }
    free(list);
}
