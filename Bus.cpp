#include<stdio.h>
#include <limits.h>
#define V 4
#define INF 99999

void printPath(int parent[], int j, int k,int arr[V])
{
    // Base Case : If j is source
    if (parent[j]==-1)
        return;

    printPath(parent, parent[j],k+1,arr);
    arr[k]=j;
 //   printf("%d ", j);
}

void printSolution(float dist[][V]);

void printSolution(float dist[][V][V]);

float printSolution(float dist[], int src, int parent[],float path[][V][V])
{
    printf("Vertex\t  Distance\tPath");
    for (int i = 0; i < V; i++)
    {

        if(i!=src){
                 int arr[V]={-1,-1,-1,-1};
        printf("\n%d -> %d \t\t %f\t\t%d ", src, i, dist[i], src);

       printPath(parent, i,0,arr);

        int k=0;
        for(int j=0;j<V;j++){
       //     printf("%d ", parent[j]);
            if(arr[V-j-1]==-1) k++;
            else
                path[src][i][j-k+1]=arr[V-j-1];
       }

            }
    }
}

int minDistance(float dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}



// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(float graph[V][V], int src,float path[][V][V])
{
    float dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i

    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];

    // Parent array to store shortest path tree
    int parent[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]

            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // print the constructed distance array
    printSolution(dist, src, parent,path);
}


// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall (float graph[V][V],float passenger[V][V],float path[V][V][V])
{
    float dist[V][V];
    int i, j, k;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++){
            dist[i][j] = graph[i][j];
            }

    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {   path[i][j][0]=i;
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                int l=1;
                if (dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];

                    while(path[i][j][l]!=-1) l++;
                    path[i][j][l]=k;
                    }

        }
    }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}

/* A utility function to print solution */
void printSolution(float dist[V][V])
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%s ", "INF");
            else
                printf (" %f ", dist[i][j]);
        }
        printf("\n");
    }
}

void printSolution(float dist[V][V][V])
{
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            for(int k=0;k<V;k++)
                printf (" %f ", dist[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
}

// driver program to test above function
void initialize(float path[][V][V], float weight[][V]){
    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++){
                weight[i][j]=0;
                path[i][j][0]=i;
            for(int k=1;k<V;k++)
                path[i][j][k]=-1;
    }

}
void update(float graph[][V],float weight[][V],float passenger[][V],float path[][V][V]){
    for(int i=0;i<V;i++)
    dijkstra(graph,i, path);
 //   printSolution(passenger);
 //   printSolution(path);
    for (int i=0;i<V;i++)
        for(int j=0;j<V;j++){
            int k=0;
                for(k=0;path[i][j][k+1]!=-1&& k+1<V;k++){
        weight[(int)path[i][j][k]][(int)path[i][j][k+1]]+=passenger[i][j];
                }
 //       weight[k+1][j]+=passenger[i][j];
   //        for(int k=0;path[i][j][k]!=-1;k++)

        }
//printSolution(weight);

}

int main()
{
    float graph[V][V] = { {0, 500,  15, 10},
                        {INF, 0,   1, 30},
                        {INF, INF, 0,   1},
                        {INF, INF, INF, 0}
                      };
    float passenger[V][V]={ {0, 14, 55, 45},
                        {0, 0, 32, 39},
                        {0, 0, 0, 71},
                        {0, 0, 0, 0}
                      };
    float weight[V][V];
    float path[V][V][V];

    for (int i=0;i<V;i++)
        for(int j=0;j<=i;j++){
        //    graph[i][j]=graph[j][i];
        //    passenger[i][j]=passenger[j][i];
        }

        int from[V]={0,0,0,0};

        for(int iter=0;iter<2*V;iter++){
        initialize(path,weight);
        int max_weight=0,to=0;
        update(graph,weight,passenger,path);
        printSolution(weight);

        for(int i=0;i<V;i++){
                if(i==from[iter]) continue;
                printf(" %f ", weight[from[iter]][i]/graph[from[iter]][i]);
            if(max_weight<weight[from[iter]][i]/graph[from[iter]][i]){
            max_weight=weight[from[iter]][i]/graph[from[iter]][i];
            to=i;
            }
        }
        passenger[from[iter]][to]=0;
        printSolution(passenger);
        for (int i=0;i<V;i++)
        for(int j=0;j<V;j++){
                for(int k=0;path[i][j][k+1]!=-1&& k+1<V;k++){
                if(path[i][j][k]==from[iter]&&path[i][j][k+1]==to){
                    passenger[from[iter]][to]=0;
                    passenger[to][j]+=passenger[i][j];
                    passenger[i][j]=0;
                    }
                }
        }

        from[iter+1]=to;
        initialize(path,weight);
        update(graph,weight,passenger,path);
        printf(" %d ", iter);
        printSolution(passenger);
        }
        printf("%d ",0);
        for(int iter=1;iter<V;iter++)
        printf ("--> %d ", from[iter]);

    return 0;
}
