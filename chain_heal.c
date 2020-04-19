#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define test printf("+++test+++\n")
#define for_each(item, list) \
    for(item = list[0]; item != NULL; item = item->next)

typedef struct node
{
    int number;
    int x, y;
    int cur_PP, max_PP;
    char *name;

    struct node *next;
    struct node *prev;
    struct node *pathNext;
    int adj_size;
    struct node **adjList;

    int visited;
} node;
typedef struct global
{
    int initial_range;
    int jump_range ;
    int num_jumps ;
    int initial_power ;
    double power_reduction;
}global;


double calculateDistance(node* n1,node* n2){
    int n1_x,n1_y,n2_x,n2_y;
    n1_x=n1->x;n1_y=n1->y;
    n2_x=n2->x;n2_y=n2->y;
    return sqrt(pow((n1_x-n2_x),2)+pow((n1_y-n2_y),2));
}
int best_heal=0;
struct node **bestPath;
struct node **tempPath;
//struct node* path=NULL;
int *best_path_heals;
int *temp_path_heals;
void DFS(node* startNode,int hop,int num_jumps,int heal_power,double power_reduction,int total_healing)
{
    double pwr_red=power_reduction;
    int current_healing_power=heal_power;
    int needed_heal=startNode->max_PP-startNode->cur_PP;
    if(needed_heal<=heal_power)
        total_healing+=needed_heal;
    else
        total_healing+=heal_power;
    current_healing_power=rint(heal_power*(1-power_reduction));
    hop++; 
    int nindex=hop-1;
    //printf("node_name:%s, hop:%d, healing_power:%d\n",startNode->name,hop,current_healing_power);
    startNode->visited=1;
    //---------------    
    tempPath[hop-1]=startNode;
    if(needed_heal<=heal_power)
        temp_path_heals[hop-1]=needed_heal;
    else
        temp_path_heals[hop-1]=heal_power;
    
    if (hop<num_jumps)
    {
        for (int i = 0; i < startNode->adj_size; i++)
        {
            if (startNode->adjList[i]->visited!=1)
                DFS(startNode->adjList[i],hop,num_jumps,current_healing_power,pwr_red,total_healing);
        }
    }

    
     if (total_healing>best_heal)
     {
        best_heal=total_healing;
        for (int i = 0; i < num_jumps; i++)
        {
            bestPath[i]=tempPath[i];
            best_path_heals[i]=temp_path_heals[i];

        }            
    }  
    if (hop==num_jumps)
    {   
        //printf("total_healing:%d\n",total_healing);
    }
     
    //printf("geri\n");
    startNode->visited=0;
    
}

int nodeArrayIndexCounter=0;
int initial_range,jump_range,num_jumps,initial_power;
double power_reduction;
int main(int argc, char **argv)
{
    global *glb=malloc(sizeof(global));
    glb->initial_range = atoi(argv[1]);
    glb->jump_range = atoi(argv[2]);
    glb->num_jumps = atoi(argv[3]);
    glb->initial_power = atoi(argv[4]);
    glb->power_reduction = atof(argv[5]);

    int x,y,cur_pp,max_PP;
    char name[64];
    node **nodeArray= (node**)malloc(5 * sizeof(node*));
    node *prev=NULL;
    node *next=NULL;
    while (scanf("%d %d %d %d %s",&x,&y,&cur_pp,&max_PP,&name)==5)
    {
        if (x<-10000 || x>10000 || y<-10000 ||y >10000|| max_PP<1 || max_PP>10000||cur_pp<0||cur_pp>max_PP)
        {
            fprintf(stderr, "Kurallar!\nX ve Y -10000 ile +10000 aralığında olmalidir...\nMaks_PP 1 ile 10000 arasında olmalidir...\nMevcut_PP 0 ile Maks_PP arasında olmalidir");
            exit(EXIT_FAILURE);
        }
        
        node *n=malloc(sizeof(node));
        nodeArray[nodeArrayIndexCounter] = n;
        n->number=nodeArrayIndexCounter;
        n->x=x;
        n->y=y;
        n->cur_PP=cur_pp;
        n->max_PP = max_PP;
        n->name = strdup(name);
        n->adj_size=0;
        n->visited=0;
        n->prev=prev;
        prev=n;
        if(nodeArrayIndexCounter>0)
            n->prev->next=n;
        if (++nodeArrayIndexCounter==5){
            n->next=next;
            break;
        }
    }
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
    double distance;
    for_each(iter1,nodeArray){
        //CREATING ADJACENY LISTS FOR NODES
        int index=0;
        for_each(iter2,nodeArray){
            distance=sqrt(pow((iter1->x-iter2->x),2)+pow((iter1->y-iter2->y),2));
            if (distance<=(double)glb->jump_range)
               iter1->adj_size++;
        }
        iter1->adjList=(node**)malloc(iter1->adj_size*sizeof(node*));
        for_each(iter2,nodeArray){
            distance=sqrt( (double)( pow((iter1->x-iter2->x),2)+pow((iter1->y-iter2->y),2)  ) );
            //printf("kisi1: %s, kisi2 %s uzaklik:%f, jump_range:%d\n",iter1->name, iter2->name, distance,global->jump_range);
            if (distance<=(double)glb->jump_range){
                iter1->adjList[index]=iter2;
                index++;
            }
        }
    }
    //KOMŞU NODELARLA İLİŞKİLENDİRME TESTİ
    // node* n;
    // for_each(n,nodeArray){
    //     printf("Ad:%s\n",n->name);
    //     printf("Komsu Sayisi:%d\n",n->adj_size);
    //     printf("Komsular:\n");
    //     node* n2;
    //     int komsuc=0;
    //     for_each(n2,n->adjList){
    //         printf("Komsu%d => %s\n",komsuc+1,n2->name);
    //         komsuc++;
    //     }
        // for (int j = 0; j < n->adj_size; j++){
        //     printf("Komsu%d => %s\n",j+1,n->adjList[j]->name);
        // }
    //     printf("--------------------------\n");
    // };
    int hop=0;
    node* init=malloc(sizeof(node));
    bestPath=malloc(glb->num_jumps*sizeof(node*));
    tempPath=malloc(glb->num_jumps*sizeof(node*));
    best_path_heals=malloc(num_jumps*sizeof(int));
    temp_path_heals=malloc(num_jumps*sizeof(int));
    for_each(init,nodeArray){
        //printf("n1:%s, n2:%s, uzaklik:%f, init range:%f\n",nodeArray[0]->name,init->name,calculateDistance(nodeArray[0],init),(double)glb->initial_range);
        if (calculateDistance(nodeArray[0],init)<=(double)glb->initial_range)
        {
            DFS(init,hop,glb->num_jumps,glb->initial_power,glb->power_reduction,0);
        }
    }
    for (int i = 0; i < glb->num_jumps; i++)
    {
        printf("%s %d\n",bestPath[i]->name,best_path_heals[i]);
    }
    printf("Total healing: %d",best_heal);
    
    return 0;
}
