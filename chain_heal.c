#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct node
{
    int x, y;
    int cur_PP, max_PP;
    char *name;

    struct node *next;
    struct node *prev;
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
    while (scanf("%d %d %d %d %s",&x,&y,&cur_pp,&max_PP,&name)==5)
    {
        node *n=malloc(sizeof(node));
        nodeArray[nodeArrayIndexCounter] = n;
        n->x=x;
        n->y=y;
        n->cur_PP=cur_pp;
        n->max_PP = max_PP;
        n->name = strdup(name);
        n->prev=prev;
        prev=n;
        if(nodeArrayIndexCounter>0)
            n->prev->next=n;
        if (++nodeArrayIndexCounter==5)
            break;
    };
    for (int i = 0; i < 5; i++)
    {
        node * n = nodeArray[i];
        printf("x=%d y=%d cur_PP=%d max_PP=%d name='%s'", 
        n->x, n->y, n->cur_PP, n->max_PP, n->name);
        if (n->prev) 
            printf("-prev='%s'-", n->prev->name);
        if(n->next)
            printf("-next='%s'-", n->next->name);
        printf("\n");
    }
    return 0;
}