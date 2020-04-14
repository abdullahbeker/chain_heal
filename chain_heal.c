#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define test printf("+++test+++\n")
#define for_each(item, list) \
    for(item = list[0]; item != NULL; item = item->next)

typedef struct node
{
    int x, y;
    int cur_PP, max_PP;
    char *name;

    struct node *next;
    struct node *prev;

    int adj_size;
    struct node **adj;
} node;
int nodeArrayIndexCounter=0;
int initial_range,jump_range,num_jumps,initial_power;
double power_reduction;
int main(int argc, char **argv)
{
    initial_range = atoi(argv[1]);
    jump_range = atoi(argv[2]);
    num_jumps = atoi(argv[3]);
    initial_power = atoi(argv[4]);
    power_reduction = atof(argv[5]);
    int x,y,cur_pp,max_PP;
    char name[64];
    node **nodeArray= (node**)malloc(5 * sizeof(node*));
    node *prev=NULL;
    node *next=NULL;
    while (scanf("%d %d %d %d %s",&x,&y,&cur_pp,&max_PP,&name)==5)
    {
        node *n=malloc(sizeof(node));
        nodeArray[nodeArrayIndexCounter] = n;
        n->x=x;
        n->y=y;
        n->cur_PP=cur_pp;
        n->max_PP = max_PP;
        n->name = strdup(name);
        n->adj_size=0;
        n->prev=prev;
        prev=n;
        if(nodeArrayIndexCounter>0)
            n->prev->next=n;
        if (++nodeArrayIndexCounter==5){
            n->next=next;
            break;
        }     
    };
    //DOSYA OKUMA VE ARG ATAMA İŞLEMLERİ TESTİ
    // for (int i = 0; i < 5; i++)
    // {
    //     node * n = nodeArray[i];
    //     printf("x=%d y=%d cur_PP=%d max_PP=%d name='%s'", 
    //     n->x, n->y, n->cur_PP, n->max_PP, n->name);
    //     if (n->prev) 
    //         printf("-prev='%s'-", n->prev->name);
    //     if(n->next)
    //         printf("-next='%s'-", n->next->name);
    //     printf("\n");
    // }
    node *iter1,*iter2;
    int distance;
    for_each(iter1,nodeArray){
        //INITING
        int index=0;
        for_each(iter2,nodeArray){
            distance=sqrt(pow((iter1->x-iter2->x),2)+pow((iter1->y-iter2->y),2)); 
            if (distance<(double)jump_range)
                iter1->adj_size++; 
        };
        iter1->adj=(node**)malloc(iter1->adj_size*sizeof(node*));
        
        for_each(iter2,nodeArray){
            distance=sqrt(pow((iter1->x-iter2->x),2)+pow((iter1->y-iter2->y),2)); 
            if (distance<(double)jump_range){
                iter1->adj[index]=iter2;
                index++;
            }
        };
    };
    //KOMŞU NODELARLA İLİŞKİLENDİRME TESTİ
    // for (int i = 0; i < 5; i++){
    //     node* n;
    //     test;
    //     for_each(n,nodeArray){
    //         printf("Ad:%s\n",n->name);
    //         printf("Komsu Sayisi:%d\n",n->adj_size);
    //         printf("Komsular:\n");
    //         for (int j = 0; j < n->adj_size; j++){
    //             printf("Komsu%d => %s\n",j+1,n->adj[j]->name);
    //         }
    //         printf("--------------------------\n");
    //     };
    // };

    return 0;
}