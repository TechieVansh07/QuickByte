
#include <stdio.h>
#include <limits.h>

#define V 6
#define INF 999999

/*
 Node IDs:
 0 = Food Corner (Restaurant)
 1 = Clock Tower
 2 = ISBT
 3 = Pacific Mall
 4 = Graphic Era
 5 = Prem Nagar
*/

static const char *names[V] = {
    "Food Corner",
    "Clock Tower",
    "ISBT",
    "Pacific Mall",
    "Graphic Era",
    "Prem Nagar"
};

static const double locations[V][2] = {
    {30.3256, 78.0437},
    {30.3255, 78.0413},
    {30.2850, 78.0120},
    {30.3660, 78.0800},
    {30.2690, 77.9950},
    {30.3200, 77.9700}
};

/* Demo road-network distances in kilometres */
static const int graph[V][V] = {
    {0, 2, 6, 7, 8, 9},
    {2, 0, 5, 6, 7, 8},
    {6, 5, 0, 8, 5, 7},
    {7, 6, 8, 0, 9, 10},
    {8, 7, 5, 9, 0, 3},
    {9, 8, 7, 10, 3, 0}
};

static int minDistance(int dist[], int visited[])
{
    int min = INF;
    int index = -1;

    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }

    return index;
}

/* Called from the C++ application */
void calculateShortestPath(int destination)
{
    if (destination < 1 || destination >= V)
    {
        printf("ROUTE_ERROR Invalid destination\n");
        return;
    }

    int dist[V];
    int visited[V] = {0};
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[0] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] > 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    int path[V];
    int count = 0;
    int current = destination;

    while (current != -1 && count < V)
    {
        path[count++] = current;
        current = parent[current];
    }

    printf("ROUTE_START\n");
    printf("DISTANCE %d\n", dist[destination]);

    for (int i = count - 1; i >= 0; i--)
    {
        int node = path[i];

        printf("NODE %d|%s|%.6f|%.6f\n",
               node,
               names[node],
               locations[node][0],
               locations[node][1]);
    }

    printf("ROUTE_END\n");
}





void calculateShortestPathTrace(int destination)
{
    if (destination < 1 || destination >= V)
    {
        printf("ROUTE_ERROR Invalid destination\n");
        return;
    }

    int dist[V];
    int visited[V] = {0};
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[0] = 0;

    printf("\n=== DIJKSTRA ALGORITHM TRACE ===\n");
    printf("Source: Food Corner (Node 0)\n");
    printf("Destination: %s (Node %d)\n\n",
           names[destination], destination);

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);

        if (u == -1)
            break;

        visited[u] = 1;

        printf("Step %d: Select %s (Node %d)\n",
               count + 1, names[u], u);

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] &&
                graph[u][v] > 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                int oldDistance = dist[v];

                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;

                printf("  UPDATE: %s | %d -> %d km"
                       " | Parent: %s\n",
                       names[v],
                       oldDistance == INF ? -1 : oldDistance,
                       dist[v],
                       names[u]);
            }
        }

        printf("  Current distances: ");

        for (int i = 0; i < V; i++)
        {
            if (dist[i] == INF)
                printf("%s=INF ", names[i]);
            else
                printf("%s=%d ", names[i], dist[i]);
        }

        printf("\n\n");
    }

    int path[V];
    int pathCount = 0;
    int current = destination;

    while (current != -1 && pathCount < V)
    {
        path[pathCount++] = current;
        current = parent[current];
    }

    printf("=== FINAL RESULT ===\n");
    printf("Minimum graph distance: %d km\n",
           dist[destination]);

    printf("Shortest path: ");

    for (int i = pathCount - 1; i >= 0; i--)
    {
        printf("%s", names[path[i]]);

        if (i > 0)
            printf(" -> ");
    }

    printf("\n===============================\n");
}

