#include<stdio.h>
#include<string.h>
#define INFINITY 99999
#define MAX 10

void Dijkstra(char [][20],int [][MAX],int,int);
int findIndex(char [][20],char [], int);
void create(char [][20],int [][MAX],int);
void display(int [][MAX], int);

//DIJKSTRA'S SHORTEST PATH ALGORITHM

void Dijkstra(char cities[][20],int G[][MAX],int n,int startnode)
{
 
    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode;
    int i,j;
   
    /*
    cost[i][j] is the distance from city i to city j
    cost is INFINITY is there is no forward path from city i to city j
    */
   
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(G[i][j]==0)
            cost[i][j]=INFINITY;
            else
            cost[i][j]=G[i][j];
        }
    }
   
    //pred[] stores the previous of each node
    //Initialize pred[],distance[] and visited[]
   
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
   
    //count is the number of nodes visited so far
   
    /*
    Step 1: Mark starting node as visited
            Set distance path value of all other nodes to INFINITY
    */
   
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    while(count<n-1)
    {
        mindistance=INFINITY;
        for(i=0;i<n;i++)
        {
            //Choosing unvisited vertex with minimum distance as next node
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        }
       
        //Marking the next node as visited
        visited[nextnode]=1;
       
        //To check if a better path exists through nextnode
       
        for(i=0;i<n;i++)
        if(!visited[i])
        {
            //Calculate distance of remaining unvisited nodes from source
            if(mindistance+cost[nextnode][i]<distance[i])
            {
                distance[i]=mindistance+cost[nextnode][i];
                pred[i]=nextnode;
            }
        }
        count++;
    }
     
    //To print the route and distance of each node
    for(i=0;i<n;i++)
    if(i!=startnode)
    {
        printf("\n\nDistance from %s to %s = %d km",cities[startnode],cities[i],distance[i]);
        if(distance[i]==INFINITY)
        printf("\nRoute: Viable route does not exist.\n");
        else
        printf("\nRoute: %s",cities[i]);
        j=i;
        do
        {
            j=pred[j];
            printf(" <- %s",cities[j]);
        }while(j!=startnode);
    }
}


//To map each city to a node number in the graph
int findIndex(char arr[][20],char st[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(strcmp(arr[i],st)==0)
        return i;
    }
    return -1;
}

//To create a directed weighted graph using user input
void create(char cities[][20],int G[][MAX],int n)
{
    int i,j;
    char c;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==j)
            G[i][j]=0;
            else
            {
                printf("Is there a direct train from %s to %s? y/n ",cities[i],cities[j]);
                scanf(" %c",&c);
                if(c=='y'||c=='Y')
                {
                    printf("Enter the distance covered from %s to %s: ",cities[i],cities[j]);
                    scanf("%d",&G[i][j]);
                }
                else
                G[i][j]=0;
                printf("\n");
            }
        }
    }
}

//To display adjacency matrix of graph
void display(int G[][MAX], int n)
{
    int i,j;
    printf("Adjacency Matrix:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d\t",G[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int G[MAX][MAX],i,j,n,src;
    char cities[MAX][20];
    char start[20];
    printf("Enter the no. of cities: ");
    scanf("%d",&n);
    printf("Enter the names of cities: \n");
    for(i=0;i<n;i++)
    scanf("%s",cities[i]);
    create(cities,G,n);
    display(G,n);
    printf("\nEnter the starting city: ");
    scanf("%s",start);
    src=findIndex(cities,start,n);

    //Loop until user enters a valid city
    while(1)
    {
        if(src==-1)
        {
            printf("City not present in graph.");
            printf("\nEnter the starting city: ");
            scanf("%s",start);
            src=findIndex(cities,start,n);
        }
        else
        break;
    }
    Dijkstra(cities,G,n,src);
    return 0;
}

